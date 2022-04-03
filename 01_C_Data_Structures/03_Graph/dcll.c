
#include    <stdio.h>
#include    <stdlib.h>

#include    "dcll.h"

/*  LIST AUXILLARY FUNCTIONS */
static  void*   xmalloc(size_t size)
{
    /* CODE */
    void *p = malloc(size);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(FAILURE);
    }
    return(p);
}

static  ret_t   list_generic_insert(p_node_t first, p_node_t mid, p_node_t last)
{
    /*  CODE */
    mid->pnext = first->pnext;
    mid->pprev = last->pprev;

    first->pnext = mid;
    last->pprev = mid;

    return(SUCCESS);
}

static  data_t   list_generic_remove(p_node_t delnode)
{
    /*  CODE */
    delnode->pprev->pnext = delnode->pnext;
    delnode->pnext->pprev = delnode->pprev;

    data_t rdata = delnode->data;
    free(delnode);
    return(rdata);
}

static  p_node_t    list_locate_node(list_t list, data_t edata, ret_t (*p_compare_proc)(data_t, data_t))
{
    /*  CODE */
    p_node_t prun = ((p_list_t)list)->pnext;

    while(true)
    {
        if( SUCCESS == p_compare_proc(prun->data, edata) )
            return(prun);

        if(prun == list)
            return(NULL);
    
        prun = prun->pnext;
    }

    return(NULL);
}

static  p_node_t list_create_node(data_t data)
{
    /* CODE */
    p_node_t pnode = (p_node_t)xmalloc(SIZE_NODE);
    pnode->data = data;
    pnode->pnext = pnode;
    pnode->pprev = pnode;
    return(pnode);
}

/*	LIST INTERFACE FUNCTION */
extern 	list_t	list_create(void)
{
    /*  CODE    */
    p_dummy_t list = (p_dummy_t)malloc( SIZE_DUMMY );
    list->noOfNodes = 0;
    list->list = NULL;
    /*((p_list_t)list)->pnext = list;
    ((p_list_t)list)->pprev = list;
    ((p_list_t)list)->data = 0;*/

    return(list);
}

extern	ret_t 	list_insert_front(list_t list, data_t data)
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status)
    {
        return(status);
    }

    if( NULL == ((p_dummy_t)list)->list )
    {
        ((p_dummy_t)list)->list = list_create_node(data);
    }
    else
        list_generic_insert(((p_dummy_t)list)->list->pprev, list_create_node(data), ((p_dummy_t)list)->list);
    
    ((p_dummy_t)list)->list = ((p_dummy_t)list)->list->pprev;

    ((p_dummy_t)list)->noOfNodes++;
    return(SUCCESS);
}

extern 	ret_t 	list_insert_back(list_t list, data_t data)
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status)
    {
        return(status);
    }

    if( NULL == ((p_dummy_t)list)->list )
    {
        ((p_dummy_t)list)->list = list_create_node(data);
    }
    else
        list_generic_insert(((p_dummy_t)list)->list->pprev, list_create_node(data), ((p_dummy_t)list)->list);
    
    ((p_dummy_t)list)->noOfNodes++;
    return(SUCCESS);
}

extern 	ret_t 	list_insert_position(list_t list, data_t data, size_t position)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if(E_LIST_NOT_PRESENT == status)
    {
        return(status);
    }

    /*if( position > ((p_list_t)list)->data )
    {
        fprintf(stderr, "ERROR: Position Out Of Limit\n");
        return(E_POSITION_OUT_OF_LIMIT);
    }*/
    if( NULL == ((p_dummy_t)list)->list )
    {
        ((p_dummy_t)list)->list = list_create_node(data);
        ((p_dummy_t)list)->noOfNodes++;
        return(SUCCESS);
    }

    if( E_LIST_EMPTY == status )
    {
        list_generic_insert(((p_dummy_t)list)->list, list_create_node(data), ((p_list_t)list)->pnext);
    }
    else
    {

        p_node_t enode = ((p_dummy_t)list)->list;

        for( int pos = 1; pos < position; pos++)
        {
            enode = enode->pnext;
        }

        p_node_t pnode = list_create_node(data);

        list_generic_insert(enode->pprev, pnode, enode);
    }

    if( 1 == position)
        ((p_dummy_t)list)->list = ((p_dummy_t)list)->list->pprev;

    ((p_dummy_t)list)->noOfNodes++;

    return(SUCCESS);
}

extern 	ret_t 	list_insert_after(list_t list, data_t edata, data_t idata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    p_node_t pnode = list_locate_node(((p_dummy_t)list)->list, idata, p_compare_proc);
    /*****************************\
     * CHECK FOR DATA REPETITION
    \*****************************/
    if( NULL != pnode )
    {
        fprintf(stderr, "ERROR: Data Already Present\n");
        return(E_DATA_ALREADY_PRESENT);
    }
    pnode = list_create_node(idata);

    list_generic_insert( enode, pnode, enode->pnext);

    ((p_dummy_t)list)->noOfNodes++;
    return(SUCCESS);
}

extern	ret_t 	list_insert_before(list_t list, data_t edata, data_t idata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);

    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);
    }

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_ALREADY_PRESENT);
    }

    p_node_t pnode = list_locate_node(((p_dummy_t)list)->list, idata, p_compare_proc);
    /*****************************\
     * CHECK FOR DATA REPETITION
    \*****************************/
    if( NULL != pnode )
    {
        fprintf(stderr, "ERROR: Data Already Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    pnode = list_create_node(idata);
    list_generic_insert(enode->pprev, pnode, enode);

    ((p_dummy_t)list)->noOfNodes++;

    return(SUCCESS);
}

extern 	ret_t 	list_insert(list_t list, data_t data)
{
    /* CODE */
    return(list_insert_back(((p_dummy_t)list)->list, data));
}

extern 	ret_t  	list_remove_front(list_t list, p_data_t pdata)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);
    }
    
    p_node_t pnode = ((p_dummy_t)list)->list;
    ((p_dummy_t)list)->list = pnode->pnext;

    if( NULL != pdata)
        *pdata = list_generic_remove(pnode);
    else
        free(list_generic_remove(pnode));

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}

extern 	ret_t 	list_remove_back(list_t list, p_data_t pdata)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);
    }

    p_node_t pnode = ((p_dummy_t)list)->list->pprev;

    if( NULL != pdata)
        *pdata = list_generic_remove(pnode);
    else
        list_generic_remove(pnode);

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}


extern 	ret_t 	list_remove_position(list_t list, size_t position, p_data_t pdata)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);
    }

    /*if( position > ((p_list_t)list)->data )
    {
        fprintf(stderr, "ERROR: Position Out Of Limit");
        return(E_POSITION_OUT_OF_LIMIT);
    }
*/
    if( 0 == position )
    {
        if( NULL != pdata)
            *pdata = ((p_dummy_t)list)->list->pnext->data;
        free(((p_dummy_t)list)->list->pnext);
        ((p_dummy_t)list)->list->pnext = NULL;
        ((p_dummy_t)list)->list->pprev = NULL;
    }
    else
    {
        p_node_t pnode = ((p_dummy_t)list)->list->pnext;

        for( int pos = 0; pos < position; pos++)
        {
            pnode = pnode->pnext;
        }

        if( NULL != pdata)
            *pdata = list_generic_remove(pnode);
        else
            list_generic_remove(pnode);
    }

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}
extern 	ret_t 	list_remove_after(list_t list, data_t edata, p_data_t pdata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode->pnext);
    else
        list_generic_remove(enode->pnext);

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}

extern 	ret_t 	list_remove_before(list_t list, data_t edata, p_data_t pdata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode->pprev);
    else
        list_generic_remove(enode->pprev);

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}

extern  ret_t   list_remove(list_t list, data_t edata, p_data_t pdata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);  
    } 

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);  
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode);
    else
        list_generic_remove(enode);

    ((p_dummy_t)list)->noOfNodes--;
    return(SUCCESS);
}

extern 	len_t 	list_length(list_t list)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status )
    {
        return(status);
    }

    return(((p_dummy_t)list)->noOfNodes);
}


extern 	ret_t 	list_contains(list_t list, data_t edata, ret_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);

    if( FAILURE != status )
    {
        return(false);
    }

    p_node_t enode = list_locate_node(((p_dummy_t)list)->list, edata, p_compare_proc);
    if(NULL == enode)
    {
        return(false);
    }

    return(true);
}

extern 	ret_t 	list_show(list_t list, void(*p_show_data)(data_t))
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if(E_LIST_NOT_PRESENT == status || E_LIST_EMPTY == status)
    {
        return(status);
    }

    p_node_t prun = ((p_dummy_t)list)->list; 
    //fprintf(stdout, "{START}");
    if( NULL != prun )
        while(true)
        {
        
            p_show_data(prun->data);
            prun = prun->pnext;

            if( ((p_dummy_t)list)->list == prun )
                break;
        }
    //fprintf(stdout, "{END}\n\n");

    return(SUCCESS);
}

extern 	ret_t 	list_is_empty(list_t list)
{
    if( NULL == list )
    {
        //fprintf(stderr, "ERROR: List Not Present\n");
        return(E_LIST_NOT_PRESENT);
    }

    if( NULL == ((p_dummy_t)list)->list)
    {
        //fprintf(stderr, "ERROR: List Empty\n");
        return(E_LIST_EMPTY);
    }

    return(FAILURE);
}

extern  list_t  list_merge(list_t list1, list_t list2, ret_t (*p_inequality_compare_proc)(data_t, data_t))
{
    /* CODE */
    ret_t status = list_is_empty(list1);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(NULL);
    }

    status = list_is_empty(list2);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(NULL);
    }

    p_node_t prun1 = ((p_dummy_t)list1)->list;
    p_node_t prun2 = ((p_dummy_t)list2)->list;
    p_list_t merge_list = list_create();

    while( true )
    {
        if( prun1 == ((p_dummy_t)list1)->list->pprev  ||
            prun2 == ((p_dummy_t)list2)->list->pprev )
        {
            break;
        }

        if( SUCCESS == p_inequality_compare_proc( prun1->data, prun2->data) )
        {
            list_insert_back(merge_list, prun1->data);
            prun1 = prun1->pnext;
        }
        else
        {
            list_insert_back(merge_list, prun2->data);
            prun2 = prun2->pnext;
        }  
    }

    if( prun1 == ((p_dummy_t)list1)->list )
    {
        while( prun2 != ((p_dummy_t)list2)->list)
        {
            list_insert_back(merge_list, prun2->data);
            prun2 = prun2->pnext;
        }
    }

    if( prun2 == ((p_dummy_t)list2)->list)
    {
        while( prun1 != ((p_dummy_t)list1)->list )
        {
            list_insert_back(merge_list, prun1->data);
            prun1 = prun1->pnext;
        }
    }

    return(merge_list);
}

extern 	list_t 	list_concate(list_t list1, list_t list2)
{
    /* CODE */
    ret_t status = list_is_empty(list1);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(NULL);
    }

    status = list_is_empty(list2);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(NULL);
    }

    p_node_t prun = ((p_dummy_t)list1)->list->pnext;
    p_list_t concate_list = list_create();

    while( prun != ((p_dummy_t)list1)->list)
    {
        list_insert_back(concate_list, prun->data);
        prun = prun->pnext;
    }

    prun = ((p_dummy_t)list2)->list->pnext;
    while( prun != ((p_dummy_t)list2)->list)
    {
        list_insert_back(concate_list, prun->data);
        prun = prun->pnext;
    }

    return(concate_list);
}

extern 	list_t 	list_reverse(list_t list)
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(NULL);
    }

    p_node_t prun = ((p_dummy_t)list)->list;

    while( true )
    {
        p_node_t temp = prun->pnext;
        prun->pnext = prun->pprev;
        prun->pprev = temp;

        prun = prun->pprev;
        
        if( ((p_dummy_t)list)->list == prun )
            break;
    }
    
    ((p_dummy_t)list)->list = ((p_dummy_t)list)->list->pnext;

    return(list);
}

extern 	ret_t  	list_append(list_t list1, list_t list2)
{
    /* CODE */
    ret_t status = list_is_empty(list1);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(status);
    }

    status = list_is_empty(list2);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status )
    {
        return(status);
    }


    ((p_dummy_t)list1)->list->pprev->pnext = ((p_dummy_t)list2)->list;
    ((p_dummy_t)list2)->list->pprev->pnext = ((p_dummy_t)list1)->list;

    ((p_dummy_t)list1)->list->pprev = ((p_dummy_t)list2)->list->pprev;
    ((p_dummy_t)list2)->list->pprev = ((p_dummy_t)list1)->list->pprev;


    ((p_dummy_t)list2)->list = NULL;
    return(SUCCESS);
}

extern 	ret_t 	list_destroy(pp_list_t pplist, void(*p_delete_data)(data_t))
{
    /* CODE */
    if( NULL == *pplist )
    {
        return(E_LIST_NOT_PRESENT);
    }
    p_list_t plist = ((p_dummy_t)*pplist)->list;
    ret_t status = list_is_empty(plist);
    if( E_LIST_NOT_PRESENT == status)
    {
        if(NULL != *pplist)
        {
            free(*pplist);
            *pplist = NULL;
        }
        return(status);
    }   

    p_node_t prun = NULL;
    p_node_t prun_next = NULL;

    //fprintf(stdout, "Deleting List:\n");
    //plist->pprev->pnext = NULL;
    prun = plist->pnext;

    while(  prun != ((p_dummy_t)*pplist)->list )
    {
        prun_next = prun->pnext;

        if( NULL != prun->data )
            p_delete_data(prun->data);
        prun->data = NULL;
        free(prun);
        prun = prun_next;
    }
    
    p_delete_data(((p_dummy_t)*pplist)->list->data);
    free(((p_dummy_t)*pplist)->list);
    ((p_dummy_t)*pplist)->list = NULL;

    free(*pplist);
    *pplist = NULL;
    return(SUCCESS);
}

extern  data_t  list_get_data(list_t list, data_t edata, ret_t (*p_compare_proc)(data_t, data_t))
{   
    return( (list_locate_node(list, edata, p_compare_proc))->data );
}
