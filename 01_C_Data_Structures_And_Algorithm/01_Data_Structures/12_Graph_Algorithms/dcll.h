

/**
 *  @author Mayur Tadekar   
 *  @date   05th May, 2022 
 *  @details    Header file for all interface functions and 
 *              required type definitions for DCLL 
 */

#ifndef     _DCLL_H
#define     _DCLL_H

//  Literals and Typedefs

#define     SUCCESS     1
#define     FAILURE     0

typedef     void*       dcll_data_t;

struct  dcll_node;

typedef     struct  dcll_node   dcll_node_t;
typedef     struct  dcll_node*  p_dcll_node_t;
typedef     struct  dcll_node** pp_dcll_node_t;

struct  dcll_dummy;

typedef     struct dcll_dummy       dcll_dummy_t;
typedef     struct dcll_dummy*      p_dcll_dummy_t;
typedef     struct dcll_dummy**     pp_dcll_dummy_t;

typedef     int     dcll_status_t;

struct dcll_node
{
    dcll_data_t     data;
    p_dcll_node_t   pnext, pprev;
};
#define     SIZE_DCLL_NODE      (sizeof(dcll_node_t))

struct dcll_dummy
{
    p_dcll_node_t   list;
    size_t          nr_elements;
};
#define     SIZE_DCLL_DUMMY     (sizeof(dcll_dummy_t))

typedef     void*   list_t;
typedef     void**  p_list_t;

typedef     dcll_status_t(*COMPARE_PROC)(dcll_data_t d1, dcll_data_t d2);
typedef     void(*SHOWDATA_PROC)(dcll_data_t d);
typedef     void(*DELETEDATA_PROC)(dcll_data_t d);

//  List Auxillary Functions
static  void*   Xcalloc(size_t nr_elements, size_t element_size);

static  dcll_status_t    list_generic_insert(p_dcll_node_t first, p_dcll_node_t mid, p_dcll_node_t last);
static  dcll_data_t      list_generic_remove(p_dcll_node_t pnode);

static  p_dcll_node_t   list_create_node(dcll_data_t data);

static  p_dcll_node_t   list_locate_node(list_t list, dcll_data_t edata, COMPARE_PROC pcompare);

//  List Interface Functions
extern  list_t  create_list();

extern  dcll_status_t   list_insert(list_t list, dcll_data_t data);
extern  dcll_status_t   list_insert_front(list_t list, dcll_data_t data);
extern  dcll_status_t   list_insert_back(list_t list, dcll_data_t data);

extern  dcll_data_t     list_remove(list_t list, dcll_data_t edata, COMPARE_PROC pcompare);
extern  dcll_data_t     list_remove_first(list_t list);
extern  dcll_data_t     list_remove_last(list_t list);

extern  dcll_data_t     list_at(list_t list, int index);

extern  size_t  list_size(list_t list);

extern  void    list_show(list_t list, SHOWDATA_PROC pshowdata);

extern  dcll_status_t    list_destroy(p_list_t plist, DELETEDATA_PROC pdeletedata);

#endif      /* _DCLL_H */

