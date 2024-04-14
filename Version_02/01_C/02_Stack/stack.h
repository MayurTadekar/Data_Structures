/**
 * S.G.M.P
 * @file: stack.h
 * @brief: Header file implementation of Stack interface functions
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 15 April 2024 (Monday) 12:29:32 AM
 */

#ifndef _STACK_H
#define	_STACK_H

// Typedefinitions
typedef	void* data_t;
typedef	int ret_t;

typedef	void(*DELETEDATAPROC)(data_t);

/**
 * Function: create_stack
 * 
 * Description: Creates a stack using a doubly linked list implementation and returns a pointer to it.
 * 
 * @param None
 * @return void* Pointer to the created stack.
 */
extern	void* create_stack();
/**
 * Function: stack_push
 * 
 * Description: Pushes data onto the top of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @param data_t data Data to be pushed onto the stack.
 * @return ret_t Returns SUCCESS upon successful push operation. Returns FAILURE otherwise.
 */
extern 	ret_t stack_push(void* stack, data_t data);
/**
 * Function: stack_pop
 * 
 * Description: Pops data from the top of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @return data_t Returns the popped data from the top of the stack.
 */
extern	data_t stack_pop(void* stack);
/**
 * Function: stack_print
 * 
 * Description: Prints the contents of the stack.
 * 
 * @param void* stack Pointer to the stack.
 * @return None
 */
extern	void	stack_print(void* stack);
/**
 * Function: stack_destroy
 * 
 * Description: Destroys the stack and frees its memory.
 * 
 * @param void** pstack Pointer to the pointer of the stack.
 * @param DELETEDATAPROC deletedataproc Pointer to the function for deleting stack data.
 * @return None
 */
extern	void	stack_destroy(void** pstack, DELETEDATAPROC deletedataproc); 

#endif	/* _STACK_H */
