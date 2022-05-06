

#pragma	once

#include	<iterator>

//	CONSTANT LITERALS 
#define		SUCCESS					0
#define		FAILURE 				1
#define		E_LIST_EMPTY			2
#define 	E_LIST_NOT_PRESENT 		3
#define		E_DATA_NOT_PRESENT 		4
#define 	E_DATA_ALREADY_PRESENT 	5
#define 	E_POSITION_OUT_OF_LIMIT 6

//	TYPE & TYPEDEFS

typedef 	int 	ret_t;

template <class _T> 
using 	P_SHOW_DATA = void(*)(_T data);

template <class _T> 
using 	P_DELETE_DATA = void(*)(_T data);

template <class _T>
using 	P_COMPARE_DATA = ret_t(*)(_T, _T);

//using PF = void (*)(double);	// using plus C-style type
//using P = [](double)->void;	// using plus suffix return type

//	Linked List Class Definition
template <class _T>
class LinkedList
{

private:

	//	Private Class Node
	class Node
	{
	private:
		Node	*pnext, *pprev;
		_T 	data;

		Node() {};
		Node(_T data) : data(data), pnext(this), pprev(this){};
		~Node() {}

		friend  class LinkedList;
	};

	Node* 	list;
	size_t	length;

	ret_t 	listGenericInsert(Node* first, Node* mid, Node* last);
	_T 		listGenericRemove(Node* pnode);
	Node* 	listLocateNode(_T e_data, P_COMPARE_DATA<_T> compare);
	Node* 	listLocateNode(size_t index);

public:
	LinkedList() : length(0) { list = new Node((_T)NULL); };
	~LinkedList() { delete(list); } 

	ret_t 	listInsertFront(_T data);
	ret_t	listInsertBack(_T data);
	ret_t 	listInsertPosition(_T data, size_t position);
	ret_t 	listInsertAfter(_T e_data, _T data, P_COMPARE_DATA<_T> compare);
	ret_t 	listInsertBefore(_T e_data, _T data, P_COMPARE_DATA<_T> compare);
	ret_t 	listInsert(_T data);
	
	_T 		listRemoveFront(void);
	_T 		listRemoveBack(void);
	_T 		listRemovePosition(size_t position);
	_T 		listRemoveAfter(_T e_data, P_COMPARE_DATA<_T> compare);
	_T 		listRemoveBefore(_T e_data, P_COMPARE_DATA<_T> compare);
	_T 		listRemove();

	void 	listDestroy();

	bool 	listContains(_T e_data, P_COMPARE_DATA<_T> compare);
	bool 	listIsEmpty();

	void 	listSwap(size_t index1, size_t index2);

	//LinkedList* listMerge(LinkedList*&, LinkedList*&);
	void 	listAppend(LinkedList*);
	void 	listReverse();
	LinkedList<_T>* listConcate(LinkedList* l);

	//void 	listShowData( P_SHOW_DATA<_T> pfun );
	
	size_t size() const { return(length); }

	_T 	operator[](int index);
	
	void operator+=(LinkedList* list);
	LinkedList<_T>* operator+(LinkedList* list);
	void operator=(LinkedList* list);

	class Iterator
	{
		private:
			const Node*	m_pCurrNode;

		public:
			Iterator() noexcept:
				m_pCurrNode(list) {};

			Iterator(const Node* pNode) noexcept :
				m_pCurrNode(pNode) {};

			Iterator& operator=(Node* pNode);
			Iterator& operator++();				//	Prefix Overloading
			Iterator& operator++(_T);			//	Postfix Overloading
			Iterator& operator--();
			Iterator& operator--(_T);
			bool 	operator!=(const Iterator& iterator);
			_T 		operator*();
	};

	Iterator begin();
	Iterator end();
};

/************** LinkedList ***************/
//	Private Functions
template <class _T>
ret_t 	LinkedList<_T>::listGenericInsert(Node* first, Node* mid, Node* last)
{
	mid->pnext = last;
	mid->pprev = first;

	last->pprev = mid;
	first->pnext = mid;

	length++;
	return(SUCCESS);
}

template <class _T>
_T 		LinkedList<_T>::listGenericRemove(Node* pnode)
{

	pnode->pprev->pnext = pnode->pnext;
	pnode->pnext->pprev = pnode->pprev;
	_T data = pnode->data;
	length--;
	delete(pnode);
	return(data);
}

template <class _T>
typename LinkedList<_T>::Node* 	LinkedList<_T>::listLocateNode(_T e_data, P_COMPARE_DATA<_T> compare)
{
	Node* prun = list->pnext;

	while(true)
	{
		if( SUCCESS == compare(prun->data, e_data) )
			return(prun);

		prun = prun->pnext;

		if( list == prun )
			return(NULL);
	}
	return(NULL);
}

template <class _T>
typename LinkedList<_T>::Node* 	LinkedList<_T>::listLocateNode(size_t index)
{
	if( list == list->pnext )
		return(NULL);

	Node* prun = list;
	
	for( int i = 0 ; i <= index; ++i )
	{
		prun = prun->pnext;
	}
	return(prun);
}


//	Public Functions
template <class _T>
ret_t 	LinkedList<_T>::listInsertFront(_T data)
{
	return( listGenericInsert(list, new Node(data), list->pnext) );
	
}

template <class _T>
ret_t 	LinkedList<_T>::listInsertBack(_T data)
{
	return( listGenericInsert(list->pprev, new Node(data), list) );
}

template <class _T>
ret_t 	LinkedList<_T>::listInsertPosition(_T data, size_t position)
{
	
	Node *prun = list;
	for(int i = 1; i < position; ++i)
	{
		prun = prun->pnext;
	}

	listGenericInsert(prun->pprev, new Node(data), prun);

	/*if( 1 == position)
		list = list->pprev;*/

	
	return(SUCCESS);
}

template <class _T>
ret_t 	LinkedList<_T>::listInsertAfter(_T e_data, _T data, P_COMPARE_DATA<_T> compare)
{
	Node* pnode = listLocateNode(e_data, compare);

	if( NULL == pnode )
		return(FAILURE);

	return(listGenericInsert(pnode, new Node(data), pnode->pnext));
}

template <class _T>
ret_t 	LinkedList<_T>::listInsertBefore(_T e_data, _T data, P_COMPARE_DATA<_T> compare)
{
	Node* pnode = listLocateNode(e_data, compare);

	if( NULL == pnode )
		return(FAILURE);

	return(listGenericInsert(pnode->pprev, new Node(data), pnode));
}

template <class _T>
ret_t 	LinkedList<_T>::listInsert(_T data)
{
	return( listInsertBack(data) );
}

template <class _T>
_T	LinkedList<_T>::listRemoveFront(void)
{
	return( ( list->pnext != list ? listGenericRemove(list->pnext) : (_T)NULL) );
}

template <class _T>
_T	LinkedList<_T>::listRemoveBack(void)
{
	return( ( list->pnext != list ? listGenericRemove(list->pprev) : (_T)NULL) );
}

template <class _T>
_T	LinkedList<_T>::listRemovePosition(size_t position)
{

	if( length <= position )
		return((_T)NULL);

	Node *prun = list->pnext;
	for(int i = 0; i < position; ++i)
	{
		prun = prun->pnext;
	}

	return( ( list->pnext != list ? listGenericRemove(prun) : (_T)NULL));
}

template <class _T>
_T	LinkedList<_T>::listRemoveAfter(_T e_data, P_COMPARE_DATA<_T> compare)
{
	Node* pnode = listLocateNode(e_data, compare);

	if( NULL == pnode || list == pnode->pnext)
		return((_T)NULL);

	return( ( list->pnext != list ? listGenericRemove(pnode->pnext) : (_T)NULL) );
}

template <class _T>
_T	LinkedList<_T>::listRemoveBefore(_T e_data, P_COMPARE_DATA<_T> compare)
{
	Node* pnode = listLocateNode(e_data, compare);

	if( NULL == pnode || list == pnode->pprev)
		return((_T)NULL);

	return( ( list->pnext != list ? listGenericRemove(pnode->pprev)  : (_T)NULL) );
}

template <class _T>
_T	LinkedList<_T>::listRemove()
{
	return( listRemoveBack() );
}

template <class _T>
void 	LinkedList<_T>::listDestroy()
{
	while( length != 0 )
	{
		delete ( listRemoveFront() );
	}
}


template <class _T>
bool 	LinkedList<_T>::listContains(_T e_data, P_COMPARE_DATA<_T> compare)
{
	return( NULL != listLocateNode(e_data, compare) );
}

template <class _T>
bool 	LinkedList<_T>::listIsEmpty()
{
	return( list == list->pnext );
}

/*template <class _T>
LinkedList* LinkedList<_T>::listMerge(LinkedList*&, LinkedList*&)
{

}*/

template <class _T>
void LinkedList<_T>::listAppend(LinkedList* l)
{
	//LinkedList<_T>* newList = new LinkedList<_T>();

	list->pprev->pnext = l->list->pnext;
	l->list->pnext->pprev = list->pprev;

	list->pprev = l->list->pprev;
	l->list->pprev->pnext = list;

	l->list->pprev = l->list->pnext = l->list;
	length += l->length;
	l->length = 0;
}

template <class _T>
LinkedList<_T>* LinkedList<_T>::listConcate(LinkedList* l)
{
	LinkedList<_T>* nl = new LinkedList<_T>();

	for( Iterator itr = begin(); itr != end(); ++itr )
	{
		nl->listInsertBack( *itr );
	}

	for( Iterator itr = l->begin(); itr != l->end(); ++itr )
	{
		nl->listInsertBack( *itr );
	}

	return(nl);
}

template <class _T>
void LinkedList<_T>::listReverse()
{
	Node* prun = list->pnext;

	while(prun != list)
	{
		Node *temp = prun->pnext;
		prun->pnext = prun->pprev;
		prun->pprev = temp;

		prun = prun->pprev;
	}
	
	Node *temp = prun->pnext;
	prun->pnext = prun->pprev;
	prun->pprev = temp;
}

/*template <class _T>
void 	LinkedList<_T>::listShowData( P_SHOW_DATA<_T> pfun )
{
	Node *pnode = list->pnext;

	std::cout << "{START}->";
	while(true)
	{
		pfun(pnode->data);
		std::cout << "->";
		pnode = pnode->pnext;

		if(pnode == list)
			break;
	}
	std::cout << "{END}\n";
}*/

template <class _T>
void 	LinkedList<_T>::listSwap(size_t index1, size_t index2)
{
	if( index1 < 0 ||
		index2 < 0  )
		return;

	_T t = (*this)[index1];
	listLocateNode(index1)->data = (*this)[index2];
	listLocateNode(index2)->data = t;

}


template <class _T>
_T 	LinkedList<_T>::operator[](int index)
{
	if( index > length )
	{
		//std::cerr << "Index Out Of Bound" << std::endl;
		return( (_T)0 );
	}

	Node* prun = list->pnext;
	for(int i = 0 ; i < index; ++i)
	{
		prun = prun->pnext;
	}
	return(prun->data);
}

template <class _T>
void LinkedList<_T>::operator+=(LinkedList* l)
{
	listAppend(l);
}

template <class _T>
LinkedList<_T>* LinkedList<_T>::operator+(LinkedList* l)
{
	return( listConcate(l) );
}

template <class _T>
void LinkedList<_T>::operator=(LinkedList* l)
{
	list = *l;
}

template<class _T>
typename LinkedList<_T>::Iterator LinkedList<_T>::begin()
{
	return(Iterator(list->pnext));
}

template<class _T>
typename LinkedList<_T>::Iterator LinkedList<_T>:: end()
{
	return(Iterator(list));
}

/************** LinkedList::Iterator ***************/

template<class _T>
typename LinkedList<_T>::Iterator& LinkedList<_T>::Iterator::operator=(Node* pNode)
{
	this->m_pCurrNode = pNode;
	return(*this);
}

template<class _T>
typename LinkedList<_T>::Iterator& LinkedList<_T>::Iterator::operator++()				//	Prefix Overloading
{
	if(m_pCurrNode)
		m_pCurrNode = m_pCurrNode->pnext;

	return(*this); 	
}

template<class _T>
typename LinkedList<_T>::Iterator& LinkedList<_T>::Iterator::operator++(_T)			//	Postfix Overloading
{
	Iterator itr = *this;
	++*this;
	return(itr);
}

template<class _T>
typename LinkedList<_T>::Iterator& LinkedList<_T>::Iterator::operator--()
{
	if( m_pCurrNode )
		m_pCurrNode = m_pCurrNode->pprev;

	return(*this);	
}

template<class _T>
typename LinkedList<_T>::Iterator& LinkedList<_T>::Iterator::operator--(_T)
{
	Iterator itr = *this;
	--*this;
	return(itr);
}

template<class _T>
bool LinkedList<_T>::Iterator::operator!=(const Iterator& iterator)
{
	return( m_pCurrNode != iterator.m_pCurrNode );
}

template<class _T>
_T 		LinkedList<_T>::Iterator::operator*()
{
	return(m_pCurrNode->data);
}
