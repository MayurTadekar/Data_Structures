
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

static  ret_t   list_generic_insert(p_node_dcll_t first, p_node_dcll_t mid, p_node_dcll_t last)
{
    /*  CODE */
    mid->pnext = first->pnext;
    mid->pprev = last->pprev;

    first->pnext = mid;
    last->pprev = mid;

    return(SUCCESS);
}

static  data_t   list_generic_remove(p_node_dcll_t delnode_dcll)
{
    /*  CODE */
    delnode_dcll->pprev->pnext = delnode_dcll->pnext;
    delnode_dcll->pnext->pprev = delnode_dcll->pprev;

    data_t rdata = delnode_dcll->data;
    free(delnode_dcll);
    return(rdata);
}

static  p_node_dcll_t    list_locate_node_dcll(list_t list, data_t edata, bool_t (*p_compare_proc)(data_t, data_t))
{
    /*  CODE */
    p_node_dcll_t prun = ((p_list_t)list)->pnext;

    while(TRUE)
    {
        if( SUCCESS == p_compare_proc(prun->data, edata) )
            return(prun);

        if(prun == list)
            return(NULL);
    
        prun = prun->pnext;
    }

    return(NULL);
}

static  p_node_dcll_t list_create_node_dcll(data_t data)
{
    /* CODE */
    p_node_dcll_t pnode_dcll = (p_node_dcll_t)xmalloc(SIZE_node_dcll);
    pnode_dcll->data = data;
    pnode_dcll->pnext = pnode_dcll;
    pnode_dcll->pprev = pnode_dcll;
    return(pnode_dcll);
}

/*	LIST INTERFACE FUNCTION */
extern 	list_t	list_create(void)
{
    /*  CODE    */
    p_dummy_t list = (p_dummy_t)malloc( SIZE_DUMMY );
    list->noOfnode_dclls = 0;
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
        ((p_dummy_t)list)->list = list_create_node_dcll(data);
    }
    else
        list_generic_insert(((p_dummy_t)list)->list->pprev, list_create_node_dcll(data), ((p_dummy_t)list)->list);
    
    ((p_dummy_t)list)->list = ((p_dummy_t)list)->list->pprev;

    ((p_dummy_t)list)->noOfnode_dclls++;
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
        ((p_dummy_t)list)->list = list_create_node_dcll(data);
    }
    else
        list_generic_insert(((p_dummy_t)list)->list->pprev, list_create_node_dcll(data), ((p_dummy_t)list)->list);
    
    ((p_dummy_t)list)->noOfnode_dclls++;
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
        ((p_dummy_t)list)->list = list_create_node_dcll(data);
        ((p_dummy_t)list)->noOfnode_dclls++;
        return(SUCCESS);
    }

    if( E_LIST_EMPTY == status )
    {
        list_generic_insert(((p_dummy_t)list)->list, list_create_node_dcll(data), ((p_list_t)list)->pnext);
    }
    else
    {

        p_node_dcll_t enode_dcll = ((p_dummy_t)list)->list;

        for( int pos = 1; pos < position; pos++)
        {
            enode_dcll = enode_dcll->pnext;
        }

        p_node_dcll_t pnode_dcll = list_create_node_dcll(data);

        list_generic_insert(enode_dcll->pprev, pnode_dcll, enode_dcll);
    }

    if( 1 == position)
        ((p_dummy_t)list)->list = ((p_dummy_t)list)->list->pprev;

    ((p_dummy_t)list)->noOfnode_dclls++;

    return(SUCCESS);
}

extern 	ret_t 	list_insert_after(list_t list, data_t edata, data_t idata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode_dcll)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    p_node_dcll_t pnode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, idata, p_compare_proc);
    /*****************************\
     * CHECK FOR DATA REPETITION
    \*****************************/
    if( NULL != pnode_dcll )
    {
        fprintf(stderr, "ERROR: Data Already Present\n");
        return(E_DATA_ALREADY_PRESENT);
    }
    pnode_dcll = list_create_node_dcll(idata);

    list_generic_insert( enode_dcll, pnode_dcll, enode_dcll->pnext);

    ((p_dummy_t)list)->noOfnode_dclls++;
    return(SUCCESS);
}

extern	ret_t 	list_insert_before(list_t list, data_t edata, data_t idata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);

    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);
    }

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode_dcll)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_ALREADY_PRESENT);
    }

    p_node_dcll_t pnode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, idata, p_compare_proc);
    /*****************************\
     * CHECK FOR DATA REPETITION
    \*****************************/
    if( NULL != pnode_dcll )
    {
        fprintf(stderr, "ERROR: Data Already Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    pnode_dcll = list_create_node_dcll(idata);
    list_generic_insert(enode_dcll->pprev, pnode_dcll, enode_dcll);

    ((p_dummy_t)list)->noOfnode_dclls++;

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
    
    p_node_dcll_t pnode_dcll = ((p_dummy_t)list)->list;
    ((p_dummy_t)list)->list = pnode_dcll->pnext;

    if( NULL != pdata)
        *pdata = list_generic_remove(pnode_dcll);
    else
        free(list_generic_remove(pnode_dcll));

    ((p_dummy_t)list)->noOfnode_dclls--;
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

    p_node_dcll_t pnode_dcll = ((p_dummy_t)list)->list->pprev;

    if( NULL != pdata)
        *pdata = list_generic_remove(pnode_dcll);
    else
        list_generic_remove(pnode_dcll);

    ((p_dummy_t)list)->noOfnode_dclls--;
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
        p_node_dcll_t pnode_dcll = ((p_dummy_t)list)->list->pnext;

        for( int pos = 0; pos < position; pos++)
        {
            pnode_dcll = pnode_dcll->pnext;
        }

        if( NULL != pdata)
            *pdata = list_generic_remove(pnode_dcll);
        else
            list_generic_remove(pnode_dcll);
    }

    ((p_dummy_t)list)->noOfnode_dclls--;
    return(SUCCESS);
}
extern 	ret_t 	list_remove_after(list_t list, data_t edata, p_data_t pdata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode_dcll)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode_dcll->pnext);
    else
        list_generic_remove(enode_dcll->pnext);

    ((p_dummy_t)list)->noOfnode_dclls--;
    return(SUCCESS);
}

extern 	ret_t 	list_remove_before(list_t list, data_t edata, p_data_t pdata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /*  CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status
        )
    {
        return(status);
    }

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode_dcll)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode_dcll->pprev);
    else
        list_generic_remove(enode_dcll->pprev);

    ((p_dummy_t)list)->noOfnode_dclls--;
    return(SUCCESS);
}

extern  ret_t   list_remove(list_t list, data_t edata, p_data_t pdata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);  
    } 

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if( NULL == enode_dcll)
    {
        fprintf(stderr, "ERROR: Data Not Present\n");
        return(E_DATA_NOT_PRESENT);  
    }

    if( NULL != pdata)
        *pdata = list_generic_remove(enode_dcll);
    else
        list_generic_remove(enode_dcll);

    ((p_dummy_t)list)->noOfnode_dclls--;
    return(SUCCESS);
}

extern 	ret_t 	list_first(list_t list, p_data_t pdata)
{
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);  
    }

    *pdata = ((p_dummy_t)list)->list->data;
    return(SUCCESS);
}

extern 	ret_t 	list_last(list_t list, p_data_t pdata)
{
    
    ret_t status = list_is_empty(list);
    if( E_LIST_NOT_PRESENT == status    ||
        E_LIST_EMPTY == status)
    {
        return(status);  
    }

    *pdata = ((p_dummy_t)list)->list->pprev->data;
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

    return(((p_dummy_t)list)->noOfnode_dclls);
}


extern 	bool_t 	list_contains(list_t list, data_t edata, bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
    /* CODE */
    ret_t status = list_is_empty(list);

    if( FAILURE != status )
    {
        return(FALSE);
    }

    p_node_dcll_t enode_dcll = list_locate_node_dcll(((p_dummy_t)list)->list, edata, p_compare_proc);
    if(NULL == enode_dcll)
    {
        return(FALSE);
    }

    return(TRUE);
}

extern 	ret_t 	list_show(list_t list, void(*p_show_data)(data_t))
{
    /* CODE */
    ret_t status = list_is_empty(list);
    if(E_LIST_NOT_PRESENT == status)
    {
        return(status);
    }

    p_node_dcll_t prun = ((p_dummy_t)list)->list; 
    fprintf(stdout, "List Data:\n{START}->");
    if( NULL != prun )
        while(TRUE)
        {
        
            p_show_data(prun->data);
            prun = prun->pnext;

            if( ((p_dummy_t)list)->list == prun )
                break;
        }
    fprintf(stdout, "{END}\n\n");

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

extern  list_t  list_merge(list_t list1, list_t list2, bool_t (*p_inequality_compare_proc)(data_t, data_t))
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

    p_node_dcll_t prun1 = ((p_dummy_t)list1)->list;
    p_node_dcll_t prun2 = ((p_dummy_t)list2)->list;
    p_list_t merge_list = list_create();

    while( TRUE )
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

    p_node_dcll_t prun = ((p_dummy_t)list1)->list->pnext;
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

    p_node_dcll_t prun = ((p_dummy_t)list)->list;

    while( TRUE )
    {
        p_node_dcll_t temp = prun->pnext;
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

    p_node_dcll_t prun = NULL;
    p_node_dcll_t prun_next = NULL;

    fprintf(stdout, "Deleting List:\n");
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
    //printf("1\n");
    
    p_delete_data(((p_dummy_t)*pplist)->list->data);
    free(((p_dummy_t)*pplist)->list);
    ((p_dummy_t)*pplist)->list = NULL;

    free(*pplist);
    *pplist = NULL;
    return(SUCCESS);
}
