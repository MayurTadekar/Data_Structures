

/**
 * @file disjointset.h
 * @author Mayur Tadekar
 * @brief Header for DisjointSet interface functions
 * @version 0.1
 * @date 05-08-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef     _DISJOINTSET_H
#define     _DISJOINTSET_H

//  Literals and Typedefinitions

#ifndef     SUCCESS
#define     SUCCESS     0
#endif

#ifndef     FAILURE
#define     FAILURE     1
#endif

struct  set_node;

typedef     struct set_node     set_node_t;
typedef     struct set_node*    p_set_node_t;
typedef     struct set_node**   pp_set_node_t;

struct set_dummy;

typedef     struct set_dummy        set_dummy_t;
typedef     struct set_dummy*       p_set_dummy_t;
typedef     struct set_dummy**      pp_set_dummy_t;

typedef     void*   set_data_t;

struct  set_node
{
    p_set_node_t    pnext;
    p_set_dummy_t   phead;

    set_data_t      data;
};
#define         SIZE_SET_NODE   (sizeof(set_node_t))

struct set_dummy
{
    p_set_node_t    head;
    p_set_node_t    tail;
    size_t          size;
};
#define     SIZE_SET_DUMMY      (sizeof(set_dummy_t))

typedef     void*   set_t;
typedef     int     status_t;    

typedef     status_t(*COMPARE_PROC)(set_data_t, set_data_t);
typedef     void(*SHOWDATA_PROC)(set_data_t);
typedef     void(*DELETEDATA_PROC)(set_data_t);

//  Set Auxillary Functions
static  void*   Xcalloc(size_t nr_elements, size_t element_size);

static  p_set_node_t    create_node(set_data_t data);

//  Set Interface Functions

extern  set_t    make_set(set_data_t data);

extern  set_data_t    set_find(set_t set, set_data_t data, COMPARE_PROC pcompare);

extern  status_t    set_union(set_t set1, set_t* pset2);

extern  void        set_traverse(set_t set, SHOWDATA_PROC pshowdata);

extern  set_data_t  set_at(set_t set, int index);

extern  size_t      set_size(set_t set);

extern  void        set_destroy(set_t* pset, DELETEDATA_PROC pdeletedata);

#endif      /* _DISJOINTSET_H */

//  Literals and Typedefs


