

#pragma     once

#include    <functional>

#define     MAX(a,b)    (a<b ? a : b)

template<typename T, typename Compare = std::less<T>>
class SplayTree
{
private:
    Compare compare;
    size_t  nr_elements;

    struct Node
    {
        Node *pleft, *pright, *parent;
        T   data;
        Node(const T& data = T()) : data(data), pleft(NULL), pright(NULL), parent(NULL) {};
        ~Node () {}
    }*proot;

    void    LeftRotate(Node *pnode)
    {
        Node *right = pnode->pright;
        Node *left = pnode->pleft;

        right->parent = pnode->parent;
        if( NULL == pnode->parent )
            proot = right;
        else if( pnode->parent->pleft == pnode )
            pnode->parent->pleft = right;
        else 
            pnode->parent->pright = right;

        pnode->pright = right->pleft;
        if( pnode->pright )
            pnode->pright->parent = pnode;

        right->pleft = pnode;
        pnode->parent = right;
    }

    void    RightRotate(Node *pnode)
    {
        Node *left = pnode->pleft;

        left->parent = pnode->parent;
        if( NULL == pnode->parent )
            proot = left;
        else if(pnode->parent->pleft == pnode)
            pnode->parent->pleft = left;
        else 
            pnode->parent->pright = left;

        pnode->pleft = left->pright;
        if(pnode->pleft)
            pnode->pleft->parent = pnode;
        
        left->pright = pnode;
        pnode->parent = left;
    }

    void    Splay(Node *pnode)
    {
        while( pnode->parent )
        {
            if( !pnode->parent->parent )
            {
                if( pnode->parent->pleft == pnode )
                    RightRotate(pnode->parent);
                else 
                    LeftRotate(pnode->parent);
            }
            else if(pnode->parent->pleft == pnode &&
                    pnode->parent->parent->pleft == pnode->parent )
            {
                RightRotate(pnode->parent->parent);
                RightRotate(pnode->parent);
            }
            else if(pnode->parent->pright == pnode &&
                    pnode->parent->parent->pright == pnode->parent)
            {
                LeftRotate(pnode->parent->parent);
                LeftRotate(pnode->parent);
            }
            else if(pnode->parent->pleft == pnode &&
                    pnode->parent->parent->pright == pnode->parent)
            {
                RightRotate(pnode->parent);
                LeftRotate(pnode->parent);
            }
            else
            {
                LeftRotate(pnode->parent);
                RightRotate(pnode->parent);   
            }
        }
    }

    void    Transplant(Node *u, Node *v)
    {
        if( NULL == u->parent )
            proot = v;
        else if( u->parent->pleft == u )
            u->parent->pleft = v;
        else 
            u->parent->pright = v;
        
        if(v)
            v->parent = u->parent;
    }

    Node*    Successor(Node *pnode)
    {
        Node *prun = pnode->pright;

        while( NULL != prun->pleft )
            prun = prun->pleft;
        
        return(prun);
    }

    void    InOrderRun(Node *pnode)
    {
        if( !pnode )
            return;

        InOrderRun(pnode->pleft);
        std::cout << "-"; 
        std::cout << pnode->data;
        InOrderRun(pnode->pright);
    }

    void    PreOrderRun(Node *pnode)
    {
        if( !pnode )
            return;
        
        std::cout << "-"; 
        std::cout << pnode->data;
        PreOrderRun(pnode->pleft);
        PreOrderRun(pnode->pright);
    }
    
    void    PostOrderRun(Node *pnode)
    {
        if( !pnode )
            return;
        
        PostOrderRun(pnode->pleft);
        PostOrderRun(pnode->pright);
        std::cout << "-"; 
        std::cout << pnode->data;
    }

    void    PostOrderDestroy(Node *pnode)
    {
        if( !pnode )
            return;

        PostOrderDestroy(pnode->pleft);
        PostOrderDestroy(pnode->pright);
        delete(pnode);
    }

    Node*   SearchNode(T& sdata)
    {
        Node* prun = proot;

        while(prun)
        {
            if( compare(prun->data, sdata) )
                prun = prun->pright;
            else if( compare(sdata, prun->data) )
                prun = prun->pleft;
            else 
                return(prun);
        }

        return(NULL);
    }

    size_t  NodeHeight(Node *pnode)
    {
        if(!pnode)
            return(0);
        
        return( MAX(    NodeHeight(pnode->pleft),
                        NodeHeight(pnode->pright)
                    ) + 1
                );
    }

public:
    SplayTree() : proot(NULL), nr_elements(0) {}
    ~SplayTree()
    { 
        PostOrderDestroy(proot); 
        proot = NULL;
        nr_elements = 0;
    }

    void    Insert(T ndata)
    {
        Node *node = new Node(ndata);
        if( NULL == proot )
        {
            proot = node;
        }
        else 
        {
            Node *prun = proot;
            while(true)
            {
                if( compare(prun->data, ndata) )
                {
                    if( NULL == prun->pright )
                    {
                        prun->pright = node;
                        break;
                    }
                    prun = prun->pright;
                }
                else 
                {
                    if( NULL == prun->pleft )
                    {
                        prun->pleft = node;
                        break;
                    }
                    prun = prun->pleft;
                }
            }
            node->parent = prun;
        }
        nr_elements++;
        
        Splay(node);
    }

    T       Remove(T rdata)
    {
        if( 0 == nr_elements )
            return((T)0);
        
        Node *pnode = SearchNode(rdata);
        if( NULL == pnode )
            return((T)0);
        
        Splay(pnode);

        if( !pnode->pleft )
        {
            Transplant(pnode, pnode->pright);
        }
        else if( !pnode->pright )
        {
            Transplant(pnode, pnode->pleft);
        }
        else 
        {
            Node *successor = Successor(pnode);
            if( successor != pnode->pright )
            {
                Transplant(successor, successor->pright);
                successor->pright = pnode->pright;
                successor->pright->parent = successor;
            }
            Transplant(pnode, successor);
            successor->pleft = pnode->pleft;
            successor->pleft->parent = successor;
        }
        T ret_data = pnode->data;
        delete(pnode);
        nr_elements--;
        return(ret_data);
    }

    T       Search(T& sdata)
    {
        if( 0 == nr_elements )
            return((T)0);
        
        return( SearchNode(sdata)->data );
    }

    void    InOrderTraversal()
    {
        std::cout << "Inorder:" << std::endl;
        InOrderRun(proot);
    }

    void    PreOrderTraversal()
    {
        std::cout << "PreOrder:" << std::endl;
        PreOrderRun(proot);
    }

    void    PostOrderTraversal()
    {
        std::cout << "PostOrder:" << std::endl;
        PostOrderRun(proot);
    }
    
    T       GetMin()
    {
        Node *prun = proot;
        while(NULL != prun->pleft)
            prun = prun->pleft;
        
        return( prun->data );
    }

    T       GetMax()
    {
        Node *prun = proot;
        while(NULL != prun->pright)
            prun = prun->pright;
        
        return(prun->data);
    }

    size_t  Height()
    {
        if( 0 == nr_elements )
            return(0);
        
        return( NodeHeight(proot) );
    }
    
    size_t  ElementCount() const { return(nr_elements); }
};
