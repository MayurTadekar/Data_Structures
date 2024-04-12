

#include    <stdio.h>
#include    <stdlib.h>

#include    <time.h>

#include    "b_tree.h"


tree_t tree;

status_t compare(data_t d1, data_t d2)
{   
    //printf("%zd - %zd\n", d1, d2);
    if( (size_t)d1 < (size_t)d2 )
        return(SUCCESS);
    
    return(FAILURE);
}

void    showdata(data_t d)
{
    printf("%zd", (size_t)d);
    //printf("%c", (char)(size_t)d);
}

void    print_tree(tree_t tree)
{
    printf("\nTree:\n");
    tree_traversal(tree, showdata);
    printf("\n");

}

int toVal(char *str)
{
    int value = 0;
    int index = 0; 
    while(str[index] != '\0')
        value = (value*10) + (str[index++] - '0');
    
    return(value);
}

int main(int argc, char **argv)
{
    if( argc < 2 )
    {
        printf("Enter number of elements\n");
        return(0);
    }

    tree = tree_create();
    size_t nr_elements = toVal(argv[1]);

    srand(time(0));
    
    /*for( int i = 0 ; i < nr_elements; ++i )
    {   
        long long data = (long long)( rand() % 1000 + 1 );
        if( FAILURE == tree_insert(tree, (data_t)data, compare) )
            printf("\n %ld alread present\n", data);
        else
            printf("\n %ld New ndata\n", data);
        print_tree(tree);
    }*/

    for( int i = 0 ; i < nr_elements; ++i )
    {
        tree_insert(tree, (data_t) (long long)( (i+1) * 10  ), compare);
        //print_tree(tree);
    }
    print_tree(tree);
    
    data_t sdata = tree_search(tree, (data_t)(long long)100, compare);

    if( NULL != sdata )
        printf("Data found = %zd\n", (size_t) sdata);
    else
        printf("Data not present\n");

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)100, compare ));
    print_tree(tree);

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)30, compare ));
    print_tree(tree);

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)90, compare ));
    print_tree(tree);

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)60, compare ));
    print_tree(tree);

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)50, compare ));
    print_tree(tree);

    printf("Deleted data = %zd\n", (size_t) tree_remove(tree, (data_t)40, compare ));
    print_tree(tree);

    printf("\n");    

    return(0);
}

