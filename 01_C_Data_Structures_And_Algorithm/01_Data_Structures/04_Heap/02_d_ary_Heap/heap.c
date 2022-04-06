

#include	<stdio.h>
#include	<stdlib.h>

#include	"heap.h"

#define 	GET_CHILD(p, c)		( (p*2) + c + 1 )

static 	int 	heapify(p_heap_t heap, 
						int size, 
						int i,
                        bool_t (*p_inequality_compare_proc)(data_t, data_t), 
						bool_t (*p_compare_proc)(data_t data1, data_t data2))		
{
	if( size == 1 )
		return(0);

	int largest = i;
	list_t list = heap->list;
	
	for( int k = 0; k < heap->ary; ++k )
	{
		int child = GET_CHILD(i, k);
		if( child < size &&
			SUCCESS == p_inequality_compare_proc( list_get(list, child), list_get(list, largest) ) )
		{
			largest = child;
		}
	}

	if( largest != i )
	{
		list_swap(list, list_get(list, i), list_get(list, largest), p_compare_proc);
	}
	return(largest);
}

extern	p_heap_t	heap_create(size_t ary)
{

	p_heap_t p = (p_heap_t) malloc(SIZE_HEAP);

	p->list = list_create();
	p->ary = ary;

	if( 0 == ary || 1 == ary )
		p->ary = 2;

	return(p);
}

extern 	void 	heap_insert_key(p_heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return;
	list_t list = heap->list;

	list_insert(list, key);

	//int i = list_length(list) - 1;

	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);
}

extern 	data_t 	heap_replace_root(	p_heap_t heap, data_t key, 
									bool_t (*p_compare_proc)(data_t data1, data_t data2),
		                        	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return(NULL);
	list_t list = heap->list;

	data_t data = NULL;
	list_remove_front(list, &data);

	list_insert_front(list, key);
	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);
	return(data);
}

extern	data_t 	heap_delete_key(p_heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t))
{
	if( NULL == heap ||
		NULL == key)
		return((data_t)0);
	list_t list = heap->list;

	data_t data;
	list_remove(list, key, &data, p_compare_proc);

	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);

	return(data);
}

extern 	void 	heap_show(	p_heap_t heap,
							void(*pshow)(data_t))
{
	list_t list = heap->list;
	list_show(list, pshow);
}

extern 	data_t 	heap_peek(	p_heap_t heap)
{
	list_t list = heap->list;
	return( list_get(list, 0) );
}

extern 	data_t 	heap_delete_root(p_heap_t heap,
								bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2))
{
	list_t list = heap->list;
	data_t data;
	list_remove_front(list, &data);
	heap_heapify(heap, p_inequality_compare_proc, p_compare_proc);

	return(data);
}

extern 	void 	heap_heapify(	p_heap_t heap,
                        		bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2))
{

	list_t list = heap->list;
	int startId = (list_length(list) / 2) - 1;

	int oldVal = 0;
	int newVal = 0;

	for( int i = startId; i >= 0; --i )
	{
		oldVal = i;
		while( true )
		{
			newVal = heapify(heap, list_length(list), oldVal, p_inequality_compare_proc, p_compare_proc);	
			
			if( newVal == oldVal )
				break;

			oldVal = newVal;
		}
	}
}

