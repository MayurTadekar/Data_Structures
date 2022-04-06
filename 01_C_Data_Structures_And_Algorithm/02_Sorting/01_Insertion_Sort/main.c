

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include	"insert_sort.h"

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

ret_t compare_proc_int(data_t d1, data_t d2)
{
	if( *(int*)d1 > *(int*)d2 )
		return(SUCCESS);

	return(FAILURE);
}

void assign_proc_int(data_t d1, data_t d2)
{
	*(int*)d1 = *(int*)d2;
}

void* get_value_int(data_t base, size_t index)
{
	return( (int*)base + index );
}

ret_t compare_proc_float(data_t d1, data_t d2)
{
	if( *(float*)d1 > *(float*)d2 )
		return(SUCCESS);

	return(FAILURE);
}

void assign_proc_float(data_t d1, data_t d2)
{
	*(float*)d1 = *(float*)d2;
}

void* get_value_float(data_t base, size_t index)
{
	return( (float*)base + index );
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

	clock_t t1, t2;

	size_t iArrSize = toInteger(argv[1]);
	int *arr = (int*)malloc( sizeof(int) * iArrSize );

	int fArrSize = (rand() % 100) + 1;
	float *farr = (float*)malloc( sizeof(float) * fArrSize );

	//	Integer Array
	printf("\nElements = %s\n", argv[1]);
	t1 = clock();
	//printf("\nInteger Array\n");
	for( int i = 0; i < iArrSize; ++i )
	{
		int value = (rand() % 100) + 1;
		assign_proc_int( arr + i, &value);
	}
	t2 = clock();
	
	long ms = timediff(t1, t2);
	printf("Time to assign value in %d.%d ms\n", ms/1000, ms%1000);

	/*printf("Before Sort:\n");
	printf("{START}->");
	for( int i = 0; i < iArrSize; ++i )
		printf("{%d}->", arr[i]);
	printf("{END}\n");*/

	t1 = clock();
	InsertionSort(	arr,
					iArrSize,
					sizeof(int),
					get_value_int,
					compare_proc_int,
					assign_proc_int);
	t2 = clock();
	
	ms = timediff(t1, t2);
	printf("Sorting Finished in %d.%d ms\n", ms/1000, ms%1000);

	/*printf("After Sort:\n");
	printf("{START}->");
	for( int i = 0; i < iArrSize; ++i )
		printf("{%d}->", arr[i]);
	printf("{END}\n");
*/

	/*

	printf("\n\nFloat Array\n");
	//	Float Array
	for( int i = 0; i < fArrSize; ++i )
	{
		float value = (float)rand() / (float)RAND_MAX * 50.0;
		assign_proc_float( farr + i, &value);
	}

	printf("Before Sort:\n");
	printf("{START}->");
	for( int i = 0; i < fArrSize; ++i )
		printf("{%0.2f}->", farr[i]);
	printf("{END}\n");

	InsertionSort(	farr,
					fArrSize,
					sizeof(int),
					get_value_float,
					compare_proc_float,
					assign_proc_float);

	printf("After Sort:\n");
	printf("{START}->");
	for( int i = 0; i < fArrSize; ++i )
		printf("{%0.2f}->", farr[i]);
	printf("{END}\n");*/

	return(0);
}

