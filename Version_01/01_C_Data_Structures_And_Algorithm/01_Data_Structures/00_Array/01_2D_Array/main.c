

#include    <stdio.h>
#include    <stdlib.h>

#include    "array_2d.h"

array_t arr;
array_t arr2;

void delete_data(data_t data)
{
    printf("Deleting = %zd\n", (size_t)data);
}

void showdata(data_t data)
{
    printf("-%zd", (size_t)data);
}

void printarray(array_t arr)
{
    printf("\nArray:\n");
    printf("START\n");
    array_traversal(arr, showdata);
    printf("END\n");
}

int main(void)
{
    arr = create_array(5, 10);
    arr2 = create_array(10, 4);

    for( int ole = 0; ole < 5; ole++ )
    {
        for( int ile = 0; ile < 10; ile++ )
        {
            assign_value_at( arr, ole, ile, (data_t) (size_t) ( (ole+1) * (ile+1) ) );
        }
    }
    
    printarray(arr);
    destroy_array(&arr, delete_data);
    printarray(arr);

    for( int ole = 0; ole < 10; ole++ )
    {
        for( int ile = 0; ile < 4; ile++ )
        {
            assign_value_at( arr2, ole, ile, (data_t) (size_t) ( (ole+1) * (ile+1) ) );
        }
    }

    printarray(arr2);
    destroy_array(&arr2, delete_data);
    printarray(arr2);

    return(0);
}

