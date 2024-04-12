

#pragma once 

#include "dcll.h"

template<typename T>
class Stack
{
private:
    LinkedList<T> *m_plist;
    size_t  m_size;

public:
    Stack() : m_plist(new LinkedList<T>), m_size(0) {}
    ~Stack() { delete(m_plist); }

    void Push(T data)
    {
        m_size++;
        m_plist->listInsertBack(data);
    }

    T Pop()
    {
        m_size--;
        return( m_plist->listRemoveBack() );
    }

    T Peek()
    {
        return( m_plist->listBack() );
    }

    size_t Size() const { return(m_size); }

    void    Traverse()
    {
        for( int i = 0; i < m_plist->size(); ++i )
        {
            std::cout << (*m_plist)[i] << std::endl;
        }
    }
};

