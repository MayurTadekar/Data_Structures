

#include    <stdio.h>
#include    <stdlib.h>

#include    "stack.h"

#include    "redblack_tree.h"

#define     MAX(a,b)    (a>b ? a : b)

//  Tree Auxillary Functions

static  p_node_tree_t    tree_successor(p_node_tree_t pnode)
{
    p_node_tree_t prun = pnode->pright;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pleft )
        prun = prun->pleft;
    
    return(prun);
}

static  p_node_tree_t    tree_predecessor(p_node_tree_t pnode)
{
    p_node_tree_t prun = pnode->pleft;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pright )
        prun = prun->pright;
    
    return(prun);
}

static  void        right_rotate(rbtree_t tree, p_node_tree_t pnode)
{
    p_node_tree_t left = pnode->pleft;
    
    left->parent = pnode->parent;
    if( NULL == left->parent )
        tree->proot = left;
    else if( pnode == pnode->parent->pleft )
        pnode->parent->pleft = left;
    else 
        pnode->parent->pright = left;

    pnode->pleft = left->pright;
    if( pnode->pleft )
        pnode->pleft->parent = pnode;
    
    left->pright = pnode;
    pnode->parent = left;
}

static  void        left_rotate(rbtree_t tree, p_node_tree_t pnode)
{
    p_node_tree_t right = pnode->pright;

    right->parent = pnode->parent;
    if( NULL == right->parent )
        tree->proot = right;
    else if( pnode == pnode->parent->pleft )
        pnode->parent->pleft = right;
    else
        pnode->parent->pright = right;
    
    pnode->pright = right->pleft;
    if( pnode->pright )
        pnode->pright->parent = pnode;
    
    right->pleft = pnode;
    pnode->parent = right;
}

static  void        insert_fixup(rbtree_t tree, p_node_tree_t pnode)
{
    p_node_tree_t p = NULL;
    p_node_tree_t gp = NULL;

    while(  pnode != tree->proot    &&
            pnode->color != BLACK   &&
            pnode->parent->color == RED )
    {
        p = pnode->parent;
        gp = p->parent;
        

        /*
            Parent of pnode is Left child of GrandParent
        */
        if( p == gp->pleft )
        {
            p_node_tree_t uncle = gp->pright;

            /*
                Case 1: Color of Uncle if RED
                Only Recolouring Required.
            */
            if( NULL != uncle   &&
                uncle->color == RED)
            {
                gp->color = RED;
                p->color = BLACK;
                uncle->color = BLACK;
                pnode = gp;
            }
            else
            {
                /*
                    Case 2: pnode is Right Child of parent
                    Left Rotation Required;
                */
                if( pnode == p->pright )
                {
                    left_rotate(tree, p);
                    pnode = p;
                    p = pnode->parent;
                }

                /* 
                    Case 3: pnode if Left Child of parent 
                    Right Rotation Required;
                */
                right_rotate(tree, gp);
                color_t color = p->color;
                p->color = gp->color;
                gp->color = color;
                pnode = p;
            }
        }
        /*
            Parent of pnode is Left child of GrandParent
        */
        else
        {
            p_node_tree_t uncle = gp->pleft;
            //printf("1\n");

            /*
                Case 1: Color of Uncle if RED
                Only Recolouring Required.
            */
            if( NULL != uncle   &&
                uncle->color == RED)
            {
                gp->color = RED;
                p->color = BLACK;
                uncle->color = BLACK;
                pnode = gp;
            }
            else
            {
                /*
                    Case 2: pnode is Left Child of parent
                    Right Rotation Required
                */
                if( pnode == p->pleft )
                {
                    right_rotate(tree, p);
                    pnode = p;
                    p = pnode->parent;
                }
                /* 
                    Case 3: pnode if Right Child of parent 
                    Left Rotation Required;
                */
                left_rotate(tree, gp);
                color_t color = p->color;
                p->color = gp->color;
                gp->color = color;
                pnode = p;
            }
        }
    }   
}

static  void        delete_fixup(rbtree_t tree, p_node_tree_t node)
{
    p_node_tree_t pnode = node;

    while(  NULL != pnode    &&
            tree->proot != pnode &&
            pnode->color == BLACK )
    {
        if( pnode == pnode->parent->pleft)
        {
            p_node_tree_t uncle = pnode->parent->pright;
            if( NULL != uncle &&
               uncle->color == RED  )
            {
                uncle->color = BLACK;
                pnode->parent->color = RED;
                left_rotate(tree, pnode->parent);
                uncle = pnode->parent->pright;
            }

            if( (uncle->pleft == NULL || BLACK == uncle->pleft->color)  &&
                (uncle->pright == NULL || BLACK == uncle->pright->color))
            {
                uncle->color = RED;
                pnode = pnode->parent;
            }
            else 
            {
                if( NULL == uncle->pright   ||
                    BLACK == uncle->pright->color)
                {
                    uncle->pleft->color = BLACK;
                    uncle->color = RED;
                    right_rotate(tree, uncle);
                    uncle = pnode->parent->pright;
                }
                uncle->color = pnode->parent->color;
                pnode->parent->color = BLACK;
                uncle->pright->color = BLACK;
                left_rotate(tree, pnode->parent);
            }
        }
        else
        {
            p_node_tree_t uncle = pnode->parent->pleft;
            if( NULL != uncle &&
                RED == uncle->color )
            {
                uncle->color = BLACK;
                pnode->parent->color = RED;
                right_rotate(tree, pnode->parent);
                uncle = pnode->parent->pleft;
            }
            if( (NULL == uncle->pleft || BLACK == uncle->pleft->color)  && 
                (NULL == uncle->pright || BLACK == uncle->pright->color))
            {
                uncle->color = RED;
                pnode = pnode->parent;
            }
            else 
            {
                if( NULL == uncle->pleft ||
                    BLACK == uncle->pleft->color )
                {
                    uncle->pright->color = BLACK;
                    uncle->color = RED;
                    left_rotate(tree, uncle->parent);
                    uncle = pnode->parent->pleft;
                }
                uncle->color = uncle->parent->color;
                pnode->parent->color = BLACK;
                uncle->pleft->color = BLACK;
                right_rotate(tree, pnode->parent);
            }
        }
        pnode = tree->proot;
    }
}

static  void        transplant(rbtree_t tree, p_node_tree_t u, p_node_tree_t v)
{
    if( NULL == u->parent )
        tree->proot = v;
    else if( u == u->parent->pleft )
        u->parent->pleft = v;
    else 
        u->parent->pright = v;

    if( v )
        v->parent = u->parent;
}

static  void        inorder_run(p_node_tree_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    inorder_run(pnode->pleft, p_showdata_proc);
    p_showdata_proc(pnode->data);
    printf("/%c", ( RED == pnode->color ? 'R' : 'B' ) );
    inorder_run(pnode->pright, p_showdata_proc);
}

static  void        preorder_run(p_node_tree_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    p_showdata_proc(pnode->data);
    preorder_run(pnode->pleft, p_showdata_proc);
    preorder_run(pnode->pright, p_showdata_proc);
}

static  void        postorder_run(p_node_tree_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    postorder_run(pnode->pleft, p_showdata_proc);
    postorder_run(pnode->pright, p_showdata_proc);
    p_showdata_proc(pnode->data);
}


static 	void		tree_inorder_non_recursive(p_node_tree_t pnode_tree_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();
	
	if( NULL == pnode_tree_tree )
		return;

	p_node_tree_t run = pnode_tree_tree;
	
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

static 	void		tree_preorder_non_recursive(p_node_tree_t pnode_tree_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_tree_t run = pnode_tree_tree;

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

static 	void		tree_postorder_non_recursive(p_node_tree_t pnode_tree_tree, SHOWDATA_PROC show_data_proc)
{
	stack_t stack = create_stack();

	p_node_tree_t run = pnode_tree_tree;
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

static  int         node_height(p_node_tree_t pnode)
{
    if( NULL == pnode )
        return(0);
    
    return  ( MAX(    node_height(pnode->pleft),
                    node_height(pnode->pright) 
                ) + 1 
            );
}

static  void        post_order_data_delete(p_node_tree_t pnode, DELETE_DATA_PROC p_deletedata_proc)
{
    if( NULL == pnode )
        return;

    post_order_data_delete(pnode->pleft, p_deletedata_proc);
    post_order_data_delete(pnode->pright, p_deletedata_proc);
    p_deletedata_proc(pnode->data);
    free(pnode);
}


static  p_node_tree_t    create_node(data_t data)
{
    p_node_tree_t p = (p_node_tree_t)Xcalloc(1, SIZE_NODE);
    p->data = data;
    p->pleft = NULL;
    p->pright = NULL; 
    p->parent = NULL;
    p->color = RED;
}

static  void*       Xcalloc(size_t nr_elememts, size_t size_of_element)
{
    void *p = calloc(1, size_of_element);
    if( NULL == p )
    {
        printf("ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

//  Tree Interface Functions
extern  rbtree_t    create_tree()
{
    rbtree_t p = (rbtree_t)Xcalloc(1, SIZE_DUMMY);
    p->nr_elements = 0;
    p->proot = NULL;
}

extern  status_t    tree_insert(rbtree_t tree, data_t ndata, COMPARE_PROC p_compare_proc)
{
    if( NULL == tree )
        return(FAILURE);

    p_node_tree_t prun = tree->proot;
    p_node_tree_t new_node = create_node(ndata);

    if(NULL == tree->proot)
    {
        tree->proot = new_node;
    }
    else
    {
        while(1)
        {
            if( SUCCESS == p_compare_proc(prun->data, ndata) )
            {
                if( NULL == prun->pleft )
                {
                    prun->pleft = new_node;
                    new_node->parent = prun;
                    break;
                }
                prun = prun->pleft;
            }
            else
            {
                if( NULL == prun->pright )
                {
                    prun->pright = new_node;
                    new_node->parent = prun;
                    break;
                }
                prun = prun->pright;
            }
        }
    }
    tree->nr_elements++;
    
    if( new_node->parent &&
        new_node->parent->parent )
        insert_fixup(tree, new_node);    

    tree->proot->color = BLACK;

    return(SUCCESS);
}

extern  data_t      tree_remove(rbtree_t tree, data_t rdata, COMPARE_PROC p_compare_proc)
{
    if( NULL == tree||
        NULL == rdata )
        return((data_t)0);

    p_node_tree_t prun = tree->proot;
    p_node_tree_t successor = NULL;
    data_t  ret_data = NULL;

    while( NULL != prun )
    {
        status_t ret = p_compare_proc(prun->data, rdata);
        if( ret == SAME_DATA)
            break;

        if( ret == BIG_DATA )
        {
            prun = prun->pleft;
        }
        else  
        {
            prun = prun->pright;
        }
    }

    if( NULL == prun )
        return((data_t)0);

    //if( successor )
    //    printf("Succ = %d\n", (int)(long long)successor->data);

    ret_data = prun->data;

    p_node_tree_t x;
    if( NULL == prun->pleft )
    {
        x = prun->pright;
        transplant(tree, prun, x);
    }
    else if( NULL == prun->pright )
    {
        x = prun->pleft;
        transplant(tree, prun, x);
    }
    else
    {
        successor = tree_successor(prun);
        x = successor->pright;

        if( successor->parent == prun )
            x->parent = prun;
        else
        {
            transplant(tree, successor, x);
            successor->pright =   prun->pright;
            successor->pright->parent = successor;
        }
        transplant(tree, prun, successor);
        successor->pleft = prun->pleft;
        successor->pleft->parent = successor;
        successor->color = prun->color;
    }

    /*while(1)
    {
        if( successor )
        {
            prun->data = successor->data;
            printf("Succ = %d\n", (int)(long long)successor->data);

            prun = successor;
            successor = tree_successor(prun);
            continue;
            

            if( successor == prun->pright )
            {
                prun->pright = successor->pright;
                if( prun->pright )
                    prun->pright->parent = prun;
            }
            else
            {
                successor->parent->pleft = successor->pright;
                if( successor->pright )
                    successor->pright->parent = successor->parent;
            }   
        }
        else
        {
            if( prun->parent )
            {
                if( prun->parent->pleft == prun )
                    prun->parent->pleft = prun->pright;
                else 
                    prun->parent->pright = prun->pright;
            }
            
            if( prun->pright )
                prun->pright->parent = prun->parent;
            
            break;
        }
    }*/
    
    //printf("freeing: %d\n", (int)(long long)prun->data);
    
    if( BLACK == prun->color )
        delete_fixup(tree, prun->parent);

    free(prun);
    tree->nr_elements--;

    //printf("1\n");
    return(ret_data);
}

extern  void        tree_inorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == tree ||
        NULL == tree->proot )
        return;
    
    inorder_run(tree->proot, p_showdata_proc);
}

extern  void        tree_preorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == tree ||
        NULL == tree->proot )
        return;
    
    preorder_run(tree->proot, p_showdata_proc);
}

extern  void        tree_postorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == tree ||
        NULL == tree->proot )
        return;
    
    postorder_run(tree->proot, p_showdata_proc);
}

extern	void		tree_in_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_inorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_pre_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_preorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_post_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_postorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern  size_t      tree_height(rbtree_t tree)
{
    return( node_height(tree->proot) );
}

extern  void        tree_destroy(p_rbtree_t ptree, DELETE_DATA_PROC p_deletedata_proc)
{
    
    if( NULL == ptree ||
        NULL == *ptree ||
        0 == (*ptree)->nr_elements
    )
    {
        printf("No Data to delete\n");
        return;
    }
    
    rbtree_t tree = *ptree;
    post_order_data_delete(tree->proot, p_deletedata_proc);

    free(tree);
    *ptree = NULL;
}

