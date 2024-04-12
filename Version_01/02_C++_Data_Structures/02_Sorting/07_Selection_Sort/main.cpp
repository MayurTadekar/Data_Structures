

#include    <iostream>
#include    <time.h>

#include    "selection_sort.h"

int toValue(char* str)
{
    int value = 0;
    int index = 0;
    while( '\0' != str[index] )
    {
        value = value * 10 + (str[index] - '0');
        index++;
    }
    return(value);    
}


long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char **argv)
{

    if( 2 > argc )
    {
        std::cout << "Enter number of elements" << std::endl;
        return(1);
    }

    int size = toValue(argv[1]);

    int *arr = new int[size]();

	clock_t t1, t2;
	long ms;

    srand(time(0));
	
    t1 = clock();
    for( int i = 0; i < size; ++i )
    {
        arr[i] = rand() % 1000 + 1;
    }
    t2 = clock();
    
	ms = timediff(t1, t2);
	printf("Time to assign value in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));

    t1 = clock();
    SelectionSort(arr, size);  
    t2 = clock();
    
	ms = timediff(t1, t2);
	printf("Sorting Finished in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));

    /*
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";   
    }
    */

    return(0);
}

