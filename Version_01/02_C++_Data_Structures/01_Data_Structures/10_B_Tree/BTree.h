

#pragma once

#define     MAX     3

#include    <vector>

template<typename T>
class BTree
{
    private:

    class Node
    {
        private:
            Node* children[2 * MAX + 1];
            T key[2 * MAX];
            bool    isLeaf;
            int     count;

            Node() : isLeaf(true), count(0) {}
            ~Node() {}

            void    SplitChild(int index)
            {
                Node *z = new Node();
                Node *y = children[index];

                z->isLeaf = y->isLeaf;
                z->count = MAX - 1;

                int i = 0;
                for( i = 0; i < MAX - 1; ++i )
                {
                    z->key[i] = y->key[ MAX + i ];
                    z->children[i] = y->children[ MAX + i];
                }
                z->children[i] = y->children[ MAX + i];

                //std::cout << "2" << std::endl;
                for( i = count; i > index; --i )
                {
                    key[i] = key[i-1];
                    children[i+2] = children[i+1];
                }
                children[i+2] = children[i+1];
                //std::cout << "3" << std::endl;
                
                children[index+1] = z;
                key[index] = y->key[MAX-1];

                count++;
                y->count = MAX - 1;
            }

            void    InsertNonFull(T data)
            {
                int index = count-1;

                for( int i = index; i >= 0; --i )
                {
                    if( data == key[i] )
                    {
                        std::cout << "Data already present" << std::endl;
                        return;
                    }
                }


                if( isLeaf )
                {

                    while(  index >= 0   &&
                            data < key[index])
                    {
                        key[index + 1] = key[index];
                        index--;
                    }
                    key[index+1] = data;
                    
                    // for( int i = 0; i < count; ++i )
                    //     std::cout << "Data : " << key[i] << "- " << count  << std::endl;
                    // std::cout << "Data Inserted " << key[index+1] << " - " << index+1 << std::endl << std::endl ;
                    
                    count++;
                }
                else
                {
                    while(  index >= 0   &&
                            data < key[index])
                    {
                        index--;
                    }
                    index++;

                    if( children[index]->count >= 2 * MAX - 1 )
                    {
                        std::cout << "1" << std::endl;
                        SplitChild(index);
                        if( data > key[index] )
                            index++;
                    }
                    children[index]->InsertNonFull(data);
                }
            }

            void    Run(int tabCnt)
            {
                if( 0 == count )
                    return;
                
                int index = 0;

                while( index < count )
                {
                    if( !isLeaf )
                        children[index]->Run(tabCnt+1);
                    
                    for( int i = 0; i < tabCnt; ++i )
                        std::cout << "\t";

                    std::cout << /*"Value " <<*/ key[index] << std::endl;
                    index++;
                }
                //std::cout << "1" << std::endl;
                if( !isLeaf )
                    children[index]->Run(tabCnt+1);
                //std::cout << "2" << std::endl;

            }

            int     FindKey(T data)
            {
                int index = 0;
                while( key[index] < data )
                    index++;
                
                return(index);
            }

            T   RemoveFromLeaf(int index)
            {
                T retdata = key[index];

                for( int i = index; i < count; ++i )
                {
                    key[i] = key[i+1];
                }
                count--;
                return(retdata);
            }

            T   RemoveFromNonLeaf(int index)
            {
                //std::cout << "Non Leaf" << std::endl; 

                T ret_data = key[index];

                //std::cout << ret_data << std::endl;

                if( children[index]->count >= MAX )
                {
                    //std::cout<<"If" << std::endl;
                    key[index] = children[index]->key[ children[index]->count-1 ];
                    children[index]->RemoveData( key[index] );
                }
                else if( children[index+1]->count >= MAX)
                {
                    key[index] = children[index+1]->key[0];
                    children[index+1]->RemoveData( key[index] );    
                }
                else 
                {
                    //std::cout<<"else" << std::endl;
                    Node* x = children[index];
                    Node* y = children[index+1];

                    int i = 0;
                    for( i = 0; i < y->count; i++ )
                    {
                        x->key[ x->count ] = y->key[i];
                        x->children[ x->count+1 ] = y->children[i];
                        x->count++;
                    }
                    x->children[ x->count+1 ] = y->children[i];

                    for( i = index; i < count; ++i )
                    {
                        key[i] = key[i+1];
                        children[i+1] = children[i+2];
                    }                
                    count--;
                    delete(y);
                }
                return(ret_data);
            }

            void    BorrowFromPrev(int index)
            {
                Node* child = children[index];
                Node* sib = children[index-1];

                int i = 0;
                for( i = child->count; i >= 0; ++i )
                {
                    child->key[i] = child->key[i-1];
                    child->children[i+1] = child->children[i];
                }
                child->children[i+1] = child->children[i];

                child->key[ 0 ] = key[index];
                child->children[ 0 ] = sib->children[ sib->count ];

                key[index] = sib->key[ sib->count - 1];

                child->count++;
                sib->count--;
            }

            void    BorrowFromNext(int index)
            {
                Node* child = children[index];
                Node* sib = children[index+1];

                child->key[ child->count ] = key[index];
                child->children[ child->count+1 ] = sib->children[ 0 ];

                key[index] = sib->key[0];

                int i = 0;
                for( i = 0; i < sib->count; --i )
                {
                    sib->key[i] = sib->key[i+1];
                    sib->children[i] = sib->children[i+1];
                }
                sib->children[i] = sib->children[i+1];

                child->count++;
                sib->count--;
            }

            void    Merge(int index)
            {
                Node* y = children[index];
                Node* z = children[index+1];

                y->key[ y->count ] = key[index];
                y->count++;

                int i = 0;
                for( i = 0; i < z->count; ++i )
                {
                    y->key[ y->count ] = z->key[i];
                    y->children[ y->count ] = z->children[i];
                    y->count++;
                }
                y->children[ y->count ] = z->children[i];

                for( i = index; index < count; ++i )
                {
                    key[index] = key[index+1];
                    children[index+1] = children[index+2];
                }
                children[index+1] = children[index+2];

                count--;

                /*if( count == 0 && m_proot == this )
                {
                    delete(this);
                    m_proot = y;
                }*/

                delete(z);
            }

            void    Fill(int index)
            {
                if( index != 0 && children[index-1]->count > MAX )
                    BorrowFromPrev(index);
                else if(index != count && children[index+1]->count > MAX)
                    BorrowFromNext(index);
                else
                {
                    if( index <= count )
                        Merge(index);
                    else 
                        Merge(index-1); 
                }
            }

            T    RemoveData(T data)
            {
                int index = FindKey(data);

                //std::cout << "Data Delete :" << key[index] << "-" << index << "-" << data << std::endl;

                if( index < count &&
                    data == key[index] )
                {
                    if( isLeaf )
                        return(RemoveFromLeaf(index));
                    else
                        return(RemoveFromNonLeaf(index));
                }
                else
                {
                    if( index > count + 1 )
                    {
                        std::cerr << "Data Not Present" << std::endl;
                        return((T)0);
                    }

                    if( isLeaf && data != key[index])
                    {
                        std::cerr << "Data Not Present" << std::endl;
                        return((T)0);
                    }   
                    
                    if( children[index]->count < MAX - 1 )
                    {
                        Fill(index);
                    }
                    return(children[index]->RemoveData(data));
                }
            }

            friend class BTree;
        };

    Node    *m_proot;
    
    public:
        BTree() { m_proot = new Node(); }
        ~BTree() { /* DESTROY TREE */ };

        void    Insert(T ndata)
        {
            Node *run = m_proot;
            
            std::cout << "0" << std::endl;
            if( 2 * MAX - 1 == run->count )
            {
                std::cout << "0" << std::endl;
                Node * newnode = new Node();
                newnode->children[0] = m_proot;
                newnode->isLeaf = false;
                newnode->count = 0;
                m_proot = newnode;
                std::cout << "1" << std::endl;
                m_proot->SplitChild(0);
                std::cout << "2" << std::endl;
                m_proot->InsertNonFull(ndata);
            }
            else 
            {
                std::cout << "else" << std::endl;
                run->InsertNonFull(ndata);
                //std::cout << "Count : " << m_proot->count << std::endl; 
            }
        }

        T       Remove(T rdata)
        {
            T retdata = m_proot->RemoveData(rdata);

            if( 0 == m_proot->count )
            {
                Node* d = m_proot;
                m_proot = m_proot->children[0];
                delete(d);
            }

            return(retdata);
        }

        T       Search(T sdata);

        void    Traverse()
        {
            m_proot->Run(0);
        }
};

