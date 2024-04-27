/**
 * S.G.M.P
 * @file: stack.c
 * @brief: Implementation of DCLL based Stack
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 15 April 2024 (Monday) 12:34:20 AM
 */

// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"dcll.h"
#include	"stack.h"

/********************* Stack Interface Functions *************************/

/**
 * Function: create_stack
 * 
 * Description: Creates a stack using a doubly linked list implementation and returns a pointer to it.
 * 
 * @param None
 * @return void* Pointer to the created stack.
 */
extern	void* create_stack()
{
	// Code
	return((void*)createlist());
}

/**
 * Function: stack_push
 * 
 * Description: Pushes data onto the top of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @param data_t data Data to be pushed onto the stack.
 * @return ret_t Returns SUCCESS upon successful push operation. Returns FAILURE otherwise.
 */
extern	ret_t	stack_push(void* stack, data_t data)
{
	// Code
	return(dcll_insertback(stack, data));
}

/**
 * Function: stack_pop
 * 
 * Description: Pops data from the top of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @return data_t Returns the popped data from the top of the stack.
 */
extern	data_t 	stack_pop(void* stack)
{
	// Code
	return(dcll_removeback(stack));
}

extern	data_t stack_peek(void* stack)
{
	// Code
	return(dcll_dataat(stack, dcll_size(stack)-1));
}


/**
 * Function: stack_print
 * 
 * Description: Prints the contents of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @return None
 */
extern	void	stack_print(void* stack)
{
	// Code
	long long length = dcll_size(stack)-1;

	printf("{END}\n");
	for(length; 0<=length; --length)
		printf("  |\n{%lld}\n", (long long)dcll_dataat(stack, length));
	printf("  |\n{START}\n\n");
}

extern size_t stack_size(void* stack)
{
	// Code
	return(dcll_size(stack));
}

/**
 * Function: stack_destroy
 * 
 * Description: Destroys the stack and frees its memory.
 * 
 * @param void** pstack Pointer to the pointer of the stack.
 * @param DELETEDATAPROC deletedataproc Pointer to the function for deleting stack data.
 * @return None
 */
extern	void	stack_destroy(void** pstack, DELETEDATAPROC deletedataproc)
{
	// Code
	dcll_destroy((PPDList)pstack, deletedataproc);
}
