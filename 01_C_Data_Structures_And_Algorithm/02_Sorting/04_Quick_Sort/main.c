

#include	<stdio.h>
#include	<stdlib.h>

#include	<time.h>

#include	"quick_sort.h"

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int toInteger(char* str)
{
	int value = 0;
	int index = 0;

	while( '\0' != str[index] )
	{
		value = value * 10 + ( str[index] - '0' );
		index++;
	}
	return(value);
}

ret_t compare(data_t d1, data_t d2)
{
	if( *(int*)d1 < *(int*)d2 )
		return(SUCCESS);

	return(FAILURE);
}

data_t get_value(data_t base, long index)
{
	return( (int*)base + index );
}

void swap(data_t d1, data_t d2)
{
	int t = *(int*)d1;
	*(int*)d1 = *(int*)d2;
	*(int*)d2 = t;
}

int main(int argc, char **argv)
{

	if( 2 > argc )
	{
		printf("Enter Number of Elements\n");
		return(1);
	}

	clock_t t1, t2;
	long ms;

	srand(time(0));

	int size = toInteger(argv[1]);
	int *arr = (int*) malloc( size * sizeof(int) );

	t1 = clock();
	for( int i = 0; i < size; ++i )
	{
		arr[i] = (rand() % 100) + 1;
	}
	t2 = clock();

	ms = timediff(t1, t2);
	printf("Time to assign value in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));

/*	printf("\nBefore Sorting:\n");
	for( int i = 0; i < size; ++i )
	{
		printf("-%d", arr[i]);
	}
	printf("\n");
*/
	t1 = clock();
	Quick_Sort(	arr,
				size,
				get_value,
				swap,
				compare);
	t2 = clock();
	
	ms = timediff(t1, t2);
	printf("Sorted in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));

/*	printf("\nBefore Sorting:\n");
	for( int i = 0; i < size; ++i )
	{
		printf("-%d", arr[i]);
	}
	printf("\n");
*/
	return(0);
}


