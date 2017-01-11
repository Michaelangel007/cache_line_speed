const char* itoa_comma( uint64_t x )
{
    const  int     NUM_BUFFERS = 4;
    static uint8_t iString     = 0;
    static char    aString[ NUM_BUFFERS ][32];
   
    char *p = &aString[ iString ][31];

    *p-- = 0;
    while( x >= 1000 )
    {
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = '0' + (x % 10); x /= 10;
        *p-- = ',';
    }

    if (x >= 100)   { *p-- = '0' + (x % 10); x /= 10; }
    if (x >=  10)   { *p-- = '0' + (x % 10); x /= 10; }
  /*if (x >=   0)*/ { *p-- = '0' + (x % 10); x /= 10; }

    iString++;
    iString &= (NUM_BUFFERS-1);

    return ++p;
}

