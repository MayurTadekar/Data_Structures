

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include	"merge_sort.h"

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

ret_t compare(data_t d1, data_t d2)
{
	if( *(size_t*)d1 >= *(size_t*)d2 )
		return(SUCCESS);

	return(FAILURE);
}

void assign_value_proc(data_t dL, data_t dR)
{
	*(size_t*)dL = *(size_t*)dR;
}

data_t get_value( data_t base, size_t index )
{
	return( (size_t*)base + index );
}

size_t toInteger(char *str)
{
	size_t value = 0;
	size_t index = 0;

	while( '\0' != str[index] )
	{
		if( str[index] >= '0' && str[index] <= '9' )
			value = (value * 10) + ( str[index] - '0' );
		else
			return(0);

		index++;
	}
	return(value);
}

int main(int argc, char **argv)
{

	srand(time(0));
	size_t iArrSize = toInteger(argv[1]);

	if( 0 == iArrSize )
		return(1);

	clock_t t1, t2;

	printf("\nElements = %s\n", argv[1]);
	size_t *arr = (size_t*) malloc(sizeof(size_t) * iArrSize);

	t1 = clock();
	for(size_t i = 0; i < iArrSize; ++i)
	{
		arr[i] = (rand() % iArrSize) + 1;
	}
	t2 = clock();
	
	long ms = timediff(t1, t2);
	printf("Time to assign value in %d.%d ms\n", ms/1000, ms%1000);

	/*printf("\nBefore Sort:\n");
	for(int i = 0; i < iArrSize; ++i)
		printf("->%zd", arr[i]);*/

	//merge_sort(arr, 0, 9);	

	//time_t start, stop;

	//time(&start);
	t1 = clock();

	MergeSort(	arr,
				iArrSize,
				sizeof(size_t),
				compare,
				assign_value_proc,
				get_value);

	t2 = clock();
	//time(&stop);

	/*printf("\nAfter Sort:\n");
	for(size_t i = 0; i < iArrSize; ++i)
		printf("->%zd", arr[i]);
	printf("\n");*/

	ms = timediff(t1, t2);
	printf("Sorting Finished in %ds %dms\n", ms/1000, ms - ( (ms / 1000) * 1000 ));	
	printf("\n\n");

	return(0);
}

