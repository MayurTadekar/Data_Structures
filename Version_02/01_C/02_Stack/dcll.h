/**
 * S.G.M.P
 * @file: dcll.h
 * @brief: Header file for implementation of Doubly Circular Linked List containing all the interface function declarations and struct definitions
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 April 2024 (Friday) 12:52:57 PM
 */

#ifndef	_DCLL_H
#define	_DCLL_H

#define	SUCCESS 0
#define FAILURE 1

#define	E_NONE				0x00000000
#define E_OUTOFMEMORY		0x00000001
#define	E_LISTEMPTY			0x00000002
#define	E_LISTNOTFOUND		0x00000004
#define	E_INDEXOUTOFBOUND	0x00000008
#define	E_DATANOTFOUND		0x00000010

//	Typedefinitions of Node
struct dnode;
typedef	struct dnode dnode;
typedef struct dnode* p_dnode;
typedef struct dnode** pp_deno;

//	Typedefinitions of DCLL
struct dcll;
typedef struct dcll 	DList;
typedef struct dcll*	PDList;
typedef struct dcll**	PPDList;

typedef	PDList 	List;

//	Typedefinitions for Data Type and Return Type
typedef	void*	data_t;
typedef	int 	ret_t;

//	Node Struct
struct dnode
{
	data_t	data;	//	store data
	p_dnode	next;	//	pointer to next node
	p_dnode	prev;	//	pointer to prev node
};
#define	SIZE_DNODE	sizeof(dnode)	//	size of the node struct

//	DCLL Struct
struct dcll
{
	p_dnode head;	//	pointer to head of list
	size_t	nrelements;	//	no of elements
};
#define	SIZE_DCLL	sizeof(DList)	//	size of list struct

// Typedefinitions of callback functions
typedef		ret_t (*COMPAREPROC)(data_t, data_t);
typedef		void (*DELETEDATAPROC)(data_t);

// DCLL Interface function declarations

/**
 * Function: createlist
 * 
 * Description: Creates and returns a new doubly linked list.
 * 
 * @param None
 * @return PDList Pointer to the newly created doubly linked list.
 */
extern PDList createlist(void);

/**
 * Function: dcll_insertfront
 * 
 * Description: Inserts data at the front of the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t data Data to be inserted.
 * @return ret_t Returns SUCCESS upon successful insertion. Returns FAILURE otherwise.
 */
extern ret_t dcll_insertfront(PDList list, data_t data);

/**
 * Function: dcll_insertback
 * 
 * Description: Inserts data at the back of the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t data Data to be inserted.
 * @return ret_t Returns SUCCESS upon successful insertion. Returns FAILURE otherwise.
 */
extern ret_t dcll_insertback(PDList list, data_t data);

/**
 * Function: dcll_insertat
 * 
 * Description: Inserts data at the specified index in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t data Data to be inserted.
 * @param long long index Index at which the data is to be inserted.
 * @return ret_t Returns SUCCESS upon successful insertion. Returns FAILURE otherwise.
 */
extern ret_t dcll_insertat(PDList list, data_t data, long long index);

/**
 * Function: dcll_insertafter
 * 
 * Description: Inserts data after a specified element in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t data Data to be inserted.
 * @param data_t e_data Element after which the data is to be inserted.
 * @param COMPAREPROC pcompareproc Pointer to the comparison function for locating the element.
 * @return ret_t Returns SUCCESS upon successful insertion.
 */
extern ret_t dcll_insertafter(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc);

/**
 * Function: dcll_insertbefore
 * 
 * Description: Inserts data before a specified element in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t data Data to be inserted.
 * @param data_t e_data Element before which the data is to be inserted.
 * @param COMPAREPROC pcompareproc Pointer to the comparison function for locating the element.
 * @return ret_t Returns SUCCESS upon successful insertion.
 */
extern ret_t dcll_insertbefore(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc);

/**
 * Function: dcll_removefront
 * 
 * Description: Removes the first element from the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @return data_t Returns the removed data.
 */
extern data_t dcll_removefront(PDList list);

/**
 * Function: dcll_removeback
 * 
 * Description: Removes the last element from the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @return data_t Returns the removed data.
 */
extern data_t dcll_removeback(PDList list);

/**
 * Function: dcll_removeat
 * 
 * Description: Removes the element at the specified index from the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param long long index Index of the element to be removed.
 * @return data_t Returns the removed data.
 */
extern data_t dcll_removeat(PDList list, long long index);

/**
 * Function: dcll_removeafter
 * 
 * Description: Removes the element after a specified element from the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t e_data Element after which the element is to be removed.
 * @param COMPAREPROC pcompareproc Pointer to the comparison function for locating the element.
 * @return data_t Returns the removed data.
 */
extern data_t dcll_removeafter(PDList list, data_t e_data, COMPAREPROC pcompareproc);

/**
 * Function: dcll_removebefore
 * 
 * Description: Removes the element before a specified element from the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t e_data Element before which the element is to be removed.
 * @param COMPAREPROC pcompareproc Pointer to the comparison function for locating the element.
 * @return data_t Returns the removed data.
 */
extern data_t dcll_removebefore(PDList list, data_t e_data, COMPAREPROC pcompareproc);

/**
 * Function: dcll_search
 * 
 * Description: Searches for an element in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param data_t s_data Data to be searched for.
 * @param COMPAREPROC pcompareproc Pointer to the comparison function for locating the element.
 * @return data_t Returns the found data.
 */
extern data_t dcll_search(PDList list, data_t s_data, COMPAREPROC pcompareproc);

/**
 * Function: dcll_dataat
 * 
 * Description: Retrieves the data at the specified index in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @param long long index Index of the data to be retrieved.
 * @return data_t Returns the data at the specified index.
 */
extern data_t dcll_dataat(PDList list, long long index);

/**
 * Function: dcll_size
 * 
 * Description: Returns the number of elements in the doubly linked list.
 * 
 * @param PDList list Pointer to the doubly linked list.
 * @return size_t Number of elements in the list.
 */
extern size_t dcll_size(PDList list);

/**
 * Function: dcll_geterrordescription
 * 
 * Description: Prints the description of the last error that occurred during list operations.
 * 
 * @param None
 * @return None
 */
extern void dcll_geterrordescription();

/**
 * Function: dcll_destroy
 * 
 * Description: Destroys the doubly linked list and frees its memory.
 * 
 * @param PPDList plist Pointer to the pointer of the doubly linked list.
 * @param DELETEDATAPROC pdeletedataproc Pointer to the function for deleting list data.
 * @return ret_t Returns SUCCESS upon successful destruction. Returns FAILURE otherwise.
 */
extern ret_t dcll_destroy(PPDList plist, DELETEDATAPROC pdeletedataproc);

#endif /* _DCLL_H */

