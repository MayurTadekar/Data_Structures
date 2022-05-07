

/**
 *  @author Mayur Tadekar   
 *  @date   06th May, 2022 
 *  @details    Header file for all interface functions and 
 *              required types definitions for Graph 
 */

#ifndef     _GRAPH_H
#define     _GRAPH_H

#include    "dcll.h"

//  Literals and Typedefs

#define     SUCCESS     1
#define     FAILURE     0

struct graph_vertex;

typedef     struct graph_vertex     vertex_t;
typedef     struct graph_vertex*    p_vertex_t;
typedef     struct graph_vertex**   pp_vertex_t;

struct  graph_edge;

typedef     struct graph_edge       edge_t;
typedef     struct graph_edge*      p_edge_t;
typedef     struct graph_edge**     pp_edge_t;

typedef     void*   graph_data_t;

struct  graph_dummy;

typedef     struct graph_dummy      graph_dummy_t;
typedef     struct graph_dummy*     p_graph_dummy_t;
typedef     struct graph_dummy**    pp_graph_dummy_t;

struct  queue_node;

typedef     struct queue_node   queue_node_t;
typedef     struct queue_node*  p_queue_node_t;
typedef     struct queue_node** pp_queue_node_t;

typedef     void*   graph_t;
typedef     int     status_t;

typedef enum
{
    GRAPH_UNDIRECTED = 0,
    GRAPH_DIRECTED
}graph_type_t;

typedef enum
{
    COLOR_BLACK = 0,
    COLOR_GRAY,
    COLOR_WHITE
}color_t;

struct  graph_vertex
{
    graph_data_t  data;
    list_t  edges;
    color_t color;
};
#define     SIZE_VERTEX         (sizeof(vertex_t))

struct  graph_edge
{
    p_vertex_t  vertex;
    size_t      weight;
};
#define     SIZE_EDGE       (sizeof(edge_t))

struct  graph_dummy
{
    graph_type_t graph_type;
    list_t  vertices;
    size_t  nr_elements;
};
#define     SIZE_GRAPH      (sizeof(graph_dummy_t))

struct queue_node
{
    p_vertex_t data;
    long  parent;
    size_t  weight;
};
#define     SIZE_QUEUE_NODE     (sizeof(queue_node_t))

typedef     void(*SHOWEDGE_PROC)(graph_data_t, size_t);

//  Graph Auxillary Functions
static  void*   Xcalloc(size_t  nr_elements, size_t element_size);

static  p_vertex_t  create_vertex(graph_data_t data);
static  p_edge_t    create_edge(p_vertex_t pvertex, size_t weight);

static  p_queue_node_t  create_queue_node(p_vertex_t vertex, long parent_index, size_t weight);

static  p_vertex_t  locate_vertex(  graph_t graph, 
                                    graph_data_t data,
                                    COMPARE_PROC pcompare);

static  p_edge_t    locate_edge(    p_vertex_t pvertex,
                                    graph_data_t data,
                                    COMPARE_PROC pcompare);

static  status_t   compare( dcll_data_t d1, 
                            dcll_data_t d2);

static  status_t   compare_edges(   dcll_data_t d1, 
                                    dcll_data_t d2);

//  Graph Interface Functions

extern  graph_t     create_graph(graph_type_t gtype);

extern  status_t    graph_add_vertex(graph_t graph, graph_data_t data);

extern  status_t    graph_add_edge( graph_t  graph, 
                                    graph_data_t v1, 
                                    graph_data_t v2, 
                                    size_t  weight,
                                    COMPARE_PROC pcompare);

extern  status_t    graph_add_directed_edge(graph_t graph,
                                            graph_data_t v1,
                                            graph_data_t v2,
                                            size_t weight,
                                            COMPARE_PROC pcompare);
                                            
extern  graph_data_t    graph_remove_vertex(graph_t graph,
                                            graph_data_t  v,
                                            COMPARE_PROC pcompare);

extern  status_t    graph_remove_edge(  graph_t graph,
                                        graph_data_t v1,
                                        graph_data_t v2,
                                        COMPARE_PROC pcompare);

extern  status_t    graph_remove_directed_edge( graph_t graph,
                                                graph_data_t v1,
                                                graph_data_t v2,
                                                COMPARE_PROC pcompare);

extern  void    graph_show( graph_t graph,
                            SHOWDATA_PROC pvertex_show,
                            SHOWEDGE_PROC pedge_show);

extern  void    graph_destroy(  graph_t* pgraph,
                                DELETEDATA_PROC pdelete);

//  Graph Algorithm Interface Functions

extern  void    graph_breadth_first_search( graph_t graph,
                                            graph_data_t source,
                                            COMPARE_PROC pcompare,
                                            SHOWDATA_PROC pshowdata);
                                            
extern  void    graph_breadth_first_search_all_vertices(graph_t graph,
                                                        COMPARE_PROC pcompare,
                                                        SHOWDATA_PROC pshowdata);
                                                
extern  void    graph_deapth_first_search(  graph_t graph,
                                            SHOWDATA_PROC pshowdata);

extern  void    graph_dijkstras_shortest_path(  graph_t graph,
                                                SHOWDATA_PROC pshowdata);

extern  void    graph_bellmann_ford(graph_t graph,
                                    SHOWDATA_PROC pshowdata);

extern  void    graph_floyd_warshall(   graph_t graph,
                                        SHOWDATA_PROC pshowdata);

extern  void    graph_prims_algorithm(  graph_t graph,
                                        SHOWDATA_PROC pshowdata);

extern  void    graph_kruskals_algorithm(   graph_t graph,
                                            SHOWDATA_PROC pshowdata);

extern  void    graph_ford_fulkerson(   graph_t graph,
                                        SHOWDATA_PROC pshowdata);

#endif      /* _GRAPH_H */

