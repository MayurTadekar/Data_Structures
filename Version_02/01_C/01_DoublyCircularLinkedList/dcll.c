/**
 * S.G.M.P
 * @file: dcll.c
 * @brief: The Source Code Implementation of Doubly Circular Linked List
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 April 2024 (Friday) 01:12:13 PM
 */

// Headers
#include 	<stdio.h>
#include 	<stdlib.h>

#include	"dcll.h"

//	Macro Definitions
#define	CREATENODE(node, data, returnvalue)	{	\
												node = createnode(data);\
												if(NULL == node) 		\
													return(returnvalue);		\
											}


#define	LISTCHECKFORERRORS(list, params, returnvalue)	{	\
															if(SUCCESS == iserror(list, params))\
																return(returnvalue);			\
														}

//	Error Checking Codes
#define	LCFE_LISTNOTFOUND	0x00000001
#define	LCFE_LISTEMPTY		0x00000002 	

// Global Object Definitions

// variable that stores the error code
static int d_errorcode = E_NONE;

/****************	Helper Function Definitions	****************/

/**
 * 
 * Function: Wrapper Function to malloc that allocates memory of nr_bytes and checks for error
 * 
 * identifier: xmalloc
 * params:	nr_bytes
 * returns:	pointer to allocated memory
 */
static void* xmalloc(size_t nr_bytes)
{
	// Code
	void* p = malloc(nr_bytes);
	
	if(NULL == p)
	{
		d_errorcode = E_OUTOFMEMORY;
		return(NULL);
	}
	return(p);
}

/**
 * 
 * Function: Allocation of new node in memory and initializing data field with n_data
 * 
 * identifier: createnode
 * params: new data to assign to new node
 * returns:	pointer to allocated node OR NULL if error
 */
static p_dnode createnode(data_t n_data)
{
	// Code
	p_dnode node = xmalloc(SIZE_DNODE);

	if(NULL == node)
		return(NULL);

	node->data = n_data;
	node->next = node;
	node->prev = node;

	return(node);
}

/**
 * 
 * Function: Insert mid in between first and last
 * 
 * identifier: genericinsert
 * params: 	1) first node
 * 			2) mid node
 * 			3) last node
 * returns:	returns success after successful insertion of node
 */
static ret_t genericinsert(PDList list, p_dnode first, p_dnode mid, p_dnode last)
{
	// Code
	first->next = mid;
	mid->next = last;

	mid->prev = first;
	last->prev = mid;

	list->nrelements++;

	return(SUCCESS);
}

/**
 * 
 * Function: Removes the node from the list
 * 
 * identifier: genericremove
 * params: dnode to be removed from list
 * returns: data of the node
 */
static data_t genericremove(PDList list, p_dnode dnode)
{
	// Code
	p_dnode first = dnode->prev;
	p_dnode last = dnode->next;

	first->next = last;
	last->prev = first;

	data_t to_return_data = dnode->data;

	free(dnode);
	dnode = NULL;

	list->nrelements--;

	return(to_return_data);
}

/**
 * 
 * Function: Check for error as per param
 * 
 * identifier:	iserror
 * params:	1)	list
 * 			2)	param
 * returns:	returns SUCCESS if error and FAILURE if no error
 */
static	ret_t 	iserror(PDList list, int codes)
{
	// Code
	if(codes & LCFE_LISTNOTFOUND)
	{
		if(NULL == list)
		{
			d_errorcode = E_LISTNOTFOUND;
			return(SUCCESS);
		}
	}

	if(codes & LCFE_LISTEMPTY)
	{
		if( list->head == list->head->next )
		{
			d_errorcode = E_LISTEMPTY;
			return(SUCCESS);
		}
	}

	return(FAILURE);
}

/**
 * 
 * Function: Search the complete list for a data and return the node consisting that data
 * 
 * identifier: locatenode
 * params:	1) list
 * 			2) data to search
 * 			3) callback function to compare data
 * returns:	node containing data or NULL
 */
static p_dnode locatenode(PDList list, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	p_dnode	runner = list->head->next;

	while(1)
	{
		if( SUCCESS == pcompareproc(runner->data, e_data) )
			return(runner);

		if(list->head == runner)
		{
			d_errorcode = E_DATANOTFOUND;
			return(NULL);			
		}

		runner = runner->next;
	}

	return(NULL);
}

/****************	Interface Function Definitions	****************/

//	DCLL Interface function declarations
extern	PDList 	createlist(void)
{
	// Code
	p_dnode node;
	CREATENODE(node, NULL, NULL)

	PDList list = xmalloc(SIZE_DCLL);
	if(NULL == list)
	{
		return(NULL);
	}
	list->head = node;

	list->nrelements = 0;

	return(list);
}

//	Interface Functions to insert data in list
extern	ret_t	dcll_insertfront(PDList list, data_t data)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND, FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE)

	return(genericinsert(list, list->head, node, list->head->next));
}

extern	ret_t	dcll_insertback(PDList list, data_t data)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND, FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE);

	return(genericinsert(list, list->head->prev, node, list->head));

}	

extern 	ret_t	dcll_insertat(PDList list, data_t data, long long index)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, FAILURE);

	if(index < 0 || index > list->nrelements)
	{
		d_errorcode = E_INDEXOUTOFBOUND;
		return(FAILURE);
	}

	p_dnode runner = list->head;
	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	p_dnode node;
	CREATENODE(node, data, FAILURE);

	return(genericinsert(list, runner, node, runner->next));
}

extern 	ret_t	dcll_insertafter(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, FAILURE);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE);

	return(genericinsert(list, enode, node, enode->next));
}

extern	ret_t	dcll_insertbefore(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, FAILURE);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE);

	return(genericinsert(list, enode->prev, node, enode));
}

// 	Interface Functions to remove data from list
extern	data_t	dcll_removefront(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	return(genericremove(list, list->head->next));
}

extern	data_t	dcll_removeback(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	return(genericremove(list, list->head->prev));
}

extern	data_t	dcll_removeat(PDList list, long long index)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	if( index < 0 || list->nrelements < index)
	{
		d_errorcode = E_INDEXOUTOFBOUND;
		return(NULL);
	}

	p_dnode runner = list->head->next;
	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	return(genericremove(list, runner));
}

extern	data_t 	dcll_removeafter(PDList list, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(genericremove(list, enode->next));
}

extern	data_t	dcll_removebefore(PDList list, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(genericremove(list, enode->prev));	
}

//	Interface functions for operations of List
extern	data_t	dcll_search(PDList list, data_t s_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, s_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(enode->data);
}

extern	data_t	dcll_dataat(PDList list, long long index)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode runner = list->head->next;
	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	return(runner->data);
}

extern	size_t	dcll_size(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, 0);

	return(list->nrelements);
}

extern	int 	dcll_geterrordescription()
{
	// Code
	switch(d_errorcode)
	{
	case E_NONE:
		fprintf(stdout, "No Error\n");
		break;

	case E_OUTOFMEMORY:
		fprintf(stdout, "Out Of Memory\n");
		break;

	case E_LISTEMPTY:
		fprintf(stdout, "List Is Empty\n");
		break;

	case E_LISTNOTFOUND:
		fprintf(stdout, "List Not Found\n");
		break;

	case E_INDEXOUTOFBOUND:
		fprintf(stdout, "Index Out Of Bound\n");
		break;

	case E_DATANOTFOUND:
		fprintf(stdout, "Data Not Found\n");
		break;
	}

	d_errorcode = E_NONE;
}


//	Interface function to destroy list
extern	ret_t	dcll_destroy(PPDList plist, DELETEDATAPROC pdeletedataproc)
{
	// Code
	if( NULL == plist)
	{
		d_errorcode = E_LISTNOTFOUND;
		return(FAILURE);
	}

	PDList list = *plist;
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND, FAILURE);

	p_dnode runner = list->head;
	runner->prev->next = NULL;	

	while(runner->next)
	{
		free(runner->prev);
		runner->prev = NULL;

		pdeletedataproc(runner->data);
		runner->data = NULL;

		runner = runner->next;
	}

	free(runner);
	runner = NULL;

	free(list);
	list = NULL;
	*plist = NULL;

	return(SUCCESS);
}

