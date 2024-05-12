/**
 * S.G.M.P
 * @file main.cpp
 * @brief This file contains the main function to demonstrate the usage of the Heap data structure.
 * @author Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date 11 May 2024 (Saturday) 04:30:09 AM
 */

// Headers
#include <iostream>
#include <stdlib.h>

#include "heap.hpp"

Heap<long long> heap;

/**
 * @brief The main function to demonstrate the usage of the Heap data structure.
 * 
 * @details Creates a heap object, inserts elements into the heap, prints the heap after each insertion,
 *          removes an element from the heap, and prints the updated heap.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * 
 * @return int The exit status of the program.
 */
int main(int argc, char** argv)
{
	// Code

	auto func = [](long long d1, long long d2){return(d1 > d2);};

	for(long long le = 1; le <= 10; ++le)
	{	
		heap.Insert((long long)(le * 22), func);
		heap.Print();
	}

	std::cout << std::endl;

	heap.Remove(154, func);
	heap.Print();

	return(EXIT_SUCCESS);
}
