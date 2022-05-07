

/**
 * @file stack.c
 * @author Mayur Tadekar (you@domain.com)
 * @brief Source Code of Helper Stack Data Structure for Graph
 * @version 0.1
 * @date 2022-05-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//  Headers

#include    <stdio.h>
#include    <stdlib.h>

#include    "stack.h"

//  Stack Auxillary Functions

/**
 * @brief Allocating 'nr_element' * 'element_size' memory
 * 
 * @param nr_elements Number of elements
 * @param element_size size of each element
 * @return void* returning the address of allocated memory
 */
static  void*   Xcalloc(size_t nr_elements, size_t element_size)
{
    //  Code
    void* p = calloc(nr_elements, element_size);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

//  Stack Interface Functions

/**
 * @brief Create a stack object
 * 
 * @return stack_t returning the address of created stack object
 */
extern  stack_t         create_stack()
{
    p_stack_dummy_t p = (p_stack_dummy_t)Xcalloc(1, SIZE_STACK);
    p->list = create_list();
    return(p);    
}

/**
 * @brief inserting(pushing) data in stack
 * 
 * @param stack to push data
 * @param data to push in stack
 * @return status_t returning status of insertion
 */
extern  status_t        stack_push(stack_t stack, stack_data_t data)
{
    return( list_insert_back( ((p_stack_dummy_t)stack)->list, data ) );
}

/**
 * @brief removing(popping) data from stack
 * 
 * @param stack to pop data
 * @return stack_data_t returning removed data from stack
 */
extern  stack_data_t    stack_pop(stack_t stack)
{
    return( list_remove_last( ((p_stack_dummy_t)stack)->list) );
}

/**
 * @brief Retrive the data at top of stack
 * 
 * @param stack to retrive data
 * @return stack_data_t returning the retrived data
 */
extern  stack_data_t    stack_peek(stack_t stack)
{
    return( list_at( ((p_stack_dummy_t)stack)->list, list_size(((p_stack_dummy_t)stack)->list) - 1 ) );
}

/**
 * @brief Size of the stack
 * 
 * @param stack to get size
 * @return stack_data_t returning the size of the stack
 */
extern  size_t    stack_size(stack_t stack)
{
    return(list_size( ((p_stack_dummy_t)stack)->list));
}

/**
 * @brief Destroy stack
 * 
 * @param pstack Pointer to Stack object to destroy  
 */
extern  void            stack_destroy(stack_t* pstack)
{
    list_destroy( &(((p_stack_dummy_t)*pstack)->list), NULL);

    free(*pstack);
    *pstack = NULL;
}
