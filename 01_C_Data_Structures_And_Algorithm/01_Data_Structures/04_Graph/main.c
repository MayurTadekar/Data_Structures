

#include	<stdio.h>
#include	<stdlib.h>

#include	"graph.h"

graph_t graph;

typedef struct node2
{
	int data;
}NODE2;

void show_data(data_t data)
{
	fprintf(stdout, "%lld", (unsigned long long)data);
}

void delete_data(data_t data)
{
	fprintf(stdout, "Deleting: %lld", (unsigned long long)data);
	//free(data);
}

ret_t compare_data(data_t data1, data_t data2)
{

	if( (unsigned long long)data1 == (unsigned long long)data2 )
		return(SUCCESS);

	return(FAILURE);
}

int main(void)
{
	graph = create_graph();

	for(int i = 0 ; i < 5; ++i)
	{
		/*NODE2* p = (NODE2*) malloc(sizeof(NODE2));
		p->data = (i+1) * 10;*/
		graph_add_vertex(graph, (data_t)(unsigned long long)((i+1) * 10));
	}

	graph_show_vertex(graph, show_data);

	graph_add_edge(graph, (data_t)(unsigned long long)10, (data_t)(unsigned long long)20, 123, compare_data);
	graph_add_edge(graph, (data_t)(unsigned long long)30, (data_t)(unsigned long long)40, 123, compare_data);
	graph_add_edge(graph, (data_t)(unsigned long long)10, (data_t)(unsigned long long)50, 123, compare_data);
	graph_show_graph(graph, show_data);


	graph_destroy(&graph, delete_data);
	graph_destroy(&graph, delete_data);

	return(0);
}
