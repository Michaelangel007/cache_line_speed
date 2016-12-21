#include "common.h"

int main( const int nArg, const char *aArg[] )
{
    size_t STRIDE = 32;

    if( nArg > 1 )
        STRIDE = atoi( aArg[ 1 ] );
    printf( "Stride: [%lu] @ %lu bytes\n", STRIDE, ELEM*STRIDE );

    Startup();
    gTimer.Start();

        for( size_t col = 0; col < STRIDE; col++ )
            for( size_t i = 0; i < LEN; i += STRIDE )
                gnSum += gpData[ i + col ];

    gTimer.Stop();
    Shutdown();

    return 0;
}

