

#include	<iostream>

#include	<time.h>

#include	"Heap.h"


class Int
{
public:
	int data;

	Int(int data) : data(data) {};
	~Int() { std::cout << "d=>" << data << " "; }

	bool operator>(Int& i)
	{
		return( data > i.data);
	}

	bool operator<(Int& i)
	{
		return( data < i.data);
	}

	bool operator==(Int& i)
	{
		return( data == i.data);
	}	

	friend std::ostream& operator<<(std::ostream& out, Int& i);
};

std::ostream& operator<<(std::ostream& out, Int& i)
{
	out << i.data;
	return( out );
}	

Heap<Int*> *h;
//Heap<Int> *hm;

void ShowData(Heap<Int*> *h)
{
	int limit = 1;
	int l = limit;

	std::cout << "{START}->\n";
	for( int i = 0; i < h->size(); ++i )
	{	
		if( i == l )
		{
			std::cout << std::endl;
			limit = limit * 2;
			l = l + limit;
		}
		//std::cout << "=" << l << "=" ;

		std::cout << *(*h)[i] << "->";
		if( i % 2 == 0 )
			std::cout << " ";
	}
	std::cout << "{END}";
}

int main(void)
{

	h = new Heap<Int*>();
	//hm = new Heap<Int>(T_MAX_HEAP);

	srand(time(0));

	size_t  iArr = ( rand() % 100 ) + 1;
	int *arr = (int*)malloc(sizeof(int) * iArr);

	for( size_t i = 0; i < iArr; ++i )
		arr[i] = rand() % 100 + 1;

	for( size_t i = 0; i < iArr; ++i )
		h->InsertKey(new Int( arr[i] ));

	std::cout << std::endl << "Min Heap" << std::endl;
	ShowData(h);
	std::cout << std::endl;

	Int* i = new Int(arr[rand() % 10]);
	std::cout << "Deleting = " << h->DeleteKey( i ) << std::endl;
	std::cout << std::endl << "Min Heap" << std::endl;
	ShowData(h);
	std::cout << std::endl;
	delete(i);

	std::cout << "Deleting = " << *h->DeleteRoot() << std::endl;
	std::cout << std::endl << "Min Heap" << std::endl;
	ShowData(h);
	std::cout << std::endl;

	int rep = rand() % 100 + 1;
	i = new Int(rep);

	std::cout << "Replacing " << *h->ReplaceRoot(i) << " with " << rep << std::endl;
	std::cout << std::endl << "Min Heap" << std::endl;
	ShowData(h);
	std::cout << std::endl;

	std::cout << "Root = " << *h->Peek();

	std::cout << std::endl;
	h->Destroy();

	delete(h);
	
	std::cout << std::endl << "Min Heap" << std::endl;
	ShowData(h);
	std::cout << std::endl;

	/*for( size_t i = 0; i < iArr; ++i )
		hm->InsertKey(Int( arr[i] ));
	std::cout << std::endl << "Max Heap" << std::endl;
	ShowData(hm);
	std::cout << std::endl;*/

	free(arr);

	return(0);
}

