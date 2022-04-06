

#include	<stdio.h>
#include	<stdlib.h>

#include	"Heap.h"

int 	HeapifyMax(int *ptr,
				int size,
				int i,
				void*(p_getvalue)(data_t, size_t),
				ret_t (*p_compare)(data_t, data_t),
				void (*p_swap)(data_t, data_t))
{

	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if( left < size	&&
		SUCCESS == p_compare( p_getvalue(ptr,left) , p_getvalue(ptr,largest) ) )
		largest = left;

	if( right < size &&
		SUCCESS == p_compare( p_getvalue(ptr,right) , p_getvalue(ptr,largest) ) )
		largest = right;

	if( largest != i )
	{
		/*int data = ptr[i];
		ptr[i] = ptr[largest];
		ptr[largest] = data;*/
	
		p_swap( p_getvalue(ptr,i), p_getvalue(ptr, largest) );
	}

	return(largest);
}

void 	HeapSort(	int *arr,
					int size,
					void*(p_getvalue)(data_t, size_t),
					ret_t (*p_compare)(data_t, data_t),
					void (*p_swap)(data_t, data_t))
{

	int oldVal = 0;
	int newVal = 0;
	for( int i = (size/2)-1; i >= 0; --i )
	{
		oldVal = i;
		while(1)
		{
			newVal = HeapifyMax(arr, 
								size, 
								oldVal,
								p_getvalue,
								p_compare,
								p_swap);
		
			if( newVal == oldVal )
				break;

			oldVal = newVal;
		}
	}

	for( int j = size-1; j >= 0; --j )
	{
		p_swap( p_getvalue(arr, 0), p_getvalue(arr, j) );

		oldVal = 0;
		while(1)
		{
			newVal = HeapifyMax(arr, 
								j+1, 
								oldVal,
								p_getvalue,
								p_compare,
								p_swap);
		
			if( newVal == oldVal )
				break;

			oldVal = newVal;
		}
	}
}
