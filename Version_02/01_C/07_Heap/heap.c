/**
 * S.G.M.P
 * @file: heap.c
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 May 2024 (Sunday) 08:52:10 PM
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "dcll.h"
#include "heap.h"

#define	PARENT(i)	((i-1)/2)
#define	LEFT(i)		(i*2+1)
#define	RIGHT(i)	(i*2+2)

/****************************************\
 * 										*
 *  		Helper Functions			*
 *  									*
\****************************************/

static void insert_heapify(void* heap, long long index, COMPAREPROC pcompareproc)
{
	// Code
	for(index; index > 0; index = PARENT(index))
	{
		if(SUCCESS == pcompareproc(dcll_dataat(heap, index), dcll_dataat(heap, PARENT(index))))
		{
			dcll_swap(heap, PARENT(index), index);
		}
	}
}

/****************************************\
 * 										*
 *  		Interface Functions			*
 *  									*
\****************************************/

extern void* create_heap()
{
	// Code
	return(createlist());
}

extern void heap_insert(void* heap, data_t data, COMPAREPROC pcompareproc)
{
	// Code
	dcll_insertback(heap, data);

	insert_heapify(heap, dcll_size(heap)-1, pcompareproc);
}

extern data_t heap_remove(void* heap, data_t data, COMPAREPROC pcompareproc )
{
	// Code
	long long index = 0;
	long long length = dcll_size(heap);
	for(index; index < length; ++index)
	{
		if(pcompareproc(dcll_dataat(heap, index), data) == SUCCESS)
			break;
	}

	if(index == length)
		return((data_t)0);

	dcll_swap(heap, index, length-1);
	return(dcll_removeback(heap));
}


extern size_t heap_size(void* heap)
{
	// Code
	return(dcll_size(heap));
}

extern data_t heap_data_at(void* heap, long long index)
{
	// Code
	return(dcll_dataat(heap, index));
}
