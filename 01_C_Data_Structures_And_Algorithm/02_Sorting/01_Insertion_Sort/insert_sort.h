

#ifndef 	_INSERTION_SORT
#define 	_INSERTION_SORT

//	Types & Typedefs

#define 	SUCCESS 	0
#define 	FAILURE 	1

typedef 	void * 	data_t;
typedef 	int 	ret_t;

typedef  	ret_t(*COMPARE_PROC)(data_t, data_t);
typedef 	void(*ASSIGN_VALUE_PROC)(data_t, data_t);
typedef 	data_t(*GET_VALUE_PROC)(data_t, size_t);

void 	InsertionSort(	data_t basePtr,
						int noOfElements,
						size_t sizeElements,
						GET_VALUE_PROC p_get_value_proc,
						COMPARE_PROC p_compare_proc,
						ASSIGN_VALUE_PROC p_assign_value_proc);

#endif 		/* _INSERTION_SORT */

