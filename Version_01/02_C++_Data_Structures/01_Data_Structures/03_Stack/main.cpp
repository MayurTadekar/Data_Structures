
#include	<iostream>

#include 	"Stack.h"

ret_t compare1(int data1, int data2)
{
	if( data1 == data2 )
		return(SUCCESS);

	return(FAILURE);
}

void 	ShowListDatai(LinkedList<int>* l)
{
	std::cout << "{START}->";
	for(int i = 0; i < l->size(); ++i)
	{
		std::cout << (*l)[i] << "->";
	} 
	std::cout << "{END}" << std::endl << std::endl;
}

int main(void)
{

	Stack<int> *s = new Stack<int>();

	s->Push(10);
	s->Push(20);
	s->Push(30);
	s->Push(40);
	s->Push(50);
	s->Push(60);
	
	s->Traverse();

	std::cout << "Peeked :" << s->Peek() << std::endl;
	std::cout << "Popped :" << s->Pop() << std::endl;

	std::cout << "Peeked :" << s->Peek() << std::endl;
	std::cout << "Popped :" << s->Pop() << std::endl;

	std::cout << "Peeked :" << s->Peek() << std::endl;
	std::cout << "Popped :" << s->Pop() << std::endl;

	delete(s);

	return(0);
}

