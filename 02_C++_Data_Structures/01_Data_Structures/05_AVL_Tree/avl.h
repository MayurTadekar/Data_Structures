

#pragma once

#define     MAX(a, b)   ( a > b ? a : b )

template<typename T>
class   AVL
{
public:
    AVL() : m_nr_elements(0), m_root(NULL) {}
    ~AVL() {}

    void InsertData(T data);
    T   RemoveData(T rdata);

    void InOrderTraversal();
    void PreOrderTraversal();
    void PostOrderTraversal();

    size_t Height();
    
    T   GetMax();
    T   GetMin();

private:
    
    class Node
    {
    private:
        T data;
        Node    *pleft, *pright, *parent; 

        Node() : data(0), pleft(NULL), pright(NULL), parent(NULL) {}
        Node(T data) : data(data), pleft(NULL), pright(NULL), parent(NULL) {}
        ~Node() { delete(data); }; 
    
        friend class AVL;
    };
    
    Node*   m_root;
    size_t  m_nr_elements;

    void    InOrderRun(Node* pnode);
    void    PreOrderRun(Node* pnode);
    void    PostOrderRun(Node* pnode);

    size_t  NodeHeight(Node* pnode);

    void    LeftRotate(Node* pnode);
    void    RightRotate(Node* pnode);
    
    long    GetBalance(Node* pnode);

    Node*   Successor(Node* pnode);
    Node*   Predecessor(Node* pnode);
  
    Node* NextImbalanceNode(Node* pnode);
};

//  AVL Tree Private Fuctions
template<typename T>
void    AVL<T>::InOrderRun(Node* pnode)
{
    if( NULL == pnode )
        return;
    
    InOrderRun(pnode->pleft);
    std::cout << "-" << pnode->data;
    InOrderRun(pnode->pright);   
}
   
template<typename T>
void    AVL<T>::PreOrderRun(Node* pnode)
{
    if( NULL == pnode )
        return;
    
    std::cout << "-" << pnode->data;
    PreOrderRun(pnode->pleft);
    PreOrderRun(pnode->pright);   
}
   
template<typename T>
void    AVL<T>::PostOrderRun(Node* pnode)
{
    if( NULL == pnode )
        return;
    
    PreOrderRun(pnode->pleft);
    PreOrderRun(pnode->pright);   
    std::cout << "-" << pnode->data;
}
  
template<typename T>
size_t  AVL<T>::NodeHeight(Node* pnode)
{
    if( NULL == pnode )
        return(0); 

    return( MAX(
                 NodeHeight(pnode->pleft),
                 NodeHeight(pnode->pright)
                ) + 1 
            );
}
   
template<typename T>
void    AVL<T>::LeftRotate(Node* pnode)
{
    Node* right = pnode->pright;

    right->parent = pnode->parent;
    if( NULL == pnode->parent )
        m_root = right;
    else if( pnode->parent->pright == pnode )
        pnode->parent->pright = right;
    else
        pnode->parent->pleft = right;
    
    pnode->pright = right->pleft;
    if( NULL != pnode->pright )
        pnode->pright->parent = pnode;

    right->pleft = pnode;
    pnode->parent = right;
}
   
template<typename T>
void    AVL<T>::RightRotate(Node* pnode)
{
    Node* left = pnode->pleft;

    left->parent = pnode->parent;
    if( NULL == left->parent )
        m_root = left;
    else if( pnode->parent->pleft == pnode )
        pnode->parent->pleft = left;
    else
        pnode->parent->pright = left;

    pnode->pleft = left->pright;
    if( NULL != pnode->pleft )
        pnode->pleft->parent = pnode;
    
    left->pright = pnode;
    pnode->parent = left;
}

template<typename T>
long    AVL<T>::GetBalance(Node* pnode)
{


    return( NodeHeight(pnode->pleft)
             - 
            NodeHeight(pnode->pright) );
}
   
template<typename T>
typename AVL<T>::Node*   AVL<T>::Successor(Node* pnode)
{
    Node* prun = pnode->pright;

    if( NULL == prun )
        return(NULL);
    
    while( NULL != prun->pleft )
    {   
        prun = prun->pleft;
    }

    return(prun);
}
   
template<typename T>
typename AVL<T>::Node*   AVL<T>::Predecessor(Node* pnode)
{
    Node* prun = pnode->pleft;

    if( NULL == prun )
        return(NULL);

    while( prun->pright )
        prun = prun->pright;
    
    return(prun);
}

template<typename T>
typename AVL<T>::Node* AVL<T>::NextImbalanceNode(Node* pnode)
{   
    Node* p = NULL;
    int balance = 0;
    p = pnode;
    while( NULL != p )
    {
        balance = GetBalance(p);
        if( balance < -1 || balance > 1 )
            break;
        p = p->parent;
    }
    return(p);
}


//  AVL Tree Public Methods
template<typename T>
void AVL<T>::InsertData(T data)
{
    Node* prun = m_root;
    Node* n_node = new Node(data);

    if( NULL == m_root )
    {
        m_root = n_node;
    }
    else
    {
        while(true)
        {
            if( *prun->data > *data )
            {
                if( NULL == prun->pleft)
                {
                    prun->pleft = n_node; 
                    n_node->parent = prun;
                    break;
                }
                prun = prun->pleft;
            }
            else
            {
                if( NULL == prun->pright)
                {
                    prun->pright = n_node; 
                    n_node->parent = prun;
                    break;
                }
                prun = prun->pright;
            }
        }
    }
    m_nr_elements++;
    
    Node* p = prun;// n_node->parent;
    Node* gp = NULL;

    if( NULL != p )
        gp = p->parent;
    
    int balance;

    while(gp != NULL)
    {
        balance = GetBalance(gp);
        if( balance < -1 || balance > 1 )
            break;
        gp = gp->parent;
        p = p->parent;
        n_node = n_node->parent;
    }

    if( NULL == gp )
        return;

    if( n_node == p->pleft && p == gp->pleft )
        RightRotate(gp);
    else if( n_node == p->pleft && p == gp->pright )
    {
        RightRotate(p);
        LeftRotate(gp);
    }
    else if( n_node == p->pright && p == gp->pleft )
    {
        LeftRotate(p);
        RightRotate(gp);
    }
    else
        LeftRotate(gp);

}

template<typename T>
T   AVL<T>::RemoveData(T rdata)
{
    Node* pnode = m_root;
    Node* rnode = NULL;

    while(true)
    {
        if( NULL == pnode )
            return(0); 

        if( pnode->data == rdata )
            break;

        if( pnode->data > rdata )
            pnode = pnode->pleft;
        else
            pnode = pnode->pright;
    }

    Node* successor = Successor(pnode);
    T ret_data = pnode->data;

    if( successor )
    {
        pnode->data = successor->data;
        pnode = successor;
    }
    
    rnode = pnode;

    if( successor )
    {
        if( pnode->parent != NULL )
        {
            if( pnode->parent->pleft == pnode )
                pnode->parent->pleft = pnode->pright;
            else
                pnode->parent->pright = pnode->pright;
        }

        if( NULL != pnode->pright )
            pnode->pright->parent = pnode;
    }    
    else
    {
        if( pnode->parent != NULL )
        {
            if( pnode->parent->pleft == pnode )
                pnode->parent->pleft = pnode->pleft;
            else
                pnode->parent->pright = pnode->pleft;
        }

        if( NULL != pnode->pleft )
            pnode->pleft->parent = pnode;
    }

    if( NULL == pnode->parent )
        m_root = pnode;
    
    Node *c = NULL;
    Node *gc = NULL;

    while( NULL != (rnode = NextImbalanceNode(rnode)) )
    {
        if( NodeHeight(rnode->pleft) > NodeHeight(rnode->pright) )
            c = rnode->pleft;
        else 
            c = rnode->pright;
        
        if( NodeHeight(c->pleft) > NodeHeight(c->pright) )
            gc = c->pleft;
        else
            gc = c->pright;

        if( !(rnode && c && gc) )
            break;
        
        if( c == rnode->pleft && gc == c->pleft )
            RightRotate(rnode);
        else if( c == rnode->pleft && gc == c->pright )
        {
            LeftRotate(c);
            RightRotate(rnode);
        }
        else if( c == rnode->pright && gc == c->pleft )
        {
            RightRotate(c);
            LeftRotate(rnode);
        }
        else
            LeftRotate(rnode);
    }
    return(ret_data);
}
   
template<typename T>
void AVL<T>::InOrderTraversal()
{
    //std::cout << "{START}->";
    InOrderRun(m_root);
    //std::cout << "{END}";
}
   
template<typename T>
void AVL<T>::PreOrderTraversal()
{
    //std::cout << "{START}->";
    PreOrderRun(m_root);
    //std::cout << "{END}";
}
   
template<typename T>
void AVL<T>::PostOrderTraversal()
{
    PostOrderRun(m_root);
}
   
template<typename T>
size_t AVL<T>::Height()
{
    return( NodeHeight(m_root) );
}
  
template<typename T>
T   AVL<T>::GetMax()
{
    if( NULL == m_root )
        return(0);

    Node* prun = m_root;

    while(prun->pright)
        prun = prun->pright;
    
    return( prun->data );
}
   
template<typename T>
T   AVL<T>::GetMin()
{
    if( NULL == m_root )
        return(0);

    Node* prun = m_root;

    while(prun->pleft)
        prun = prun->pleft;
    
    return( prun->data );
}

