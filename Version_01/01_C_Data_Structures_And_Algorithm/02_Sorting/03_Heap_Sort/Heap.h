

#ifndef 	_HEAP_H
#define 	_HEAP_H

#define 	SUCCESS 	0
#define  	FAILURE 	1

typedef 	int  	ret_t;
typedef  	void*  	data_t;

int 	HeapifyMax(int *ptr,
				int size,
				int i,
				void*(p_getvalue)(data_t, size_t),
				ret_t (*p_compare)(data_t, data_t),
				void (*p_swap)(data_t, data_t));

void 	HeapSort(	int *arr,
					int size,
					void*(p_getvalue)(data_t, size_t),
					ret_t (*p_compare)(data_t, data_t),
					void (*p_swap)(data_t, data_t));

#endif 		/* _HEAP_H */

