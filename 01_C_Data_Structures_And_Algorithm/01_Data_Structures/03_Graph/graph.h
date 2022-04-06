

#ifndef		_GRAPH_H
#define		_GRAPH_H

#include	"dcll.h"

/* TYPE & TYPEDEFS */

struct vertex;
typedef		struct vertex 	vertex_t;
typedef 	struct vertex* 	p_vertex_t;
typedef 	struct vertex** pp_vertex_t;

struct edge;
typedef 	struct edge 	edge_t;
typedef 	struct edge* 	p_edge_t;
typedef 	struct edge** 	pp_edge_t;

typedef 	void* 		data_t;
typedef 	data_t* 	p_data_t;

typedef 	int 		ret_t;

typedef 	list_t 		graph_t;
typedef 	pp_list_t 	p_graph_t;

struct vertex
{
	data_t 	data;
	list_t	edges;
};
#define		SIZE_VERTEX 	(sizeof(vertex_t))

struct edge
{
	data_t 	value;
	int 	weight;
};
#define 	SIZE_EDGE		(sizeof(edge_t))

typedef void(*SHOW_DATA_FUNC)(data_t);
typedef void(*DELETE_DATA_FUNC)(data_t);
typedef ret_t(*COMPARE_DATA_FUNC)(data_t, data_t);

/* INTERFACE FUNCTIONS */
extern 	graph_t 	create_graph(void);

extern	ret_t 	graph_add_vertex(graph_t graph, data_t vdata);
extern	ret_t 	graph_add_edge(graph_t graph, data_t vertex1, data_t vertex2, size_t weight, COMPARE_DATA_FUNC compare_data);
extern	ret_t 	graph_add_directed_edge(graph_t graph, data_t vertex1, data_t vertex2, size_t weight, COMPARE_DATA_FUNC compare_data);

extern	void 	graph_show_vertex(graph_t graph, void(*showdata)(data_t data));
extern	void 	graph_show_graph(graph_t graph, void(*showdata)(data_t data));

extern	void	graph_destroy(p_graph_t graph, DELETE_DATA_FUNC p_delete_data);

/* GRAPH AUXILLARY FUNCTIONS */

#endif		/* _GRAPH_H */
