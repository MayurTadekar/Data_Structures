

#ifndef     _STACK_H
#define     _STACK_H

#include    "dcll.h"

struct dummy_stack;

typedef     struct dummy_stack    dummy_stack_t;
typedef     struct dummy_stack*   p_dummy_stack_t;
typedef     struct dummy_stack**  pp_dummy_stack_t;

typedef     void*   stack_t;

typedef     stack_t*   p_stack_t;

typedef     void*   data_t;

typedef     void(*SHOWDATA_PROC)(data_t data);
typedef     void(*DELETEDATA_PROC)(data_t data);

struct dummy_stack
{
    list_t list;
    size_t size;
};
#define     SIZE_dummy_stack      (sizeof(dummy_stack_t))

stack_t     create_stack();

void        stack_push(stack_t stack, data_t data);

data_t      stack_pop(stack_t  stack);
data_t      stack_peek(stack_t  stack);

void        stack_traverse(stack_t stack, SHOWDATA_PROC pshowdata);

void        stack_destroy(p_stack_t stack, DELETEDATA_PROC pdeletedata);

size_t      stack_size( stack_t s );

#endif      /* _STACK_H */

