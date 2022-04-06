

#	pragma	once

#include	"LinkedList.hpp"

#define 	PARENT(i) 	( (i-1) / 2 )
#define 	LEFT(i)		( 2*i + 1 )
#define 	RIGHT(i)	( 2*i + 2 )

enum HEAPTYPE
{
	T_MIN_HEAP = 0,
	T_MAX_HEAP
};

template<typename T>
class 	Heap
{
private:
	LinkedList<T> *list;

	HEAPTYPE m_heapType;

	int Heapify(size_t index);
	void Heapify();

public:
	Heap() : m_heapType(T_MIN_HEAP) { list = new LinkedList<T>(); }
	Heap(HEAPTYPE heapType) : m_heapType(heapType) { list = new LinkedList<T>(); }
	~Heap() { delete(list); }

	void 	InsertKey(T key);
	T 		DeleteKey(T key);
	T 		DeleteRoot();
	T 		ReplaceRoot(T newRoot);

	void 	Destroy();

	T 		Peek();

	size_t 	size() const { return(list->size()); };

	T 	operator[](size_t index);
};

/*************** Heap Private Function ***************/


template<typename T>
void Heap<T>::Heapify()
{
	int size = (list->size() / 2) - 1;

	int oldValue, newValue;

	for( int i = size; i >= 0; --i )
	{
		oldValue = i;
		while(true)
		{
			newValue = Heapify(oldValue);
			
			if( oldValue == newValue )
				break;

			oldValue = newValue;
		}
	}
}

template<typename T>
int Heap<T>::Heapify(size_t index)
{
	size_t largest = index;
	size_t left = LEFT(index);
	size_t right = RIGHT(index);

	/*std::cout << (*this)[largest] << " " << (*this)[left] << " " << (*this)[right] << " ";
	std::cout << std::endl;
*/
	if( list->size() == 0 )
		return(0);

	if( left < list->size()	&&
		( T_MAX_HEAP == m_heapType ? *(*list)[left] > *(*list)[largest] : *(*list)[left] < *(*list)[largest] ) )    
	{
		largest = left;
	}

	if( right < list->size()	&&
		( T_MAX_HEAP == m_heapType ? *(*list)[right] > *(*list)[largest] : *(*list)[right] < *(*list)[largest] ) )    
	{
		largest = right;
	}

	if( largest != index )
	{
		list->listSwap(index, largest);
	}
	return(largest);
}

/*************** Heap Interface Function ***************/

template<typename T>
void 	Heap<T>::InsertKey(T key)
{
	list->listInsertBack(key);

	Heapify();
}

template<typename T>
T 	Heap<T>::DeleteKey(T key)
{
	T data = (T)0;
	for( int i = 0 ; i < list->size(); ++i )
	{
		if( (*list)[i] == key )
			data = list->listRemovePosition(i);
	}
	Heapify();

	return( data );
}

template<typename T>
T 	Heap<T>::DeleteRoot()
{
	T data = list->listRemoveFront();
	Heapify();

	return( data );
}

template<typename T>
T 	Heap<T>::ReplaceRoot(T newRoot)
{
	T data = list->listRemoveFront();
	list->listInsertFront(newRoot);
	Heapify();
	return(data);	
}

template<typename T>
void 	Heap<T>::Destroy()
{
	list->listDestroy();
}


template<typename T>
T 	Heap<T>::Peek()
{
	return( (*list)[0] );
}

template<typename T>
T 	Heap<T>::operator[](size_t index)
{
	return( (*list)[index] );
}

