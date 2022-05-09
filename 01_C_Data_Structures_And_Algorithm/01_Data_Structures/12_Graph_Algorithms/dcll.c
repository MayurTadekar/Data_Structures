

/**
 * @file dcll.c
 * @author Mayur Tadekar
 * @brief Source Code of Helper Doubly Circular Linker List Data Structure for Graph
 * @version 0.1
 * @date 05-06-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include    <stdio.h>
#include    <stdlib.h>

#include    "dcll.h"

//  List Auxillary Functions

/**
 * @brief Allocating memory for 'nr_elements' * 'element_size' bytes
 * 
 * @param nr_elements  total number of elements
 * @param element_size size of each element to allocate
 * @return void*    returning the address of allocated memory 
 */
static  void*   Xcalloc(size_t nr_elements, size_t element_size)
{
    //  Code
    void* p = calloc(nr_elements, element_size);
    if(p == NULL)
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

/**
 * @brief Adding the 'mid' node in the list
 * 
 * @param first Node after which new node gets inserted
 * @param mid   Node to insert
 * @param last  Node before which new node gets inserted
 * @return status_t returning the status of completion of insertion option
 */
static  dcll_status_t    list_generic_insert(p_dcll_node_t first, p_dcll_node_t mid, p_dcll_node_t last)
{
    //  Code
    mid->pnext = last;
    mid->pprev = first;

    first->pnext = mid;
    last->pprev = mid;

    return(SUCCESS);
}

/**
 * @brief Removing the node from the list 
 * 
 * @param pnode The node to remove from the list 
 * @return data_t returning the data contained by the node
 */
static  dcll_data_t      list_generic_remove(p_dcll_node_t pnode)
{
    //  Code
    pnode->pprev->pnext = pnode->pnext;
    pnode->pnext->pprev = pnode->pprev;

    dcll_data_t ret_data = pnode->data;
    free(pnode);
    return(ret_data);
}

/**
 * @brief creating a new node to insert in list
 * 
 * @param data to add in the node.
 * @return p_dcll_node_t returning the address of newly created node
 */
static  p_dcll_node_t   list_create_node(dcll_data_t data)
{
    //  Code
    p_dcll_node_t p = (p_dcll_node_t)Xcalloc(1, SIZE_DCLL_NODE);
    p->data = data;
    p->pprev = p;
    p->pnext = p;
    return(p);
}

static  p_dcll_node_t   list_locate_node(list_t list, dcll_data_t edata, COMPARE_PROC pcompare)
{
    //  Code
    p_dcll_dummy_t pd = ((p_dcll_dummy_t)list);
    
    p_dcll_node_t run = pd->list->pnext;

    while(1)
    {
        if( pd->list == run )
            return(NULL);

        if( SUCCESS == pcompare(run->data, edata) )
            return(run);
        
        run = run->pnext;
    }

    return(run);
}

/**
 * @brief Assign data to list at index
 * 
 * @param list to assign data to 
 * @param index to assign data at
 * @param data to assign in list at index
 */
static  void        list_assign_data(list_t list, long index, dcll_data_t data)
{
    //  Code
    
    p_dcll_node_t run = ((p_dcll_dummy_t)list)->list->pnext;

    for( int i = 0; i < index; ++i )
        run = run->pnext;

    run->data = data;
}


/**
 * @brief Merge function to merge sorted list
 * 
 * @param list base node of list
 * @param first index of list element
 * @param mid index of list element
 * @param last index of list element
 */
static  void         merge(list_t list, long left, long mid, long right, COMPARE_PROC pcompare)
{
    //  Code

    long    lSize = mid - left + 1;
    long    rSize = right - mid;

    list_t list_left = create_list();
    list_t list_right = create_list();

    //printf("%d - %d\n", lSize, rSize);

    for( int i = 0; i < lSize; ++i )
        list_insert_back( list_left, list_at(list, left + i) );
    
    for( int i = 0; i < rSize; ++i )
        list_insert_back( list_right, list_at(list, mid + 1 + i ));

    long    i = 0;
    long    j = 0;
    long    k = left;

    for( k = left; k <= right; ++k )
    {
        if( i < lSize && j < rSize )
        {
            if( SUCCESS == pcompare( list_at(list_left, i), list_at(list_right, j) ) )
            {
                list_assign_data( list, k, list_at(list_left, i) );
                i++;
            }
            else
            {
                list_assign_data( list, k, list_at(list_right, j) );
                j++;
            }
        }
        else
        {
            if( j < list_size(list_right) )
            {
                list_assign_data( list, k, list_at(list_right, j) );
                j++;
            }
            else if( i < list_size(list_left) )
            {
                list_assign_data( list, k, list_at(list_left, i) );
                i++;
            }
        }
    }

    list_destroy( &list_left, NULL );
    list_destroy( &list_right, NULL );
}


/**
 * @brief Merge Sort  function for list
 * 
 * @param list base node
 * @param first first index of list element
 * @param last last index of list element
 */
static  void         merge_sort(list_t list, long first, long last, COMPARE_PROC pcompare)
{
    //  Code
    if( last <= first )
        return;

    long mid = ( last + first ) / 2;     

    merge_sort(list, first, mid, pcompare);
    merge_sort(list, mid+1, last, pcompare);
    merge(list, first, mid, last, pcompare);
}

//  List Interface Functions

/**
 * @brief Create a list object
 * 
 * @return list_t returning the base address of created list
 */
extern  list_t  create_list()
{
    //  Code
    p_dcll_dummy_t pd = (p_dcll_dummy_t) Xcalloc(1, SIZE_DCLL_DUMMY);
    pd->list = list_create_node(NULL);
    pd->nr_elements = 0;
    return(pd); 
}

/**
 * @brief Insert new data to list
 * 
 * @param list List to insert data in.
 * @param data Data to be insert in list
 * @return dcll_status_t Returning the status of insertion in list
 */
extern  dcll_status_t    list_insert(list_t list, dcll_data_t data)
{
    //  Code
    return( list_insert_back(list, data) );
}

/**
 * @brief Inserting new data to the front of the list
 * 
 * @param list List to insert data in.
 * @param data Data to be inserted in list
 * @return dcll_status_t returning the status of insertion in list
 */
extern  dcll_status_t    list_insert_front(list_t list, dcll_data_t data)
{
    //  Code
    if( NULL == list ||
        NULL == ((p_dcll_dummy_t)list)->list)
        return(FAILURE);
    
    ((p_dcll_dummy_t)list)->nr_elements++;
    return( list_generic_insert(((p_dcll_dummy_t)list)->list, 
                                list_create_node(data),
                                ((p_dcll_dummy_t)list)->list->pnext)
        );
}

/**
 * @brief Inserting new data to the end of the list
 * 
 * @param list list to insert data in
 * @param data Data to be inserted in list
 * @return dcll_status_t returning the status of insertion in list
 */
extern  dcll_status_t    list_insert_back(list_t list, dcll_data_t data)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list)
        return(FAILURE);

    ((p_dcll_dummy_t)list)->nr_elements++;
    //printf("\n%p", data);
    return( list_generic_insert(((p_dcll_dummy_t)list)->list->pprev,
                                list_create_node(data),
                                ((p_dcll_dummy_t)list)->list ) );
}

/**
 * @brief Removing data from the list
 * 
 * @param list List to remove data from.
 * @param edata  data to be removed from list
 * @param pcompare callback function to compare function data
 * @return dcll_data_t returning data if removed
 */
extern  dcll_data_t      list_remove(list_t list, dcll_data_t edata, COMPARE_PROC pcompare)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list    ||
        0 == ((p_dcll_dummy_t)list)->nr_elements )
        return(NULL);
    
    p_dcll_node_t pnode = list_locate_node(list, edata, pcompare);

    if( NULL == pnode )
        return(NULL);

    ((p_dcll_dummy_t)list)->nr_elements--;
    return( list_generic_remove(pnode) );
}

/**
 * @brief Removing the first element of list
 * 
 * @param list  List to remove element from 
 * @return dcll_data_t Returning data of the element removed
 */
extern  dcll_data_t      list_remove_first(list_t list)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list    ||
        0 == ((p_dcll_dummy_t)list)->nr_elements )
        return(NULL);
    
    ((p_dcll_dummy_t)list)->nr_elements--;
    return( list_generic_remove( ((p_dcll_dummy_t)list)->list->pnext ) );
}

/**
 * @brief Removing the last element of list
 * 
 * @param list List to remove element from
 * @return dcll_data_t Returning data of the element removed
 */
extern  dcll_data_t      list_remove_last(list_t list)
{
    
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list    ||
        0 == ((p_dcll_dummy_t)list)->nr_elements )
        return(NULL);
    
    ((p_dcll_dummy_t)list)->nr_elements--;
    return( list_generic_remove( ((p_dcll_dummy_t)list)->list->pprev ) );
}

/**
 * @brief Get data from list at an index
 * 
 * @param list List to get data from
 * @param index Position of data in list to retrive
 * @return dcll_data_t Returning data at index
 */
extern  dcll_data_t      list_at(list_t list, int index)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list        ||
        0 == ((p_dcll_dummy_t)list)->nr_elements    ||
        index >= ((p_dcll_dummy_t)list)->nr_elements )
        return(NULL);
    
    p_dcll_node_t run = ((p_dcll_dummy_t)list)->list->pnext;

    for( int i = 0; i < index; ++i )
        run = run->pnext;

    return( run->data );    
}

/**
 * @brief Getting total number of elements from list
 * 
 * @param list List to get size of
 * @return size_t returning the total number of elements in list
 */
extern  size_t      list_size(list_t list)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list        ||
        0 == ((p_dcll_dummy_t)list)->nr_elements    )
        return(0);
    
    return(((p_dcll_dummy_t)list)->nr_elements);
}

/**
 * @brief Sort elements of list
 * 
 * @param list to sort 
 * @param pcompare callback function for comparing data
 */
extern  void    list_sort(list_t list, COMPARE_PROC pcompare)
{
    //  Code
    p_dcll_dummy_t pl = (p_dcll_dummy_t)list;
    if( NULL == pl  ||
        NULL == pl->list   ||
        0 == pl->nr_elements )
    {
        return;
    }

    //printf("1\n");
    merge_sort(list, 0, pl->nr_elements - 1, pcompare);
    //printf("2\n");
}    


/**
 * @brief Traversing through the list to retrive data of each element
 * 
 * @param list List to retrive each data element
 * @param pshowdata Callback to give data to user
 */
extern  void        list_show(list_t list, SHOWDATA_PROC pshowdata)
{
    //  Code
    if( NULL == list    ||
        NULL == ((p_dcll_dummy_t)list)->list        ||
        0 == ((p_dcll_dummy_t)list)->nr_elements    )
        return;

    p_dcll_node_t run = ((p_dcll_dummy_t)list)->list->pnext;

    while( ((p_dcll_dummy_t)list)->list != run )
    {
        pshowdata( run->data );
        run = run->pnext;
    }
}

/**
 * @brief Destroying the list by deleting every element
 * 
 * @param plist     Pointer to listt to destroy
 * @param pdeletedata Delete data callback for user
 * @return dcll_status_t Returning the status of destroying the list
 */
extern  dcll_status_t    list_destroy(p_list_t plist, DELETEDATA_PROC pdeletedata)
{
    //  Code
    if( NULL == plist  )
        return(FAILURE);

    p_dcll_dummy_t pd = ((p_dcll_dummy_t)*plist);
    
    p_dcll_node_t run = pd->list->pnext;
    p_dcll_node_t run_next = NULL;

    run->pprev->pnext = NULL;

    while( run != NULL && pd->list != run)
    {
        if( NULL != pdeletedata )
            pdeletedata(run->data);
        run_next = run->pnext;

        free(run);
        run = run_next;
    }

    free(run);

    free(pd);
    *plist = NULL;
    return(SUCCESS);
}       
