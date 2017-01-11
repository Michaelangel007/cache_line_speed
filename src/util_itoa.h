/*
    Version 4 - document hard-coded max string length 32
    Version 3 - cleanup '>= 10' to '> 9'
    Verison 2 - add 4 buffers
    Version 1 - initial implementation
*/
const char*
itoa_comma( uint64_t x )
{
    const  int     MAX_CHARS   = 31; // 2^32 - 1 =              4,294,967,295 = 13 chars
    const  int     NUM_BUFFERS =  4; // 2^64 - 1 = 18,446,744,073,709,551,615 = 26 chars

    static char    aString[ NUM_BUFFERS ][ MAX_CHARS+1 ];
    static uint8_t iString     = 0;
   
    char *p = &aString[ iString ][ MAX_CHARS ];

    *p-- = 0;
    while( x > 999 )
    {
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = ',';
    }

    if (x > 99)   { *p-- = '0' + (x % 10); x /= 10; }
    if (x >  9)   { *p-- = '0' + (x % 10); x /= 10; }
  /*if (x > -1)*/ { *p-- = '0' + (x % 10); x /= 10; }

    iString++;
    iString &= (NUM_BUFFERS-1);

    return ++p;
}

