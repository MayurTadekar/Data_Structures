 

#pragma     once

#define     SUCCESS     0
#define     FAILURE     1

#define     MAX(a,b)    (a>b ? a : b)

typedef     int     status_t;

typedef enum
{
    RED = 0,
    BLACK
}color_t;

template<typename T>
class RedBlackTree
{
    private:
    
        class Node
        {
            private:
                T data;
                Node *pleft, *pright, *parent;
                color_t color;

                Node() : data(), pleft(NULL), pright(NULL), parent(NULL), color(RED) {};
                Node(T data) : data(data), pleft(NULL), pright(NULL), parent(NULL), color(RED) {} 
                ~Node() { }
        
            friend class RedBlackTree;
        };

        Node *proot;
        size_t nr_elements;

        void    InsertFixup(Node* pnode);
        void    DeleteFixup(Node* pnode);

        void    Transplant(Node* u, Node* v);

        void    InorderRun(Node* pnode);
        void    PreOrderRun(Node* pnode);
        void    PostOrderRun(Node* pnode);
        
        void    LeftRotate(Node* pnode);
        void    RightRotate(Node* pnode);

        size_t  NodeHeight(Node* pnode);

        Node*   Successor(Node* pnode);

    public:

        RedBlackTree() : proot(NULL), nr_elements(0) {}

        status_t    InsertData(T ndata);
        T           RemoveData(T rdata);

        void        InorderTraversal();
        void        PreOrderTraversal();
        void        PostOrderTraversal();

        T   GetMax();
        T   GetMin();

        T   Search(T sdata);

        size_t  Height();
        size_t  GetNoOfElements() const { return(nr_elements); }
};

template<typename T>
void    RedBlackTree<T>::InsertFixup(Node* pnode)
{
    Node* prun = pnode;


    Node* parent;
    Node* grandparent;

    while(  prun != proot   &&
            BLACK != prun->color   &&
            RED == prun->parent->color)
    {

        parent = pnode->parent;
        grandparent = parent->parent;

        if( parent == grandparent->pleft )
        {
            Node* uncle = grandparent->pright;

            if( NULL != uncle   &&
                RED == uncle->color )
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                grandparent->color = RED;
                prun = grandparent;
            }
            else
            {
                if( prun == parent->pright )
                {
                    LeftRotate(parent);
                    prun = parent;
                    parent = prun->parent;
                }
                RightRotate(grandparent);
            color_t t = grandparent->color;
            grandparent->color = parent->color;
            parent->color = t;
            prun = parent;
            }
        }
        else
        {
            Node* uncle = grandparent->pleft;

            if( NULL != uncle &&
                RED == uncle->color )
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                grandparent->color = RED;
                prun = grandparent;
            }
            else
            {
                if( prun == parent->pleft )
                {
                    RightRotate(parent);
                    prun = parent;
                    parent = prun->parent;
                }

                LeftRotate(grandparent);
                color_t t = grandparent->color;
                grandparent->color = parent->color;
                parent->color = t;
                prun = parent;
            }
        }
    }


    proot->color = BLACK;
}

template<typename T>
void    RedBlackTree<T>::DeleteFixup(Node* node)
{
    Node* prun = node;

    while(  NULL != prun &&
            proot != prun &&
            prun->color == BLACK)
    {
        if( prun == prun->parent->pleft )
        {
            Node* uncle = prun->parent->pright;

            if( NULL != uncle &&
                RED == uncle->color )
            {
                uncle->color = BLACK;
                prun->parent->color = RED;
                LeftRotate(prun->parent);
                uncle = prun->parent->pright;
            } 

            if( (NULL == uncle->pleft || BLACK == uncle->pleft->color)    &&
                (NULL == uncle->pright || BLACK == uncle->pright->color) )
            {
                uncle->color = RED;
                prun = prun->parent;
            }
            else 
            {
                if( NULL == uncle->pright   ||
                    BLACK == uncle->pright->color )
                {
                    uncle->pleft->color = BLACK;
                    uncle->color = RED;
                    RightRotate(uncle);
                    uncle = prun->parent->pright;
                }
                uncle->color =  prun->parent->color;
                prun->parent->color = BLACK;
                uncle->pright->color = BLACK;
                LeftRotate(prun->parent);
            }
        }
        else
        {
            Node* uncle = prun->parent->pleft;

            if( NULL != uncle   &&
                RED == uncle->color )
            {
                uncle->color = BLACK;
                prun->parent->color = RED;
                RightRotate(prun->parent);
                uncle = prun->parent->pleft;
            }

            if( (NULL == uncle->pleft || BLACK == uncle->pleft->color)  &&
                (NULL == uncle->pright || BLACK == uncle->pright->color) )
            {
                uncle->color = RED;
                prun = prun->parent;
            }
            else
            {
                if( NULL == uncle->pleft ||
                    BLACK == uncle->pleft->color)
                {
                    uncle->pright->color = BLACK;
                    uncle->color = RED;
                    LeftRotate(uncle->parent);
                    uncle = prun->parent->pleft;
                }
                uncle->color = prun->parent->color;
                prun->parent->color = BLACK;
                uncle->pleft->color = BLACK;
                RightRotate(prun->parent);
            }
        }
        prun = proot; 
    }
    proot->color = BLACK;
}

template<typename T>
void    RedBlackTree<T>::Transplant(Node* u, Node* v)
{

    if( NULL == u->parent )
        proot = v;
    else if( u == u->parent->pleft )
        u->parent->pleft = v;
    else 
        u->parent->pright = v;

    if(v)
        v->parent = u->parent;
}

template<typename T>
void    RedBlackTree<T>::InorderRun(Node* pnode)
{
    if(!pnode)
        return;

    InorderRun(pnode->pleft);
    std::cout << "-";
    std::cout << pnode->data;
    std::cout << "/" << (pnode->color ? "B" : "R" );
    InorderRun(pnode->pright); 
}

template<typename T>
void    RedBlackTree<T>::PreOrderRun(Node* pnode)
{
    if( !pnode )
        return;
    
    std::cout << "-";
    std::cout << pnode->data;
    std::cout << "/" << (pnode->color ? "B" : "R" );
    PreOrderRun(pnode->pleft);
    PreOrderRun(pnode->pright);
}

template<typename T>
void    RedBlackTree<T>::PostOrderRun(Node* pnode)
{
    if( !pnode )
        return;

    PostOrderRun(pnode->pleft);
    PostOrderRun(pnode->pright);
    std::cout << "-";
    std::cout << pnode->data; 
    std::cout << "/" << (pnode->color ? "B" : "R" );
}

template<typename T>
void    RedBlackTree<T>::LeftRotate(Node* pnode)
{
    Node* right = pnode->pright;

    right->parent = pnode->parent;
    if(NULL == pnode->parent)
        proot = right;
    else if(pnode->parent->pleft == pnode)
        pnode->parent->pleft = right;
    else 
        pnode->parent->pright = right;
    
    pnode->pright = right->pleft;
    if( pnode->pright )
        pnode->pright->parent = pnode;

    right->pleft = pnode;
    pnode->parent = right;
}

template<typename T>
void    RedBlackTree<T>::RightRotate(Node* pnode)
{
    Node* left = pnode->pleft;

    left->parent = pnode->parent;
    if( NULL == pnode->parent )
        proot = left;
    else if( pnode->parent->pleft == pnode )
        pnode->parent->pleft = left;
    else 
        pnode->parent->pright = left;
    
    pnode->pleft = left->pright;
    if( pnode->pleft )
        pnode->pleft->parent = pnode;

    left->pright = pnode;
    pnode->parent = left;    
}

template<typename T>
size_t  RedBlackTree<T>::NodeHeight(Node* pnode)
{
    if( !pnode )
        return(0);

    return( MAX(    NodeHeight(pnode->pleft),
                    NodeHeight(pnode->pright)
                ) + 1 
            );
}

template<typename T>
typename RedBlackTree<T>::Node*   RedBlackTree<T>::Successor(Node* pnode)
{
    Node* prun = pnode->pright;

    //std::cout << "succ : " << prun->data << std::endl;
    while( NULL != prun->pleft )
        prun = prun->pleft;

    return(prun);
}

template<typename T>
status_t    RedBlackTree<T>::InsertData(T ndata)
{
    Node* newnode = new Node(ndata);

    if( NULL == proot )
        proot = newnode;
    else
    {
        Node* prun = proot;

        while(true)
        {
            if( prun->data == ndata )
                return(FAILURE);

            if( prun->data > ndata )
            {
                if(NULL == prun->pleft)
                {
                    prun->pleft = newnode;
                    newnode->parent = prun;
                    break;
                }
                prun = prun->pleft;
            }
            else
            {
                if(NULL == prun->pright)
                {
                    prun->pright = newnode;
                    newnode->parent = prun;
                    break;
                }
                prun = prun->pright;
            }
        }
    }
    nr_elements++;
    //std::cout << "Inserted1" << std::endl;

    if( newnode->parent &&
        newnode->parent->parent )
        InsertFixup(newnode);
    //std::cout << "Inserted2" << std::endl;

    proot->color = BLACK;
    return(SUCCESS);    
}

template<typename T>
T   RedBlackTree<T>::RemoveData(T rdata)
{
    Node* prun = proot;
    
    while(true)
    {
        if( prun->data == rdata )
            break;
    
        if( prun->data > rdata )
            prun = prun->pleft;
        else 
            prun = prun->pright;
        
        if( !prun )
            return((T)0);
    }
    
    Node* x;
    if( NULL == prun->pleft )
    {
        x = prun->pright;
        Transplant(prun, prun->pright);
    }
    else if( NULL == prun->pright )
    {
        x = prun->pleft;
        Transplant(prun, prun->pleft);
    }
    else
    {
        Node* successor = Successor(prun);
        x = successor->pright;

        if( successor->parent == prun )
        {
            if(x)
                x->parent = prun;
        }
        else
        {
            Transplant(successor, x);
            successor->pright = prun->pright;
            successor->pright->parent = successor;
        }
        Transplant(prun, successor);
        successor->pleft = prun->pleft;
        successor->pleft->parent = successor;
        successor->color = prun->color;
    }

    if( BLACK == prun->color )
        DeleteFixup(prun->parent);

    T ret_data = prun->data;
    delete(prun);
    nr_elements--;
    proot->color = BLACK;

    return(ret_data);
}

template<typename T>
void        RedBlackTree<T>::InorderTraversal()
{
    InorderRun(proot);
}

template<typename T>
void        RedBlackTree<T>::PreOrderTraversal()
{
    PreOrderRun(proot);
}

template<typename T>
void        RedBlackTree<T>::PostOrderTraversal()
{
    PostOrderRun(proot);
}

template<typename T>
T   RedBlackTree<T>::GetMax()
{}

template<typename T>
T   RedBlackTree<T>::GetMin()
{}

template<typename T>
T   RedBlackTree<T>::Search(T sdata)
{}

template<typename T>
size_t  RedBlackTree<T>::Height()
{
    return( NodeHeight(proot) );
}
