

#include    <stdio.h>
#include    <stdlib.h>

#include    "b_tree.h"

//  Tree Auxillary Functions

static  void*   Xcalloc(size_t nr_elements, size_t size_element)
{
    void* p = calloc(nr_elements, size_element);

    if( NULL == p )
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }

    return(p);
}

static  p_node_t    create_node()
{
    p_node_t pnode = (p_node_t) Xcalloc(1, SIZE_NODE);
    for( int i = 0; i < MAX; ++i )
    {
        pnode->children[i] = NULL;
        pnode->data[i] = NULL;
    }
    pnode->count = 0;
    pnode->isleaf = TRUE;
    pnode->parent = NULL;

    return(pnode);
}

static  void    split_child(p_node_t pnode, int index)
{
    p_node_t newnode = create_node();
    p_node_t child = pnode->children[index];

    newnode->isleaf = child->isleaf;
    newnode->count = MAX - 1;
    
    size_t median = MAX - 1;

    for( size_t i = 0; i < MAX - 1; ++i )
    {
        newnode->data[i] = child->data[median + i + 1];
        child->data[median + i + 1] = NULL;
    }

    if( !child->isleaf )
    {
        for( size_t i = 0; i <= MAX; ++i )
        {
            newnode->children[i] = child->children[i + median + 1];
            child->children[i + median + 1] = NULL;
        }
    }

    //newnode->count = child->count - median - 1;
    child->count =  MAX - 1;


    //printf("\n1\n");

    for(size_t i = pnode->count; i > index; --i)
        pnode->children[i+1] = pnode->children[i];
    pnode->children[index+1] = newnode;

    //printf("\n2\n");

    for(int i = pnode->count-1; i >= index; --i)
    {
        //printf("\n4 - %zd - %zd\n", (size_t)pnode->data[i], index);
        pnode->data[i+1] = pnode->data[i];
    }
    pnode->data[index] = child->data[median];
    //pnode->children[index+1] = newnode;

    //printf("\n3\n");

    child->parent = pnode;
    newnode->parent = pnode;

    pnode->count++;
    //printf("\nMedian:%zd - %zd\n", (size_t)child->data[median], child->count);
    //printf("\nNewnode:%zd - %zd\n", (size_t)newnode->data[median], newnode->count);
}

static  status_t    insert_non_full(p_node_t pnode, data_t newdata, COMPARE_PROC compare)
{
    size_t index = pnode->count - 1;
    if( pnode->isleaf )
    {
        if( !(  compare(newdata, pnode->data[index]) == SUCCESS ||
                compare(pnode->data[index], newdata) == SUCCESS )    )
                return(FAILURE);

        while(  index >= 0 && 
                compare(newdata, pnode->data[index]) == SUCCESS)
        {
            //printf("\n1\n");
            pnode->data[index+1] = pnode->data[index];
            pnode->children[index+2] = pnode->children[index+1];
            index--;
        }
        
        pnode->data[index+1] = newdata;
        pnode->count = pnode->count+1;

        //printf("\n%zd - %d\n", (size_t)newdata, pnode->count);
    }
    else 
    {
        while(  index >= 0 &&
                compare(newdata, pnode->data[index]) == SUCCESS )
        {
            if( !(  compare(newdata, pnode->data[index]) == SUCCESS ||
                    compare(pnode->data[index], newdata) == SUCCESS )    )
                return(FAILURE);

            index--;
        }
        index = index+1;

        if( pnode->children[index]->count == 2 * MAX - 1 )
        {
            
            if( !(  compare(newdata, pnode->data[index]) == SUCCESS ||
                    compare(pnode->data[index], newdata) == SUCCESS )    )
                return(FAILURE);

            //printf("\n%zd\n", (size_t)newdata);
            split_child(pnode, index);
            //exit(0);

            if( compare(pnode->data[index], newdata) == SUCCESS)
                index = index+1;
        }
        return(insert_non_full(pnode->children[index], newdata, compare));
    }

    return(SUCCESS);
}


static  void    tree_run(p_node_t pnode, SHOWDATA_PROC pshowdata, size_t parent_index, size_t tab_count)
{
    if( NULL == pnode )
        return;

    size_t i = 0; 
    for( i = 0; i < pnode->count ; ++i )
    {
        tree_run(pnode->children[i], pshowdata, i, tab_count+1);
        
        for(size_t j = 0; j < tab_count; j++)
            printf("\t");

        //if( pnode->parent )
            //printf("%zd - ", pnode->count);//(size_t)pnode->parent->data[parent_index]);
        pshowdata(pnode->data[i]);
        printf("\n");
    } 
    if( i <= 2 * MAX )
        tree_run(pnode->children[i], pshowdata, i-1, tab_count+1);
}

//  Tree Interface Functions
extern  tree_t  tree_create()
{
    tree_t ptree = (tree_t) Xcalloc(1, SIZE_DUMMY);
    ptree->nr_elements = 1;
    ptree->proot = create_node();
    return(ptree);
}

extern  status_t    tree_insert(tree_t tree, data_t data, COMPARE_PROC pcompare)
{
    p_node_t prun = tree->proot;

    if( prun->count == 2 * MAX - 1 )
    {
        //printf("\nMax\n");
        p_node_t newnode = create_node();
        newnode->count = 0;
        newnode->isleaf = FALSE;
        newnode->children[0] = prun;
        tree->proot = newnode;
        
        split_child(newnode, 0);
        return(insert_non_full(newnode, data, pcompare));
    }
    else
    {
        return(insert_non_full(tree->proot, data, pcompare));
    }
}

extern  data_t  tree_remove(tree_t tree, COMPARE_PROC pcompare);

extern  data_t  tree_search(tree_t tree, data_t sdata, COMPARE_PROC pcompare);

extern  void    tree_traversal(tree_t tree, SHOWDATA_PROC pshowdata)
{
    tree_run(tree->proot, pshowdata, 0, 0);
}

