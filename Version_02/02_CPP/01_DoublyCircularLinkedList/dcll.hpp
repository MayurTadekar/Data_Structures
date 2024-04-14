/**
 * S.G.M.P
 * @file: dcll.hpp
 * @brief: C++ Implementation of Doubly Circular Linked List
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 April 2024 (Friday) 04:41:51 PM
 */

#pragma once

// Headers
#include <iostream>

#define	SUCCESS	0
#define	FAILURE	1

template <class T>
class DCLL;

template<class E>
class Node
{
private:
	E 	m_data;
	Node<E>*	m_next;
	Node<E>*	m_prev;

	Node<E>(E init_data) : 	m_data(init_data), 
							m_next(this), 
							m_prev(this) {}

	template<class T>
	friend class DCLL;
};

template <class E>
class DCLL
{
private:
	enum class ERRORS
	{
		E_NONE = 0x00,
		E_LISTEMPTY = 0x01,
		E_DATANOTFOUND = 0x02,
		E_INDEXOUTOFBOUND = 0x03,
	};

	// typedef	Node<E>		Node<E>;
	// typedef	Node<E>*		Node<E>*;
	typedef	int 		ret_t;

	Node<E>*	m_head;
	size_t	m_size;
	ERRORS 	m_ecode;

	ret_t	GenericInsert(Node<E>* first, Node<E>* mid, Node<E>* last)
	{
		// Code
		first->m_next = mid;
		mid->m_next = last;

		mid->m_prev = first;
		last->m_prev = mid;

		m_size++;

		return(SUCCESS);
	}

	E	GenericRemove(Node<E>* node)
	{
		// Code
		Node<E>* first = node->m_prev;
		Node<E>* last = node->m_next;

		first->m_next = last;
		last->m_prev = first;

		E to_return_data = node->m_data;

		delete(node);
		node = nullptr;

		m_size--;

		return(to_return_data);
	}

	Node<E>*	LocateNode(E e_data)
	{
		// Code
		Node<E>* runner = m_head->m_next;

		while(true)
		{
			if(e_data == runner->m_data)
				return(runner);

			if(m_head == runner)
				return(nullptr);

			runner = runner->m_next;
		}

		return(nullptr);
	}

public:
	DCLL() : 	m_head(new Node<E>((E)0)), 
				m_size(0), 
				m_ecode(ERRORS::E_NONE)
	{}

	~DCLL()
	{
		// Code
		Node<E>* runner = m_head->m_next;
		runner->m_prev->m_next = nullptr;

		while(runner->m_next)
		{
			delete(runner->m_prev);
			runner = runner->m_next;
		}

		delete(runner);
	}

	ret_t 	InsertFront(E data)
	{
		// Code
		
		return(GenericInsert(m_head, new Node<E>(data), m_head->m_next));
	}

	ret_t 	InsertBack(E data)
	{
		// Code

		return(GenericInsert(m_head->m_prev, new Node<E>(data), m_head));
	}

	ret_t 	InsertAfter(E data, E e_data)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);
		
		Node<E>* node = LocateNode(e_data);

		return(GenericInsert(node, 
							new Node<E>(data), 
							node->m_next));
	}

	ret_t 	InsertBefore(E data, E e_data)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);
		Node<E>* node = LocateNode(e_data);

		return(GenericInsert(node->m_prev, 
							new Node<E>(data), 
							node));
	}

	ret_t 	InsertAt(E data, long long index)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		Node<E>* runner = m_head;
		for(long long le = 0; le < index; ++le)
			runner = runner->m_next;

		return(GenericInsert(runner, new Node<E>(data), runner->m_next));
	}

	E 	RemoveFront()
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		if( m_head == m_head->m_next )
		{
			m_ecode = ERRORS::E_LISTEMPTY;
			return((E)0);
		}

		return(GenericRemove(m_head->m_next));
	}

	E 	RemoveBack()
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		if(m_head == m_head->m_next)
		{
			m_ecode = ERRORS::E_LISTEMPTY;
			return((E)0);
		}

		return(GenericRemove(m_head->m_prev));
	}

	E 	RemoveAfter(E e_data)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		Node<E>* node = LocateNode(e_data);
		if( nullptr == node || node->m_next == m_head)
		{
			m_ecode = ERRORS::E_DATANOTFOUND;
			return((E)0);
		}

		return(GenericRemove(node->m_next));
	}

	E 	RemoveBefore(E e_data)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		Node<E>* node = LocateNode(e_data);
		if(nullptr == node || node->m_prev == m_head)
		{
			m_ecode = ERRORS::E_DATANOTFOUND;
			return((E)0);
		}

		return(GenericRemove(node->m_prev));
	}

	E 	RemoveAt(long long index)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		if(index < 0 || m_size <= index)
		{
			m_ecode = ERRORS::E_INDEXOUTOFBOUND;
			return((E)0);
		}

		Node<E>* runner = m_head->m_next;
		for(long long le = 0; le < index; ++le)
			runner = runner->m_next;

		return(GenericRemove(runner));
	}

	E DataAt(long long index)
	{
		// Code
		return((*this)[index]);
	}

	E operator[](long long index)
	{
		// Code
		if(IsEmpty())
			return(FAILURE);

		if(index < 0 || m_size <= index)
		{
			m_ecode = ERRORS::E_INDEXOUTOFBOUND;
			return((E)0);
		}

		Node<E>* runner = m_head->m_next;
		for(long long le = 0; le < index; ++le)
			runner = runner->m_next;

		return(runner->m_data);
	}

	bool	IsEmpty()
	{
		// Code
		return( 0 == m_size);
	}

	size_t Size()
	{
		// Code
		return(m_size);
	}

	// template<class T>
	// friend std::ostream operator<<(std::ostream&, DCLL<T>);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, DCLL<T>& list)
{
	//	Code
	os << "List: {START}->";
	for(long long le = 0; le < list.Size(); ++le)
	{
		os << "{" << list[le] << "}->";
	}
	os << "{END}" << std::endl << std::endl;

	return(os);
}
