

#ifndef 	_QUICK_SORT_H
#define 	_QUICK_SORT_H

#define 	SUCCESS 	0
#define 	FAILURE 	1

typedef 	void* 	data_t;
typedef 	int  	ret_t; 	

void 	Quick_Sort(	void* ptr,
					long size,
					data_t(*get_value)(data_t base, long index),
					void(*swap_value)(data_t data1, data_t data2),
					ret_t(*compare_value)(data_t data1, data_t data2));

#endif 		/* _QUICK_SORT_H */

