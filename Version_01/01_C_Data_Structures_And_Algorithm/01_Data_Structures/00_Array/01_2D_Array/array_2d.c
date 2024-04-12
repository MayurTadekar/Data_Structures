

#include    <stdio.h>
#include    <stdlib.h>

#include    "array_2d.h"


static  void*   Xcalloc(size_t nr_elements, size_t element_size)
{
    void* p = calloc( nr_elements, element_size );
    if( NULL == p)
    {
        fprintf(stderr, "ERROR: Out of Memory\n");
        exit(1);
    }
    return(p);
}

array_t     create_array(size_t dimen1, size_t dimen2)
{
    array_t arr = (array_t) Xcalloc( 1, SIZE_DUMMY);
    arr->arr = (data_t*) Xcalloc( dimen1 * dimen2, SIZE_DATA);
    arr->dimen_1 = dimen1;
    arr->dimen_2 = dimen2;
    return(arr);
}

void        assign_value_at(array_t arr, long index1, long index2, data_t ndata)
{
    if( NULL  == arr            ||
        index1 >= arr->dimen_1    ||
        index2 >= arr->dimen_2)
    {
        return;
    }
    
    *(arr->arr + (index1 * arr->dimen_2) + index2 ) = ndata;
}

data_t      get_value_at(array_t arr, long index1, long index2)
{
    if( NULL  == arr            || 
        index1 >= arr->dimen_1  ||
        index2 >= arr->dimen_2)
    {
        return(NULL);
    }
    
    return( *(arr->arr + (index1 * arr->dimen_2) + index2 ) );
}

void        array_traversal(array_t parr, SHOWDATA_PROC pshowdata)
{
    if( NULL  == parr )
        return; 

    for( int ole = 0; ole < parr->dimen_1; ++ole )
    {
        for( int ile = 0; ile < parr->dimen_2; ++ile )
        {
            pshowdata( get_value_at(parr, ole, ile) );
        }
        printf("\n");
    }  
}

void        destroy_array(p_array_t parr, DESTROYDATA_PROC pdestroydata)
{
    
    if( NULL  == parr   ||
        NULL  == (*parr)->arr )
        return;
        
    data_t* arr = (*parr)->arr;
    for( int ole = 0; ole < (*parr)->dimen_1; ++ole )
    {
        for( int ile = 0; ile < (*parr)->dimen_2; ++ile )
        {
            pdestroydata( get_value_at((*parr), ole, ile) );
        }
    }
    free(arr);
    free(*parr);
    *parr = NULL;
}
