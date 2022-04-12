

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include	"counting_sort.h"

size_t toInteger(char* str)
{
	size_t value = 0;
	int index = 0;

	while( '\0' != str[index] )
	{
		if( !(str[index] >= '0' && str[index] <= '9') )
			return(0);
		value = value * 10 + (str[index] - '0');
		index++;
	}

	return(value);
}

long get_value(void* d1, size_t index)
{
	return( *( (int*)d1 + index) );
}

void* get_value_ptr(void* d1, size_t index)
{
	return( ( (int*)d1 + index) );
}

void assign_value(void* d1, void* d2)
{
	*(int*)d1 = *(int*)d2;
}

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char** argv)
{
	if( 2 > argc )
	{
		printf("Enter number of elements\n");
		return(1);
	}

	printf("Elements: %s\n", argv[1]);

	size_t size = toInteger(argv[1]);

	if( 0 >= size )
		return(1);

	int *arr = (int*) malloc(size * sizeof(int));
	int max = 0;

	srand(time(0));
	
	clock_t t1, t2;
	long ms;

	t1 = clock();
	for(int i = 0; i < size; ++i)
	{
		int value = (rand() % 1000) + 1;
		arr[i] = value;
		if( max < value )
			max = value;
	}
	t2 = clock();

	ms = timediff(t1, t2);
	printf("Time to assign value in %ds %dms\n", ms/1000, ms);


	/*printf("\nBefore Sorting:\n");
	for(int i = 0; i < size; ++i)
	{
		printf("->%d\n", arr[i]);
	}
	printf("\n");*/

	t1 = clock();

	printf("1\n");
	counting_sort(	arr, 
					sizeof(int),
					size, 
					max,
					get_value,
					get_value_ptr,
					assign_value);
	printf("2\n");
	t2 = clock();

	/*printf("\nAfter Sorting:\n");
	for(int i = 0; i < size; ++i)
	{
		printf("->%d", arr[i]);
	}
	printf("\n");*/

	ms = timediff(t1, t2);
	printf("Sorting Finished in %ds %dms\n", ms/1000, ms - ( (ms / 1000) * 1000 ));	
	printf("\n");

	free(arr);

	return(0);
}

