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

//	DCLL Interface function declarations
extern	PDList 	createlist(void);

//	Interface Functions to insert data in list
extern	ret_t	dcll_insertfront(PDList list, data_t data);
extern	ret_t	dcll_insertback(PDList list, data_t data);
extern 	ret_t	dcll_insertat(PDList list, data_t data, long long index);
extern 	ret_t	dcll_insertafter(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc);
extern	ret_t	dcll_insertbefore(PDList list, data_t data, data_t e_data, COMPAREPROC pcompareproc);

// 	Interface Functions to remove data from list
extern	data_t	dcll_removefront(PDList list);
extern	data_t	dcll_removeback(PDList list);
extern	data_t	dcll_removeat(PDList list, long long index);
extern	data_t 	dcll_removeafter(PDList list, data_t e_data, COMPAREPROC pcompareproc);
extern	data_t	dcll_removebefore(PDList list, data_t e_data, COMPAREPROC pcompareproc);

//	Interface functions for operations of List
extern	data_t	dcll_search(PDList list, data_t s_data, COMPAREPROC pcompareproc);
extern	data_t	dcll_dataat(PDList list, long long index);
extern	size_t	dcll_size(PDList list);

extern	void 	dcll_geterrordescription();

//	Interface function to destroy list
extern	ret_t	dcll_destroy(PPDList plist, DELETEDATAPROC pdeletedataproc);

#endif /* _DCLL_H */

