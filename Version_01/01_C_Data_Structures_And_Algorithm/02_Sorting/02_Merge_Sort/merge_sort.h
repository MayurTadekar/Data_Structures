

#ifndef 	_MERGE_SORT
#define 	_MERGE_SORT

#define 	SUCCESS 	0
#define 	FAILURE 	1

typedef 	void* 		data_t;
typedef 	int 		ret_t;

typedef 	ret_t(*COMPARE_PROC)(data_t dataL, data_t dataR);
typedef 	void(*ASSIGN_VALUE_PROC)(data_t dataL, data_t dataR);
typedef 	data_t(*GET_VALUE_PROC)(data_t base, size_t index);

extern	ret_t 	MergeSort( 	data_t base,
							int size,
							int eleSize,
							COMPARE_PROC compare_proc,
							ASSIGN_VALUE_PROC assign_value_proc,
							GET_VALUE_PROC get_value_proc);

#endif 		/* _MERGE_SORT */

