

#include    <stdio.h>
#include    <stdlib.h>

#include    "redblack_tree.h"

//  Tree Auxillary Functions

static  p_node_t    tree_successor(p_node_t pnode)
{
    p_node_t prun = pnode->pright;

    if( NULL == prun )
        return(NULL);

    while( NULL == prun->pleft )
        prun = prun->pleft;
    
    return(prun);
}

static  p_node_t    tree_predecessor(p_node_t pnode)
{
    p_node_t prun = pnode->pleft;

    if( NULL == prun )
        return(NULL);

    while( NULL == prun->pright )
        prun = prun->pright;
    
    return(prun);
}

static  void        right_rotate(rbtree_t tree, p_node_t pnode)
{
    p_node_t left = pnode->pleft;
    
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

static  void        left_rotate(rbtree_t tree, p_node_t pnode)
{
    p_node_t right = pnode->pright;

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

static  void        insert_fixup(rbtree_t tree, p_node_t pnode)
{
    p_node_t p = NULL;
    p_node_t gp = NULL;

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
            p_node_t uncle = gp->pright;

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
            p_node_t uncle = gp->pleft;
            printf("1\n");

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

static  void        inorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    inorder_run(pnode->pleft, p_showdata_proc);
    p_showdata_proc(pnode->data);
    printf("/%c", ( RED == pnode->color ? 'R' : 'B' ) );
    inorder_run(pnode->pright, p_showdata_proc);
}

static  void        preorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    p_showdata_proc(pnode->data);
    preorder_run(pnode->pleft, p_showdata_proc);
    preorder_run(pnode->pright, p_showdata_proc);
}

static  void        postorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;
    
    postorder_run(pnode->pleft, p_showdata_proc);
    postorder_run(pnode->pright, p_showdata_proc);
    p_showdata_proc(pnode->data);
}

static  int         node_height(p_node_t pnode);

static  p_node_t    create_node(data_t data)
{
    p_node_t p = (p_node_t)Xcalloc(1, SIZE_NODE);
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

    p_node_t prun = tree->proot;
    p_node_t new_node = create_node(ndata);

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

    p_node_t prun = tree->proot;
    p_node_t successor = NULL;
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

    successor = tree_successor(prun);

    ret_data = prun->data;

    if( successor )
    {
        prun->data = successor->data;
    }

    

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
