

#include    <iostream>

#include    <time.h>

#include    "splaytree.h"


class Int
{
    private:
        int data;
    
    public:
        Int() : data() {}
        Int(int data) : data(data) {}
        ~Int() { std::cout << "Deleting: " << data << std::endl; }
    
        friend bool   operator< (const Int& i1, const Int& i2)
        {
            return(i1.data < i2.data);
        }

        bool    operator> (const Int& i)
        {
            return(data > i.data);
        }

        bool    operator== (const Int& i)
        {
            return(data == i.data);
        }

        friend std::ostream& operator<<(std::ostream& out, Int& i)
        {
            out << i.data;
            return(out);
        }
};

SplayTree<Int> *tree;

int main(void)
{
    tree = new SplayTree<Int>();

    srand(time(0));
    size_t size = rand() % 1000 + 1;

    for( int i = 0 ; i < size; ++i )
        tree->Insert(Int( rand() % 1000 + 1 ));

    std::cout << std::endl;
    tree->InOrderTraversal();

    std::cout << std::endl;
    tree->PreOrderTraversal();

    Int i = tree->Remove( Int(60) );
    std::cout << std::endl << "Removing:" << i;

    std::cout << std::endl;
    tree->InOrderTraversal();

    std::cout << std::endl;
    tree->PreOrderTraversal();

    i = tree->Remove( Int(40) );
    std::cout << std::endl << "Removing:" << i;

    std::cout << std::endl;
    tree->InOrderTraversal();

    std::cout << std::endl;
    tree->PreOrderTraversal();

    delete(tree);

    return(0);    
}
