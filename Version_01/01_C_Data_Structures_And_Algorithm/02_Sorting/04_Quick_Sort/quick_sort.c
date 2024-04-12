

#include	<stdio.h>
#include	"quick_sort.h"


long 	partition(	void* ptr,
					long first,
					long last,
					data_t(*get_value)(data_t base, long index),
					void(*swap_value)(data_t d1, data_t d2),
					ret_t (*compare_value)(data_t d1, data_t d2))
{

	long pivot = last;

	long i = first - 1;

	for( long j = first; j < last; ++j )
	{
		if( SUCCESS == compare_value( get_value(ptr, j), get_value(ptr, pivot) ) )
		{
			i++;
			swap_value( get_value(ptr, i), get_value(ptr, j) );
		}
	}
	swap_value( get_value(ptr, i + 1), get_value(ptr, last) );

	return(i+1);
}

void 	quick_sort(	void* ptr,
					long first,
					long last,
					data_t(*get_value)(data_t base, long index),
					void(*swap_value)(data_t d1, data_t d2),
					ret_t (*compare_value)(data_t d1, data_t d2))
{
	if( first >= last )
		return;

		long mid = partition(	ptr,
								first,
								last,
								get_value,
								swap_value,
								compare_value);

		quick_sort( ptr,
					first,
					mid - 1,
					get_value,
					swap_value,
					compare_value);

		quick_sort(	ptr,
					mid + 1,
					last,
					get_value,
					swap_value,
					compare_value);
	
}

void 	Quick_Sort(	void* ptr,
					long size,
					data_t(*get_value)(data_t base, long index),
					void(*swap_value)(data_t data1, data_t data2),
					ret_t(*compare_value)(data_t data1, data_t data2))
{

	quick_sort( ptr,	
				0,
				size - 1,
				get_value,
				swap_value,
				compare_value);
}

