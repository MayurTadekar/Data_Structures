

/**
 * @author  Mayur Tadekar    
 * @date    05th May, 2022 
 * @details Driver Source code form DCLL
 */

#include    <stdio.h>
#include    <stdlib.h>

#include    "dcll.h"

list_t list;

void    showdata(dcll_data_t data)
{
    printf("%d->",(long long)data);
}

void    deletedata(dcll_data_t data)
{
    printf("delete = %d\n",(long long)data);
}

void    PrintList(list_t list)
{
    printf("List:\n");
    printf("{START}->");
    list_show(list, showdata);
    printf("{END}\n\n");
}

dcll_status_t compare(dcll_data_t d1, dcll_data_t d2)
{
    if( (long long)d1 == (long long)d2 )
        return(SUCCESS);
    
    return(FAILURE);
}

int main(void)
{
    list = create_list();
    
    list_insert(list, (dcll_data_t)10);
    list_insert(list, (dcll_data_t)20);
    list_insert(list, (dcll_data_t)30);
    list_insert(list, (dcll_data_t)40);
    list_insert(list, (dcll_data_t)50);
    list_insert(list, (dcll_data_t)60);
    list_insert(list, (dcll_data_t)70);
    list_insert(list, (dcll_data_t)80);
    list_insert(list, (dcll_data_t)90);
    list_insert(list, (dcll_data_t)100);
    
    PrintList(list);

    for( int i = 0 ; i < list_size(list); ++i )
    {
        printf(" %d => %d\n", i, (long long)list_at(list, i));
    }

    list_remove(list, (dcll_data_t)10, compare);
    list_remove(list, (dcll_data_t)50, compare);
    list_remove(list, (dcll_data_t)90, compare);
    PrintList(list);

    for( int i = 0 ; i < list_size(list); ++i )
    {
        printf(" %d => %d\n", i, (long long)list_at(list, i));
    }

    list_destroy(&list, deletedata);
    
    PrintList(list);

    return(0);    
}


