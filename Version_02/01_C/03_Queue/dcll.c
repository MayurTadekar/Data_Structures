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

/**
 * Function: Creates a new doubly linked list and initializes it with a dummy node.
 * 
 * identifier: createlist
 * params: void (No parameters)
 * returns: PDList Returns a pointer to the newly created doubly linked list. Returns NULL if memory allocation fails.
 */
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

/**
 * Function: Inserts data at the front of a doubly linked list.
 * 
 * identifier: dcll_insertfront
 * params: PDList list - Pointer to the doubly linked list, data_t data - Data to be inserted.
 * returns: ret_t Returns SUCCESS upon successful insertion. Returns FAILURE if the list is not found or if memory allocation fails.
 */
extern	ret_t	dcll_insertfront(PDList list, data_t data)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND, FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE)

	return(genericinsert(list, list->head, node, list->head->next));
}

/**
 * Function: Inserts data at the back of a doubly linked list.
 * 
 * identifier: dcll_insertback
 * params: PDList list - Pointer to the doubly linked list, data_t data - Data to be inserted.
 * returns: ret_t Returns SUCCESS upon successful insertion. Returns FAILURE if the list is not found or if memory allocation fails.
 */
extern	ret_t	dcll_insertback(PDList list, data_t data)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND, FAILURE);

	p_dnode node;
	CREATENODE(node, data, FAILURE);

	return(genericinsert(list, list->head->prev, node, list->head));

}	

/**
 * Function: Inserts data at the specified index in a doubly linked list.
 * 
 * identifier: dcll_insertat
 * params: PDList list - Pointer to the doubly linked list, data_t data - Data to be inserted, long long index - Index at which the data is to be inserted.
 * returns: ret_t Returns SUCCESS upon successful insertion. Returns FAILURE if the list is not found, if the list is empty, or if the index is out of bounds.
 */
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

/**
 * Function: Inserts data after a specific element in a doubly linked list.
 * 
 * identifier: dcll_insertafter
 * params: PDList list - Pointer to the doubly linked list, data_t data - Data to be inserted, data_t e_data - Element after which the data is to be inserted, COMPAREPROC pcompareproc - Pointer to the comparison function.
 * returns: ret_t Returns SUCCESS upon successful insertion. Returns FAILURE if the list is not found, if the list is empty, or if the element after which the data is to be inserted is not found.
 */
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

/**
 * Function: Inserts data before a specific element in a doubly linked list.
 * 
 * identifier: dcll_insertbefore
 * params: PDList list - Pointer to the doubly linked list, data_t data - Data to be inserted, data_t e_data - Element before which the data is to be inserted, COMPAREPROC pcompareproc - Pointer to the comparison function.
 * returns: ret_t Returns SUCCESS upon successful insertion. Returns FAILURE if the list is not found, if the list is empty, or if the element before which the data is to be inserted is not found.
 */
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

/**
 * Function: Removes data from the front of a doubly linked list.
 * 
 * identifier: dcll_removefront
 * params: PDList list - Pointer to the doubly linked list.
 * returns: data_t Returns the removed data. Returns NULL if the list is not found or if the list is empty.
 */
extern	data_t	dcll_removefront(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	return(genericremove(list, list->head->next));
}

/**
 * Function: Removes data from the back of a doubly linked list.
 * 
 * identifier: dcll_removeback
 * params: PDList list - Pointer to the doubly linked list.
 * returns: data_t Returns the removed data. Returns NULL if the list is not found or if the list is empty.
 */
extern	data_t	dcll_removeback(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	return(genericremove(list, list->head->prev));
}

/**
 * Function: Removes data at the specified index from a doubly linked list.
 * 
 * identifier: dcll_removeat
 * params: PDList list - Pointer to the doubly linked list, long long index - Index of the data to be removed.
 * returns: data_t Returns the removed data. Returns NULL if the list is not found, if the list is empty, or if the index is out of bounds.
 */
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

/**
 * Function: Removes data after a specific element from a doubly linked list.
 * 
 * identifier: dcll_removeafter
 * params: PDList list - Pointer to the doubly linked list, data_t e_data - Element after which the data is to be removed, COMPAREPROC pcompareproc - Pointer to the comparison function.
 * returns: data_t Returns the removed data. Returns NULL if the list is not found, if the list is empty, or if the element after which the data is to be removed is not found.
 */
extern	data_t 	dcll_removeafter(PDList list, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(genericremove(list, enode->next));
}

/**
 * Function: Removes data before a specific element from a doubly linked list.
 * 
 * identifier: dcll_removebefore
 * params: PDList list - Pointer to the doubly linked list, data_t e_data - Element before which the data is to be removed, COMPAREPROC pcompareproc - Pointer to the comparison function.
 * returns: data_t Returns the removed data. Returns NULL if the list is not found, if the list is empty, or if the element before which the data is to be removed is not found.
 */
extern	data_t	dcll_removebefore(PDList list, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, e_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(genericremove(list, enode->prev));	
}

/**
 * Function: Searches for a specific data in a doubly linked list.
 * 
 * identifier: dcll_search
 * params: PDList list - Pointer to the doubly linked list, data_t s_data - Data to search for, COMPAREPROC pcompareproc - Pointer to the comparison function.
 * returns: data_t Returns the found data. Returns NULL if the list is not found, if the list is empty, or if the data is not found.
 */
extern	data_t	dcll_search(PDList list, data_t s_data, COMPAREPROC pcompareproc)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, NULL);

	p_dnode enode = locatenode(list, s_data, pcompareproc);
	if(NULL == enode)
		return(NULL);

	return(enode->data);
}

/**
 * Function: Retrieves data at the specified index from a doubly linked list.
 * 
 * identifier: dcll_dataat
 * params: PDList list - Pointer to the doubly linked list, long long index - Index of the data to retrieve.
 * returns: data_t Returns the retrieved data. Returns NULL if the list is not found, if the list is empty, or if the index is out of bounds.
 */
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

/**
 * Function: Returns the number of elements in a doubly linked list.
 * 
 * identifier: dcll_size
 * params: PDList list - Pointer to the doubly linked list.
 * returns: size_t Returns the number of elements in the list. Returns 0 if the list is not found or if the list is empty.
 */
extern	size_t	dcll_size(PDList list)
{
	// Code
	LISTCHECKFORERRORS(list, LCFE_LISTNOTFOUND | LCFE_LISTEMPTY, 0);

	return(list->nrelements);
}

/**
 * Function: Retrieves the error description for the last operation performed on a doubly linked list.
 * 
 * identifier: dcll_geterrordescription
 * params: None
 * returns: int Returns an error code describing the last operation. Prints the error description to stdout.
 */
extern	void 	dcll_geterrordescription()
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

/**
 * Function: Destroys a doubly linked list and frees its memory.
 * 
 * identifier: dcll_destroy
 * params: PPDList plist - Pointer to the pointer to the doubly linked list, DELETEDATAPROC pdeletedataproc - Pointer to the function used to delete the data.
 * returns: ret_t Returns SUCCESS upon successful destruction. Returns FAILURE if the list is not found.
 */
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
	runner = runner->next;

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

