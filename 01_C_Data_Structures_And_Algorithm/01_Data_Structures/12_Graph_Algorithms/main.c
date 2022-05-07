

/**
 * @author  Mayur Tadekar    
 * @date    05th May, 2022 
 * @details Driver Source code form DCLL
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

//#include    "dcll.h"
#include    "graph.h"
    
#define     NEW_LINE    (printf("\n"))

graph_t graph;


void    showdata(graph_data_t data)
{
    printf("%d",(long long)data);
}

void    showedge(graph_data_t data, size_t weight)
{
    printf("%d/%zd",(long long)data, weight);
}

void    deletedata(graph_data_t data)
{
    printf("delete = %d\n",(long long)data);
}

// void    PrintList(list_t list)
// {
//     printf("List:\n");
//     printf("{START}->");
//     list_show(list, showdata);
//     printf("{END}\n\n");
// }

dcll_status_t compare(dcll_data_t d1, dcll_data_t d2)
{
    if( (long long)d1 == (long long)d2 )
        return(SUCCESS);
    //printf(" %d == %d\n", (long long)d1, (long long)d2);
    
    return(FAILURE);
}

int main(void)
{
    // list = create_list();
    
    // list_insert(list, (dcll_data_t)10);
    // list_insert(list, (dcll_data_t)20);
    // list_insert(list, (dcll_data_t)30);
    // list_insert(list, (dcll_data_t)40);
    // list_insert(list, (dcll_data_t)50);
    // list_insert(list, (dcll_data_t)60);
    // list_insert(list, (dcll_data_t)70);
    // list_insert(list, (dcll_data_t)80);
    // list_insert(list, (dcll_data_t)90);
    // list_insert(list, (dcll_data_t)100);
    
    // PrintList(list);

    // for( int i = 0 ; i < list_size(list); ++i )
    // {
    //     printf(" %d => %d\n", i, (long long)list_at(list, i));
    // }

    // list_remove(list, (dcll_data_t)10, compare);
    // list_remove(list, (dcll_data_t)50, compare);
    // list_remove(list, (dcll_data_t)90, compare);
    // PrintList(list);

    // for( int i = 0 ; i < list_size(list); ++i )
    // {
    //     printf(" %d => %d\n", i, (long long)list_at(list, i));
    // }

    // list_destroy(&list, deletedata);
    
    // PrintList(list);
    
    graph = create_graph(GRAPH_UNDIRECTED);

    srand(time(0));
    // size_t size = rand() % 10 + 1;
    // for( size_t i = 0; i < size; ++i )
    //     graph_add_vertex(graph, (graph_data_t)(size_t)( rand() % 100 + 1 ) );

    graph_add_vertex(graph, (graph_data_t)(size_t)( 10 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 20 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 30 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 40 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 50 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 60 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 70 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 80 ) );
    graph_add_vertex(graph, (graph_data_t)(size_t)( 90 ) );

    
    size_t size = rand() % 1000 + 1;
    for( size_t i = 0; i < size; ++i )
        graph_add_edge( graph,
                        (graph_data_t)(size_t)(( rand() % 10 + 1 ) * 10),
                        (graph_data_t)(size_t)(( rand() % 10 + 1 ) * 10),
                        ( rand() % 100 + i ),
                        compare);

    graph_show(graph, showdata, showedge);

    NEW_LINE;
    printf("\nDeleted = %zd\n", (size_t) graph_remove_vertex(graph, 
                                        (graph_data_t)(size_t) 30,
                                        compare)
    );
    printf("\nDeleted = %zd\n", (size_t) graph_remove_vertex(graph, 
                                        (graph_data_t)(size_t) 60,
                                        compare)
    );
    printf("\nDeleted = %zd\n", (size_t) graph_remove_vertex(graph, 
                                        (graph_data_t)(size_t) 90,
                                        compare)
    );
    NEW_LINE;

    NEW_LINE;
    graph_show(graph, showdata, showedge);
    NEW_LINE;
    NEW_LINE;

    printf("Breadth First Search Single Source:\n");
    graph_breadth_first_search( graph,
                                (graph_data_t)(size_t)80,
                                compare,
                                showdata);
    NEW_LINE;
    
    printf("Breadth First Search All Vertices:\n");
    graph_breadth_first_search_all_vertices(graph,
                                            compare,
                                            showdata);
    NEW_LINE;

    NEW_LINE;
    
    printf("Deapth First Search All Vertices:\n");
    graph_deapth_first_search(graph,
                                (graph_data_t)(size_t)80,
                                compare,
                                showdata);
    NEW_LINE;
    
    printf("Deapth First Search All Vertices:\n");
    graph_deapth_first_search_all_vertices( graph,
                                            compare,
                                            showdata);
    NEW_LINE;
    // graph_remove_edge(graph, (graph_data_t)(size_t)10, (graph_data_t)(size_t)20, compare);

    // NEW_LINE;
    // graph_show(graph, showdata, showedge);
    // NEW_LINE;

    // graph_destroy(&graph, deletedata);

    // NEW_LINE;
    // graph_show(graph, showdata, showedge);
    // NEW_LINE;

    return(0);    
}


