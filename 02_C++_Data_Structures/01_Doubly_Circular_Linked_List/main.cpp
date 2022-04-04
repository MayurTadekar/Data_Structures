
#include	<iostream>

#include	"LinkedList.hpp"

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

	LinkedList<int> *l = new LinkedList<int>();
	LinkedList<int> *l2 = new LinkedList<int>();
	//LinkedList<float> *l2 = new LinkedList<float>();

	ShowListDatai(l);

	std::cout << std::endl;
	std::cout << "List Insert First:" << std::endl;
	for(int i = 0; i < 10; ++i)
		l->listInsertFront( (i+1) * 10);
	ShowListDatai(l);

	/*std::cout << std::endl;
	std::cout << "List Insert Back:" << std::endl;
	for(int i = 10; i < 20; ++i)
		l->listInsertBack( (i+1) * 10);
	ShowListDatai(l);

	std::cout << std::endl;
	std::cout << "List Insert Position:" << std::endl;
	l->listInsertPosition( 5, 1 );
	l->listInsertPosition( 111, 10 );
	l->listInsertPosition( 555, 13 );
	ShowListDatai(l);

	std::cout << std::endl;
	std::cout << "List Insert After:" << std::endl;
	l->listInsertAfter( 50, 55, compare1 );
	l->listInsertAfter( 555, 655, compare1 );
	l->listInsertAfter( 180, 188, compare1 );
	l->listInsertAfter( 500, 188, compare1 );
	ShowListDatai(l);

	std::cout << std::endl;
	std::cout << "List Insert Before:" << std::endl;
	l->listInsertBefore( 30, 22, compare1 );
	l->listInsertBefore( 150, 145, compare1 );
	l->listInsertBefore( 200, 199, compare1 );
	l->listInsertBefore( 1212, 199, compare1 );
	ShowListDatai(l);
	
	std::cout << "Size = " << l->size() << std::endl;

	for( auto itr = l->begin(); itr != l->end(); ++itr )
	{
		std::cout << *itr << " ";
	}

	std::cout << std::endl << "Removing Front:" << std::endl;
	for(int i = 0 ; i < 10; ++i)
	{
		std::cout << "Deleting :" << l->listRemoveFront() << std::endl;
	}
	ShowListDatai(l);

	std::cout << std::endl << "Removing Back:" << std::endl;
	for(int i = 0 ; i < 10; ++i)
	{
		std::cout << "Deleting :" << l->listRemoveBack() << std::endl;
	}
	ShowListDatai(l);

	//std::cout << std::endl << "Removing After:" << std::endl;
	//l->listRemoveAfter()

	std::cout << std::endl << "Removing Position:" << std::endl;
	l->listRemovePosition(0);
	ShowListDatai(l);
	l->listRemovePosition(5);
	ShowListDatai(l);
	l->listRemovePosition(2);
	ShowListDatai(l);

	std::cout << std::endl << "List Contains:" << std::endl;
	std::cout << l->listContains(140, compare1) << std::endl;
	std::cout << l->listContains(655, compare1) << std::endl;
	std::cout << l->listContains(999, compare1) << std::endl;
	std::cout << std::endl;*/

	std::cout << std::endl;
	std::cout << "List2 Insert First:" << std::endl;
	for(int i = 0; i < 10; ++i)
		l2->listInsertFront( (i+1) * 12);
	ShowListDatai(l2);

	/*std::cout << std::endl;
	std::cout << "List2 Insert Back:" << std::endl;
	for(int i = 10; i < 20; ++i)
		l2->listInsertBack( (i+1) * 13);
	ShowListDatai(l2);*/

	LinkedList<int> *ln = l->listConcate(l2);

	ShowListDatai(l);
	ShowListDatai(l2);
	ShowListDatai(ln);

	(*l) += l2;
	ShowListDatai(l);
	ShowListDatai(l2);

	ln->listReverse();
	ShowListDatai(ln);

	/*std::cout << std::endl << "Removing After/Before:" << std::endl;
	l->listRemoveAfter(140, compare1);
	l->listRemoveAfter(655, compare1);
	l->listRemoveAfter(10, compare1);
	l->listRemoveBefore(130, compare1);
	l->listRemoveBefore(140, compare1);
	ShowListDatai(l);

	l->listRemove();
	l->listRemove();
	l->listRemove();
	ShowListDatai(l);*/

	return(0);
}

