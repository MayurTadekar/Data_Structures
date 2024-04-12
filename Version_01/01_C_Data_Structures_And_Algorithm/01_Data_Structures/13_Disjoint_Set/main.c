



#include    <stdio.h>
#include    <stdlib.h>

#include    "disjointset.h"

#define     NEW_LINE    (printf("\n"))

set_t   set1;
set_t   set2;

void    showdata(set_data_t data)
{
    printf("->%zd", (size_t)data);
}

status_t compare(set_data_t d1, set_data_t d2)
{
    if( (size_t)d1 == (size_t)d2 )
        return(SUCCESS);
    
    return(FAILURE);
}

void print_set(set_t set)
{
    printf("{START}");
    set_traverse(set, showdata);
    printf("->{END}\n");
}

int main(void)
{
    set1 = make_set((set_data_t)(size_t)10);
    set2 = make_set((set_data_t)(size_t)20);
    
    NEW_LINE;
    printf("Set1:\n");
    print_set(set1);

    NEW_LINE;
    printf("Set2:\n");
    print_set(set2);

    set_union(set1, &set2);

    NEW_LINE;
    printf("Set1:\n");
    print_set(set1);
    
    NEW_LINE;
    printf("Set2:\n");
    print_set(set2);


    return(0);
}

