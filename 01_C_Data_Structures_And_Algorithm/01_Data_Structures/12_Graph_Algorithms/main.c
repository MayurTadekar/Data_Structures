

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

status_t compare_in(graph_data_t d1, graph_data_t d2)
{
    if( (size_t)d1 < (size_t)d2 )
        return(SUCCESS);
    
    return(FAILURE);
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

int toValue(char* str)
{
    //  Code
    int value = 0;
    int index = 0;
    while( '\0' != str[index] )
    {
        if( '0' <= str[index] && '9' >= str[index] )
            value = (value * 10) + ( str[index] - '0' );
        else
        {
            return(-1);
        }
        ++index;
    }

    return(value);
}

int main(int argc, char **argv)
{

    if( argc < 3 )
    {
        fprintf(stderr, "ERROR: please enter EXE_NAME <NO_OF_VERTICES> <NO_OF_EDGES>\n");
        exit(1);
    }

    graph = create_graph(GRAPH_UNDIRECTED);
    srand(time(0));
    long nr_elements = toValue(argv[1]);
    if( -1 == nr_elements )
    {
        fprintf(stderr, "ERROR: Invalid Input\n");
        exit(1);
    }
    
    for( size_t i = 0; i < nr_elements; ++i )
        graph_add_vertex(graph, (graph_data_t)(size_t)( i + 1 ) );

    // graph_add_vertex(graph, (graph_data_t)(size_t)( 10 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 20 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 30 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 40 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 50 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 60 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 70 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 80 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 90 ) );
    // graph_add_vertex(graph, (graph_data_t)(size_t)( 100 ) );

    
    //size = rand() % 1000 + 1;
    long nr_edges = toValue(argv[2]);
    if( -1 == nr_edges )
    {
        fprintf(stderr, "ERROR: Invalid Input\n");
        exit(1);
    }
    for( size_t i = 0; i < nr_edges; ++i )
        graph_add_edge( graph,
                        (graph_data_t)(size_t)( rand() % nr_elements + 1 ),
                        (graph_data_t)(size_t)( rand() % nr_elements + 1 ),
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
    
    /*NEW_LINE;

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

    graph_formulate_set(graph, showdata);*/
    NEW_LINE;

    graph_kruskals_algorithm(graph, compare_in, showdata);

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


