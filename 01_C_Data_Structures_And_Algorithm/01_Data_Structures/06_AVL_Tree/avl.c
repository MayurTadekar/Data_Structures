

#include    <stdio.h>
#include    <stdlib.h>
#include    <assert.h>

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

static  void    tree_left_rotate(tree_t ptree, p_node_t pnode)
{
    p_node_t    right = pnode->pright;

    right->parent = pnode->parent;
    if( NULL == pnode->parent )
        ptree->p_root = right;
    else if( pnode->parent->pleft == pnode )
        pnode->parent->pleft = right;
    else 
        pnode->parent->pright = right;

    pnode->pright = right->pleft;
    if( pnode->pright ) 
        pnode->pright->parent = pnode;

    right->pleft = pnode;
    pnode->parent = right;
}

static  void    tree_right_rotate(tree_t ptree, p_node_t pnode)
{
    p_node_t    left =  pnode->pleft;

    left->parent = pnode->parent;
    if( NULL == left->parent )
        ptree->p_root = left;
    else if( pnode->parent->pright )
        pnode->parent->pright = left;
    else
        pnode->parent->pleft = left;
    
    pnode->pleft = left->pright;
    if( pnode->pleft )
        pnode->pleft->parent = pnode;
    
    left->pright = pnode;
    pnode->parent = left;
}

static  p_node_t tree_successor(p_node_t pnode)
{
    p_node_t prun = pnode->pright;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pleft )
        prun = prun->pleft;

    return(prun);
}

static  p_node_t tree_predecessor(p_node_t pnode)
{
    p_node_t prun = pnode->pleft;

    if( NULL == prun )
        return(NULL);

    while( NULL != prun->pright)
        prun = prun->pright;

    return(prun);
}

static  void    tree_transplant(tree_t ptree, p_node_t pnode, p_node_t tranp)
{
    if( NULL == pnode->parent )
        ptree->p_root = tranp;
    else if( pnode->parent->pleft == pnode )
        pnode->parent->pleft = tranp;
    else
        pnode->parent->pright = tranp;
    
    if( tranp )
        tranp->parent = pnode->parent;
}

static  size_t  tree_get_height_node(p_node_t pnode)
{
    if( NULL == pnode )
        return(0);

    return( MAX_HEIGHT( 
                        tree_get_height_node(pnode->pleft), 
                        tree_get_height_node(pnode->pright) 
                        ) + 1 
            );
}

static  p_node_t tree_get_next_imbalanced_node(p_node_t pnode)
{
    p_node_t u;
    long balance = 0;
    u = pnode;
    while( u != NULL )
    {
        balance = tree_get_balance(u);
        if( balance < -1 || balance > 1 )
            break;
        u = u->parent;
    }
    return(u);
}

static  p_node_t tree_get_max_node(p_node_t pnode)
{
    p_node_t prun = pnode;
    
    if( NULL == prun )
        return(prun);

    while( NULL != prun->pright )
        prun = prun->pright;
    
    return(prun);
}

static  p_node_t tree_get_min_node(p_node_t pnode)
{
    p_node_t prun = pnode;
    
    if( NULL == prun )
        return(prun);

    while( NULL != prun->pleft )
        prun = prun->pleft;
    
    return(prun);
}

static  void    tree_inorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;

    tree_inorder_run(pnode->pleft, p_showdata_proc);

    p_showdata_proc(pnode->data);

    tree_inorder_run(pnode->pright, p_showdata_proc);
}

static  void    tree_preorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;

    p_showdata_proc(pnode->data);
    if( pnode->parent )
        printf("/%d", (int)(long long)pnode->parent->data);

    tree_preorder_run(pnode->pleft, p_showdata_proc);

    tree_preorder_run(pnode->pright, p_showdata_proc);
}

static  void    tree_postorder_run(p_node_t pnode, SHOWDATA_PROC p_showdata_proc)
{
    if( NULL == pnode )
        return;

    tree_postorder_run(pnode->pleft, p_showdata_proc);

    tree_postorder_run(pnode->pright, p_showdata_proc);

    p_showdata_proc(pnode->data);
}

static  int     tree_get_balance(p_node_t p_node)
{
    return( tree_get_height_node(p_node->pleft) - tree_get_height_node(p_node->pright) );
}

static  p_node_t tree_create_node(data_t new_data)
{
    p_node_t p = (p_node_t)Xcalloc(1, SIZE_NODE);
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

    //p_node_t new_node = tree_create_node(new_data);
    
    if( NULL == ptree->p_root )
    {
        ptree->p_root = tree_create_node(new_data);
        ptree->no_of_elements++;
        return(SUCCESS);
    }

    p_node_t pnode = ptree->p_root;
    p_node_t new_node = tree_create_node(new_data);

    while(1)
    {
        if( SUCCESS == p_compare_proc(pnode->data, new_data) )
        {
            if( NULL == pnode->pleft )
            {
                pnode->pleft = new_node;
                new_node->parent = pnode;
                break;
            }
            pnode = pnode->pleft;
        }
        else
        {
            if( NULL == pnode->pright )
            {
                pnode->pright = new_node;
                new_node->parent = pnode;
                break;
            }
            pnode = pnode->pright;
        }
    }
    ptree->no_of_elements++;

    p_node_t p = pnode;
    p_node_t gp = NULL; 
    if( p )
        gp = p->parent;

    while( gp != NULL )
    {
        int balance = tree_get_balance(gp);
        if( balance < -1 || balance > 1 )
            break;
        gp = gp->parent;
        p = p->parent;
        new_node = new_node->parent;
    }

    if( NULL == gp )
        return(SUCCESS);


    if( new_node == p->pleft && p == gp->pleft )
    {
        tree_right_rotate(ptree, gp);
    }
    else if( new_node == p->pleft && p == gp->pright )
    {
        tree_right_rotate(ptree, p);
        tree_left_rotate(ptree, gp);
    }
    else if( new_node == p->pright && p == gp->pleft )
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

    p_node_t pnode = ptree->p_root;
    p_node_t rnode = NULL;
    data_t ret_data = NULL;

    p_node_t successor;

    while(1)
    {
        if( NULL == pnode )
            return(NULL);

        status_t ret = p_compare_proc(pnode->data, rem_data);

        if( SAME_DATA == ret )
        {
            ret_data = pnode->data;
            successor = tree_successor(pnode);
            rnode = pnode;
            if( NULL != successor )
            {
                pnode->data = successor->data;
                pnode = successor;
            }
            break;
        }
        if( BIG_DATA == ret )
        {
            pnode = pnode->pleft;
        } 
        else 
        {
            pnode = pnode->pright;
        }
    }

    p_node_t parent = pnode->parent;
    
    if( NULL != successor )
    {
        if( NULL != parent )
        {
            if( pnode->parent->pright == pnode )
                pnode->parent->pright = pnode->pright;
            else
                pnode->parent->pleft = pnode->pright;
        }

        if( NULL != pnode->pright )
            pnode->pright->parent = parent;
    }
    else
    {
        if( NULL != parent )
        {
            if( pnode->parent->pright == pnode )
                pnode->parent->pright = pnode->pleft;
            else
                pnode->parent->pleft = pnode->pleft;
        }

        if( NULL != pnode->pleft )
            pnode->pleft->parent = parent;
    }

    if( NULL == pnode->parent )
        ptree->p_root = NULL;
    
    p_node_t c = NULL;
    p_node_t gc = NULL;

    while( NULL != ( rnode = tree_get_next_imbalanced_node(rnode)) )
    {

        if( tree_get_height_node(rnode->pleft) > tree_get_height_node(rnode->pright) )
            c = rnode->pleft;
        else
            c = rnode->pright;
            
        if( c )
        {
            if( tree_get_height_node(c->pleft) > tree_get_height_node(c->pright) )
                gc = c->pleft;
            else
                gc = c->pright;
        }

        if( !( rnode && c && gc ) )
            break;
        
        if( gc == c->pleft && c == rnode->pleft )
        {
            tree_right_rotate(ptree, rnode);
        }
        else if( gc == c->pleft && c == rnode->pright )
        {
            tree_right_rotate(ptree, c);
            tree_left_rotate(ptree, rnode);
        }
        else if( gc == c->pright && c == rnode->pleft )
        {
            tree_left_rotate(ptree, c);
            tree_right_rotate(ptree, rnode);
        }
        else
        {
            tree_left_rotate(ptree, rnode);
        }
    }

    free(pnode);
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

extern  data_t      tree_get_max(tree_t ptree)
{
    p_node_t pnode = tree_get_max_node(ptree->p_root);
    return( (pnode ? pnode->data : NULL) );
}

extern  data_t      tree_get_min(tree_t ptree)
{
    p_node_t pnode = tree_get_min_node(ptree->p_root);
    return( (pnode ? pnode->data : NULL) );
}

extern  size_t      tree_get_height(tree_t ptree)
{
    if( NULL == ptree   ||
        NULL == ptree->p_root)
        return(0);

    tree_get_height_node(ptree->p_root); 
}
