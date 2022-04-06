

#ifndef 	_HEAP_H
#define	 	_HEAP_H

#include	"dcll.h"

/* Type & Typedefs */

struct Heap;

typedef 	list_t 		heap_t;
typedef 	p_list_t 	p_heap_t;
typedef 	pp_list_t 	pp_heap_t;

/*************** Heap Interface Functions ***************/

extern	heap_t 	heap_create();
extern	void 	heap_insert_key(heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern	data_t 	heap_delete_key(heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern 	data_t 	heap_delete_root(heap_t heap,
								bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2));

extern 	data_t 	heap_replace_root(	heap_t heap, data_t key, 
									bool_t (*p_compare_proc)(data_t data1, data_t data2),
		                        	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern 	void 	heap_show(	heap_t heap,
							void(*pshow)(data_t));

extern 	data_t 	heap_peek(	heap_t heap);

extern 	void 	heap_heapify(	heap_t heap,
                        		bool_t (*p_inequality_compare_proc)(data_t, data_t),
								bool_t (*p_compare_proc)(data_t data1, data_t data2));

#endif 		/* _HEAP_H */

