

#include    <stdio.h>
#include    <stdlib.h>
#include    <assert.h>

#include    "stack.h"

#include    "avl.h"

#define     MAX_HEIGHT( a, b)   ( a > b ? a : b )

//  TREE AUXILLARY FUNCTIONS
void*   Xcalloc(size_t no_elements, size_t size_per_element)
{
    void* p = calloc(no_elements, size_per_element);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }

    return(p);
}

static  void    tree_left_rotate(tree_t ptree, p_node_tree_t pnode_tree)
{
    p_node_tree_t    right = pnode_tree->pright;

    right->parent = pnode_tree->parent;
    if( NULL == pnode_tree->parent )
        ptree->p_root = right;
    else if( pnode_tree->parent->pleft == pnode_tree )
        pnode_tree->parent->pleft = right;
    else 
        pnode_tree->parent->pright = right;

    pnode_tree->pright = right->pleft;
    if( pnode_tree->pright ) 
        pnode_tree->pright->parent = pnode_tree;

    right->pleft = pnode_tree;
    pnode_tree->parent = right;
}

static  void    tree_right_rotate(tree_t ptree, p_node_tree_t pnode_tree)
{
    p_node_tree_t    left =  pnode_tree->pleft;

    left->parent = pnode_tree->parent;
    if( NULL == left->parent )
        ptree->p_root = left;
    else if( pnode_tree->parent->pright )
        pnode_tree->parent->pright = left;
    else
        pnode_tree->parent->pleft = left;
    
    pnode_tree->pleft = left->pright;
    if( pnode_tree->pleft )
        pnode_tree->pleft->parent = pnode_tree;
    
    left->pright = pnode_tree;
    pnode_tree->parent = left;
}

static  p_node_tree_t tree_successor(p_node_tree_t pnode_tree)
{
    p_node_tree_t prun = pnode_tree->pright;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pleft )
        prun = prun->pleft;

    return(prun);
}

static  p_node_tree_t tree_predecessor(p_node_tree_t pnode_tree)
{
    p_node_tree_t prun = pnode_tree->pleft;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pright)
        prun = prun->pright;

    return(prun);
}

static  void    tree_transplant(tree_t ptree, p_node_tree_t pnode_tree, p_node_tree_t tranp)
{
    if( NULL == pnode_tree->parent )
        ptree->p_root = tranp;
    else if( pnode_tree->parent->pleft == pnode_tree )
        pnode_tree->parent->pleft = tranp;
    else
        pnode_tree->parent->pright = tranp;
    
    if( tranp )
        tranp->parent = pnode_tree->parent;
}

static  size_t  tree_get_height_node_tree(p_node_tree_t pnode_tree)
{
    if( NULL == pnode_tree )
        return(0);

    return( MAX_HEIGHT( 
                        tree_get_height_node_tree(pnode_tree->pleft), 
                        tree_get_height_node_tree(pnode_tree->pright) 
                        ) + 1 
            );
}

static  p_node_tree_t tree_get_next_imbalanced_node_tree(p_node_tree_t pnode_tree)
{
    p_node_tree_t u;
    long balance = 0;
    u = pnode_tree;
    while( u != NULL )
    {
        balance = tree_get_balance(u);
        if( balance < -1 || balance > 1 )
            break;
        u = u->parent;
    }
    return(u);
}

static  p_node_tree_t tree_get_max_node_tree(p_node_tree_t pnode_tree)
{
    p_node_tree_t prun = pnode_tree;
    
    if( NULL == prun )
        return(prun);

    while( NULL != prun->pright )
        prun = prun->pright;
    
    return(prun);
}

static  p_node_tree_t tree_get_min_node_tree(p_node_tree_t pnode_tree)
{
    p_node_tree_t prun = pnode_tree;
    
    if( NULL == prun )
        return(prun);

    while( NULL != prun->pleft )
        prun = prun->pleft;
    
    return(prun);
}

static  void    tree_inorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode_tree )
        return;

    tree_inorder_run(pnode_tree->pleft, p_showdata_proc);

    p_showdata_proc(pnode_tree->data);

    tree_inorder_run(pnode_tree->pright, p_showdata_proc);
}

static  void    tree_preorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode_tree )
        return;

    p_showdata_proc(pnode_tree->data);
    if( pnode_tree->parent )
        printf("/%d", (int)(long long)pnode_tree->parent->data);

    tree_preorder_run(pnode_tree->pleft, p_showdata_proc);

    tree_preorder_run(pnode_tree->pright, p_showdata_proc);
}

static  void    tree_postorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode_tree )
        return;

    tree_postorder_run(pnode_tree->pleft, p_showdata_proc);

    tree_postorder_run(pnode_tree->pright, p_showdata_proc);

    p_showdata_proc(pnode_tree->data);
}


static 	void		tree_inorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();
	
	if( NULL == pnode_tree )
		return;

	p_node_tree_t run = pnode_tree;
	
	stack_push(stack, run);
	
	while( 0 != stack_size(stack) )
	{
		while( NULL != run )
		{
			run = run->pleft;
			if( NULL == run )
				break;
			stack_push(stack, run);
		}

		run = stack_pop(stack);
		show_data_proc(run->data);
		fprintf(stdout,"-");

		run = run->pright;
		if( NULL != run )
			stack_push(stack, run);
	}  
}

static 	void		tree_preorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_tree_t run = pnode_tree;

	stack_push(stack, run);

	while( 0 != stack_size(stack) )
	{
		while( NULL != run )
		{
			show_data_proc(run->data);
			fprintf(stdout,"-");
			run = run->pleft;
			if( NULL == run )
				break;
			stack_push(stack, run);
		}

		run = stack_pop(stack);
		run = run->pright;
		if( NULL != run )
			stack_push(stack, run);
	}
}

static 	void		tree_postorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_tree_t run = pnode_tree;
	bool_t flag = TRUE;

	// /stack_push(stack, run);

	while( 0 != stack_size(stack) || flag == TRUE)
	{
		flag = FALSE;
		while( NULL != run )
		{
			if( run->pright )
				stack_push(stack, run->pright);
			stack_push(stack, run);

			run = run->pleft;
		}

		run = stack_pop(stack);

		if( run && run->pright == stack_peek(stack) )
		{
			stack_pop(stack);
			stack_push(stack, run);
			
			run = run->pright;
		}
		else
		{
			show_data_proc(run->data);
			fprintf(stdout,"-");
			run = NULL;
		}
	}
}

static  int     tree_get_balance(p_node_tree_t p_node_tree)
{
    return( tree_get_height_node_tree(p_node_tree->pleft) - tree_get_height_node_tree(p_node_tree->pright) );
}

static  p_node_tree_t tree_create_node_tree(data_t new_data)
{
    p_node_tree_t p = (p_node_tree_t)Xcalloc(1, SIZE_node_tree);
    p->data = new_data;
    p->pleft = p->pright = p->parent = NULL;
}

//  TREE INTERFACE FUNCTIONS
extern  tree_t  create_tree(void)
{
    tree_t ptree = Xcalloc(1, SIZE_DUMMY);
    ptree->p_root = NULL;
    ptree->no_of_elements = 0;
    return(ptree);
} 

extern  status_t    tree_insert(tree_t ptree, data_t new_data, COMPARE_PROC p_compare_proc)
{
    //  Code
    if( NULL == ptree )
        return(TREE_EMPTY);

    //p_node_tree_t new_node_tree = tree_create_node_tree(new_data);
    
    if( NULL == ptree->p_root )
    {
        ptree->p_root = tree_create_node_tree(new_data);
        ptree->no_of_elements++;
        return(SUCCESS);
    }

    p_node_tree_t pnode_tree = ptree->p_root;
    p_node_tree_t new_node_tree = tree_create_node_tree(new_data);

    while(1)
    {
        if( SUCCESS == p_compare_proc(pnode_tree->data, new_data) )
        {
            if( NULL == pnode_tree->pleft )
            {
                pnode_tree->pleft = new_node_tree;
                new_node_tree->parent = pnode_tree;
                break;
            }
            pnode_tree = pnode_tree->pleft;
        }
        else
        {
            if( NULL == pnode_tree->pright )
            {
                pnode_tree->pright = new_node_tree;
                new_node_tree->parent = pnode_tree;
                break;
            }
            pnode_tree = pnode_tree->pright;
        }
    }
    ptree->no_of_elements++;

    p_node_tree_t p = pnode_tree;
    p_node_tree_t gp = NULL; 
    if( p )
        gp = p->parent;

    while( gp != NULL )
    {
        int balance = tree_get_balance(gp);
        if( balance < -1 || balance > 1 )
            break;
        gp = gp->parent;
        p = p->parent;
        new_node_tree = new_node_tree->parent;
    }

    if( NULL == gp )
        return(SUCCESS);


    if( new_node_tree == p->pleft && p == gp->pleft )
    {
        tree_right_rotate(ptree, gp);
    }
    else if( new_node_tree == p->pleft && p == gp->pright )
    {
        tree_right_rotate(ptree, p);
        tree_left_rotate(ptree, gp);
    }
    else if( new_node_tree == p->pright && p == gp->pleft )
    {
        tree_left_rotate(ptree, p);
        tree_right_rotate(ptree, gp);
    }
    else
    {
        tree_left_rotate(ptree, gp);
    }
    return(SUCCESS);
}

extern  data_t      tree_remove(tree_t ptree, data_t rem_data, COMPARE_PROC p_compare_proc)
{
    if( NULL == ptree ||
        NULL == ptree->p_root)
        return(NULL);

    p_node_tree_t pnode_tree = ptree->p_root;
    p_node_tree_t rnode_tree = NULL;
    data_t ret_data = NULL;

    p_node_tree_t successor;

    while(1)
    {
        if( NULL == pnode_tree )
            return(NULL);

        status_t ret = p_compare_proc(pnode_tree->data, rem_data);

        if( SAME_DATA == ret )
        {
            ret_data = pnode_tree->data;
            successor = tree_successor(pnode_tree);
            rnode_tree = pnode_tree;
            if( NULL != successor )
            {
                pnode_tree->data = successor->data;
                pnode_tree = successor;
            }
            break;
        }
        if( BIG_DATA == ret )
        {
            pnode_tree = pnode_tree->pleft;
        } 
        else 
        {
            pnode_tree = pnode_tree->pright;
        }
    }

    p_node_tree_t parent = pnode_tree->parent;
    
    if( NULL != successor )
    {
        if( NULL != parent )
        {
            if( pnode_tree->parent->pright == pnode_tree )
                pnode_tree->parent->pright = pnode_tree->pright;
            else
                pnode_tree->parent->pleft = pnode_tree->pright;
        }

        if( NULL != pnode_tree->pright )
            pnode_tree->pright->parent = parent;
    }
    else
    {
        if( NULL != parent )
        {
            if( pnode_tree->parent->pright == pnode_tree )
                pnode_tree->parent->pright = pnode_tree->pleft;
            else
                pnode_tree->parent->pleft = pnode_tree->pleft;
        }

        if( NULL != pnode_tree->pleft )
            pnode_tree->pleft->parent = parent;
    }

    if( NULL == pnode_tree->parent )
        ptree->p_root = NULL;
    
    p_node_tree_t c = NULL;
    p_node_tree_t gc = NULL;

    while( NULL != ( rnode_tree = tree_get_next_imbalanced_node_tree(rnode_tree)) )
    {

        if( tree_get_height_node_tree(rnode_tree->pleft) > tree_get_height_node_tree(rnode_tree->pright) )
            c = rnode_tree->pleft;
        else
            c = rnode_tree->pright;
            
        if( c )
        {
            if( tree_get_height_node_tree(c->pleft) > tree_get_height_node_tree(c->pright) )
                gc = c->pleft;
            else
                gc = c->pright;
        }

        if( !( rnode_tree && c && gc ) )
            break;
        
        if( gc == c->pleft && c == rnode_tree->pleft )
        {
            tree_right_rotate(ptree, rnode_tree);
        }
        else if( gc == c->pleft && c == rnode_tree->pright )
        {
            tree_right_rotate(ptree, c);
            tree_left_rotate(ptree, rnode_tree);
        }
        else if( gc == c->pright && c == rnode_tree->pleft )
        {
            tree_left_rotate(ptree, c);
            tree_right_rotate(ptree, rnode_tree);
        }
        else
        {
            tree_left_rotate(ptree, rnode_tree);
        }
    }

    free(pnode_tree);
    ptree->no_of_elements--;

    return(ret_data);
}

extern  void        tree_inorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc)
{
    //  Code
    if( NULL == ptree ||
        NULL == ptree->p_root)
        return;

    tree_inorder_run(ptree->p_root, p_showdata_proc);
}

extern  void        tree_preorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc)
{
    //  Code
    if( NULL == ptree ||
        NULL == ptree->p_root)
        return;

    tree_preorder_run(ptree->p_root, p_showdata_proc);
}

extern  void        tree_postorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc)
{
    //  Code
    if( NULL == ptree ||
        NULL == ptree->p_root)
        return;

    tree_postorder_run(ptree->p_root, p_showdata_proc);
}


extern	void		tree_in_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_inorder_non_recursive(ptree->p_root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_pre_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_preorder_non_recursive(ptree->p_root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_post_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_postorder_non_recursive(ptree->p_root, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern  data_t      tree_get_max(tree_t ptree)
{
    p_node_tree_t pnode_tree = tree_get_max_node_tree(ptree->p_root);
    return( (pnode_tree ? pnode_tree->data : NULL) );
}

extern  data_t      tree_get_min(tree_t ptree)
{
    p_node_tree_t pnode_tree = tree_get_min_node_tree(ptree->p_root);
    return( (pnode_tree ? pnode_tree->data : NULL) );
}

extern  size_t      tree_get_height(tree_t ptree)
{
    if( NULL == ptree   ||
        NULL == ptree->p_root)
        return(0);

    tree_get_height_node_tree(ptree->p_root); 
}
