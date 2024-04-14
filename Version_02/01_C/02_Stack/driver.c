/**
 * S.G.M.P
 * @file: Driver.c
 * @brief: Implementation of Driver code of Stack
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 15 April 2024 (Monday) 12:42:36 AM
 */

// Header
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Global Data Definitions
void* stack = NULL;

/**
 * Function: delete_data
 * 
 * Description: Prints the data to be deleted.
 * 
 * @param data_t data Data to be deleted.
 * @return None
 */
void delete_data(data_t data)
{
	// Code
	printf("Deleting = %lld\n", (long long)data);
}

/**
 * Function: Entry Point Function
 * 
 * Description: Entry point function for the program. Creates a stack, pushes elements onto it, prints the stack, pops an element, prints the stack again, destroys the stack, and prints the stack one last time.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns EXIT_SUCCESS upon successful execution.
 */
int main(int argc, char** argv)
{
	// Code
	stack = create_stack();

	for(long long le = 0; le < 5; ++le)
		stack_push(stack, (data_t)(long long)((le+1) * 22));

	stack_print(stack);

	stack_pop(stack);

	stack_print(stack);

	stack_destroy(&stack, delete_data);

	stack_print(stack);

	exit(EXIT_SUCCESS);
}
