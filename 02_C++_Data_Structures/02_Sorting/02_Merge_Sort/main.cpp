

#include	<iostream>

#include	<time.h>

#include	"merge_sort.h"


class Int
{
private:
	int data;

public:
	Int() : data(0) {};
	Int(int data) : data(data) {};
	~Int() {}

	bool operator>(const Int& i)
	{
		return( data > i.data );
	}

	bool operator<(const Int& i)
	{
		return( data < i.data );
	}

	bool operator==(const Int& i)
	{
		return( data == i.data );
	}

	int operator*()
	{
		return(data);
	}

	friend std::ostream& operator<<(std::ostream& out, Int& i)
	{
		out << i.data;
		return(out);
	}

	void operator=(Int& i)
	{
		data = i.data;
		//return(out);
	}

	void SetValue(int data)
	{
		this->data = data;
	}

};

long toInteger(char* str)
{
	long value = 0;
	long index = 0;

	while( '\0' != str[index] )
	{
		value = value * 10 + ( str[index] - '0' );
		index++; 
	}

	return(value);
}

Int *arr;

int main(int argc, char **argv)
{
	if( argc < 2 )
	{
		std::cout << "Enter No of elements" << std::endl;
		return(1);
	}

	long size = toInteger(argv[1]);

	arr = new Int[size];

	srand(time(0));

	for(int i = 0; i < size; ++i)
	{
		arr[i].SetValue( rand() % 100 + 1 );
	} 

	std::cout << std::endl << "Before Sorting" << std::endl;
	for(int i = 0; i < size; ++i)
	{
		std::cout << *arr[i] << " ";
	}	
	std::cout << std::endl;

	Merge_Sort<Int>(arr, 10);

	std::cout << std::endl << "After Sorting" << std::endl;
	for(int i = 0; i < size; ++i)
	{
		std::cout << *arr[i] << " ";
	}	
	std::cout << std::endl;

	return(0);
}
