/**
 * S.G.M.P
 * @file: Queue.c
 * @brief: Implementation of DCLL based Queue in C
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 11:40:55 AM
 */

// Header
#include	<stdio.h>
#include 	<stdlib.h>

#include	"dcll.h"
#include	"queue.h"

//	Interface Functions

/**
 * Creates a new queue.
 * 
 * Function: Creates a new queue by initializing a doubly linked list.
 * 
 * identifier: create_queue
 * params: None
 * returns: Pointer to the newly created queue.
 * Notes: This function internally calls the 'createlist' function to initialize the linked list structure.
 *        The caller is responsible for managing the memory of the returned queue.
 */
extern void* create_queue(void)
{
	// Code
	return(createlist());
}

/**
 * Enqueues data into the queue.
 * 
 * Function: Enqueues data into the queue by adding a new node at the front.
 * 
 * identifier: queue_enqueue
 * params: 
 *   - queue: Pointer to the queue.
 *   - data: Data to be enqueued.
 * returns: Status of the enqueue operation.
 * Notes: This function adds a new node with the provided data to the front of the queue.
 *        It internally calls the 'dcll_insertfront' function to perform the enqueue operation.
 */
extern	ret_t	queue_enqueue(void* queue, data_t data)
{
	// Code
	return(dcll_insertfront(queue, data));
}

/**
 * Dequeues data from the queue.
 * 
 * Function: Dequeues data from the queue by removing and returning the last node's data.
 * 
 * identifier: queue_dequeue
 * params: Pointer to the queue.
 * returns: Dequeued data.
 * Notes: This function removes and returns the data from the back of the queue.
 *        It internally calls the 'dcll_removeback' function to perform the dequeue operation.
 */
extern	data_t	queue_dequeue(void* queue)
{
	// Code
	return(dcll_removeback(queue));
}

/**
 * Prints the contents of the queue.
 * 
 * Function: Prints the contents of the queue by applying the provided printing function to each data element.
 * 
 * identifier: queue_print
 * params: 
 *   - queue: Pointer to the queue.
 *   - printdata: Function pointer for printing each data element.
 * returns: None
 * Notes: This function iterates through each node of the queue, retrieves its data,
 *        and applies the provided printing function to print the data.
 */
extern	void	queue_print(void* queue, PRINTDATAPROC printdata)
{
	// Code
	long long size = dcll_size(queue);

	for(long long le = 0; le < size; ++le)
		printdata(dcll_dataat(queue, le));
}

/**
 * Destroys the queue and frees its memory.
 * 
 * Function: Destroys the queue by freeing the memory occupied by each node.
 * 
 * identifier: destroy_queue
 * params: 
 *   - queue: Pointer to the pointer to the queue.
 *   - deletedataproc: Function pointer for deleting each data element if needed.
 * returns: None
 * Notes: This function internally calls the 'dcll_destroy' function to free the memory occupied by each node in the queue.
 *        If 'deletedataproc' is provided, it will be called for each data element to perform additional cleanup.
 *        The caller is responsible for managing the memory of the queue structure itself.
 */
extern	void	destroy_queue(void** queue, DELETEDATAPROC deletedataproc)
{
	// Code
	dcll_destroy((PPDList)queue, deletedataproc);
}
