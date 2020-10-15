#include<stdlib.h>

bool TestForPrime( int val ){
    int limit, factor = 2;
    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;
    return( factor > limit );
}