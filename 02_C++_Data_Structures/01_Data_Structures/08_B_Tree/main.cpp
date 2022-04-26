

#include    <iostream>

#include    "BTree.h"

BTree<int> *tree;

void PrintTree(BTree<int>*&t)
{   
    std::cout << "Tree:" << std::endl;
    t->Traverse();
    std::cout << std::endl;
}

int toValue(char *str)
{
    int value = 0;
    int index = 0;

    while('\0' != str[index])
    {
        if( '0' <= str[index] && '9' >= str[index] )
        {
            value = value * 10 + ( str[index] - '0' );
            index++;
        }
        else 
        {
            std::cerr << "Number of elements Invalid" << std::endl;
            exit(1);
        }
    }

    return(value);
}

int main(int argc, char **argv)
{
    if( 2 > argc )
    {
        std::cerr << "Please Enter number of elements" << std::endl;
        return(0);
    }

    int size = toValue(argv[1]); 

    tree = new BTree<int>();

    for( int i = 0 ; i < size; ++i )
    {
        tree->Insert( (i+1) * 10 );
    }
    PrintTree(tree);    

    tree->Remove(10);
    PrintTree(tree);
    
    tree->Remove(30);
    PrintTree(tree);

    tree->Remove(60);
    PrintTree(tree); 

    tree->Remove(50);
    PrintTree(tree);  

    tree->Remove(70);
    PrintTree(tree);    

    tree->Remove(80);
    PrintTree(tree);    

    tree->Remove(10);
    PrintTree(tree);    

    // tree->Insert(20);
    // PrintTree(tree);    

    // tree->Insert(30);
    // PrintTree(tree);
    
    // tree->Insert(40);
    // PrintTree(tree);
    
    // tree->Insert(50);
    // PrintTree(tree);
    
    // tree->Insert(60);
    // PrintTree(tree);
    
    // tree->Insert(70);
    // PrintTree(tree);
    
    // tree->Insert(80);
    // PrintTree(tree);
    
    // tree->Insert(90);
    // PrintTree(tree);
    
    // tree->Insert(100);
    // PrintTree(tree);
    
    return(0);
}
