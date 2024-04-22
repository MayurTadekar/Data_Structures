/**
 * S.G.M.P
 * @file: queue.h
 * @brief: The header file of DCLL based queue in C
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 11:41:18 AM
 */

#ifndef	_QUEUE_H
#define	_QUEUE_H

// Typedefinitions
typedef	int 	ret_t;
typedef	void*	data_t;

typedef	void(*PRINTDATAPROC)(data_t);
typedef void(*DELETEDATAPROC)(data_t);

extern void* create_queue(void);
extern ret_t queue_enqueue(void*	queue, data_t data);
extern data_t queue_dequeue(void* queue);

extern void queue_print(void* queue, PRINTDATAPROC printdata);
extern void queue_destroy(void** queue, DELETEDATAPROC deletedata);

#endif /* _QUEUE_H */