

#include	<stdio.h>

#include	"heap.h"

#define 	PARENT(i)	( i-1 / 2 )
#define  	LEFT(i)		( 2*i + 1 ) 
#define  	RIGHT(i)	( 2*i + 2 ) 

static 	int 	heapify(heap_t heap, 
						int size, 
						int i,
                        bool_t (*p_inequality_compare_proc)(data_t, data_t), 
						bool_t (*p_compare_proc)(data_t data1, data_t data2))		
{
	if( size == 1 )
		return(0);

	int largest = i;
	int l = LEFT(i);
	int r = RIGHT(i);

	//printf("largest == %d, Left = %d, Right = %d\n", (int)list_get(heap, largest), (int)list_get(heap, l), (int)list_get(heap, r));
	if( l < size &&
		SUCCESS == p_inequality_compare_proc( list_get(heap, l), list_get(heap, largest) ) )
	{
		largest = l;
	}

	if( r < size &&
		SUCCESS == p_inequality_compare_proc( list_get(heap, r), list_get(heap, largest) ) )
	{
		largest = r;
	}

	if( largest != i )
	{
		list_swap(heap, list_get(heap, i), list_get(heap, largest), p_compare_proc);
		return(largest);
		//heapify(heap, size, largest, p_inequality_compare_proc, p_compare_proc);
	}
	return(largest);
}

extern	heap_t	heap_create()
{
	return(list_create());
}

extern 	void 	heap_insert_key(heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return;

	list_insert(heap, key);

	int i = list_length(heap) - 1;

	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);
}

extern 	data_t 	heap_replace_root(	heap_t heap, data_t key, 
									bool_t (*p_compare_proc)(data_t data1, data_t data2),
		                        	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return(NULL);

	data_t data = NULL;
	list_remove_front(heap, &data);

	list_insert_front(heap, key);
	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);
	return(data);
}

extern	data_t 	heap_delete_key(heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return((data_t)0);

	data_t data;
	list_remove(heap, key, &data, p_compare_proc);

	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);

	return(data);
}

extern 	void 	heap_show(	heap_t heap,
							void(*pshow)(data_t))
{
	list_show(heap, pshow);
}

extern 	data_t 	heap_peek(	heap_t heap)
{
	return( list_get(heap, 0) );
}

extern 	data_t 	heap_delete_root(heap_t heap,
								bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
	data_t data;
	list_remove_front(heap, &data);
	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);

	return(data);
}

extern 	void 	heap_heapify(	heap_t heap,
                        		bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2))
{

	int startId = (list_length(heap) / 2) - 1;

	int oldVal = 0;
	int newVal = 0;

	for( int i = startId; i >= 0; --i )
	{
		oldVal = i;
		while( true )
		{
			newVal = heapify(heap, list_length(heap), oldVal, p_inequality_compare_proc, p_compare_proc);	
			
			if( newVal == oldVal )
				break;

			oldVal = newVal;
		}
	}
}

