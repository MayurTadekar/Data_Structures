

#include	<iostream>
#include	<time.h>

#include	"quick_sort.h"


class Int
{
private:
	int data;

public:

	bool operator<(Int& i)
	{
		return( data < i.data );
	}

	void operator=(Int& i)
	{
		this->data = i.data;
	}

	friend std::ostream& operator<<(std::ostream& out, Int& i)
	{
		out << i.data;
		return(out);
	}

	void SetValue(int data)
	{
		this->data = data;
	}
};

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
		std::cout << "Enter No of elements" << std::endl;
		return(1); 
	}

	int size = toValue(argv[1]);

	Int *arr = new Int[size]();

	clock_t t1, t2;
	long ms;

	std::cout << std::endl << "Elements:" << size << std::endl;


	srand(time(0));

	t1 = clock();
	for( int i = 0; i < size; ++i )
	{
		arr[i].SetValue( (rand()%100 + 1) );
	}
	t2 = clock();

	ms = timediff(t1, t2);
	printf("Time to assign value in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));
/*
	std::cout << "Before Sort" << std::endl;
	for( int i = 0; i < size; ++i )
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;*/

	t1 = clock();
	QuickSort(arr, size);
	t2 = clock();
	
	ms = timediff(t1, t2);
	printf("Sorted in %ds %d ms\n", ms/1000, ms - ((ms/1000)*1000));
/*
	std::cout << "After Sort" << std::endl;
	for( int i = 0; i < size; ++i )
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;*/

	delete [] arr;

	return(0);
}



