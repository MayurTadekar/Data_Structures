

#include    <stdio.h>
#include    <stdlib.h>

#include    "avl.h"

tree_t  tree;

status_t compare(data_t d1, data_t d2)
{
    if( (int)(long long)d1 > (int)(long long)d2 )
        return(SUCCESS);

    return(FAILURE);
}

status_t compare_2(data_t tree_data, data_t rem_data)
{
    if( (int)(long long)tree_data == (int)(long long)rem_data )
        return(SAME_DATA);

    if( (int)(long long)tree_data > (int)(long long)rem_data )
        return(BIG_DATA);
    else 
        return(SMALL_DATA);
}

void   show(data_t d)
{
    printf("-%d", (int)(long long)d);
}

int main(void)
{
    tree = create_tree();

    for( int i = 0 ; i < 10; ++i )
    {
        tree_insert(tree, (data_t)(long long)((i+1) * 10), compare);
        printf("\n");
        tree_preorder_traversal(tree, show);
    }
    
    tree_remove(tree, (data_t)40, compare_2);
    printf("\n");
    tree_preorder_traversal(tree, show);
    
    /*
    tree_remove(tree, (data_t)50, compare_2);
    printf("\n");
    tree_preorder_traversal(tree, show);
    
    tree_remove(tree, (data_t)30, compare_2);
    printf("\n");
    tree_preorder_traversal(tree, show);
    */

    printf("\nHeight = %zd\n", tree_get_height(tree));

    return(0);    
}

