

#include	<stdio.h>
#include	<stdlib.h>
#include	"graph.h"

SHOW_DATA_FUNC p_show_data = NULL;
SHOW_DATA_FUNC p_delete_data = NULL;
COMPARE_DATA_FUNC p_compare_data = NULL;

/* GRAPH AUXILLARY FUNCTIONS */
static	void* 	Xmalloc(size_t size)
{
	void* p = malloc(size);
	if(NULL == p)
	{
		fprintf(stderr, "%s\n", "ERROR: Out Of Memory");
		exit(1);
	}
	return(p);
}

static 	p_vertex_t graph_create_vertex(data_t vdata)
{
	p_vertex_t pv = (p_vertex_t) Xmalloc(SIZE_VERTEX);
	pv->data = vdata;
	pv->edges = list_create();

	return(pv);
}

static void show_edge(data_t data)
{
	p_show_data(((p_edge_t)data)->value);
	fprintf(stdout, "/%d -> ",((p_edge_t)data)->weight);
}

static void delete_edge(data_t data)
{
	p_delete_data(((p_edge_t)data)->value);
	fprintf(stdout, "/%d -> ",((p_edge_t)data)->weight);
	free(data);
}

static void show_vertex(data_t data)
{
	p_show_data(((p_vertex_t)data)->data);
	fprintf(stdout, "->");
	//list_show(((p_vertex_t)data)->edges, show_edge);
}

static void show_graph(data_t data)
{
	printf("\n");
	p_show_data(((p_vertex_t)data)->data);
	fprintf(stdout, " => ");	
	list_show(((p_vertex_t)data)->edges, show_edge);
	fprintf(stdout, "{END}\n|");	
}


static void delete_graph(data_t data)
{
	printf("\n");
	p_delete_data(((p_vertex_t)data)->data);
	fprintf(stdout, " => ");	
	list_destroy(&((p_vertex_t)data)->edges, delete_edge);
	free(data);
	fprintf(stdout, "\n|");	
}

static ret_t compare_vertex(data_t v1, data_t v2)
{
	return( p_compare_data(((p_vertex_t)v1)->data, v2 ) );
}

static ret_t graph_add_generic_edge(graph_t graph, data_t vertex1, data_t vertex2, size_t weight, COMPARE_DATA_FUNC compare_data)
{
	p_vertex_t v1 = (p_vertex_t)list_get_data(graph, vertex1, compare_vertex);
	p_vertex_t v2 = (p_vertex_t)list_get_data(graph, vertex2, compare_vertex);

	if( NULL == v1 || NULL == v2 )
		return(FAILURE);

	p_edge_t pe = (p_edge_t) Xmalloc(SIZE_EDGE);
	pe->value = v2->data;
	pe->weight = weight;

	return(list_insert_back(v1->edges, pe));
}

/* INTERFACE FUNCTIONS */
extern 	graph_t 	create_graph(void)
{
	return(list_create());
}

extern	ret_t 	graph_add_vertex(graph_t graph, data_t vdata)
{
	return( list_insert_back(graph, graph_create_vertex(vdata)) );
}

extern	ret_t 	graph_add_edge(graph_t graph, data_t vertex1, data_t vertex2, size_t weight, COMPARE_DATA_FUNC compare_data)
{

	p_compare_data = compare_data;

	graph_add_generic_edge(graph, vertex1, vertex2, weight, compare_data);
	graph_add_generic_edge(graph, vertex2, vertex1, weight, compare_data);

	return(SUCCESS);
}

extern	ret_t 	graph_add_directed_edge(graph_t graph, data_t vertex1, data_t vertex2, size_t weight, COMPARE_DATA_FUNC compare_data)
{

	p_compare_data = compare_data;

	graph_add_generic_edge(graph, vertex1, vertex2, weight, compare_data);

	return(SUCCESS);
}

extern	void 	graph_show_vertex(graph_t graph, SHOW_DATA_FUNC showdata)
{
	p_show_data = showdata;
	printf("\nVERTICES:\n");
	printf("{START}->");
	list_show(graph, show_vertex);
	printf("{END}\n");
}

extern	void 	graph_show_graph(graph_t graph, SHOW_DATA_FUNC showdata)
{
	p_show_data = showdata;
	printf("\nGRAPH:\n");
	printf("{START}\n|");
	list_show(graph, show_graph);
	printf("\n{END}\n");
}

extern	void 	graph_destroy(p_graph_t graph, DELETE_DATA_FUNC deletedata)
{
	p_delete_data = deletedata;
	printf("\nGRAPH:\n");
	printf("{START}\n|");
	list_destroy(graph, delete_graph);
	printf("\n{END}\n");
}

