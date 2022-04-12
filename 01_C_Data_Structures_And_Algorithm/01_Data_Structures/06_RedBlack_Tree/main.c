

#include    <stdio.h>
#include    <stdlib.h>

#include    "redblack_tree.h"

rbtree_t tree = NULL;

status_t compare(data_t td, data_t nd)
{
    if( (int)(long long)td > (int)(long long)nd )
    {
        return(SUCCESS);
    }
    return(FAILURE);
}

void    showdata(data_t data)
{
    printf("-%d", (int)(long long)data);
}

int main(void)
{
    tree = create_tree();

    tree_insert(tree, (data_t)10, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)20, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");
    
    tree_insert(tree, (data_t)30, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)40, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)50, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)60, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)70, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

    tree_insert(tree, (data_t)80, compare);
    tree_inorder_traversal(tree, showdata);
    printf("\n");
    tree_preorder_traversal(tree, showdata);
    printf("\n");

/*
    tree_inorder_traversal(tree, showdata);
    printf("\n");

    tree_preorder_traversal(tree, showdata);
    printf("\n");

    
    tree_postorder_traversal(tree, showdata);
    printf("\n");
    */

    return(0);
}
