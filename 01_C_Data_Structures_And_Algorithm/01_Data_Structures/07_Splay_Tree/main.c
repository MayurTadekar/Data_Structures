

#include    <stdio.h>
#include    <stdlib.h>

#include    <time.h>

#include    "SplayTree.h"

tree_t tree;

status_t compare_less(data_t d1, data_t d2)
{
    if( (size_t)d1 < (size_t)d2 )
        return(SUCCESS);
    
    return(FAILURE);
}

void    showdata(data_t data)
{
    fprintf(stdout, "-%ld", (size_t)data);
}

int main(void)
{
    tree = tree_create();

    srand(time(0));
    size_t size = (rand() % 1000) + 1;

    for( size_t i = 0; i < size; ++i)
        tree_insert(tree, (data_t)(long long)((rand() % 1000) + 1), compare_less);

    tree_inorder_traversal(tree, showdata);
    tree_preorder_traversal(tree, showdata);

    tree_remove(tree, (data_t)20, compare_less);
    tree_inorder_traversal(tree, showdata);
    tree_preorder_traversal(tree, showdata);

    fprintf(stdout, "\n Destroy Tree:\n");
    tree_destroy(&tree, showdata);

    return(0);
}


