

#ifndef 	_HEAP_H
#define	 	_HEAP_H

#include	"dcll.h"

/* Type & Typedefs */

struct Heap;

typedef 	struct Heap* 	heap_t;
typedef 	struct Heap* 	p_heap_t;
typedef 	struct Heap** 	pp_heap_t;

struct 	Heap
{
	list_t 	list;
	size_t	ary;
};
#define 	SIZE_HEAP 	(sizeof(struct Heap))

/*************** Heap Interface Functions ***************/

extern	heap_t 	heap_create(size_t ary);
extern	void 	heap_insert_key(p_heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern	data_t 	heap_delete_key(p_heap_t heap, data_t key, 
								bool_t (*p_compare_proc)(data_t data1, data_t data2),
                            	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern 	data_t 	heap_delete_root(p_heap_t heap,
								bool_t (*p_inequality_compare_proc)(data_t, data_t), 
								bool_t (*p_compare_proc)(data_t data1, data_t data2));

extern 	data_t 	heap_replace_root(	p_heap_t heap, data_t key, 
									bool_t (*p_compare_proc)(data_t data1, data_t data2),
		                        	bool_t (*p_inequality_compare_proc)(data_t, data_t));

extern 	void 	heap_show(	p_heap_t heap,
							void(*pshow)(data_t));

extern 	data_t 	heap_peek(	p_heap_t heap);

extern 	void 	heap_heapify(	p_heap_t heap,
                        		bool_t (*p_inequality_compare_proc)(data_t, data_t),
								bool_t (*p_compare_proc)(data_t data1, data_t data2));

#endif 		/* _HEAP_H */

