/**
 * S.G.M.P
 * @file: 
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 13 May 2024 (Monday) 11:03:33 AM
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

// Global Data Definition
void* heap = NULL;

int compare(data_t d1, data_t d2)
{
	// Code
	if((long long)d1 > (long long)d2)
		return(SUCCESS);

	return(FAILURE);
}

int compare_equal(data_t d1, data_t d2)
{
	// Code
	if((long long)d1 == (long long)d2)
		return(SUCCESS);

	return(FAILURE);
}

void print(void* heap)
{
	// Code
	size_t length = heap_size(heap);

	printf("START|");
	for(long long le = 0; le < length; ++le)
	{
		printf("%lld|", (long long)heap_data_at(heap, le));
	}
	printf("END\n\n");
}

int main(int argc, char** argv)
{
	// Code
	heap = create_heap();

	for(long long le = 0; le < 10; ++le)
	{
		heap_insert(heap, (data_t)(long long)((le+1) * 41), compare);
		print(heap);
	}

	heap_remove(heap, (data_t)(long long)246, compare_equal);
	print(heap);

	return(0);
}