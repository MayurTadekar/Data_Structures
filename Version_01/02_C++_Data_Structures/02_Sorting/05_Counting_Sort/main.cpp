

#include	<iostream>
#include	<vector>

#include	<time.h>

#include	"counting_sort.h"

class Value
{
private:
	int data;

public:

	Value() : data(0) {}
	Value(int data) : data(data) {}
	~Value() {}

	int operator*() const { return(data); }

	friend std::ostream& operator<<(std::ostream& out, Value& i)
	{
		out << i.data;
		return(out);
	}
};

size_t toInteger(char* str)
{
	size_t value = 0;
	size_t index = 0;

	while( '\0' != str[index] )
	{
		if( !(str[index] >= '0' && str[index] <= '9') )
			return(0);

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
		std::cout << "Enter Number of elements" << std::endl;
		return(1);
	} 

	std::vector<Value*> v;

	size_t size = toInteger(argv[1]);
	if( 0 == size )
		return(1);

	size_t max = 0;

	clock_t t1, t2;
	long ms;

	srand(time(0));

	t1 = clock();
	for( int i = 0; i < size; ++i )
	{
		v.push_back(new Value( rand() % 100 + 1 ) );
	}
	t2 = clock();
	ms = timediff(t1, t2);
	std::cout << "Assigining value finished in " << ms/1000 << "s " << ms - ((ms/1000) * 1000) << "ms " << std::endl;

	t1 = clock();
	Counting_Sort(v, 100);
	t2 = clock();

	/*for( int i = 0; i < size; ++i )
	{
		std::cout << *v[i] << " ";
	}*/
	ms = timediff(t1, t2);
	std::cout << "Sorting Finished in " << ms/1000 << "s " << ms - ((ms/1000) * 1000) << "ms " << std::endl;
	
	return(0);
}

