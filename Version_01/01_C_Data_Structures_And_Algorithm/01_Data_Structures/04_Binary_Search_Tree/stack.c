

#include    <stdio.h>
#include    <stdlib.h>

#include    "stack.h"

void* Xmalloc(size_t size)
{
    void* p = malloc(size);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

stack_t     create_stack()
{
    p_dummy_stack_t d = (p_dummy_stack_t) Xmalloc(SIZE_dummy_stack);
    d->list = list_create();
    d->size = 0;
}

void        stack_push(stack_t stack, data_t data)
{
    if( NULL == stack )
        return;

    p_dummy_stack_t pd = (p_dummy_stack_t)stack;
    list_insert_back(pd->list, data);
    pd->size++;
}

data_t      stack_pop(stack_t  stack)
{
    if( NULL == stack ||
        0 == ((p_dummy_stack_t)stack)->size)
        return(NULL);

    p_dummy_stack_t pd = (p_dummy_stack_t)stack;

    data_t data;
    list_remove_back(pd->list, &data);
    pd->size--;
    return(data);    
}

data_t      stack_peek(stack_t  stack)
{
    if( NULL == stack ||
        0 == ((p_dummy_stack_t)stack)->size)
        return(NULL);

    p_dummy_stack_t pd = (p_dummy_stack_t)stack;

    data_t data;
    list_last(pd->list, &data);
    return(data); 
}

void        stack_traverse(stack_t stack, SHOWDATA_PROC pshowdata)
{
    if( NULL == stack ||
        0 == ((p_dummy_stack_t)stack)->size)
        return;
    
    list_show(((p_dummy_stack_t)stack)->list, pshowdata);
}

void        stack_destroy(p_stack_t pstack, DELETEDATA_PROC pdeletedata)
{
    if( NULL == pstack ||
        NULL == *(p_dummy_stack_t*)pstack ||
        0 == (*(p_dummy_stack_t*)pstack)->size)
        return;
    
    p_dummy_stack_t pd = *(p_dummy_stack_t*)pstack;
    
    list_destroy( (pp_list_t)&(pd->list), pdeletedata );
    free(*(p_dummy_stack_t*)pstack);
    *(p_dummy_stack_t*)pstack = NULL;
}   

size_t      stack_size( stack_t s ) 
{ 
    return( ((p_dummy_stack_t)s)->size ); 
}

