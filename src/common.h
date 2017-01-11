#include <stdio.h>  // sprintf
//#include <string.h> // 
#include <stdlib.h> // atoi
#include <stdint.h> // uint8_t, uint32_t

#include "timer.h"     // Timer
#include "util_itoa.h" // itoa_comma

const size_t K    = 1024;
const size_t LEN  = K*K*K; // 1 GB = 1K * 1MB = 1K * 1K * 1K
const size_t ELEM = sizeof( unsigned int );
const size_t SIZE = ELEM * LEN;

Timer         gTimer;
unsigned int *gpData = 0;
uint64_t      gnSum = 0;

void Startup()
{
    gpData = new unsigned int [ LEN ];

    // Sum( i, 0, LEN )
    for( size_t i = 0; i < LEN; i++ )
        gpData[i] = i;

    gnSum = 0;
}

void Shutdown()
{
    gTimer.Throughput( LEN );
 
   
    printf( "Len: %s\n", itoa_comma( (long long unsigned int)   LEN ) );
    printf( "int: %s\n", itoa_comma( (long long unsigned int)  ELEM ) );
    printf( "Mem: %s\n", itoa_comma( (long long unsigned int)  SIZE ) );
    printf( "Sum= %s  ", itoa_comma( (long long unsigned int) gnSum ) );

    printf( "%s\n", 
        (gnSum != 576460751766552576ull)
        ? "FAIL. ERROR: Checksum failure!"
        : "pass"
    );

    printf( "%d %c cells/s %.f seconds = %s%s\n"
        , (int)gTimer.throughput.per_sec, gTimer.throughput.prefix
        , gTimer.elapsed
        , gTimer.day
        , gTimer.hms
    );

    printf( "\n" );

    delete [] gpData;
}

