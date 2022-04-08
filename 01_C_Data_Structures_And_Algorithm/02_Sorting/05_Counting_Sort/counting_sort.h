

#ifndef 	_COUNTING_SORT
#define 	_COUNTING_SORT

void 	counting_sort(	void* arr,
						size_t eleSize,
						size_t size, 
						size_t range,
						long (*get_value)(void* base, size_t index),
						void* (*get_value_ptr)(void* base, size_t index),
						void (*assign_value)(void* d1, void* d2));

#endif 		/* _COUNTING_SORT */

