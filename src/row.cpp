#include "common.h"

int main()
{
    Startup();
    gTimer.Start();

        for( size_t i = 0; i < LEN; i++ )
            gnSum += gpData[ i ];

    gTimer.Stop();
    Shutdown();

    return 0;
}
