/**
 * S.G.M.P
 * @file: driver.c
 * @brief: The driver source code for use of implementation of DCLL
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 April 2024 (Friday) 02:26:25 PM
 */

// Header
#include <stdio.h>
#include <stdlib.h>

#include "dcll.h"

// Global Data Definition
List list = NULL;

/**
 * Function: Prints the elements of a doubly linked list.
 * 
 * identifier: printlist
 * params: List list - Doubly linked list to be printed.
 * returns: void No return value.
 */
void printlist(List list)
{
	// Code
	size_t length = dcll_size(list);
	printf("List: {START}->");
	for(long long le = 0; le < length; ++le)
	{
		printf("{%lld}->", (long long)dcll_dataat(list, le));
	}
	printf("{END}\n");
	printf("\n");
}

/**
 * Function: Compares two data elements.
 * 
 * identifier: compare
 * params: data_t data1 - First data element, data_t data2 - Second data element.
 * returns: ret_t Returns SUCCESS if the two data elements are equal. Returns FAILURE otherwise.
 */
ret_t compare(data_t data1, data_t data2)
{
	// Code
	if((long long)data1 == (long long)data2)
		return(SUCCESS);

	return(FAILURE);
}

/**
 * Function: Entry point function.
 * 
 * identifier: main
 * params: int argc - Number of command-line arguments, char** argv - Array of command-line arguments.
 * returns: int Returns 0 upon successful execution.
 */
int main(int argc, char** argv)
{
	// Code
	list = createlist();

	for(long long le = 0; le < 10; ++le)
	{
		dcll_insertfront(list, (data_t)((le+1) * 11));
	}
	printlist(list);

	for(long long le = 0; le < 10; ++le)
	{
		dcll_insertback(list, (data_t)((le+1) * 22));
	}
	printlist(list);

	dcll_insertafter(list, (data_t)(long long)7171, (data_t)(long long)77, compare);
	dcll_insertafter(list, (data_t)(long long)8181, (data_t)(long long)88, compare);
	printlist(list);

	dcll_insertbefore(list, (data_t)(long long)7171, (data_t)(long long)77, compare);
	dcll_insertbefore(list, (data_t)(long long)8181, (data_t)(long long)88, compare);
	printlist(list);

	dcll_insertat(list, (data_t)(long long)7171, 10);
	dcll_insertat(list, (data_t)(long long)8181, 20);
	printlist(list);

	printf("Removed Data = %lld\n", (long long)dcll_removefront(list));
	printf("Removed Data = %lld\n", (long long)dcll_removefront(list));
	printf("Removed Data = %lld\n", (long long)dcll_removefront(list));
	printf("Removed Data = %lld\n", (long long)dcll_removefront(list));
	printlist(list);

	printf("Removed Data = %lld\n", (long long)dcll_removeback(list));
	printf("Removed Data = %lld\n", (long long)dcll_removeback(list));
	printf("Removed Data = %lld\n", (long long)dcll_removeback(list));
	printf("Removed Data = %lld\n", (long long)dcll_removeback(list));
	printlist(list);

	printf("Removed Data = %lld\n", (long long)dcll_removeat(list, 1));
	printf("Removed Data = %lld\n", (long long)dcll_removeat(list, 0));
	printf("Removed Data = %lld\n", (long long)dcll_removeat(list, 10));
	printf("Removed Data = %lld\n", (long long)dcll_removeat(list, 99));
	printlist(list);

	exit(0);
}

