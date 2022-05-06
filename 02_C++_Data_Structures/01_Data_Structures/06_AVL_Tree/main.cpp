

#include    <iostream>
#include    <time.h>

#include    "avl.h"

class Int
{
private:
    int data;

public:

    Int() : data(0) {}
    Int(int data) : data(data) {}

    bool operator>(Int& i)
    {
        return( data > i.data );
    } 
    
    bool operator<(Int& i)
    {
        return( data < i.data );
    } 

    bool operator==(Int& i)
    {
        return( data == i.data );
    }

    friend std::ostream& operator<<(std::ostream& out, Int& i)
    {
        out << i.data;
        return(out);
    }

};
AVL<Int*> *avl;

int main(void)
{
    avl = new AVL<Int*>();

    srand(time(0));

    for(int i = 0 ; i < 50; ++i)
    {
        avl->InsertData(new Int( rand() % 1000 + 1));
        avl->PreOrderTraversal();
        std::cout << std::endl;
    }   

    //avl->RemoveData(Int(20));
    //avl->PreOrderTraversal();
    //std::cout << std::endl;

    Int a = *avl->GetMax();
    std::cout << "Max : " << a << std::endl;
    
    a = *avl->GetMin();
    std::cout << "Min : " << a << std::endl;

    std::cout << avl->Height();

    return(0);
}

