/**
 * S.G.M.P
 * @file: rbt.h
 * @brief: Header file for implementation of Red-Black Tree in C
 * 
 * This header file defines the structures and functions for a Red-Black Tree (RBT) implementation in C.
 * It provides operations for creating, inserting, removing, searching, and iterating over elements in the RBT.
 * 
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 10 May 2024 (Friday) 10:20:24 PM
 */

#ifndef	_RBT_H
#define	_RBT_H

#ifndef	DATA_T
#define	DATA_T
typedef	void*	data_t;
#endif	/* DATA_T */

#ifndef	RET_T
#define	RET_T
typedef	int 	ret_t;
#endif	/* RET */

#define	CMP_SAME	1
#define	CMP_LESS	2
#define	CMP_GREAT	3

#define	SUCCESS 0
#define	FAILURE	1

struct Node;
typedef struct Node* PNode;
// typedef struct Node* PPNode;

struct RBT;
typedef	struct RBT*		PRBT;
typedef	struct RBT**	PPRBT;

typedef	struct RBT*		RBTree;

typedef	ret_t(*COMPAREPROC)(data_t, data_t);
typedef	void(*DELETEDATAPROC)(data_t);
typedef	void(*PRINTDATAPROC)(data_t);

#define	RED 	0
#define	BLACK	1

struct Node
{
	data_t	data;
	PNode 	left;
	PNode 	right;
	PNode	parent;
	int 	color;
};
#define	SIZE_TNODE	(sizeof(struct Node))

struct RBT
{
	PNode	root;
	size_t 	nr_elements;
};
#define	SIZE_RBT	(sizeof(struct RBT))

enum ITERATORTYPE
{
	ITR_PREORDER = 1,
	ITR_INORDER,
	ITR_POSTORDER
};

struct Iterator
{
	PNode itr;
	void*	stack;
	int	type;
};
#define	SIZE_ITERATOR	(sizeof(struct Iterator))

typedef	struct Iterator*	PIterator;
typedef	struct Iterator**	PPIterator;

/********** Interface Functions **********/
extern	RBTree create_tree();

extern	ret_t rbt_insert(PRBT tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	rbt_remove(PRBT tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	rbt_search(PRBT tree, data_t data, COMPAREPROC pcompareproc);

extern	PIterator 	rbt_inorder_iterator(PRBT tree);
extern	PIterator 	rbt_preorder_iterator(PRBT tree);
extern	PIterator 	rbt_postorder_iterator(PRBT tree);
extern 	ret_t 	rbt_iterator_end(PIterator itr);

extern	data_t	itr_data(PIterator itr);
extern	PIterator 	itr_next(PIterator itr);
extern	void	destroy_itr(PPIterator pitr);

extern void 	rbt_print(PRBT tree, PRINTDATAPROC pprintdataproc);

extern	void	rbt_destroy(PPRBT ptree, DELETEDATAPROC pdeletedataproc);

#endif /* _RBT_H */
