

#include	<stdlib.h>

#include	"insert_sort.h"

void 	InsertionSort(	data_t basePtr,
						int noOfElements,
						size_t sizeElements,
						GET_VALUE_PROC p_get_value_proc,
						COMPARE_PROC p_compare_proc,
						ASSIGN_VALUE_PROC p_assign_value_proc)
{
	//	Code

	for( int i = 1; i < noOfElements; ++i )
	{
		data_t key = malloc(sizeElements);
		for( int k = 0; k < sizeElements; ++k )
			((char*)key)[k] = ((char*)p_get_value_proc(basePtr, i))[k];

		int j = i - 1;
		while( 	j >= 0 &&
				SUCCESS == p_compare_proc( p_get_value_proc(basePtr, j), key ) )
		{
			p_assign_value_proc( p_get_value_proc(basePtr, j+1), p_get_value_proc(basePtr, j) );
			j--;
		}
		p_assign_value_proc( p_get_value_proc(basePtr, j+1), key );
		free(key);
	}
}

