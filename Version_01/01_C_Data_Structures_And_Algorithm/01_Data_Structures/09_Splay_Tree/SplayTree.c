

#include    <stdio.h>
#include    <stdlib.h>

#include    "stack.h"
#include    "SplayTree.h"

//  Tree auxillary functions
static  void*   Xcalloc(size_t nr_elements, size_t size_element)
{
    void *p = calloc(nr_elements, size_element);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

static  p_node_tree_t    create_node(data_t data)
{
    p_node_tree_t pnode = (p_node_tree_t) Xcalloc(1, SIZE_NODE);
    pnode->data = data;
    pnode->pleft = NULL;
    pnode->pright = NULL;
    pnode->parent = NULL;
}

static  void    transplant(tree_t tree, p_node_tree_t u, p_node_tree_t v)
{
    if( NULL == u->parent )
        tree->proot = v;
    else if( u->parent->pleft == u )
        u->parent->pleft = v;
    else 
        u->parent->pright = v;
    
    if(v)
        v->parent = u->parent;
}

static  void    inorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata)
{
    if( !pnode )
        return;

    inorder_run(pnode->pleft, pshowdata);
    pshowdata(pnode->data);
    inorder_run(pnode->pright, pshowdata);
}

static  void    preorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata)
{
    if(!pnode)
        return;
    
    pshowdata(pnode->data);
    preorder_run(pnode->pleft, pshowdata);
    preorder_run(pnode->pright, pshowdata);
}

static  void    postorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata)
{
    if(!pnode)
        return;
    
    postorder_run(pnode->pleft, pshowdata);
    postorder_run(pnode->pright, pshowdata);
    pshowdata(pnode);
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

static  p_node_tree_t    find_node(tree_t tree, data_t data, COMPARE_PROC pcompare)
{
    if( NULL == tree ||
        NULL == tree->proot )
        return(NULL);

    p_node_tree_t prun = tree->proot;

    while(prun)
    {
        if( pcompare(prun->data, data) == SUCCESS )
            prun = prun->pright;
        else if( pcompare(data, prun->data) == SUCCESS )
            prun = prun->pleft;
        else 
            return(prun);
    }
}

static  void    left_rotate(tree_t tree, p_node_tree_t pnode)
{
    p_node_tree_t right = pnode->pright;
    
    transplant(tree, pnode, right);

    pnode->pright = right->pleft;
    if(pnode->pright)
        pnode->pright->parent = pnode;

    right->pleft = pnode;
    pnode->parent = right;
}

static  void    right_rotate(tree_t tree, p_node_tree_t pnode)
{
    p_node_tree_t left = pnode->pleft;

    transplant(tree, pnode, left);

    pnode->pleft = left->pright;
    if(pnode->pleft)
        pnode->pleft->parent = pnode;
    
    left->pright = pnode;
    pnode->parent = left;
}

static  p_node_tree_t    successor(p_node_tree_t pnode)
{
    p_node_tree_t prun = pnode->pright;

    while( NULL != prun->pleft )
        prun = prun->pleft;

    return(prun);
}

static  void    splay(tree_t tree, p_node_tree_t pnode)
{
    while( pnode->parent )
    {
        if( !pnode->parent->parent )
        {
            if( pnode->parent->pright == pnode )
                left_rotate(tree, pnode->parent);
            else 
                right_rotate(tree, pnode->parent);
        }
        else if(    pnode->parent->pleft == pnode &&
                    pnode->parent->parent->pleft == pnode->parent )
        {
            right_rotate(tree, pnode->parent->parent);
            right_rotate(tree, pnode->parent);
        }
        else if(    pnode->parent->pright == pnode &&
                    pnode->parent->parent->pright == pnode->parent )
        {
            left_rotate(tree, pnode->parent->parent);
            left_rotate(tree, pnode->parent);
        }
        else if(    pnode->parent->pright == pnode &&
                    pnode->parent->parent->pleft == pnode->parent )
        {
            left_rotate(tree, pnode->parent);
            right_rotate(tree, pnode->parent);
        }
        else
        {
            right_rotate(tree, pnode->parent);
            left_rotate(tree, pnode->parent);
        }        
    }
}

static  void    postorder_destroy(p_node_tree_t pnode, DELETEDATA_PROC pdeletedata)
{
    if( !pnode )
        return;

    postorder_destroy(pnode->pleft, pdeletedata);
    postorder_destroy(pnode->pright, pdeletedata);
    pdeletedata(pnode->data);
}

//  Tree Interface Functions
extern  tree_t  tree_create()
{
    tree_t ptree = (tree_t)Xcalloc(1, SIZE_DUMMY);
    ptree->proot = NULL;
    ptree->nr_elements = 0 ;

    return(ptree);
}

extern  void    tree_insert(tree_t tree, data_t data, COMPARE_PROC pcompare)
{
    p_node_tree_t newnode = create_node(data);
    if( NULL == tree->proot )
    {
        tree->proot = newnode;
    }
    else
    {
        p_node_tree_t prun = tree->proot;
        while(1)
        {
            if( pcompare(prun->data, data) == SUCCESS )
            {
                if( NULL == prun->pright )
                {
                    prun->pright = newnode;
                    break;
                }
                prun = prun->pright;
            }
            else
            {
                if( NULL == prun->pleft )
                {
                    prun->pleft = newnode;
                    break;
                }
                prun = prun->pleft;
            }
        }
        newnode->parent = prun;
    }
    tree->nr_elements++;
    splay(tree, newnode);
}

extern  data_t  tree_remove(tree_t tree, data_t rdata, COMPARE_PROC pcompare)
{
    if( NULL == tree &&
        NULL == tree->proot )
        return(NULL);

    p_node_tree_t dnode = find_node(tree, rdata, pcompare);

    splay(tree, dnode);

    if( !dnode->pleft )
    {
        fprintf(stdout, "\nright Deldata: %ld", (size_t)dnode->data);
        transplant(tree, dnode, dnode->pright);
    }
    else if( !dnode->pright )
    {
        fprintf(stdout, "\nleft Deldata: %ld", (size_t)dnode->data);
        transplant(tree, dnode, dnode->pleft);
    }
    else
    {
        p_node_tree_t succ = successor(dnode);

        if( succ != dnode->pright )
        {
            transplant(tree, succ, succ->pright);
            succ->pright = dnode->pright;
            succ->pright->parent = succ;
        } 
        transplant(tree, dnode, succ);
        succ->pleft = dnode->pleft;
        succ->pleft->parent = succ;
    }
    tree->nr_elements--;
    data_t rd = dnode->data;
    
    free(dnode);
    return(rd);
}

extern  void    tree_inorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata)
{
    fprintf(stdout, "\nInorder:\n");
    inorder_run(tree->proot, pshowdata);
}

extern  void    tree_preorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata)
{
    fprintf(stdout, "\nPreorder:\n");
    preorder_run(tree->proot, pshowdata);
}

extern  void    tree_postorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata)
{
    fprintf(stdout, "\nPostorder:\n");
    postorder_run(tree->proot, pshowdata);
}



extern	void		tree_in_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_inorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_pre_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_preorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern	void		tree_post_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC show_data_proc)
{
	//	Code
	fprintf(stdout,"\n{START}-");
	if( SUCCESS == tree_check_root(ptree) )
	{
		tree_postorder_non_recursive(ptree->proot, show_data_proc);
	}
	fprintf(stdout,"{END}");
}

extern  void    tree_destroy(tree_t* ptree, DELETEDATA_PROC pdeletedata)
{
    postorder_destroy((*ptree)->proot, pdeletedata);
    free(*ptree);
    *ptree = NULL;
}
