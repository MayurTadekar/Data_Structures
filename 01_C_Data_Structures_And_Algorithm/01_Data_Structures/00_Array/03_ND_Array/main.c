

#include    <stdio.h>
#include    <stdlib.h>

#include    "array_nd.h"

array_t arr;

#define     MAX     3

void showdata(data_t data)
{
    printf("-%zd", (size_t) data);
}

void printarray(array_t arr)
{
    printf("Array:\n");
    array_traverse(arr, showdata);
    printf("\n");
}

int main(void)
{
    arr = create_array( 15, 
                        MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX, 
                        MAX, MAX, MAX, MAX, MAX);

    long value = 1;
    for( int i = 0; i < MAX; ++i )
        for( int j = 0; j < MAX; ++j )
            for( int k = 0; k < MAX; ++k )
                for( int l = 0; l < MAX; ++l )
                    for( int m = 0; m < MAX; ++m )
                        for( int n = 0; n < MAX; ++n )
                            for( int o = 0; o < MAX; ++o )
                                for( int p = 0; p < MAX; ++p )
                                    for( int q = 0; q < MAX; ++q )
                                        for( int r = 0; r < MAX; ++r )
                                            for( int s = 0; s < MAX; ++s )
                                                for( int t = 0; t < MAX; ++t )
                                                    for( int u = 0; u < MAX; ++u )
                                                        for( int v = 0; v < MAX; ++v )
                                                            for( int w = 0; w < MAX; ++w )
                                                                assign_value(arr, (data_t)(size_t)(value++), 
                                                                            i, j, k, l, m, n, o, p, q, r, 
                                                                            s, t, u, v, w);    
    

    for( int i = 0; i < MAX; ++i )
        for( int j = 0; j < MAX; ++j )
            printf("%d\n", get_value(   arr, 
                                        i, j, MAX-1, MAX-1, MAX-1, MAX-1, MAX-1, MAX-1, MAX-1, MAX-1, 
                                        MAX-1, MAX-1, MAX-1, MAX-1, MAX-1)
                                    );

    return(0);
}
