

#include	<stdio.h>
#include	<stdlib.h>

#include 	"stack.h"

#include	"tree.h"


/*	Tree Auxillary Functions	*/
static 	void* 		Xmalloc(size_t size)
{
	//	Code
	void* ptr = malloc(size);

	if( NULL == ptr )
	{
		fprintf(stdout, "ERROR: Out Of Memory\n");
		exit(FAILURE);
	}

	return(ptr);
}

static 	p_node_t 	tree_create_node(data_t data)
{
	//	Code
	p_node_t pnode = (p_node_t) Xmalloc(SIZE_NODE);

	pnode->data = data;
	pnode->p_left = NULL;
	pnode->p_right = NULL;
	pnode->p_parent = NULL;
	pnode->height = 0;

	return(pnode);
}

static	status_t	tree_check_root(tree_t ptree)
{
	// 	Code
	if( NULL == ptree || NULL == ptree->root )
		return(FAILURE);

	return(SUCCESS);
}

static	size_t 		tree_height(p_node_t pnode)
{
	// 	Code
	if( NULL == pnode )
		return(0);
	else
	{
		size_t left_height = tree_height(pnode->p_left);
		size_t right_height = tree_height(pnode->p_right);

		if( left_height > right_height )
			return(left_height);
		else
			return(right_height);
	}
}

static	status_t 	tree_generic_insert(p_node_t pnode, p_node_t n_node, P_COMPARE_PROC compare_proc)
{
	// 	Variable
	p_node_t walk = pnode;
	status_t is_inserted = FAILURE;

	// 	Code
	while( is_inserted )
	{
		short ret = compare_proc(walk->data, n_node->data);
		if( SAME_DATA == ret )
		{
			fprintf(stdout, "ERROR: Data Already Present\n");
			return(FAILURE);
		}

		if( BIG_DATA == ret )
		{
			if( NULL == walk->p_right )
			{
				walk->p_right = n_node;
				n_node->p_parent = walk;
				is_inserted = SUCCESS;
				continue;
			}
			walk = walk->p_right;
		}
		else
		{
			if( NULL == walk->p_left )
			{
				walk->p_left = n_node;
				n_node->p_parent = walk;
				is_inserted = SUCCESS;
				continue;
			}
			walk = walk->p_left;
		}
	}

	return(SUCCESS);
}

static	data_t 		tree_generic_delete(tree_t ptree, p_node_t pnode)
{
	//	Code
	if( NULL == pnode->p_left )
	{
		tree_transplant(ptree, pnode, pnode->p_right);
	}
	else if( NULL == pnode->p_right )
	{
		tree_transplant(ptree, pnode, pnode->p_left);
	}
	else
	{
		p_node_t successor = tree_successor(pnode);
		if( pnode != successor->p_parent )
		{
			tree_transplant( ptree, successor, successor->p_right );
			successor->p_right = pnode->p_right;
			successor->p_right->p_parent = successor;
		}
		tree_transplant(ptree, pnode, successor);
		successor->p_left = pnode->p_left;
		successor->p_left->p_parent = successor;
	}

	data_t ret_data = pnode->data;
	free(pnode);
	return(ret_data);
}

static	void 		tree_transplant(tree_t ptree, p_node_t pnode, p_node_t t_pnode)
{
	if( NULL == pnode->p_parent )
		ptree->root = t_pnode;
	else if( pnode == pnode->p_parent->p_left )
		pnode->p_parent->p_left = t_pnode;
	else 
		pnode->p_parent->p_right = t_pnode;

	if( NULL != t_pnode )
		t_pnode->p_parent = pnode->p_parent;
}

static 	p_node_t 	tree_find_node(tree_t ptree, data_t s_data, P_COMPARE_PROC compare_proc)
{
	//	Code
	short ret = 0;

	if( FAILURE == tree_check_root(ptree) )
		return(NULL);

	p_node_t walk = ptree->root;

	while( 1 )
	{
		if( NULL == walk )
			return(NULL);

		ret = compare_proc(walk->data, s_data);
		if( SAME_DATA == ret ) 
			return(walk);

		if( BIG_DATA == ret )
		{
			walk = walk->p_right;
		}
		else
		{
			walk = walk->p_left;
		}
	}
}


static	p_node_t 	tree_successor(p_node_t pnode)
{
	//	Code
	p_node_t walk = pnode->p_right;

	if( NULL == walk)
		return(NULL);

	while( NULL != walk->p_left )
		walk = walk->p_left;

	return(walk);
}

static	p_node_t 	tree_predecessor(p_node_t pnode)
{
	//	Code
	p_node_t walk = pnode->p_left;

	if( NULL == walk )
		return(NULL);

	while( NULL != walk->p_right )
		walk = walk->p_right;

	return(walk);
}

static 	void		tree_inorder(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	if( NULL == pnode )
		return;

	tree_inorder(pnode->p_left, show_data_proc);
	show_data_proc(pnode->data);
	fprintf(stdout,"-");
	tree_inorder(pnode->p_right, show_data_proc);
}

static 	void		tree_preorder(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	if( NULL == pnode )
		return;

	show_data_proc(pnode->data);
	fprintf(stdout,"-");
	tree_preorder(pnode->p_left, show_data_proc);
	tree_preorder(pnode->p_right, show_data_proc);
}

static 	void		tree_postorder(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	if( NULL == pnode )
		return;

	tree_postorder(pnode->p_left, show_data_proc);
	tree_postorder(pnode->p_right, show_data_proc);
	show_data_proc(pnode->data);
	fprintf(stdout,"-");
}

static 	void		tree_inorder_non_recursive(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	stack_t stack = create_stack();
	
	if( NULL == pnode )
		return;

	p_node_t run = pnode;
	
	stack_push(stack, run);
	
	while( 0 != stack_size(stack) )
	{
		while( NULL != run )
		{
			run = run->p_left;
			if( NULL == run )
				break;
			stack_push(stack, run);
		}

		run = stack_pop(stack);
		show_data_proc(run->data);
		fprintf(stdout,"-");

		run = run->p_right;
		if( NULL != run )
			stack_push(stack, run);
	}  
}

static 	void		tree_preorder_non_recursive(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_t run = pnode;

	stack_push(stack, run);

	while( 0 != stack_size(stack) )
	{
		while( NULL != run )
		{
			show_data_proc(run->data);
			fprintf(stdout,"-");
			run = run->p_left;
			if( NULL == run )
				break;
			stack_push(stack, run);
		}

		run = stack_pop(stack);
		run = run->p_right;
		if( NULL != run )
			stack_push(stack, run);
	}
}

static 	void		tree_postorder_non_recursive(p_node_t pnode, P_SHOW_DATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_t run = pnode;
	bool_t flag = TRUE;

	// /stack_push(stack, run);

	while( 0 != stack_size(stack) || flag == TRUE)
	{
		flag = FALSE;
		while( NULL != run )
		{
			if( run->p_right )
				stack_push(stack, run->p_right);
			stack_push(stack, run);

			run = run->p_left;
		}

		run = stack_pop(stack);

		if( run && run->p_right == stack_peek(stack) )
		{
			stack_pop(stack);
			stack_push(stack, run);
			
			run = run->p_right;
		}
		else
		{
			show_data_proc(run->data);
			fprintf(stdout,"-");
			run = NULL;
		}
	}
}

static 	void		tree_postorder_destroy(tree_t ptree, p_node_t pnode, P_DELETE_DATA_PROC delete_data_proc)
{
	//	Code
	if( NULL == pnode )
		return;

	tree_postorder_destroy(ptree, pnode->p_left, delete_data_proc);
	tree_postorder_destroy(ptree, pnode->p_right, delete_data_proc);
	delete_data_proc(pnode->data);
	pnode->data = NULL;
	tree_generic_delete(ptree, pnode);
}


/***************************************************************************************/
/*	Tree Interface Functions */
extern	tree_t		tree_create(void)
{
	//	Code
	tree_t ptree = (tree_t) Xmalloc(SIZE_dummy_tree);

	ptree->root = NULL;

	return(ptree);
}

extern	status_t	tree_insert(tree_t ptree, data_t data, P_COMPARE_PROC compare_proc)
{
	//	Code
	if( NULL == ptree	|| 
		NULL == compare_proc)
		return(FAILURE);

	p_node_t n_node = tree_create_node(data);

	if( NULL == ptree->root )
	{
		ptree->root = n_node;
		return(SUCCESS);
	}

	return( tree_generic_insert(ptree->root, n_node, compare_proc) );

}

extern	data_t		tree_delete(tree_t ptree, data_t data, P_COMPARE_PROC compare_proc)
{
	//	Code
	if( FAILURE == tree_check_root(ptree) ||
		NULL == compare_proc)
	{
		return(NULL);
	}

	p_node_t del_node = tree_find_node(ptree, data, compare_proc);
	if( NULL == del_node )
		return(NULL);

	return( tree_generic_delete(ptree, del_node) );
}

extern	void		tree_in_order_traversal(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_inorder(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_pre_order_traversal(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_preorder(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_post_order_traversal(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_postorder(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_in_order_traversal_non_recursive(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_inorder_non_recursive(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_pre_order_traversal_non_recursive(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_preorder_non_recursive(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_post_order_traversal_non_recursive(tree_t ptree, P_SHOW_DATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_postorder_non_recursive(ptree->root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	data_t		tree_search(tree_t ptree, data_t s_data, P_COMPARE_PROC compare_proc)
{
	//	Code

	p_node_t pnode = tree_find_node(ptree, s_data, compare_proc);

	if( NULL == pnode)
		return(NULL);

	return(pnode->data);
}

extern	data_t 		tree_get_successor(tree_t ptree, data_t data, P_COMPARE_PROC compare_proc)
{
	//	Code
	if( FAILURE == tree_check_root(ptree) )
		return(NULL);

	p_node_t pnode = tree_find_node(ptree, data, compare_proc);
	if( NULL == pnode )
		return(NULL);

	return( tree_successor(pnode)->data );
}

extern	data_t 		tree_get_predecessor(tree_t ptree, data_t data, P_COMPARE_PROC compare_proc)
{
	//	Code
	if( FAILURE == tree_check_root(ptree) )
		return(NULL);

	p_node_t pnode = tree_find_node(ptree, data, compare_proc);
	if( NULL == pnode )
		return(NULL);

	return( tree_predecessor(pnode)->data );
}

extern 	status_t	tree_destroy(tree_t* pptree, P_DELETE_DATA_PROC delete_data_proc)
{
	if( FAILURE == tree_check_root( *pptree ) ||
		NULL == delete_data_proc)
		return(FAILURE);

	fprintf(stdout, "\nDelete Data:\n");
	tree_postorder_destroy( *pptree, (*pptree)->root, delete_data_proc);

	free(*pptree);
	*pptree = NULL;
}
