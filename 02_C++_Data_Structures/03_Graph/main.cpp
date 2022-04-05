

#include	<iostream>

#include	<time.h>

#include	"Graph.h"


Graph<int>*	graph = NULL;

ret_t 	compare(int d1, int d2)
{
	if( d1 == d2 )
		return(SUCCESS);

	return(FAILURE);
}

int main(void)
{
	graph = new Graph<int>();

	for( int i = 0; i < 10; ++i )
		graph->AddVertex( (i+1) * 10 );

	std::cout << "Vertices:" << std::endl;
	for( int i = 0; i < graph->size(); ++i )
	{
		std::cout << (*graph)[i]->GetData() << std::endl;
	}

	srand(time(0));

	for( int i = 0; i < rand() % 100 + 1; ++i )
		graph->AddEdge(	(rand() % 10 + 1) * 10, 
						(rand() % 10 + 1) * 10, 
						(rand() % 100 + 1), 
						compare);

	std::cout << std::endl << "Graph:" << std::endl;
	for( int i = 0; i < graph->size(); ++i )
	{
		std::cout << (*graph)[i]->GetData();//std::endl;
		for(int j = 0; j < (*graph)[i]->size(); ++j)
			std::cout<< " -> " << (*(*graph)[i])[j];	
		std::cout << std::endl;
	}

	return(0);
}

