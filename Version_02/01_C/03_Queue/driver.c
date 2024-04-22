/**
 * S.G.M.P
 * @file: driver.c
 * @brief: Implementation of Driver code using Queue
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 11:50:35 AM
 */

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// Global Data Definition
void*	queue = NULL;

/**
 * Prints the data element.
 * 
 * Function: Prints the provided data element.
 * 
 * identifier: print_data
 * params: data - Data to be printed.
 * returns: None
 * Notes: This function prints the provided data element using the printf function.
 */
void print_data(data_t data)
{
	// Code
	printf("{%lld}->", (long long)data);
}

/**
 * Deletes the data element.
 * 
 * Function: Deletes the provided data element.
 * 
 * identifier: delete_data
 * params: data - Data to be deleted.
 * returns: None
 * Notes: This function prints a message indicating the deletion of the provided data element using the printf function.
 */
void detele_data(data_t data)
{
	// Code
	printf("Deleting : %lld\n", (long long)data);
}

/**
 * Prints the contents of the queue.
 * 
 * Function: Prints the contents of the queue.
 * 
 * identifier: print_queue
 * params: queue - Pointer to the queue.
 * returns: None
 * Notes: This function prints the start and end markers of the queue and then calls queue_print to print the data elements of the queue.
 */
void print_queue(void* queue)
{
	// Code
	printf("{START}->");
	queue_print(queue, print_data);
	printf("{END}\n\n");
}

/**
 * Entry Point Function.
 * 
 * Function: Entry point of the program.
 * 
 * identifier: main
 * params: 
 *   - argc: Number of command-line arguments.
 *   - argv: Array of command-line arguments.
 * returns: Integer representing the exit status.
 * Notes: This function initializes a queue, enqueues data into it, prints the queue,
 *        dequeues some elements, prints the updated queue, destroys the queue, prints the empty queue,
 *        and returns 0 to indicate successful program execution.
 */
int main(int argc, char** argv)
{
	// Code
	queue = create_queue();

	for(long long le = 0; le < 10; ++le)
		queue_enqueue(queue, (data_t)(long long)((le+1) * 22));

	print_queue(queue);

	queue_dequeue(queue);
	queue_dequeue(queue);
	queue_dequeue(queue);
	queue_dequeue(queue);

	print_queue(queue);

	destroy_queue(&queue, detele_data);

	print_queue(queue);

	return(0);
}
