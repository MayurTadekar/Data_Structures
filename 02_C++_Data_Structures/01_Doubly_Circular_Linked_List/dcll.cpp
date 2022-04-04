

#include	<iostream>

#include	"dcll.hpp"

template <class _T> 
ret_t 	LinkedList<_T>::listGenericInsert(Node<_T>* first, Node<_T>* mid, Node<_T>* last)
{
	mid->pnext = last;
	mid->pprev = first;

	last->pprev = mid;
	first->pnext = mid;

	return(SUCCESS);
}

template <class _T> 
ret_t 	LinkedList<_T>::listInsertFront(_T data)
{
	if(NULL == list)
	{
		list = new Node<_T>(data);
	}
	else
	{
		return( listGenericInsert(list->pprev, new Node<_T>(data), list) );
	}
	list = list->pprev;
	return(SUCCESS);
}

template <class _T> 
ret_t 	LinkedList<_T>::listInsertBack(_T data);
template <class _T> 
ret_t 	LinkedList<_T>::listInsertPosition(_T data);
template <class _T> 
ret_t 	LinkedList<_T>::listInsertAfter(_T e_data, _T data);
template <class _T> 
ret_t 	LinkedList<_T>::listInsertBefore(_T e_data, _T data);
template <class _T> 
ret_t 	LinkedList<_T>::listInsert(_T data);

template <class _T>	
void	LinkedList<_T>::listShowData(P_SHOW_DATA<_T> pfun)
{
	Node<_T> *pnode = list;

	for(pnode; pnode->pnext != list; pnode = pnode->pnext)
	{
		pfun(pnode->data);
	}
}
