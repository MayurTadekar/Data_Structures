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

	/**
	 * Function: Inserts a node between two given nodes.
	 * 
	 * Description: Inserts a node between the first and last nodes provided.
	 * 
	 * @param Node<E>* first Pointer to the first node.
	 * @param Node<E>* mid Pointer to the node to be inserted.
	 * @param Node<E>* last Pointer to the last node.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
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

	/**
	 * Function: Removes a node from the list.
	 * 
	 * Description: Removes the given node from the list and returns the data it contained.
	 * 
	 * @param Node<E>* node Pointer to the node to be removed.
	 * @return E Returns the data of the removed node.
	 */
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

	/**
	 * Function: Locates a node with the given data.
	 * 
	 * Description: Searches for a node containing the specified data in the list.
	 * 
	 * @param E e_data Data to be searched for.
	 * @return Node<E>* Pointer to the node containing the specified data, or nullptr if not found.
	 */
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
	/**
	 * Function: Constructor for the doubly linked list.
	 * 
	 * Description: Initializes the doubly linked list with a head node containing the data 0.
	 * 
	 * @param None
	 * @return None
	 */
	DCLL() : 	m_head(new Node<E>((E)0)), 
				m_size(0), 
				m_ecode(ERRORS::E_NONE)
	{}

	/**
	 * Function: Destructor for the doubly linked list.
	 * 
	 * Description: Destroys the doubly linked list and frees its memory.
	 * 
	 * @param None
	 * @return None
	 */
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

	/**
	 * Function: Inserts data at the front of the doubly linked list.
	 * 
	 * Description: Inserts the specified data at the front of the doubly linked list.
	 * 
	 * @param E data Data to be inserted.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
	ret_t 	InsertFront(E data)
	{
		// Code
		
		return(GenericInsert(m_head, new Node<E>(data), m_head->m_next));
	}

	/**
	 * Function: Inserts data at the back of the doubly linked list.
	 * 
	 * Description: Inserts the specified data at the back of the doubly linked list.
	 * 
	 * @param E data Data to be inserted.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
	ret_t 	InsertBack(E data)
	{
		// Code

		return(GenericInsert(m_head->m_prev, new Node<E>(data), m_head));
	}

	/**
	 * Function: Inserts data after a specific element in the doubly linked list.
	 * 
	 * Description: Inserts the specified data after the element with the provided data in the list.
	 * 
	 * @param E data Data to be inserted.
	 * @param E e_data Element after which the data is to be inserted.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
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

	/**
	 * Function: Inserts data before a specific element in the doubly linked list.
	 * 
	 * Description: Inserts the specified data before the element with the provided data in the list.
	 * 
	 * @param E data Data to be inserted.
	 * @param E e_data Element before which the data is to be inserted.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
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

	/**
	 * Function: Inserts data at a specified index in the doubly linked list.
	 * 
	 * Description: Inserts the specified data at the specified index in the list.
	 * 
	 * @param E data Data to be inserted.
	 * @param long long index Index at which the data is to be inserted.
	 * @return ret_t Returns SUCCESS upon successful insertion.
	 */
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

	/**
	 * Function: Removes data from the front of the doubly linked list.
	 * 
	 * Description: Removes the data from the front of the doubly linked list and returns it.
	 * 
	 * @param None
	 * @return E Returns the removed data.
	 */
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

	/**
	 * Function: Removes data from the back of the doubly linked list.
	 * 
	 * Description: Removes the data from the back of the doubly linked list and returns it.
	 * 
	 * @param None
	 * @return E Returns the removed data.
	 */
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

	/**
	 * Function: Removes data after a specific element in the doubly linked list.
	 * 
	 * Description: Removes the data after the element with the provided data in the list and returns it.
	 * 
	 * @param E e_data Element after which the data is to be removed.
	 * @return E Returns the removed data.
	 */
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

	/**
	 * Function: Removes data before a specific element in the doubly linked list.
	 * 
	 * Description: Removes the data before the element with the provided data in the list and returns it.
	 * 
	 * @param E e_data Element before which the data is to be removed.
	 * @return E Returns the removed data.
	 */
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

	/**
	 * Function: Removes data at a specified index in the doubly linked list.
	 * 
	 * Description: Removes the data at the specified index in the list and returns it.
	 * 
	 * @param long long index Index of the data to be removed.
	 * @return E Returns the removed data.
	 */
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

	/**
	 * Function: Retrieves data at a specified index in the doubly linked list.
	 * 
	 * Description: Retrieves the data at the specified index in the list.
	 * 
	 * @param long long index Index of the data to be retrieved.
	 * @return E Returns the retrieved data.
	 */
	E DataAt(long long index)
	{
		// Code
		return((*this)[index]);
	}

	/**
	 * Function: Overloaded subscript operator for accessing data at a specified index in the doubly linked list.
	 * 
	 * Description: Overloads the subscript operator to provide access to data at the specified index in the list.
	 * 
	 * @param long long index Index of the data to be accessed.
	 * @return E Returns the accessed data.
	 */
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

	/**
	 * Function: Checks if the doubly linked list is empty.
	 * 
	 * Description: Checks if the doubly linked list is empty.
	 * 
	 * @param None
	 * @return bool Returns true if the list is empty, false otherwise.
	 */
	bool	IsEmpty()
	{
		// Code
		return( 0 == m_size);
	}

	/**
	 * Function: Returns the size of the doubly linked list.
	 * 
	 * Description: Returns the number of elements in the doubly linked list.
	 * 
	 * @param None
	 * @return size_t Returns the size of the list.
	 */
	size_t Size()
	{
		// Code
		return(m_size);
	}

};

/**
 * Function: Overloaded output stream insertion operator for the Doubly Linked List (DCLL) class.
 * 
 * Description: Prints the elements of the doubly linked list to the output stream.
 * 
 * @param os Reference to the output stream.
 * @param list Reference to the Doubly Linked List object to be printed.
 * @return std::ostream& Reference to the output stream.
 */
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
