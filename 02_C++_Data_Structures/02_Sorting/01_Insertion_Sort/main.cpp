

#include	<iostream>

#include	"insert_sort.h"


class Int
{
private:
	int data;

public:
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

};

int main(void)
{
	Int* arr[10];

	for(int i = 0; i < 10; ++i)
	{
		arr[i] = new Int( (10-i) * 10 );
	} 

	for(int i = 0; i < 10; ++i)
	{
		std::cout << *(*arr[i]) << " ";
	}	
	std::cout << std::endl;

	InsertionSort<Int*>(arr, 10);

	for(int i = 0; i < 10; ++i)
	{
		std::cout << *(*arr[i]) << " ";
	}	
	std::cout << std::endl;

	return(0);
}
