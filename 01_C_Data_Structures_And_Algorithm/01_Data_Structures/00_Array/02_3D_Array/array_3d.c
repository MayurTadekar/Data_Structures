

#include    <stdio.h>
#include    <stdlib.h>

#include    "array_3d.h"


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

array_t     create_array(size_t dimen1, size_t dimen2, size_t dimen3)
{
    array_t arr = (array_t) Xcalloc( 1, SIZE_DUMMY);
    arr->arr = (data_t*) Xcalloc( dimen1 * dimen2 * dimen3, SIZE_DATA);
    arr->dimen_1 = dimen1;
    arr->dimen_2 = dimen2;
    arr->dimen_3 = dimen3;
    return(arr);
}

void        assign_value_at(array_t arr, long index1, long index2, long index3, data_t ndata)
{
    if( NULL  == arr            ||
        index1 >= arr->dimen_1    ||
        index2 >= arr->dimen_2    ||
        index3 >= arr->dimen_3)
    {
        return;
    }
    
    *(  arr->arr    + 
        (index1 * arr->dimen_2 * arr->dimen_3) + 
        (index2 * arr->dimen_3) +
        (index3)) = ndata;
}

data_t      get_value_at(array_t arr, long index1, long index2, long index3)
{
    if( NULL  == arr            || 
        index1 >= arr->dimen_1  ||
        index2 >= arr->dimen_2  ||
        index3 >= arr->dimen_3)
    {
        return(NULL);
    }
    
    return( *(arr->arr    + 
            (index1 * arr->dimen_2 * arr->dimen_3) + 
            (index2 * arr->dimen_3) +
            (index3) ) 
            );
}

void        array_traversal(array_t parr, SHOWDATA_PROC pshowdata)
{
    if( NULL  == parr )
        return; 

    for( int index1 = 0; index1 < parr->dimen_1; ++index1 )
    {
        for( int index2 = 0; index2 < parr->dimen_2; ++index2 )
        {
            for( int index3 = 0; index3 < parr->dimen_3; ++index3 )
            {
                pshowdata( get_value_at(parr, index1, index2, index3) );
            }
            printf("\n");
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
    for( int index1 = 0; index1 < (*parr)->dimen_1; ++index1 )
    {
        for( int index2 = 0; index2 < (*parr)->dimen_2; ++index2 )
        {
            for( int index3 = 0; index3 < (*parr)->dimen_3; ++index3 )
            {
                pdestroydata( get_value_at((*parr), index1, index2, index3) );
            }
        }        
    }
    free(arr);
    free(*parr);
    *parr = NULL;
}
