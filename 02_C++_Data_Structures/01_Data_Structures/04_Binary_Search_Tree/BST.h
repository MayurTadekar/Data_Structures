

#pragma	once

#include	<iterator>

#include 	"Stack.h"

//	TYPES & TYPEDEFS

#define 	SUCCESS 	0
#define 	FAILURE 	1

#define 	SAME_DATA 	0
#define 	SMALL_DATA 	1
#define 	BIG_DATA 	2

typedef 	int 	ret_t;

template <typename _T>
using	P_COMPARE_FUNC = ret_t(*)(_T, _T);

template <typename _T>
using 	P_SHOW_FUNC = void(*)(_T);

template <typename _T>
using 	P_DELETE_FUNC = void(*)(_T);

template <typename _T>
class BinarySearchTree
{

private:
	class Node
	{
	private:
		_T data;
		Node 	*pleft, *pright, *parent;
		
		Node() : data((_T)0), pleft(NULL), pright(NULL), parent(NULL) {}
		Node(_T data) : data(data), pleft(NULL), pright(NULL), parent(NULL) {}
		~Node() { }
		
		friend class BinarySearchTree;
	};

	Node *m_Root;

	void InOrder(Node*, P_SHOW_FUNC<_T>);
	void PreOrder(Node*, P_SHOW_FUNC<_T>);
	void PostOrder(Node*, P_SHOW_FUNC<_T>);

	void InOrder_Iterative(Node*, P_SHOW_FUNC<_T>);
	void PreOrder_Iterative(Node*, P_SHOW_FUNC<_T>);
	void PostOrder_Iterative(Node*, P_SHOW_FUNC<_T>);

	Node* 	Successor(Node* pnode);
	Node* 	Predecessor(Node* pnode);

	_T 	GenericDelete(Node*);
	Node*	LocateNode(_T e_data, P_COMPARE_FUNC<_T> compare_proc);

	void 	TreeTransplant(Node* pnode, Node* tnode);

	void 	Destroy( Node*, P_DELETE_FUNC<_T>);

public:

	BinarySearchTree() : m_Root(NULL) {};
	~BinarySearchTree() {};

	ret_t 	TreeAddNode(_T data, P_COMPARE_FUNC<_T> compare_proc);
	_T 		TreeDeleteNode(_T data, P_COMPARE_FUNC<_T> compare_proc);

	_T 		TreeSearchNode(_T data, P_COMPARE_FUNC<_T> compare_proc);

	void 	TreeDestroy(P_DELETE_FUNC<_T>);

	inline	void	TreeInOrder(P_SHOW_FUNC<_T>);
	inline	void	TreePreOrder(P_SHOW_FUNC<_T>);
	inline	void	TreePostOrder(P_SHOW_FUNC<_T>);

	inline	void	TreeInOrder_Iterative(P_SHOW_FUNC<_T>);
	inline	void	TreePreOrder_Iterative(P_SHOW_FUNC<_T>);
	inline	void	TreePostOrder_Iterative(P_SHOW_FUNC<_T>);

};

/***************** BinarySearchTree Private Functions *****************/

template <typename _T>
void BinarySearchTree<_T>::InOrder(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{

	if( pnode->pleft )
		InOrder(pnode->pleft, showdata_proc);

	showdata_proc(pnode->data);

	if( pnode->pright)
		InOrder(pnode->pright, showdata_proc);
}

template <typename _T>
void BinarySearchTree<_T>::PreOrder(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{
	showdata_proc(pnode->data);

	if( NULL != pnode->pleft )
		PreOrder(pnode->pleft, showdata_proc);

	if( NULL != pnode->pright)
		PreOrder(pnode->pright, showdata_proc);
}

template <typename _T>
void BinarySearchTree<_T>::PostOrder(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{

	if( NULL != pnode->pleft )
		PostOrder(pnode->pleft, showdata_proc);

	if( NULL != pnode->pright)
		PostOrder(pnode->pright, showdata_proc);

	showdata_proc(pnode->data);
}

template <typename _T>
void BinarySearchTree<_T>::InOrder_Iterative(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{
	Stack<Node*> *stack = new Stack<Node*>();

	Node* run = pnode;

	stack->Push(run);

	while( 0 != stack->Size())
	{
		while( run != NULL )
		{
			//std::cout << "-" << run->data << "-" << run->pleft->data << std::endl;
			run = run->pleft;
			if(!run)
				break;
			stack->Push(run);
		}

		run = stack->Pop();

		showdata_proc(run->data);

		run = run->pright;
		if( run )
			stack->Push(run);
	}
}

template <typename _T>
void BinarySearchTree<_T>::PreOrder_Iterative(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{
	Stack<Node*> *stack = new Stack<Node*>();

	stack->Push(pnode);

	while( 0 != stack->Size() )
	{
		while( pnode != NULL )
		{
			showdata_proc(pnode->data);
			pnode = pnode->pleft;
			if( !pnode )
				break;
			stack->Push(pnode);
		}

		pnode = stack->Pop();

		if( pnode->pright )
			stack->Push(pnode->pright);
		pnode = pnode->pright;
	}
}

template <typename _T>
void BinarySearchTree<_T>::PostOrder_Iterative(Node* pnode, P_SHOW_FUNC<_T> showdata_proc)
{
	Stack<Node*> *stack = new Stack<Node*>();

	bool flag = true;

	while( 0 != stack->Size() || flag)
	{
		flag = false;
		while( pnode )
		{
			if( pnode->pright )
				stack->Push(pnode->pright);
			
			stack->Push(pnode);

			pnode = pnode->pleft;
		}
		
		pnode = stack->Pop();

		if( pnode && pnode->pright == stack->Peek() )
		{
			stack->Pop();
			stack->Push(pnode);
			
			pnode = pnode->pright;
		}
		else 
		{
			showdata_proc(pnode->data);
			pnode = NULL;
		}
	}
}

template <typename _T>
typename BinarySearchTree<_T>::Node* 	BinarySearchTree<_T>::Successor( Node* pnode )
{
	BinarySearchTree<_T>::Node* prun = pnode->pleft;

	if( NULL == prun )
		return(NULL);

	while( NULL != prun->pright )
		prun = prun->pright;

	return(prun);
}

template <typename _T>
typename BinarySearchTree<_T>::Node* 	BinarySearchTree<_T>::Predecessor( Node* pnode )
{
	Node* prun = pnode->pright;

	if( NULL == prun )
		return(NULL);

	while( NULL != prun->pleft )
		prun = prun->pleft;

	return(prun);
}	

template <typename _T>
_T 	BinarySearchTree<_T>::GenericDelete(Node* pnode)
{
	if( NULL == pnode->pleft )
	{
		TreeTransplant(pnode, pnode->pright);
	}
	else if( NULL == pnode->pright)
	{
		TreeTransplant(pnode, pnode->pleft);
	}
	else
	{
		Node* successor = Successor(pnode);
		if( pnode != successor->parent )
		{
			TreeTransplant(successor, successor->pright);
			successor->pright = pnode->pright;
			successor->pright->parent =  successor->parent;
		}

		TreeTransplant(pnode, successor);
		successor->pleft = pnode->pleft;
		successor->pleft->parent = successor;
	}

	_T retData = pnode->data;
	delete(pnode);
	return(retData);
}

template <typename _T>
void 	BinarySearchTree<_T>::TreeTransplant(Node* pnode, Node* tnode)
{
	if( NULL == pnode->parent )
		m_Root = tnode;
	else if(pnode == pnode->parent->pleft)
		pnode->parent->pleft = tnode;
	else
		pnode->parent->pright = tnode;

	if( NULL != tnode )
		tnode->parent = pnode->parent;
}

template <typename _T>
void 	BinarySearchTree<_T>::Destroy( Node* pnode, P_DELETE_FUNC<_T> delete_proc)
{
	if( NULL != pnode->pleft)
		Destroy(pnode->pleft, delete_proc);

	if( NULL != pnode->pright)
		Destroy(pnode->pright, delete_proc);

	delete_proc(pnode->data);
	delete(pnode);
}

template <typename _T>
typename BinarySearchTree<_T>::Node*	BinarySearchTree<_T>::LocateNode(_T e_data, P_COMPARE_FUNC<_T> compare_proc)
{
	if( NULL == m_Root )
		return(NULL);

	Node* pnode = m_Root;

	while( true )
	{
		ret_t retValue = compare_proc(pnode->data, e_data);

		if( SAME_DATA == retValue )
		{
			return(pnode);
		}

		if( SMALL_DATA == retValue )
		{
			if( NULL == pnode->pleft )
				break;

			pnode = pnode->pleft;
		}
		else
		{
			if( NULL == pnode->pright )
				break;

			pnode = pnode->pright;
		}
	}

	return(NULL);
}

/***************** BinarySearchTree Functions *****************/

template <typename _T>
ret_t 	BinarySearchTree<_T>::TreeAddNode(_T data, P_COMPARE_FUNC<_T> compare_proc)
{
	//	Code
	if( NULL == m_Root )
	{
		m_Root = new Node(data);
	}
	else
	{
		Node* prun = m_Root;

		while(true)
		{
			if( SUCCESS == compare_proc(prun->data, data) )
			{
				if( NULL == prun->pleft )
				{
					prun->pleft = new Node(data);
					prun->pleft->parent = prun;
					break;
				}
				prun = prun->pleft;
			}
			else
			{
				if( NULL == prun->pright )
				{
					prun->pright = new Node(data);
					prun->pright->parent = prun;
					break;
				}
				prun = prun->pright;
			}
		}
	}
	return(SUCCESS);
}

template <typename _T>
_T 		BinarySearchTree<_T>::TreeDeleteNode(_T data, P_COMPARE_FUNC<_T> compare_proc)
{
	if( NULL == m_Root )
		return((_T)0);

	Node* delNode = LocateNode(data, compare_proc);
	if( NULL == delNode )
		return((_T)0);

	return( GenericDelete(delNode) );
}

template <typename _T>
_T 		BinarySearchTree<_T>::TreeSearchNode(_T data, P_COMPARE_FUNC<_T> compare_proc)
{
	Node* pnode = LocateNode(data, compare_proc);

	if( NULL == pnode)
		return((_T)0);

	return(pnode->data);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreeInOrder(P_SHOW_FUNC<_T> showdata_proc)
{	
	if(NULL != m_Root)
		InOrder(m_Root, showdata_proc);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreePreOrder(P_SHOW_FUNC<_T> showdata_proc)
{
	if(NULL != m_Root)
		PreOrder(m_Root, showdata_proc);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreePostOrder(P_SHOW_FUNC<_T> showdata_proc)
{
	if(NULL != m_Root)
		PostOrder(m_Root, showdata_proc);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreeInOrder_Iterative(P_SHOW_FUNC<_T> showdata_proc)
{	
	if(NULL != m_Root)
		InOrder_Iterative(m_Root, showdata_proc);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreePreOrder_Iterative(P_SHOW_FUNC<_T> showdata_proc)
{
	if(NULL != m_Root)
		PreOrder_Iterative(m_Root, showdata_proc);
}

template <typename _T>
inline	void BinarySearchTree<_T>::TreePostOrder_Iterative(P_SHOW_FUNC<_T> showdata_proc)
{
	if(NULL != m_Root)
		PostOrder_Iterative(m_Root, showdata_proc);
}

template <typename _T>
inline	void 	BinarySearchTree<_T>::TreeDestroy(P_DELETE_FUNC<_T> delete_proc)
{
	Destroy(m_Root, delete_proc);
	m_Root = NULL;
}

