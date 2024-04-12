

#include    <stdio.h>

#include    "Vector.h"

vector_t vec;

int main(void)
{
    vec = create_vector();

    printf("Capacity = %zd\n", vector_capacity(vec));
    printf("Size = %zd\n", vector_size(vec));

    for( int i = 0; i < 10; ++i )
    {
        vector_push_back(vec, (data_t) (size_t)((i+1) * 10) );
    }
    
    printf("Capacity = %zd\n", vector_capacity(vec));
    printf("Size = %zd\n", vector_size(vec));
    for( int i = 0; i < vector_size(vec); ++i)
    {
        printf("-%zd", (size_t)vector_at(vec, i) );
    }
    printf("\n");
    
    for( int i = 0; i < 5; ++i)
    {
        printf("Poped = %zd\n", (size_t)vector_pop_back(vec) );
    }
    printf("\n");
    
    for( int i = 0; i < vector_size(vec); ++i)
    {
        printf(" %zd\n", (size_t)vector_at(vec, i) );
    }
    printf("\n");

    return(0);
}

