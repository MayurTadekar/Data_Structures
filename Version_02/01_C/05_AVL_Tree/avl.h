/**
 * S.G.M.P
 * @file: avl.h
 * @brief: Header file for implementation of AVL Tree in C
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 07 May 2024 (Tuesday) 04:12:11 PM
 */

#ifndef	_avl_H
#define	_avl_H

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

struct AVL;
typedef	struct AVL*		PAVL;
typedef	struct AVL**	PPAVL;

typedef	struct AVL*		AVLTree;

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

struct AVL
{
	PNode	root;
	size_t 	nr_elements;
};
#define	SIZE_AVL	(sizeof(struct AVL))

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
extern	AVLTree create_tree();

extern	ret_t avl_insert(PAVL tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	avl_remove(PAVL tree, data_t data, COMPAREPROC pcompareproc);
extern	data_t	avl_search(PAVL tree, data_t data, COMPAREPROC pcompareproc);

extern	PIterator 	avl_inorder_iterator(PAVL tree);
extern	PIterator 	avl_preorder_iterator(PAVL tree);
extern	PIterator 	avl_postorder_iterator(PAVL tree);
extern 	ret_t 	avl_iterator_end(PIterator itr);

extern	data_t	itr_data(PIterator itr);
extern	PIterator 	itr_next(PIterator itr);
extern	void	destroy_itr(PPIterator pitr);

extern void 	avl_print(PAVL tree, PRINTDATAPROC pprintdataproc);

extern	void	avl_destroy(PPAVL ptree, DELETEDATAPROC pdeletedataproc);

#endif /* _avl_H */
