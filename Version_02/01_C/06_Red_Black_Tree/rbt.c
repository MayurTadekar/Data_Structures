/**
 * S.G.M.P
 * @file: avl.c
 * @brief: Implementation of AVL Tree (AVLTree) operations in C.
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 10 May 2024 (Friday) 10:35:41 PM
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "rbt.h"
#include "stack.h"

/******************************************************\ 
 *					Helper Functions 
\******************************************************/

/**
 * @brief Allocates memory dynamically.
 * @details Allocates memory dynamically for a given number of bytes.
 * @param nr_bytes Number of bytes to allocate.
 * @return A pointer to the allocated memory if successful, otherwise NULL.
 */
static void* xmalloc(size_t nr_bytes)
{
	// Code
	void* p = malloc(nr_bytes);
	if(NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		return(NULL);
	}
	return(p);
}

/**
 * @brief Creates a new node for the BST.
 * @details Allocates memory for a new BST node and initializes its fields.
 * @param data The data to be stored in the node.
 * @return A pointer to the newly created node if successful, otherwise NULL.
 */
static PNode create_node(data_t data)
{
	// Code
	PNode node = xmalloc(SIZE_TNODE);

	if(NULL == node)
		return(NULL);

	node->data = data;
	node->left = node->right = node->parent = NULL;
	node->color = RED;

	return(node);
}

/**
 * @brief Locates a node in the BST.
 * @details Searches for a node with the specified data in the BST.
 * @param tree Pointer to the BST.
 * @param e_data The data to search for.
 * @param pcompareproc Pointer to the comparison function.
 * @return A pointer to the located node if found, otherwise NULL.
 */
static PNode locate_node(PRBT tree, data_t e_data, COMPAREPROC pcompareproc)
{
	// Code
	PNode runner = tree->root;

	while(1)
	{
		int status = pcompareproc(runner->data, e_data);
		if(CMP_SAME == status)
		{
			return(runner);
		}

		if(CMP_LESS == status)
			runner = runner->left;
		else 
			runner = runner->right;

		if(NULL == runner)
			return(runner);
	}

	return(NULL);
}

/**
 * @brief Finds the minimum node in a subtree.
 * @details Traverses left recursively to find the minimum node in a subtree.
 * @param node Root of the subtree.
 * @return A pointer to the minimum node.
 */
static PNode minimum(PNode node)
{
	// Code
	while(node->left)
	{
		node = node->left;
	}
	return(node);
}

/**
 * @brief Finds the maximum node in a subtree.
 * @details Traverses right recursively to find the maximum node in a subtree.
 * @param node Root of the subtree.
 * @return A pointer to the maximum node.
 */
static PNode maximum(PNode node)
{
	// Code
	while(node->right)
	{
		node = node->right;
	}
	return(node);
}

/**
 * @brief Finds the successor node of a given node.
 * @details Finds the node with the smallest data greater than the given node's data.
 * @param node Pointer to the given node.
 * @return A pointer to the successor node.
 */
static PNode successor(PNode node)
{
	// Code
	PNode succ = NULL;
	if(node->right)
		return(minimum(node->right));
	succ = node->parent;

	while(NULL != succ && succ->right == node)
	{
		node = succ;
		succ = node->parent;
	}

	return(succ);
}

/**
 * @brief Finds the predecessor node of a given node.
 * @details Finds the node with the largest data smaller than the given node's data.
 * @param node Pointer to the given node.
 * @return A pointer to the predecessor node.
 */
static PNode predecessor(PNode node)
{
	// Code
	PNode pred = NULL;
	if(node->left)
		return(maximum(node->left));
	pred = node->parent;
	while(NULL != pred && pred->left == node)
	{
		node = pred;
		pred = node->parent;
	}
	return(pred);
}

/**
 * @brief Performs a left rotation on the subtree rooted at the given node.
 * @details This function performs a left rotation to balance the subtree by adjusting the pointers appropriately. It restructures the subtree to ensure that the left child becomes the new root, and the original root becomes the right child of the new root.
 * @param node The root node of the subtree where left rotation is performed.
 * @return The new root node after left rotation.
 */
static PNode left_rotate(PNode node)
{
	// Code
	PNode right = node->right;

	node->right = right->left;
	if(node->right)
	{
		node->right->parent = node;
	}
	right->left = node;

	right->parent = node->parent;
	if(node->parent)
	{
		if(node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
	}
	node->parent = right;

	return(right);
}

/**
 * @brief Performs a right rotation on the subtree rooted at the given node.
 * @details This function performs a right rotation to balance the subtree by adjusting the pointers appropriately. It restructures the subtree to ensure that the right child becomes the new root, and the original root becomes the left child of the new root.
 * @param node The root node of the subtree where right rotation is performed.
 * @return The new root node after right rotation.
 */
static PNode right_rotate(PNode node)
{
	// Code
	PNode left = node->left;

	node->left = left->right;
	if(node->left)
	{
		node->left->parent = node;
	}
	left->right = node;

	left->parent = node->parent;
	if(node->parent)
	{
		if(node == node->parent->left)
			node->parent->left = left;
		else 
			node->parent->right = left;
	}
	node->parent = left;

	return(left);
}

/**
 * @brief Fixes Red-Black Tree violations after node insertion.
 *
 * This function corrects any Red-Black Tree violations that may arise after inserting a node into the tree.
 * It ensures that the Red-Black Tree properties are maintained, including maintaining the red-black color invariant
 * and balancing the tree.
 *
 * @param tree Pointer to the Red-Black Tree structure.
 * @param node Pointer to the newly inserted node, which may violate Red-Black Tree properties.
 */
void insert_fixup(PRBT tree, PNode node)
{
	// Code
	while(	node->parent	&&
			RED == node->parent->color &&
			node->parent->parent)
	{
		PNode uncle;
		if(node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;

			if(uncle && RED == uncle->color)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if(node == node->parent->right)
				{
					node = node->parent;
					left_rotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = right_rotate(node->parent->parent);
			}
		}
		else
		{
			uncle = node->parent->parent->left;

			if(uncle && RED == uncle->color)
			{
				node->parent->color = BLACK;
				node->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if(node == node->parent->left)
				{
					node = node->parent;
					right_rotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = left_rotate(node->parent->parent);
			}
		}
	}

	if(!node->parent)
	{
		tree->root = node;
	}
	tree->root->color = BLACK;
}

/**
 * @brief Fixes Red-Black Tree violations after node deletion.
 *
 * This function corrects any Red-Black Tree violations that may arise after deleting a node from the tree.
 * It ensures that the Red-Black Tree properties are maintained, including maintaining the red-black color invariant
 * and balancing the tree.
 *
 * @param tree Pointer to the Red-Black Tree structure.
 * @param node Pointer to the node that may violate Red-Black Tree properties after deletion.
 */
void delete_fixup(PRBT tree, PNode node)
{
	// Code
	while(node->parent && BLACK == node->color)
	{
		// Code
		if(node == node->parent->left)
		{
			PNode sib = node->parent->right;

			if(sib && RED == sib->color)
			{
				sib->color = BLACK;
				node->parent->color = RED;
				left_rotate(node->parent);
				sib = node->parent->right;
			}
			else if(sib	&&
					(NULL == sib->left || BLACK == sib->left->color)	&&
					(NULL == sib->right || BLACK == sib->right->color)	)
			{
				sib->color = RED;
				node = node->parent;
			}
			else
			{
				if(NULL == sib->right || BLACK == sib->right->color)
				{
					sib->left->color = BLACK;
					sib->color = RED;
					right_rotate(sib);
					sib = node->parent->right;
				}

				sib->color = node->parent->color;
				node->parent->color = BLACK;
				sib->right->color = BLACK;
				left_rotate(node->parent);
				node = tree->root;
			}
		}
		else
		{
			PNode sib = node->parent->left;

			if(sib && RED == sib->color)
			{
				sib->color = BLACK;
				node->parent->color = RED;
				right_rotate(node->parent);
				sib = node->parent->left;
			}
			else if(sib	&&
					(NULL == sib->left || BLACK == sib->left->color)	&&
					(NULL == sib->right || BLACK == sib->right->color)	)
			{
				sib->color = RED;
				node = node->parent;
			}
			else
			{
				if(NULL == sib->left || BLACK == sib->left->color)
				{
					sib->right->color = BLACK;
					sib->color = RED;
					left_rotate(sib);
					sib = node->parent->left;
				}
				sib->color = node->parent->color;
				node->parent->color = BLACK;
				sib->left->color = BLACK;
				right_rotate(node->parent);
				node = tree->root;
			}
		}
	}

	node->color = BLACK;
}

/********************************************************\ 
 * 														*
 *					Interface Functions 				*
 *  													*
\********************************************************/

/**
 * @brief Creates a new empty AVL Tree (BST).
 * @details Allocates memory for a new BST structure, initializes it with root as NULL,
 * and sets the number of elements to zero.
 * @return A pointer to the newly created BST.
 */
extern	RBTree create_tree()
{
	// Code
	RBTree tree = xmalloc(SIZE_RBT);
	tree->root = NULL;
	tree->nr_elements = 0;

	return(tree);
}

/**
 * @brief Inserts a new node with the specified data into the BST.
 * @details Inserts a new node with the specified data into the appropriate position in the BST.
 * If the tree is empty, the new node becomes the root.
 * @param tree Pointer to the BST.
 * @param data The data to insert.
 * @param pcompareproc Pointer to the comparison function.
 * @return SUCCESS if insertion is successful, otherwise FAILURE.
 */
extern	ret_t	rbt_insert(PRBT tree, data_t data, COMPAREPROC pcompareproc)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: Tree not found\n");
		return(FAILURE);
	}

	if(NULL == tree->root)
	{
		tree->root = create_node(data);
	}
	else
	{
		PNode runner = tree->root;
		while(1)
		{
			int status = pcompareproc(data, runner->data);

			if(CMP_SAME == status)
			{
				fprintf(stderr, "ERROR: data already present\n");
				return(FAILURE);
			}
			else if(CMP_LESS == status)
			{
				if(runner->left)
					runner = runner->left;
				else
				{
					runner->left = create_node(data);
					runner->left->parent = runner;
					insert_fixup(tree, runner->left);
					break;
				}
			}
			else
			{
				if(runner->right)
					runner = runner->right;
				else
				{
					runner->right = create_node(data);
					runner->right->parent = runner;
					insert_fixup(tree, runner->right);
					break;
				}
			}
		}
	}

	tree->nr_elements++;
	return(SUCCESS);
}

/**
 * @brief Removes a node with the specified data from the BST.
 * @details Removes a node with the specified data from the BST if it exists.
 * @param tree Pointer to the BST.
 * @param data The data to remove.
 * @param pcompareproc Pointer to the comparison function.
 * @return The removed data if successful, otherwise 0.
 */
extern	data_t	rbt_remove(PRBT tree, data_t data, COMPAREPROC pcompareproc)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: tree not found\n");
		return((data_t)0);
	}

	if(NULL == tree->root)
	{
		fprintf(stderr, "ERROR: tree empty\n");
		return((data_t)0);
	}

	PNode node = locate_node(tree, data, pcompareproc);

	if(NULL == node)
	{
		fprintf(stderr, "ERROR: Data not found\n");
		return((data_t)0);
	}

	data_t to_return_data = node->data;

	while(1)
	{
		if(node->right)
		{
			PNode succ = minimum(node->right);
			node->data = succ->data;
			node = succ;
		}
		else if(node->left)
		{
			PNode pred = maximum(node->left);
			node->data = pred->data;
			node = pred;
		}
		else
		{
			if(NULL == node->parent)
			{
				tree->root = NULL;
			}
			else if(node == node->parent->left)
			{
				node->parent->left = NULL;
			}
			else
			{
				node->parent->right = NULL;
			}
			break;
		}
	}
	delete_fixup(tree, node);
	free(node);
	tree->nr_elements--;
	return(to_return_data);
}

/**
 * @brief Searches for a node with the specified data in the BST.
 * @details Searches for a node with the specified data in the BST.
 * @param tree Pointer to the BST.
 * @param data The data to search for.
 * @param pcompareproc Pointer to the comparison function.
 * @return The data if found, otherwise 0.
 */
extern	data_t	rbt_search(PRBT tree, data_t data, COMPAREPROC pcompareproc)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: tree not found\n");
		return((data_t)0);
	}

	if(NULL == tree->root)
	{
		fprintf(stderr, "ERROR: tree empty\n");
		return((data_t)0);
	}

	PNode node = locate_node(tree, data, pcompareproc);

	if(NULL == node)
	{
		fprintf(stderr, "ERROR: Data not found\n");
		return((data_t)0);
	}

	return(node->data);
}

/**
 * @brief Creates an inorder iterator for the BST.
 * @details Creates an iterator that traverses the BST in inorder.
 * @param tree Pointer to the BST.
 * @return A pointer to the created iterator.
 */
extern	PIterator 	rbt_inorder_iterator(PRBT tree)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: tree not found\n");
		return((data_t)0);
	}

	if(NULL == tree->root)
	{
		fprintf(stderr, "ERROR: tree empty\n");
		return((data_t)0);
	}

	PIterator itr = xmalloc(SIZE_ITERATOR);

	itr->type = ITR_INORDER;
	itr->stack = create_stack();
	itr->itr = tree->root;

	while(1)
	{
		if(itr->itr->left)
		{
			stack_push(itr->stack, itr->itr);
			itr->itr = itr->itr->left;
		}
		else
			break;
	}

	return(itr);
}

/**
 * @brief Creates a preorder iterator for the BST.
 * @details Creates an iterator that traverses the BST in preorder.
 * @param tree Pointer to the BST.
 * @return A pointer to the created iterator.
 */
extern	PIterator 	rbt_preorder_iterator(PRBT tree)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: tree not found\n");
		return((data_t)0);
	}

	if(NULL == tree->root)
	{
		fprintf(stderr, "ERROR: tree empty\n");
		return((data_t)0);
	}

	PIterator itr = xmalloc(SIZE_ITERATOR);

	itr->type = ITR_PREORDER;
	itr->stack = create_stack();
	itr->itr = tree->root;

	stack_push(itr->stack, itr->itr);

	return(itr);
}

/**
 * @brief Creates a postorder iterator for the BST.
 * @details Creates an iterator that traverses the BST in postorder.
 * @param tree Pointer to the BST.
 * @return A pointer to the created iterator.
 */
extern	PIterator 	rbt_postorder_iterator(PRBT tree)
{
	// Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: tree not found\n");
		return((data_t)0);
	}

	if(NULL == tree->root)
	{
		fprintf(stderr, "ERROR: tree empty\n");
		return((data_t)0);
	}

	PIterator itr = xmalloc(SIZE_ITERATOR);

	itr->type = ITR_POSTORDER;
	itr->stack = create_stack();
	itr->itr = tree->root;

	stack_push(itr->stack, itr->itr);

	while(1)
	{
		while(itr->itr->left)
		{
			itr->itr = itr->itr->left;
			stack_push(itr->stack, itr->itr);
		}

		if(itr->itr->right)
		{
			itr->itr = itr->itr->right;
			stack_push(itr->stack, itr->itr);
		}

		if(!itr->itr->left && !itr->itr->right)
			break;
	}

	return(itr);
}

/**
 * @brief Checks if the iterator has reached the end of traversal.
 * @details Checks if the iterator has reached the end of traversal.
 * @param itr Pointer to the iterator.
 * @return 1 if the iterator has reached the end, otherwise 0.
 */
extern 	ret_t 	rbt_iterator_end(PIterator itr)
{
	// Code
	return(itr->itr == NULL);
}

/**
 * @brief Retrieves the data of the current iterator position.
 * @details Retrieves the data of the current iterator position.
 * @param itr Pointer to the iterator.
 * @return The data at the current iterator position.
 */
extern	data_t	itr_data(PIterator itr)
{
	// Code
	return(itr->itr->data);
}

/**
 * @brief Moves the iterator to the next position.
 * @details Moves the iterator to the next position according to the traversal order.
 * @param itr Pointer to the iterator.
 * @return A pointer to the updated iterator.
 */
extern	PIterator 	itr_next(PIterator itr)
{
	// Code
	if(NULL == itr->itr)
	{
		return(itr);
	}

	switch(itr->type)
	{
		case ITR_INORDER:
			if(itr->itr->right)
			{
				itr->itr = itr->itr->right;
				while(itr->itr->left)
				{
					stack_push(itr->stack, itr->itr);
					itr->itr = itr->itr->left;
				}
			}
			else if(stack_size(itr->stack))
			{
				itr->itr = stack_pop(itr->stack);
			}
			else
			{
				itr->itr = NULL;
				stack_destroy(&(itr->stack), NULL);
			}
			return(itr);

		case ITR_PREORDER:

			if(itr->itr->left)
			{
				itr->itr = itr->itr->left;
				stack_push(itr->stack, itr->itr);
			}
			else
			{
				if(stack_peek(itr->stack) == itr->itr)
				{
					stack_pop(itr->stack);
				}

				while(!(itr->itr->right))
				{
					itr->itr = stack_pop(itr->stack);
					if(NULL == itr->itr)
						return(itr);
				}
				itr->itr = itr->itr->right;
				stack_push(itr->stack, itr->itr);
			}
			return(itr);

		case ITR_POSTORDER:

			if(NULL == stack_peek(itr->stack))
			{
				itr->itr = NULL;
				free(itr->stack);
				itr->stack = NULL;
				return(itr);
			}

			if( itr->itr == stack_peek(itr->stack) )
				stack_pop(itr->stack);

			if( itr->itr == ((PNode)stack_peek(itr->stack))->right)
			{
				itr->itr = stack_pop(itr->stack);
				return(itr);
			}
			else
			{
				itr->itr = stack_peek(itr->stack);
			}

			if( itr->itr->right )
			{
				itr->itr = itr->itr->right;
				stack_push(itr->stack, itr->itr);

				while(1)
				{
					while(itr->itr->left)
					{
						itr->itr = itr->itr->left;
						stack_push(itr->stack, itr->itr);
					}

					if(itr->itr->right)
					{
						itr->itr = itr->itr->right;
						stack_push(itr->stack, itr->itr);
					}

					if(!itr->itr->left && !itr->itr->right)
						break;
				}
			}
			return(itr);

		default:
			return(itr);
	}
}

/**
 * @brief Destroys the iterator and frees memory.
 * @details Destroys the iterator and frees the memory allocated for it.
 * @param pitr Pointer to the iterator pointer.
 */
extern	void	destroy_itr(PPIterator pitr)
{
	// Code
	(*pitr)->itr = NULL;


	if((*pitr)->stack)
	{
		free((*pitr)->stack);
	}

	free(*pitr);
	*pitr = NULL;
}

/**
 * @brief Recursively destroys a BST node and its descendants.
 * @details Recursively destroys a BST node and its descendants. Optionally applies a deletion
 * function to the data stored in each node before freeing memory.
 * @param node Pointer to the node to destroy.
 * @param pdeletedataproc Pointer to the function for deleting data (optional).
 */
static 	void	rbt_destroy_node(PNode node, DELETEDATAPROC pdeletedataproc)
{
	// Code
	if(node->left)
		rbt_destroy_node(node->left, pdeletedataproc);

	if(node->right)
		rbt_destroy_node(node->right, pdeletedataproc);

	if(pdeletedataproc)
		pdeletedataproc(node->data);
	free(node);
	node = NULL;
}

/**
 * @brief Destroys the entire BST.
 * @details Destroys the entire BST by recursively destroying each node and its descendants.
 * Optionally applies a deletion function to the data stored in each node before freeing memory.
 * @param ptree Pointer to the pointer to the BST.
 * @param pdeletedataproc Pointer to the function for deleting data (optional).
 */
extern	void	rbt_destroy(PPRBT ptree, DELETEDATAPROC pdeletedataproc)
{
	// Code
	rbt_destroy_node((*ptree)->root, pdeletedataproc);

	free(*ptree);
	*ptree = NULL;
}
