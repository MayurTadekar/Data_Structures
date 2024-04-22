/**
 * S.G.M.P
 * @file: Driver.cpp
 * @brief: Implementation of Driver code in CPP for Queue
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 12:14:44 PM
 */

// Headers
#include <iostream>

#include "queue.hpp"

/**
 * Global Data Definition: queue
 * 
 * Description: Global pointer to a Queue object.
 * 
 * Identifier: queue
 * 
 * Type: Queue<long long>*
 * 
 * Initial Value: NULL
 * 
 * Notes: This global variable is used to store a pointer to a Queue object.
 *        It is initialized to NULL and can be dynamically allocated and deallocated.
 */
Queue<long long>* queue = NULL;

/**
 * Entry Point Function: main
 * 
 * Description: Entry point of the program.
 * 
 * Identifier: main
 * 
 * Params:
 *   - argc: Number of command-line arguments.
 *   - argv: Array of command-line arguments.
 * 
 * Returns: Integer representing the exit status.
 * 
 * Notes: This function initializes a Queue object, enqueues data into it, prints the queue,
 *        dequeues some elements, prints the updated queue, deletes the queue object,
 *        and returns the SUCCESS status.
 */
int main(int argc, char** argv)
{
	// Code
	queue = new Queue<long long>();

	for(long long le = 0; le < 10; ++le)
		queue->Enqueue((le+1) * 21);

	std::cout << queue;

	queue->Dequeue();
	queue->Dequeue();
	queue->Dequeue();
	queue->Dequeue();

	std::cout << queue;

	delete(queue);
	queue = NULL;

	return(SUCCESS);
}
