

/**
 * @file disjointset.c
 * @author Mayur Tadekar
 * @brief Source code of Disjoint Set
 * @version 0.1
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//  Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "disjointset.h"

//  Set Auxillary Functions

/**
 * @brief Allocating 'nr_elements' * 'element_size' memory
 * 
 * @param nr_elements number of elements
 * @param element_size size of each element
 * @return void* returning address of allcoated memory 
 */
static  void*   Xcalloc(size_t nr_elements, size_t element_size)
{
    //  Code
    void* p = calloc(nr_elements, element_size);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

/**
 * @brief Create a node object
 * 
 * @param data data to assign to allocated node object
 * @return p_set_node_t 
 */
static  p_set_node_t    create_node(set_data_t data)
{
    //  Code
    p_set_node_t pn = (p_set_node_t)Xcalloc(1, SIZE_SET_NODE);
    pn->data = data;
    pn->phead = NULL;
    pn->pnext = NULL;
    return(pn);
}

//  Set Interface Functions
/**
 * @brief Create a new set
 * 
 * @param data data to allocate to created set
 * @return set_t returning the create set address 
 */
extern  set_t    make_set(set_data_t data)
{
    //  Code
    p_set_dummy_t ps = (p_set_dummy_t) Xcalloc(1, SIZE_SET_DUMMY);
    ps->head = create_node(data);
    ps->tail = ps->head;
    ps->size = 1;
    return(ps);
}

/**
 * @brief Find object in the set
 * 
 * @param set to find object into
 * @param data data to find in the set
 * @param pcompare callback function to compare
 * @return status_t returninig the found data
 */
extern  set_data_t    set_find(set_t set, set_data_t data, COMPARE_PROC pcompare)
{
    //  Code
    p_set_dummy_t ps = (p_set_dummy_t)set;
    if( NULL == ps  ||
        0 == ps->size)
        return(NULL);

    p_set_node_t run = ps->head;
    while( run )
    {
        if( SUCCESS == pcompare( run->data, data ) )
            return( ps->head->data );

        run = run->pnext;
    }

    return(NULL);
}

/**
 * @brief Create a union both Set
 * 
 * @param set1 set to perform union with
 * @param pset2 pointer to set to perform union with and destroy
 * @return status_t returning the status of union
 */
extern  status_t    set_union(set_t set1, set_t* pset2)
{
    //  Code
    p_set_dummy_t ps1 = (p_set_dummy_t)set1;
    p_set_dummy_t ps2 = (p_set_dummy_t)*pset2;

    if( NULL == ps1 ||
        NULL == ps2 ||
        0 == ps1->size  ||
        0 == ps2->size )
        return(FAILURE);
    
    ps1->tail->pnext = ps2->head;
    ps1->tail = ps2->tail;

    ps1->size += ps2->size;

    p_set_node_t run = ps2->head;

    while( run )
    {
        run->phead = set1;
        run = run->pnext;
    }

    free(*pset2);
    *pset2 = NULL;
    return(SUCCESS);
}

/**
 * @brief Traverse the set objects
 * 
 * @param set to traverse
 * @param pshowdata callback function to show data
 */
extern  void        set_traverse(set_t set, SHOWDATA_PROC pshowdata)
{
    //  Code
    p_set_dummy_t ps = (p_set_dummy_t)set;

    if( NULL == ps ||
        0 == ps->size )
        return;

    p_set_node_t run = ps->head;

    while( run )
    {
        pshowdata(run->data);
        run = run->pnext;
    } 
}

/**
 * @brief get object at the index position
 * 
 * @param set to get the object
 * @param index position of object in set
 * @return set_data_t data present at the position
 */
extern  set_data_t  set_at(set_t set, int index)
{
    //  Code
    p_set_dummy_t ps = (p_set_dummy_t)set;
    if( NULL == ps ||
        0 == ps->size   ||
        index >= ps->size)
        return(NULL);
    
    p_set_node_t run = ps->head;

    for( int i = 0 ; i < index; ++i )
    {
        run = run->pnext;
    }

    return(run->data);
}

/**
 * @brief Size of the set
 * 
 * @param set to get size
 * @return size_t size of the set
 */
extern  size_t      set_size(set_t set)
{
    if( NULL != set )
        return( ((p_set_dummy_t)set)->size );
    else
        return(0);
}

/**
 * @brief Destroy the Set
 * 
 * @param pset pointer to set to destroy
 * @param pdeletedata callback function for deleting data
 */
extern  void        set_destroy(set_t* pset, DELETEDATA_PROC pdeletedata)
{
    //  Code
    if( NULL == *pset )
        return;

    p_set_dummy_t ps = (p_set_dummy_t)*pset;

    p_set_node_t run = ps->head;
    p_set_node_t run_next = run->pnext;
    
    while(run)
    {
        if( NULL != pdeletedata )
            pdeletedata(run->data);
        run_next = run->pnext;        
        free(run);
        run = run_next;
    }
    free(*pset);
    *pset = NULL;
}

