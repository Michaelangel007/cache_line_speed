// Reference(s):
// http://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c/36095407#36095407

#ifdef WIN32
    // Note: This also exists in winsock2.h
//    typedef struct timeval {
//        long tv_sec;
//        long tv_usec;
//    } timeval;

    // Win32/Win64 doesn't have gettimeofday()
    int gettimeofday(struct timeval * tp, struct timezone * tzp)
    {
        (void) tzp;

        // FILETIME Jan 1 1970 00:00:00
        // Note: Some broken Window implementations have only 8 trailing zero's; the correct epoch has 9 trailing zero's
        static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL); 

        SYSTEMTIME  system_time;
        FILETIME    file_time;
        uint64_t    time;

        GetSystemTime( &system_time );
        SystemTimeToFileTime( &system_time, &file_time ); // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
        time =  ((uint64_t)file_time.dwLowDateTime )      ;
        time += ((uint64_t)file_time.dwHighDateTime) << 32;

        tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
        tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
        return 0;
    }
#else
    #include <sys/time.h>
// #ifdef __APPLE__ // OSX
// #else            // Linux
//	getTimeOfDay();
#endif

    struct DataRate
   {
        uint64_t samples;
        uint64_t per_sec;
        char     prefix ;
    };

    class Timer
    {
        timeval start, end; // Windows: winsock2.h  Unix: sys/time.h
    public:
        double   elapsed; // total seconds
        long     micro;
        uint8_t  secs;
        uint8_t  mins;
        uint8_t  hour;
        uint32_t days;

        DataRate throughput;
        char     day[ 16 ]; // output
        char     hms[ 12 ]; // output

        void Start()
        {
            elapsed = 0.0;
            gettimeofday( &start, NULL );
        }

        void Stop()
        {
            gettimeofday( &end, NULL );
            elapsed = (end.tv_sec - start.tv_sec);
            micro   = (end.tv_usec - start.tv_usec);

            elapsed += (micro / 1000000.0);

            size_t s = (size_t)elapsed;
            secs = s % 60; s /= 60;
            mins = s % 60; s /= 60;
            hour = s % 24; s /= 24;
            days = (uint32_t)s;

            day[0] = 0;
            if( days > 0 )
                snprintf( day, 15, "%d day%s, ", days, (days == 1) ? "" : "s" );

            sprintf( hms, "%02d:%02d:%02d", hour, mins, secs );
        }

        // size is number of bytes in a file, or number of iterations that you want to benchmark
        void Throughput( uint64_t size )
        {
            const int MAX_PREFIX = 4;
            DataRate datarate[ MAX_PREFIX ] =
            {
                  {0,0,' '} //             1
                , {0,0,'K'} //         1,000
                , {0,0,'M'} //     1,000,000
                , {0,0,'G'} // 1,000,000,000
            };

            if( !elapsed )
                return;

            int best = 0;
            for( int units = 0; units < MAX_PREFIX; units++ )
            {
                    datarate[ units ].samples = size >> (10*units);
                    datarate[ units ].per_sec = (uint64_t) (datarate[units].samples / elapsed);
                if (datarate[ units ].per_sec > 0)
                    best = units;
            }
            throughput = datarate[ best ];
        }
    };

