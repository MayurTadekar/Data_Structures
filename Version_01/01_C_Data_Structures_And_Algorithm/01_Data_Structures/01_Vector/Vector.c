

#include    <stdio.h>
#include    <stdlib.h>

#include    "Vector.h"

void*   Xrealloc(void* p, size_t nr_elements, size_t element_size)
{  
    void* np = realloc(p, nr_elements * element_size);
    if( NULL == np && nr_elements != 0)
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(np);
}

vector_t    create_vector()
{
    vector_t v = (vector_t) Xrealloc(NULL, 1, SIZE_DUMMY);
    v->capacity = 1;
    v->size = 0;
    v->data = (data_t*) Xrealloc(NULL, v->capacity, SIZE_DATA);
    return(v);
}

void        vector_push_back(vector_t vec, data_t data)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return;
    }

    if( vec->size == vec->capacity )
    {
        vec->capacity *= 2;
        vec->data = (data_t*) Xrealloc(vec->data, vec->capacity, SIZE_DATA);
    }

    vec->data[ vec->size ] = data;
    
    vec->size++;
}

data_t      vector_pop_back(vector_t vec)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(NULL);
    }

    if( vec->size <= (vec->capacity/2) )
    {
        vec->capacity /= 2;
        vec->data = (data_t*) Xrealloc(vec->data, vec->capacity, SIZE_DATA);
    }

    data_t retdata = vec->data[ --vec->size ];
}

data_t      vector_at(vector_t vec, size_t index)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(NULL);
    }

    if( vec->size <= index )
    {
        printf("Error Index out Of Bound\n");
        return(NULL);
    }

    return( vec->data[index] );
}

size_t      vector_size(vector_t vec)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(0);
    }

    return(vec->size);
}

data_t      vector_front(vector_t vec)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(NULL);
    }

    return(vec->data[0]);
}

data_t      vector_back(vector_t vec)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(NULL);
    }
    return(vec->data[ vec->size-1]);
}

size_t      vector_capacity(vector_t vec)
{
    if( NULL == vec )
    {
        printf("Error No Vector\n");
        return(0);
    }
    return(vec->capacity);
}

int         vector_empty(vector_t vec)
{
    return( (vec->size ? 0 : 1) );
}
