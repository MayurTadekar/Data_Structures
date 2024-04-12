

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include 	"Heap.h"

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

void* GetValue(void* ptr, size_t index)
{
	return( (int*)ptr + index );
}

ret_t Compare(data_t d1, data_t d2)
{

	if( *(int*)d1 > *(int*)d2 )
		return(SUCCESS);

	return(FAILURE);
}
	
void Swap( data_t d1, data_t d2 )
{
	int t = *(int*)d1;
	*(int*)d1 = *(int*)d2;
	*(int*)d2 = t;
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

	if( argc < 2 )
	{
		printf("\nEnter number of elements:\n");
		return(1);
	}

	srand(time(0));

	int iArr = toInteger(argv[1]);
	int *arr = (int*) malloc( sizeof(int) * iArr );

	clock_t t1, t2;

	printf("\nHeap Sort: %d\n", iArr);

	t1 = clock();
	for( int i = 0; i < iArr; ++i )
		arr[i] = (rand() % 100) + 1;
	t2 = clock();

	long ms = timediff(t1, t2);
	printf("Time to assign value in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));

	/*printf("Before Heapifying:\n");
	printf("{START}->");
	for( int i = 0; i < iArr; ++i )
	{
		printf("%d->", arr[i]);
	}
	printf("{END}\n");*/

	t1 = clock();
	HeapSort(arr, 
			iArr,
			GetValue,
			Compare,
			Swap);
	t2 = clock();

	/*printf("After Heapifying:\n");
	printf("{START}->");
	for( int i = 0; i < iArr; ++i )
	{
		printf("%d->", arr[i]);
	}
	printf("{END}\n");*/

	ms = timediff(t1, t2);
	printf("Sorting Finished in %ds %dms\n", ms/1000, ms - ( (ms / 1000) * 1000 ));	
	printf("\n\n");

	free(arr);

	return(0);
}



