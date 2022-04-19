

#include    <iostream>
#include    <time.h>

#include    "rbtree.h"

class MyInt
{
    private:
        int data;

    public:
        MyInt() : data() {}
        MyInt(int data) : data(data) {}
        ~MyInt() {}

        bool operator < (MyInt& i)
        {
            return( data < i.data );
        }  

        bool operator > (MyInt& i)
        {
            return( data > i.data);
        }

        bool operator == (MyInt& i)
        {
            return( data == i.data);
        }

        friend std::ostream& operator<<(std::ostream& out, MyInt& i)
        {
            out << i.data;
            return(out);
        }
};

RedBlackTree<MyInt> *tree;

int main(void)
{
    tree = new RedBlackTree<MyInt>();

    srand(time(0));
    size_t size = (rand() % 1000) + 1;
    for( int i = 0; i < 3; ++i )
    {   
        //std::cout << "1 : "<< std::endl; 
        tree->InsertData(MyInt( (int)( (i + 1) * 10 )) );
        //std::cout << "Succecssful : " << size << std::endl; 
    }
    
    std::cout << "Inorder:" << std::endl;
    tree->InorderTraversal();
    std::cout << std::endl;

    std::cout << "Preorder:" << std::endl;
    tree->PreOrderTraversal();
    std::cout << std::endl;

    std::cout << "Postorder:" << std::endl;
    tree->PostOrderTraversal();
    std::cout << std::endl;

    std::cout << std::endl << "Deleting:";
    MyInt i = tree->RemoveData(MyInt(20));
    std::cout << i << std::endl << std::endl;
    
    std::cout << "Inorder:" << std::endl;
    tree->InorderTraversal();
    std::cout << std::endl;

    /*std::cout << "Preorder:" << std::endl;
    tree->PreOrderTraversal();
    std::cout << std::endl;

    std::cout << "Postorder:" << std::endl;
    tree->PostOrderTraversal();
    std::cout << std::endl;*/

    return(0);
}

