

#pragma once

#include    <iostream>
#include    <iterator>
#include    <vector>

template<typename T> 
class Vector
{
    private:
    T*  m_data;
    
    size_t  m_capacity;
    size_t  m_size;

    public:
    
    Vector() : m_capacity(1), m_size(0) { m_data = (T*) malloc(sizeof(T)); }
    ~Vector() 
    { 
        free(m_data); 
        m_capacity = 0;
        m_size = 0;   
    }

    void push_back(T ndata)
    {
        if( m_size == m_capacity )
        {
            m_capacity *= 2;
            m_data = (T*) realloc(m_data, sizeof(T) * m_capacity);
        }
        m_data[m_size++] = ndata;
        //m_size++;
    }

    T pop_back()
    {
        if( m_size == (m_capacity/2) )
        {
            m_capacity /= 2;
            m_data = (T*) realloc(m_data, m_capacity * sizeof(T));
        }
        return( m_data[--m_size] );
    }

    T at(long index)
    {
        if( index >= m_size )
        {
            std::cerr << "Index out of bound" << std::endl;
            return( (T)0 );
        }

        return( m_data[index] );
    }

    T   operator[] (long index)
    {
        return( at(index) );
    }

    Vector& operator=(const Vector& nvec)
    {
        for(size_t i = 0 ; i < nvec.size(); ++i)
            push_back( nvec[i] );
        
        return(*this);
    }

    class Iterator
    {
        private:
        T* m_curr;

        public:
        Iterator( ) : m_curr(m_data) {}
        Iterator( T* p ) : m_curr(p) {}
        ~Iterator() {}

        Iterator& operator++()
        {
            if( m_curr )
                m_curr = m_curr + 1;
            return(*this);
        }

        Iterator& operator--()
        {
            if(m_curr)
                m_curr = m_curr - 1;
            return(*this);
        }
        
        Iterator& operator++(int)
        {
            Iterator itr = *this;
            ++*this;
            return(itr);
        }

        Iterator& operator--(int)
        {
            Iterator itr = *this;
            --*this;
            return(itr);
        }

        T operator*()
        {
            return( *m_curr );
        }

        bool operator!=( const Iterator& itr )
        {
            return( m_curr != itr.m_curr );
        }

        bool operator==(const Iterator& itr)
        {
            return( m_capacity == itr.m_curr );
        }
    };
    
    Iterator  begin() const { return( Iterator(m_data) ); }
    Iterator  end()   const { return( Iterator(m_data + m_size) ); }
    
    size_t size() { return(m_size); }
    size_t capacity() { return(m_capacity); }

    T front()   { return(m_data[0]); }
    T back()    { return(m_data[m_size-1]); }
};

