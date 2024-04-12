

#include	<stdio.h>
#include	<stdlib.h>

#include	"merge_sort.h"

COMPARE_PROC p_compare_proc = NULL;
GET_VALUE_PROC p_get_value_proc = NULL;
ASSIGN_VALUE_PROC p_assign_value_proc = NULL;

size_t elementSize = 0;

static	void merge(int* ptr, int left, int mid, int right)
{
	int leftArr = mid - left + 1;
	int rightArr = right - mid;

	int *pLeft = (int*)malloc( sizeof(elementSize) * leftArr );
	int *pRight = (int*)malloc( sizeof(elementSize) * rightArr );

	for( int i = 0 ; i < leftArr; ++i )
		p_assign_value_proc(p_get_value_proc(pLeft, i), 
							p_get_value_proc(ptr, left + i));

	for( int i = 0 ; i < rightArr; ++i )
		p_assign_value_proc(	p_get_value_proc(pRight, i), 
								p_get_value_proc(ptr, (mid + 1 + i)));
		
	int i = 0;
	int j = 0;
	
	for( int k = left; k <= right; ++k )
	{
		if( i < leftArr && j < rightArr )
		{
			if( p_compare_proc( p_get_value_proc(pLeft, i), 
								p_get_value_proc(pRight, j) ) )
			{
				p_assign_value_proc(p_get_value_proc(ptr, k),
									p_get_value_proc(pLeft, i) );
				++i;
			}
			else
			{
				p_assign_value_proc(p_get_value_proc(ptr, k),
									p_get_value_proc(pRight, j) );
				++j;
			}
		}
		else
		{
			if( i < leftArr )
			{
				p_assign_value_proc(p_get_value_proc(ptr, k),
									p_get_value_proc(pLeft, i) );
				++i;
			}
			else if( j < rightArr )
			{
				p_assign_value_proc(p_get_value_proc(ptr, k),
									p_get_value_proc(pRight, j) );
				++j;
			}
		}
	}

	free(pLeft);
	free(pRight);
}

static	void merge_sort(int *ptr, int left, int right)
{
	if( left >= right )
		return;

	int mid = (right + left)/2;

	merge_sort(ptr, left, mid);
	merge_sort(ptr, mid + 1, right);
	merge(ptr, left, mid, right);
}

extern 	ret_t 	MergeSort( 	data_t base,
							int size,
							int eleSize,
							COMPARE_PROC compare_proc,
							ASSIGN_VALUE_PROC assign_value_proc,
							GET_VALUE_PROC get_value_proc)
{

	if( 0 == eleSize ||
		NULL == compare_proc ||
		NULL == assign_value_proc ||
		NULL == get_value_proc)
		return(FAILURE);

	elementSize = eleSize;
	p_compare_proc = compare_proc;
	p_assign_value_proc = assign_value_proc;
	p_get_value_proc = get_value_proc;

	merge_sort(base, 0, size-1);
	return(SUCCESS);
}
