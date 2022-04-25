

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
            //printf("%zd - %d - ", pnode->count, i);//(size_t)pnode->parent->data[parent_index]);
        pshowdata(pnode->data[i]);
        printf("\n");
    } 
    if( i <= 2 * MAX )
        tree_run(pnode->children[i], pshowdata, i-1, tab_count+1);
}

static  status_t tree_search_node(p_node_t pnode, data_t sdata, pp_node_t snode, int* sindex, COMPARE_PROC pcompare)
{
    int index = 0;

    //printf("1\n");
    while(  index < pnode->count &&
            pcompare(pnode->data[index], sdata) == SUCCESS )
    {
        index++;
    }

    //printf("2 - %zd\n", (size_t)pnode->data[index-1]);

    if( index <= pnode->count   &&
        !(pcompare(pnode->data[index], sdata) == SUCCESS   ||
          pcompare(sdata, pnode->data[index]) == SUCCESS  ) )
    {
        *snode = pnode;
        *sindex = index;
        return(SUCCESS);
    }
    else if( pnode->isleaf == TRUE )
    {
        snode = NULL;
        *sindex = 0;
        return(FAILURE);
    }
    else 
    {
        return( tree_search_node(pnode->children[index], sdata, snode, sindex, pcompare) );
    }
}


static  data_t  remove_from_leaf(p_node_t pnode, int index)
{
    p_node_t ret_data = pnode->data[index];

    while( index < pnode->count)
    {
        pnode->data[index] = pnode->data[index+1];
        pnode->children[index] = pnode->children[index+1];
        index++;
    }
    pnode->children[index] = pnode->children[index+1];
    pnode->count--;
    return(ret_data);
}

static  data_t  remove_from_nonleaf(tree_t tree, p_node_t pnode, int dindex, COMPARE_PROC pcompare)
{

    //  x == pnode
    //  y == predecessor child of x
    //  z == successor child of x
    //printf("Non Leaf\n");

    data_t retdata;

    // Case 2-a
    // y have at least 't' keys.    
    if( pnode->children[dindex]->count >= MAX )
    {
        data_t rdata = pnode->children[dindex]->data[pnode->children[dindex]->count-1];
        //tree_remove(tree, rdata, pcompare);
        tree_remove_data(tree, pnode->children[dindex], rdata, pcompare);
        retdata = pnode->data[dindex];

        pnode->data[dindex] = rdata;
    }
    // Case 2-b
    // z have at least 't' keys.
    else if( pnode->children[dindex+1]->count >= MAX )
    {
        data_t rdata = pnode->children[dindex+1]->data[0];
        //tree_remove(tree, rdata, pcompare);
        tree_remove_data(tree, pnode->children[dindex+1], rdata, pcompare);
        retdata = pnode->data[dindex];

        pnode->data[dindex] = rdata;
    }
    //  Case 2-c
    //  y and z have 't-1' keys, merge k and all of z into y.
    //  Thus, x will loose k and pointer to z 
    else
    {
        // printf("\n Case 2 Else\n");
        p_node_t y = pnode->children[dindex];
        p_node_t z = pnode->children[dindex+1];
        
        // printf("y->data = %zd\n", y->data[0]);
        // printf("z->data = %zd\n", z->data[0]);

        int i = 0;
        for( i = 0; i < z->count; ++i )
        {
            y->data[y->count] = z->data[i];
            y->children[y->count+1] = z->children[i];
            y->count++;
        }
        y->children[y->count] = z->children[i];

        // printf("y->count = %zd\n", y->count);
        // for( int i = 0; i < y->count; ++i )
        // {
        //     printf("y->data[%d] = %zd\n", i, y->data[i]);
        // }

        retdata = pnode->data[dindex];
        free( pnode->children[dindex+1] );
        
        i = 0;
        for( i = dindex+1; i < pnode->count; ++i )
        {
            pnode->data[i-1] = pnode->data[i];
            pnode->children[i] = pnode->children[i+1];
        }
        pnode->children[i] = pnode->children[i+1];
        pnode->count--;
    }

    if( pnode->count == 0 && pnode == tree->proot )
    {
        tree->proot = pnode->children[0];
        free(pnode);
    }
    
    return(retdata);        
}

static  int     find_index(p_node_t pnode, data_t rdata, COMPARE_PROC pcompare)
{
    int index = 0;
    while(  index < pnode->count &&
            SUCCESS == pcompare(pnode->data[index], rdata) )
    {
        //printf("Compared %zd = %zd\n", (size_t)pnode->data[index], (size_t)rdata );
        index++;
    }
    
    ///printf("Returning = %d\n", index);
    return(index);
}

static  void    fill_child(tree_t tree, p_node_t pnode, int index)
{
    if( index != 0 && pnode->children[index-1]->count >= MAX )
    {
        //  Borrow From Prev
        borrow_from_prev(pnode, index);
    }
    else if ( index != pnode->count && pnode->children[index+1]->count >= MAX)
    {
        //  Borrow From Next
        borrow_from_next(pnode, index);
    }
    else
    {
        //printf("fill else %d - %zd \n", index, pnode->count);
        if( index <= pnode->count )
            merge_node(tree, pnode, index);
        else 
            merge_node(tree, pnode, index-1);
    }
}

static  void    merge_node(tree_t tree, p_node_t pnode, int index)
{
    p_node_t y = pnode->children[index];
    p_node_t z = pnode->children[index+1];
    
    //  printf("y->data = %zd\n", y->data[0]);
    //  printf("z->data = %zd\n", z->data[0]);
    //  printf("pnode->data = %zd\n", pnode->data[index]);

    y->data[y->count] = pnode->data[index];
    y->count++;

    int i = 0;
    for( i = 0; i < z->count; ++i )
    {
        y->data[y->count] = z->data[i];
        y->children[y->count] = z->children[i];
        y->count++;
    }
    y->children[y->count] = z->children[i];

    for( int i = index; i < pnode->count; ++i )
    {
        pnode->data[index] = pnode->data[index+1];
        pnode->children[index+1] = pnode->children[index+2]; 
    }    
    pnode->children[index+1] = pnode->children[index+2]; 

    pnode->count--;

    if( pnode->count == 0 && 
        tree->proot == pnode )
    {
        tree->proot = y;
        free(pnode);
    }

    // for( int i = 0 ; i < y->count; ++i )
    //     printf("*- %zd\n", y->data[i]);

    free(z);    
}

static  void    borrow_from_prev(p_node_t pnode, int index)
{

    p_node_t child = pnode->children[index];
    p_node_t sib = pnode->children[index-1];

    int i =  0;
    for( i = child->count; i > 0; ++i )
    {
        child->data[i] = child->data[i-1];
        child->children[i+1] = child->children[i];
    }
    child->children[i+1] = child->children[i];

    child->data[0] = pnode->data[index];

    pnode->data[index] = sib->data[sib->count-1];

    child->children[0] = sib->children[sib->count+1];

    sib->count--;
    child->count++;
}

static  void    borrow_from_next(p_node_t pnode, int index)
{
    p_node_t child = pnode->children[index];
    p_node_t sib = pnode->children[index+1];

    child->data[child->count] = pnode->data[index];
    child->children[child->count+1] = sib->children[0];
    pnode->data[index] = sib->data[0];

    int i = 0;
    for( i = 0; i < sib->count; i++ )
    {
        sib->data[i] = sib->data[i+1];
        sib->children[i] = sib->children[i+1];
    }
    sib->children[i] = sib->children[i+1];

    child->count++;
    sib->count--;
}


static  data_t  tree_remove_data(tree_t tree, p_node_t pnode, data_t rdata, COMPARE_PROC pcompare)
{
    int index = find_index(pnode, rdata, pcompare);

    //printf("\ndata -> %d - %zd -- %zd\n\n", index, pnode->data[index], rdata);

    if( index < pnode->count &&
        !(  (SUCCESS == pcompare(pnode->data[index], rdata) ) ||
            (SUCCESS == pcompare(rdata, pnode->data[index]) )  
        ) 
    )
    {
        if( TRUE == pnode->isleaf )
        {
            return(remove_from_leaf(pnode, index));
        }
        else
        { 
            return(remove_from_nonleaf(tree, pnode, index, pcompare));
        }
    }
    else
    {
        //printf("else\n");
        if( index > pnode->count )
            return(NULL);
        
        //printf("1 \n");
        
        if( MAX - 1 > pnode->children[index]->count )
        {
            //printf("FILL\n");
            fill_child(tree, pnode->children[index], index);
            
        }
        //printf("2 - %d\n", index);

        //if( index == pnode->count )
            return(tree_remove_data(tree, pnode->children[index], rdata, pcompare));
        //else 
        //    return(tree_remove_data(tree, pnode->children[index-1], rdata, pcompare));
    }
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

extern  data_t  tree_remove(tree_t tree, data_t rdata, COMPARE_PROC pcompare)
{
    if( NULL == tree ||
        NULL == tree->proot )
        return(NULL);
    
    p_node_t dnode = NULL;
    int     dindex = 0;
    data_t  ret_data = NULL;

    //printf("1\n");
    ret_data = tree_remove_data(tree, tree->proot, rdata, pcompare);

    return(ret_data);
}

extern  data_t  tree_search(tree_t tree, data_t sdata, COMPARE_PROC pcompare)
{
    if( NULL != tree ||
        NULL != tree->proot)
    {
        p_node_t pnode = NULL;
        int index = 0;
        tree_search_node(tree->proot, sdata, &pnode, &index, pcompare);
        return( pnode->data[index] );
    }

    return(NULL);
}

extern  void    tree_traversal(tree_t tree, SHOWDATA_PROC pshowdata)
{
    tree_run(tree->proot, pshowdata, 0, 0);
}

