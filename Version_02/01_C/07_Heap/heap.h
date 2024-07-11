/**
 * S.G.M.P
 * @file: heap.h
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 May 2024 (Sunday) 08:47:42 PM
 */

#ifndef	_HEAP_H
#define	_HEAP_H

#ifndef	SUCCESS
#define	SUCCESS	0
#endif	/* SUCCESS */

#ifndef	FAILURE
#define	FAILURE	1
#endif	/* FAILURE */

typedef void* data_t;

typedef	int (*COMPAREPROC)(data_t, data_t);
typedef	void(*DELETEDATAPROC)(data_t);

extern void* create_heap();

extern void heap_insert(void* heap, data_t data, COMPAREPROC pcompareproc);

extern data_t heap_remove(void* heap, data_t data, COMPAREPROC pcompareproc );

extern data_t heap_data_at(void* heap, long long index);

extern size_t heap_size(void* heap);

extern int heap_destroy(void** heap, DELETEDATAPROC pdeletedataproc);

#endif	/* _HEAP_H */
