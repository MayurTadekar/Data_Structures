


#include	<stdio.h>
#include	<stdlib.h>

#include	"counting_sort.h"

void 	counting_sort(	void* arr,
						size_t eleSize,
						size_t size, 
						size_t range,
						long (*get_value)(void* base, size_t index),
						void* (*get_value_ptr)(void* base, size_t index),
						void (*assign_value)(void* d1, void* d2))
{
	
	size_t *count = (size_t*)malloc( sizeof(size_t) * (range+1) );
	size_t index;

	void *temp = malloc( eleSize * size );
	for( size_t i = 0 ; i < eleSize * size; ++i )
	{
		((char*)temp)[i] = ((char*)arr)[i];
	}

	memset(count, 0, eleSize * (range+1));

	for( int i = 0 ; i < size; ++i )
	{
		++count[ get_value(temp, i) ];
	}

	for( index = 1; index <= range; ++index )
	{
		count[index] += count[index - 1];
	}

	for( int i = 0 ; i < size; ++i )
	{
		assign_value( get_value_ptr( arr, count[ get_value(temp, i) ] - 1 ), get_value_ptr(temp, i) );
		count[ get_value(temp, i) ]--;
	}

	free(count);
	free(temp);
}
