


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

	printf("2\n");

	void *temp = malloc( eleSize * size );
	for( size_t i = 0 ; i < eleSize * size; ++i )
	{
		((char*)temp)[i] = ((char*)arr)[i];
	}
	printf("3\n");

	memset(count, 0, eleSize * (range+1));

	printf("4\n");
	for( int i = 0 ; i < size; ++i )
	{
		++count[ get_value(temp, i) ];
	}

	printf("5\n");
	for( index = 1; index <= range; ++index )
	{
		count[index] += count[index - 1];
	}

	printf("6\n");
	for( size_t i = 0 ; i < size; ++i )
	{
		printf("8\n");

		void* pl = get_value_ptr( arr, count[ get_value(temp, i) ] - 1 );
		printf("9\n");
		void* pr = get_value_ptr(temp, i);

		printf("10\n");
		assign_value( pl, pr );
		
		count[ get_value(temp, i) ]--;
	}

	printf("7\n");
	free(count);
	free(temp);
}
