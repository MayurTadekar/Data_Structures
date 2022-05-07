

/**
 *  @author Mayur Tadekar   
 *  @date   07th May, 2022 
 *  @details    Header file for all interface functions and 
 *              required types definitions for Stack 
 */

#ifndef     _STACK_H
#define     _STACK_H

//  Literals and Type definitions
#include    "dcll.h"

struct stack_dummy;

typedef     struct stack_dummy      stack_dummy_t;
typedef     struct stack_dummy*     p_stack_dummy_t;
typedef     struct stack_dummy**    pp_stack_dummy_t;

typedef     void*   stack_t;

typedef     int     status_t;

typedef     dcll_data_t     stack_data_t;

struct stack_dummy
{
    list_t list;
};
#define     SIZE_STACK      (sizeof(stack_dummy_t))

//  Stack Auxillary Functions
static  void*   Xcalloc(size_t nr_elements, size_t element_size);

//  Stack Interface Functions
extern  stack_t         create_stack();

extern  status_t        stack_push(stack_t stack, stack_data_t);

extern  stack_data_t    stack_pop(stack_t stack);

extern  stack_data_t    stack_peek(stack_t stack);

extern  size_t      stack_size(stack_t stack);

extern  void            stack_destroy(stack_t* pstack);

#endif      /* _STACK_H */

