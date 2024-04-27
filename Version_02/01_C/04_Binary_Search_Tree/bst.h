/**
 * S.G.M.P
 * @file: bst.h
 * @brief: Header file for implementation of Binary Search Tree in C
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 27 April 2024 (Saturday) 03:10:03 PM
 */

#ifndef	_BST_H
#define	_BST_H

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

struct BST;
typedef	struct BST*		PBST;
typedef	struct BST**	PPBST;

typedef	struct BST*		BinarySearchTree;

typedef	ret_t(*COMPAREPROC)(data_t, data_t);
typedef	void(*DELETEDATAPROC)(data_t);
typedef	void(*PRINTDATAPROC)(data_t);

struct Node
{
	data_t	data;
	PNode 	left;
	PNode 	right;
	PNode	parent;
};
#define	SIZE_TNODE	(sizeof(struct Node))

struct BST
{
	PNode	root;
	size_t 	nr_elements;
};
#define	SIZE_BST	(sizeof(struct BST))

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
extern	BinarySearchTree create_tree();

extern	ret_t bst_insert(PBST tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	bst_remove(PBST tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	bst_search(PBST tree, data_t data, COMPAREPROC pcompareproc);

extern	PIterator 	bst_inorder_iterator(PBST tree);
extern	PIterator 	bst_preorder_iterator(PBST tree);
extern	PIterator 	bst_postorder_iterator(PBST tree);
extern 	ret_t 	bst_iterator_end(PIterator itr);

extern	data_t	itr_data(PIterator itr);
extern	PIterator 	itr_next(PIterator itr);
extern	void	destroy_itr(PPIterator pitr);

extern void 	bst_print(PBST tree, PRINTDATAPROC pprintdataproc);

extern	void	bst_destroy(PPBST ptree, DELETEDATAPROC pdeletedataproc);

#endif /* _BST_H */
