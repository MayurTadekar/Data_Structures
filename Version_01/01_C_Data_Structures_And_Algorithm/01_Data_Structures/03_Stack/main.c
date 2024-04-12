

#include    <stdio.h>
#include    <stdlib.h>

#include    "stack.h"

stack_t stack;

void showdata(data_t data)
{
    printf("\n%zd", (size_t)data);
}

int main(void)
{
    stack = create_stack();

    stack_push(stack, (data_t)(size_t)10);
    stack_push(stack, (data_t)(size_t)20);
    stack_push(stack, (data_t)(size_t)30);
    stack_push(stack, (data_t)(size_t)40);
    stack_push(stack, (data_t)(size_t)50);
    stack_push(stack, (data_t)(size_t)60);

    stack_traverse(stack, showdata);

    printf("Removed = %zd\n", (size_t)stack_pop(stack));
    printf("Removed = %zd\n", (size_t)stack_pop(stack));
    printf("Removed = %zd\n", (size_t)stack_pop(stack));

    stack_traverse(stack, showdata);

    stack_destroy(&stack, showdata);

    return(0);
}


