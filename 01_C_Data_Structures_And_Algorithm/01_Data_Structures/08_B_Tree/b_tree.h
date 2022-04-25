

#ifndef     _B_TREE
#define     _B_TREE 

//  Literals and Macros

#define     SUCCESS     0
#define     FAILURE     1

#define     MAX     3
#define     MIN     2

struct Node;

typedef     struct Node     node_t;
typedef     struct Node*    p_node_t;
typedef     struct Node**   pp_node_t;

struct Dummy;

typedef     struct Dummy    dummy_t;
typedef     struct Dummy*   p_dummy_t;
typedef     struct Dummy**  pp_dummy_t;

typedef     p_dummy_t   tree_t;

typedef     void*   data_t;
typedef     int     status_t;

typedef     status_t(*COMPARE_PROC)(data_t, data_t);
typedef     void(*SHOWDATA_PROC)(data_t);

typedef enum 
{
    FALSE = 0,
    TRUE
}bool_t;

struct Node
{
    size_t      count;
    p_node_t    parent;
    bool_t      isleaf;
    
    data_t      data[2 * MAX];
    p_node_t    children[2 * MAX + 1];
};
#define     SIZE_NODE   (sizeof(node_t))

struct Dummy
{
    p_node_t    proot;
    size_t      nr_elements;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

//  Tree Auxillary Functions

static  void*   Xcalloc(size_t nr_elements, size_t size_element);

static  p_node_t    create_node();

static  void    split_child(p_node_t pnode, int index);
static  status_t    insert_non_full(p_node_t pnode, data_t newdata, COMPARE_PROC compare);

static  void    tree_run(p_node_t pnode, SHOWDATA_PROC pshowdata, size_t parent_index, size_t tab_count);

static  status_t tree_search_node(p_node_t pnode, data_t sdata, pp_node_t snode, int* index, COMPARE_PROC pcompare);

static  int     find_index(p_node_t pnode, data_t rdata, COMPARE_PROC pcompare);

static  data_t  remove_from_leaf(p_node_t pnode, int dindex);
static  data_t  remove_from_nonleaf(tree_t tree, p_node_t pnode, int dindex, COMPARE_PROC pcompare);

static  void    fill_child(tree_t tree, p_node_t pnode, int index);

static  void    borrow_from_prev(p_node_t pnode, int index);
static  void    borrow_from_next(p_node_t pnode, int index);
static  void    merge_node(tree_t, p_node_t, int);

static  data_t  tree_remove_data(tree_t tree, p_node_t pnode, data_t rdata, COMPARE_PROC pcompare);

//  Tree Interface Functions

extern  tree_t  tree_create();

extern  status_t    tree_insert(tree_t tree, data_t data, COMPARE_PROC pcompare);

extern  data_t  tree_remove(tree_t tree, data_t rdata, COMPARE_PROC pcompare);

extern  data_t  tree_search(tree_t tree, data_t sdata, COMPARE_PROC pcompare);

extern  void    tree_traversal(tree_t tree, SHOWDATA_PROC pshowdata);

#endif      /* _B_TREE */

