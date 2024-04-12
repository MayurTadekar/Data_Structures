

/**
 * @file graph.c
 * @author Mayur Tadekar 
 * @brief Source Code of Generic Data Implements of Graph Data Structure
 * @version 0.1
 * @date 05-06-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include    <stdio.h>
#include    <stdlib.h>

#include    "graph.h"
#include    "queue.h"
#include    "stack.h"
#include    "disjointset.h"

//  Graph Global Variables
COMPARE_PROC g_compare = NULL;

//  Graph Auxillary Functions
/**
 * @brief Allocating 'nr_elements' * 'element_size' bytes
 * 
 * @param nr_elements Total number of elements to allocate
 * @param element_size size of element
 * @return void* Returning the address of memeory allocated
 */
static  void*   Xcalloc(size_t  nr_elements, size_t element_size)
{
    //  Code
    void* p = calloc(nr_elements, element_size);
    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory");
        exit(1);
    }
    return(p);
}

/**
 * @brief Create a vertex object
 * 
 * @param data Assigning data to created vertex object
 * @return p_vertex_t returning address of allocated vertex object
 */
static  p_vertex_t  create_vertex(graph_data_t data)
{
    //  Code
    p_vertex_t pv = (p_vertex_t) Xcalloc(1, SIZE_VERTEX);
    pv->data = data;
    pv->edges = create_list();
    return(pv);
}

/**
 * @brief Create a edge object
 * 
 * @param pvertex Assigning vertex to the edge
 * @param weight Assigning weight to the edge
 * @return p_edge_t returning address of allocate edge object 
 */
static  p_edge_t    create_edge(p_vertex_t pvertex, size_t weight)
{
    //  Code
    p_edge_t pe = (p_edge_t) Xcalloc(1, SIZE_EDGE);
    pe->vertex = pvertex;
    pe->weight = weight;
    return(pe);
}

/**
 * @brief Create a queue node object
 * 
 * @param vertex vertex to add to queue node
 * @param parent_index index of parent node
 * @param weight weight of path till this vertex 
 * @return p_dfs_bfs_node_t returning the address of allocated queue node
 */
static  p_dfs_bfs_node_t  create_dfs_bfs_node(p_vertex_t vertex, long parent_index, size_t weight)
{
    p_dfs_bfs_node_t pq = (p_dfs_bfs_node_t) Xcalloc(1, SIZE_DFS_BFS_NODE);
    pq->data = vertex;
    pq->weight = weight;
    pq->parent = parent_index;
    return(pq);
}

/**
 * @brief Create a mst node object
 * 
 * @param v1 Vertex1
 * @param v2 Vertex2
 * @param weight weight of the edge
 * @return p_mst_node_t returning address of allocated mst node object 
 */
static  p_mst_node_t    create_mst_node(p_vertex_t v1, p_vertex_t v2, size_t weight)
{
    //  Code
    p_mst_node_t p = (p_mst_node_t)Xcalloc(1, SIZE_MST_NODE);
    p->v1 = v1;
    p->v2 = v2;
    p->weight = weight;
    return(p);
}

/**
 * @brief Locating the specific vertex in vertices list
 * 
 * @param graph The graph to get the specific vertex
 * @param data Vertex data to search 
 * @param pcompare Callback function to compare
 * @return p_vertex_t returning the found vertex object
 */
static  p_vertex_t  locate_vertex(  graph_t graph, 
                                    graph_data_t data,
                                    COMPARE_PROC pcompare)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t p = (p_vertex_t)list_at(pd->vertices, i);
        if( SUCCESS == pcompare( p->data, data ) )
            return(p);
    } 

    return(NULL);
}

/**
 * @brief Locate edge if present in the graph
 * 
 * @param pvertex Vertex to search the edge 
 * @param data vertex2 data, to find the connedted edge
 * @param pcompare Callback function for comparison
 * @return status_t returning status of locating the edge
 */
                                    
static  p_edge_t    locate_edge(    p_vertex_t pvertex,
                                    graph_data_t data,
                                    COMPARE_PROC pcompare)
{
    if( NULL == pvertex->edges )
        return(NULL);
    
    for( int i = 0; i < list_size(pvertex->edges); ++i )
    {
        p_edge_t pe = list_at(pvertex->edges, i);

        if( SUCCESS == pcompare( pe->vertex->data, data ) )
            return(pe);
    }

    return(NULL);
}

/**
 * @brief Comparing data from list and d2
 * 
 * @param d1 data1 
 * @param d2 data2
 * @return status_t returning status of comparison 
 */
static  status_t   compare( dcll_data_t d1, 
                            dcll_data_t d2)
{
    //  Code
    if( d1 == d2 )
        return(SUCCESS);
    //printf("\n%zd == %zd\n", ((p_vertex_t)d1)->data, ((p_vertex_t)d2)->data );
    
    return(FAILURE);
}

static status_t     compare_vertex( dcll_data_t d1, 
                                    dcll_data_t d2)
{
    return( g_compare( ((p_vertex_t)d1)->data, ((p_vertex_t)d2)->data ) );
}

/**
 * @brief Comparing edges from list
 * 
 * @param d1 edge to compare with
 * @param d2 vertex to compare with
 * @return status_t returning status of comparison
 */
static  status_t   compare_edges(   dcll_data_t d1, 
                                    dcll_data_t d2)
{
    //  Code
    if( ((p_edge_t)d1)->vertex == ((p_edge_t)d2)->vertex )
        return(SUCCESS);
    
    return(FAILURE);
}


/**
 * @brief Adding a new edge to the graph
 * 
 * @param graph Graph to add edge to
 * @param v1 Vertex1 of the edge
 * @param v2 Vertex2 of the edge
 * @param weight weight of the edge between v1 and v2
 * @param pcompare Callback function to compare data
 * @return status_t returning status of instertion of the edge
 */
extern  status_t    graph_add_undirected_edge(  graph_t  graph, 
                                                graph_data_t v1, 
                                                graph_data_t v2, 
                                                size_t  weight,
                                                COMPARE_PROC pcompare)
{
    //  Code
    p_vertex_t pv1 = locate_vertex(graph, v1, pcompare);
    p_vertex_t pv2 = locate_vertex(graph, v2, pcompare);

    if( NULL == pv1     ||
        NULL == pv2     ||
        SUCCESS == pcompare(pv1->data, pv2->data))
    {
        return(FAILURE);
    }
    
    if( NULL != locate_edge(pv1, v2, pcompare)   ||
        NULL != locate_edge(pv2, v1, pcompare))
        return(FAILURE);
    
    list_insert_back(pv1->edges, create_edge(pv2, weight));
    list_insert_back(pv2->edges, create_edge(pv1, weight));

    return(SUCCESS);
}

/**
 * @brief Adding a directed edge to the graph
 * 
 * @param graph The graph to add edge to
 * @param v1 Vertex1 of the edge
 * @param v2 vertex2 of the edge
 * @param weight weight of the edge between v1 and v2
 * @param pcompare callback function to compare data
 * @return status_t returning status of insertion of edge
 */
extern  status_t    graph_add_directed_edge(graph_t graph,
                                            graph_data_t v1,
                                            graph_data_t v2,
                                            size_t weight,
                                            COMPARE_PROC pcompare)
{
    //  Code
    
    p_vertex_t pv1 = locate_vertex(graph, v1, pcompare);
    p_vertex_t pv2 = locate_vertex(graph, v2, pcompare);

    if( NULL == pv1     ||
        NULL == pv2     ||
        SUCCESS == pcompare(pv1->data, pv2->data))
    {
        return(FAILURE);
    }

    if( NULL != locate_edge(pv1, v2, pcompare)   ||
        NULL != locate_edge(pv2, v1, pcompare))
    {
        return(FAILURE);
    }
    
    return(list_insert_back( pv1->edges, create_edge(pv2, weight) ) );
}


/**
 * @brief Removing edge from graph
 * 
 * @param graph Graph to remove edge from
 * @param v1 Vertex1 of the edge
 * @param v2 Vertex2 of the edge
 * @param pcompare Callback function to compare data 
 * @return status_t returning status of removing edge
 */
static  status_t        graph_remove_undirected_edge(   graph_t graph,
                                                        graph_data_t v1,
                                                        graph_data_t v2,
                                                        COMPARE_PROC pcompare)
{
    //  Code
    
    p_vertex_t pv1 = locate_vertex(graph, v1, pcompare);
    p_vertex_t pv2 = locate_vertex(graph, v2, pcompare);
    //printf("0\n");

    if( NULL == pv1     ||
        NULL == pv2     ||
        SUCCESS == pcompare(pv1->data, pv2->data))
    {
        return(FAILURE);
    }
    //printf("1\n");
    
    p_edge_t pe1 = locate_edge(pv1, v2, pcompare);
    p_edge_t pe2 = locate_edge(pv2, v1, pcompare);

    //printf("2\n");

    if( NULL == locate_edge(pv1, v2, pcompare)   ||
        NULL == locate_edge(pv2, v1, pcompare))
        return(FAILURE);

    list_remove(pe1->vertex->edges, pe2, compare_edges);
    //printf("\n2.5\n");
    list_remove(pe2->vertex->edges, pe1, compare_edges);

    //printf("3\n");

    return(SUCCESS);
}

/**
 * @brief Removing edge from directed graph
 * 
 * @param graph Graph to remove edge from
 * @param v1 Vertex1 of the edge
 * @param v2 Vertex2 of the edge
 * @param pcompare Callback function to compare data 
 * @return status_t returning status of removing edge
 */
static  status_t        graph_remove_directed_edge( graph_t graph,
                                                    graph_data_t v1,
                                                    graph_data_t v2,
                                                    COMPARE_PROC pcompare)
{
    //  Code
    
    p_vertex_t pv1 = locate_vertex(graph, v1, pcompare);
    p_vertex_t pv2 = locate_vertex(graph, v2, pcompare);

    if( NULL == pv1     ||
        NULL == pv2     ||
        SUCCESS == pcompare(pv1->data, pv2->data))
    {
        return(FAILURE);
    }
    
    p_edge_t pe1 = locate_edge(pv1, v2, pcompare);
    p_edge_t pe2 = locate_edge(pv2, v1, pcompare);

    if( NULL == locate_edge(pv1, v2, pcompare)   ||
        NULL == locate_edge(pv2, v1, pcompare))
        return(FAILURE);

    list_remove(pe1->vertex->edges, pe2, compare_edges);
    
    return(SUCCESS);
}

/**
 * @brief Destroy set data
 * 
 * @param data data stored in list
 */
static  void        destroy_set_data( dcll_data_t data)
{
    set_t s = (set_t) data;
    set_destroy(&s, NULL);
}

/**
 * @brief Comparing MST nodes
 * 
 * @param d1 data1 of list
 * @param d2 data2 of list
 * @return status_t returning the status of comparison
 */
static  status_t    compare_mst_node(dcll_data_t d1, dcll_data_t d2)
{
    //  Code
    //printf("9 = %zd = %zd\n", ((p_mst_node_t)d1)->weight, ((p_mst_node_t)d2)->weight );
    if( ((p_mst_node_t)d1)->weight < ((p_mst_node_t)d2)->weight )
        return(SUCCESS);
    
    return(FAILURE);
}

/**
 * @brief Deleting data of MST node
 * 
 * @param d data to delete
 */
static  void    delete_mst_node(dcll_data_t d)
{
    //printf("\ndeleting = %zd = %zd = %d\n", ((p_mst_node_t)d)->v1->data, ((p_mst_node_t)d)->v1->data, ((p_mst_node_t)d)->weight );
    free(d);
}

/**
 * @brief Formulate set from the edges of graph
 * 
 * @param graph Graph to from set
 * @param plist pointer to list to create sorted edges
 * @param pshowdata callback function to show data
 */
static  void    graph_formulate_set(    graph_t graph,
                                        list_t edge_list,
                                        list_t* plist, 
                                        list_t* p_mst_list,
                                        COMPARE_PROC pcompare,
                                        SHOWDATA_PROC pshowdata)
{
    //  Code
    //list_t list = NULL;
    p_graph_dummy_t pg = (p_graph_dummy_t)graph;
    if( NULL == pg  ||
        NULL == pg->vertices )
        return;
    
    *plist = create_list();
    for( int i = 0; i < list_size(pg->vertices); ++i )
    {
        list_insert_back(*plist, make_set( list_at(pg->vertices, i) ) );
    }

    // for( int i = 0; i < list_size( list ); ++i )
    // {
    //     printf("\nSet%d:\n", i+1);
    //     set_t s = list_at(list, i);
    //     for( int j = 0; j < set_size( s ); ++j )
    //     {
    //         printf("->");
    //         pshowdata( ((p_vertex_t)set_at(s, j))->data );
    //     }
    // }

    for( int j = 0; j < list_size( edge_list); ++j )
    {
        p_mst_node_t pmst = (p_mst_node_t) list_at(edge_list, j);
        set_t s1 = NULL;
        set_t s2 = NULL;

        //printf("\npv->data = %zd\n", pv->data);
        //printf("pe->vectex->data = %zd\n\n", pe->vertex->data);

        for( int k = 0; k < list_size( *plist ); ++k )
        {
            if( NULL != set_find( list_at(*plist, k), pmst->v1, compare ) )
            {
                //printf("1\n");
                s1 = list_at(*plist, k);
            }

            if( NULL != set_find( list_at(*plist, k), pmst->v2, compare ) )
            {
                //printf("2\n");
                s2 = list_at(*plist, k);
            }

            if( NULL != s1 && NULL != s2 )
                break;
        }
        
        
        if( s1 != s2 )
        {
            list_remove( *plist, s2, compare);
            set_union( s1, &s2 );
            list_insert_back( *p_mst_list, pmst );
        }
    }

    //g_compare = pcompare;
}

/*********************************************************\
 * 
 *   Graph Interface Functions
 * 
\*********************************************************/

/**
 * @brief Create a graph object
 * 
 * @param gtype type of graph to create
 * @return graph_t Address of the created graph object
 */
extern  graph_t     create_graph(graph_type_t gtype)
{
    p_graph_dummy_t pg = (p_graph_dummy_t)Xcalloc(1, SIZE_GRAPH);

    pg->nr_elements = 0;
    pg->vertices = create_list();
    pg->graph_type = gtype;

    return(pg);
}


/**
 * @brief Adding new Vertex to graph
 * 
 * @param graph graph to add vertex to
 * @param data vertex data to add to graph
 * @return status_t returning status of insertion to graph
 */
extern  status_t    graph_add_vertex(graph_t graph, graph_data_t data)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t) graph;
    if( NULL == pd )
    {
        return(FAILURE);
    }

    pd->nr_elements++;
    return(list_insert_back( pd->vertices, create_vertex(data) ) );
}

/**
 * @brief Add edge to graph
 * 
 * @param graph to add edge
 * @param v1 v1 of the edge
 * @param v2 v2 of the edge
 * @param weight weight of the edge
 * @param pcompare callback function to compare
 * @return status_t returning status of addition of edge
 */
extern  status_t    graph_add_edge( graph_t  graph, 
                                    graph_data_t v1, 
                                    graph_data_t v2, 
                                    size_t  weight,
                                    COMPARE_PROC pcompare)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t) graph;
    if( NULL == pd  ||
        0 == pd->nr_elements)
    {
        return(FAILURE);
    }

    if( GRAPH_DIRECTED == pd->graph_type)
        return(graph_add_directed_edge(graph, v1, v2, weight, pcompare));
    else 
        return(graph_add_undirected_edge(graph, v1, v2, weight, pcompare));
}

/**
 * @brief Removing vertex from the graph
 * 
 * @param graph Graph to remove vertex from
 * @param v vertex to remove from Graph
 * @param pcompare Callback function to compare data
 * @return graph_data_t returning data removed from the graph 
 */
extern  graph_data_t    graph_remove_vertex(graph_t graph,
                                            graph_data_t  v,
                                            COMPARE_PROC pcompare)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements )
        return(NULL);

    p_vertex_t pv = NULL;
    graph_data_t ret_data = NULL;

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        pv = (p_vertex_t)list_at(pd->vertices, i);

        if( SUCCESS != pcompare(pv->data, v) )
        {
            for( int j = 0; j < list_size(pv->edges); ++j )
            {
                p_edge_t pe = (p_edge_t) list_at(pv->edges, j);

                if( SUCCESS == pcompare(pe->vertex->data, v) )
                {
                    list_remove(pv->edges, pe, compare);
                }
            }
        }
        else
        {
            list_destroy( &(pv->edges), NULL);
            ret_data = pv->data;
            list_remove(pd->vertices, pv, compare);
            --i;
        }
    }    

    return(ret_data);
}
 
/**
 * @brief Remove edge (Directed/Undirect) from graph
 * 
 * @param graph to remove edge from
 * @param v1 of the edge 
 * @param v2 of the edge
 * @param pcompare callback function for data coparison
 * @return status_t returning status of removing edge
 */
extern  status_t    graph_remove_edge(  graph_t graph,
                                        graph_data_t v1,
                                        graph_data_t v2,
                                        COMPARE_PROC pcompare)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t) graph;
    if( NULL == pd  ||
        0 == pd->nr_elements )
    {
        return(FAILURE);
    }

    if( GRAPH_DIRECTED == pd->graph_type)
        return(graph_remove_directed_edge( graph, v1, v2, pcompare ));
    else
        return(graph_remove_undirected_edge( graph, v1, v2, pcompare));
}
                                           

/**
 * @brief Show Graph complete data
 * 
 * @param graph graph to show data
 * @param pvertex_show Callback to show data
 * @param pedge_show Callback to show edge data  
 */

extern  void        graph_show( graph_t graph,
                                SHOWDATA_PROC pvertex_show,
                                SHOWEDGE_PROC pedge_show)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements )
        return;
    
    printf("{START}\n|");
    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = list_at(pd->vertices, i);
        printf("\n");
        pvertex_show(pv->data);
    
        for( int j = 0 ; j < list_size(pv->edges); ++j )
        {
            p_edge_t pe = (p_edge_t) list_at(pv->edges, j);
            printf("->");
            pedge_show(pe->vertex->data, pe->weight);
        }
        printf("\n|");
    }
    printf("\n{END}");
}   

/**
 * @brief Destroying the graph
 * 
 * @param pgraph Pointer to graph to destroy
 * @param pdelete Callback to delete data of graph
 */
extern  void        graph_destroy(  graph_t* pgraph,
                                    DELETEDATA_PROC pdelete)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)*pgraph;
    if( NULL == pd  ||
        0 == pd->nr_elements )
        return;
    
    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = list_at(pd->vertices, i);
       
        pdelete(pv->data);
        pv->data = NULL;
        list_destroy( &(pv->edges), NULL);

    }

    list_destroy( &(pd->vertices), NULL);

    free(*pgraph);
    *pgraph = NULL;
}


//  Graph Algorithm Interface Functions

/**
 * @brief Graph breadth first search
 * 
 * @param graph graph to travel 
 * @param source to start the searching from
 * @param pcompare Callback function to compare data 
 * @param pshowdata Callback function to show data
 */

extern  void    graph_breadth_first_search( graph_t graph,
                                            graph_data_t source,
                                            COMPARE_PROC pcompare,
                                            SHOWDATA_PROC pshowdata)
{
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements)
    {
        return;
    }

    p_vertex_t psource = NULL;

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = (p_vertex_t)list_at(pd->vertices, i);
        pv->color = COLOR_WHITE;

        if( SUCCESS == pcompare(pv->data, source) )
            psource = pv;
    }

    if( NULL == psource )
    {
        fprintf(stderr, "ERROR: No source node found\n");
        return;
    }

    queue_t queue = create_queue();

    queue_enqueue(queue, create_dfs_bfs_node(psource, -1, 0) );

    ((p_vertex_t)queue_first(queue))->color = COLOR_GRAY;

    long index = 0; 
    size_t w = 0;

    printf("{START}");
    while( index < queue_size(queue) )
    {
        p_dfs_bfs_node_t pn = queue_at(queue, index);
        
        for( int i = 0 ; i < list_size( pn->data->edges ); ++i )
        {
            p_vertex_t pv_child = ((p_edge_t)list_at(pn->data->edges, i))->vertex;
            size_t weight = ((p_edge_t)list_at(pn->data->edges, i))->weight;
            //printf("->->%zd\n", weight)
            
            if( COLOR_WHITE == pv_child->color )
            {
                queue_enqueue( queue, create_dfs_bfs_node( pv_child, index, weight + pn->weight) );
                pv_child->color = COLOR_GRAY;
            }
        }
        pn->data->color = COLOR_BLACK;
        printf("->");
        pshowdata(pn->data->data);
        index++;
        w = pn->weight;
        //free(pn);
    }

    queue_destroy(&queue);

    printf("->{END} : %zd(path weight) \n", w);
}

/**
 * @brief Graph breadth first search all the vertices as source
 * 
 * @param graph graph to travel 
 * @param pcompare Callback function to compare data 
 * @param pshowdata Callback function to show data
 */
extern  void    graph_breadth_first_search_all_vertices(graph_t graph,
                                                        COMPARE_PROC pcompare,
                                                        SHOWDATA_PROC pshowdata)
{
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements)
    {
        return;
    }

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = (p_vertex_t)list_at(pd->vertices, i);
        printf("\n");
        printf("Vertex => ");
        pshowdata(pv->data);
        printf("\n");
        graph_breadth_first_search( graph, 
                                    pv->data,
                                    pcompare,
                                    pshowdata);
    } 
}

/**
 * @brief Graph Depth first search for the source
 * 
 * @param graph to travel in depth first order
 * @param source to start the traversal from
 * @param pcompare Callback function to compare data 
 * @param pshowdata callback function to show data
 */
extern  void    graph_deapth_first_search(  graph_t graph,
                                            graph_data_t source,
                                            COMPARE_PROC pcompare,
                                            SHOWDATA_PROC pshowdata)
{

    //  Code
    //  Code
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements)
    {
        return;
    }

    p_vertex_t psource = NULL;

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = (p_vertex_t)list_at(pd->vertices, i);
        pv->color = COLOR_WHITE;

        if( SUCCESS == pcompare(pv->data, source) )
            psource = pv;
    }

    if( NULL == psource )
    {
        fprintf(stderr, "ERROR: No source node found\n");
        return;
    }

    stack_t stack = create_stack();
    
    stack_push( stack, create_dfs_bfs_node(psource, -1, 0) );

    p_dfs_bfs_node_t pn = (p_dfs_bfs_node_t) stack_peek( stack );
    pn->data->color = COLOR_GRAY;

    printf("{START}");
    printf("->");
    pshowdata(pn->data->data);

    while( 0 != stack_size(stack) )
    {
        pn = (p_dfs_bfs_node_t) stack_pop( stack );
        for( int i = 0; i < list_size( pn->data->edges ); ++i )
        {
            p_edge_t pedge = (p_edge_t) list_at( pn->data->edges, i );
            if( pedge->vertex->color == COLOR_WHITE )
            {
                stack_push( stack, create_dfs_bfs_node( pedge->vertex, 0, pn->weight + pedge->weight ) );
                i = -1;
                pn = stack_peek(stack);
                pn->data->color = COLOR_GRAY;
                printf("->");
                pshowdata(pn->data->data);
                continue;
            }
        }
        pn->data->color = COLOR_BLACK;
    }
    printf("->{END}\n");

    stack_destroy( &stack );
}
/**
 * @brief Graph deapth first search all the vertices as source
 * 
 * @param graph graph to travel 
 * @param pcompare Callback function to compare data 
 * @param pshowdata Callback function to show data
 */
extern  void    graph_deapth_first_search_all_vertices( graph_t graph,
                                                        COMPARE_PROC pcompare,
                                                        SHOWDATA_PROC pshowdata)
{
    p_graph_dummy_t pd = (p_graph_dummy_t)graph;
    if( NULL == pd  ||
        0 == pd->nr_elements)
    {
        return;
    }

    for( int i = 0; i < list_size(pd->vertices); ++i )
    {
        p_vertex_t pv = (p_vertex_t)list_at(pd->vertices, i);
        printf("\n");
        printf("Vertex => ");
        pshowdata(pv->data);
        printf("\n");
        graph_deapth_first_search(  graph, 
                                    pv->data,
                                    pcompare,
                                    pshowdata);
    } 
}

extern  void    graph_dijkstras_shortest_path(  graph_t graph,
                                                SHOWDATA_PROC pshowdata)
{

}

extern  void    graph_bellmann_ford(graph_t graph,
                                    SHOWDATA_PROC pshowdata)
{
    
}
extern  void    graph_floyd_warshall(   graph_t graph,
                                        SHOWDATA_PROC pshowdata)
{
    
}
extern  void    graph_prims_algorithm(  graph_t graph,
                                        SHOWDATA_PROC pshowdata)
{
    
}

/**
 * @brief Kruskal Algorithm for Minimum Spanning Tree
 * 
 * @param graph to build the minimum spanning tree
 * @param pshowdata callback to show data
 */
extern  void    graph_kruskals_algorithm(   graph_t graph,
                                            COMPARE_PROC pcompare,
                                            SHOWDATA_PROC pshowdata)
{
    //  Code
    p_graph_dummy_t pg = (p_graph_dummy_t)graph;
    if( NULL == pg  ||
        NULL == pg->vertices )
    {
        return;
    }

    list_t list = create_list();
    set_t set_list = create_list();
    list_t mst = create_list();

    for( int i = 0 ; i < list_size(pg->vertices); ++i )
    {
        p_vertex_t pv = (p_vertex_t) list_at(pg->vertices, i);

        for( int j = 0; j < list_size(pv->edges); ++j)
        {
            p_edge_t pe = (p_edge_t)list_at(pv->edges, j);
            
            list_insert_back(list, create_mst_node(pv, pe->vertex, pe->weight) );
        }
    }

    // for( int i = 0; i < list_size(list); ++i )
    // {
    //     p_mst_node_t pm = (p_mst_node_t)list_at(list, i);

    //     printf("-->");
    //     pshowdata(pm->v1->data);
    //     printf(" \t ");
    //     pshowdata(pm->v1->data);
    //     printf(" \t %zd\n", pm->weight);
    //     //free(pm);
    // }

    list_sort( list, compare_mst_node);

    // printf("Sorted Edge list\n");
    // for( int i = 0; i < list_size(list); ++i )
    // {
    //     p_mst_node_t pm = (p_mst_node_t)list_at(list, i);

    //     printf("-->");
    //     pshowdata(pm->v1->data);
    //     printf(" \t ");
    //     pshowdata(pm->v2->data);
    //     printf(" \t %zd\n", pm->weight);
    //     //free(pm);
    // }  
    
    graph_formulate_set( graph, list, &set_list, &mst, pcompare, pshowdata);

    for( int i = 0; i < list_size( set_list ); ++i )
    {
        printf("\nSet %d:\n", i+1);
        set_t s = list_at(set_list, i);
        //list_sort(s, compare_vertex);
        for( int j = 0; j < set_size( s ); ++j )
        {
            printf("->");
            pshowdata( ((p_vertex_t)set_at(s, j))->data );
        }
        printf("\n");
    }

    long total_cost = 0;
    printf("\nMinimum Spanning Tree:\n");
    printf("Src\tDest\tWeight");
    for( int i = 0; i < list_size( mst ); ++i )
    {
        p_mst_node_t pmst = list_at(mst, i);
        
        printf("\n");
        pshowdata( pmst->v1->data );
        printf("\t");
        pshowdata( pmst->v2->data );
        printf("\t");
        printf(" %zd ", pmst->weight );

        total_cost += pmst->weight;
    }

    printf("\nTotal Cost of Minimum Spanning Tree = %zd\n", total_cost);


    list_destroy(&set_list, delete_mst_node);
    set_list = NULL;
    
    list_destroy(&mst, NULL);
    mst = NULL;

    list_destroy(&list, delete_mst_node);
}
extern  void    graph_ford_fulkerson(   graph_t graph,
                                        SHOWDATA_PROC pshowdata)
{
    
}


