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

// Global Data Definition
Queue<long long>* queue = NULL;

// Entry Point Function
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