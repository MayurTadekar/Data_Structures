

#ifndef     _AVL_H
#define     _AVL_H

//  LITERALS AND MACROS

#define     SUCCESS         0
#define     FAILURE         1
#define     DATA_NOT_FOUND  2
#define     TREE_EMPTY      3

#define     SAME_DATA       0
#define     BIG_DATA        1   //  When Data in tree Greater Than Data to delete 
#define     SMALL_DATA      2   //  When Data in tree Lesser Than Data to delete

//  Types and Typedefs
struct  node;

typedef     struct node     node_t;
typedef     struct node*    p_node_t;
typedef     struct node**   pp_node_t;

struct  dummy;

typedef     struct dummy    dummy_t;
typedef     struct dummy*   p_dummy_t;
typedef     struct dummy**  pp_dummy_t;

typedef     p_dummy_t   tree_t;

typedef     void*       data_t;
typedef     int         status_t;

struct node
{
    data_t data;
    p_node_t    pleft, pright, parent;
};
#define     SIZE_NODE   (sizeof(node_t))

struct dummy
{
    p_node_t    p_root;
    size_t      no_of_elements;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

typedef     status_t(*COMPARE_PROC)(data_t, data_t);
typedef     void(*SHOWDATA_PROC)(data_t);

//  TREE INTERFACE FUNCTIONS

extern  tree_t  create_tree(void);

extern  status_t    tree_insert(tree_t ptree, data_t new_data, COMPARE_PROC p_compare_proc);
extern  data_t      tree_remove(tree_t ptree, data_t rem_data, COMPARE_PROC p_compare_proc);

extern  void        tree_inorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc);
extern  void        tree_preorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc);
extern  void        tree_postorder_traversal(tree_t ptree, SHOWDATA_PROC p_showdata_proc);

extern  data_t      tree_get_max(tree_t ptree);
extern  data_t      tree_get_min(tree_t ptree);

extern  size_t      tree_get_height(tree_t ptree);

//  TREE AUXILLARY FUNCTIONS
static  void    tree_left_rotate(tree_t ptree, p_node_t pnode);
static  void    tree_right_rotate(tree_t ptree, p_node_t pnode);

static  p_node_t tree_successor(p_node_t pnode);
static  p_node_t tree_predecessor(p_node_t pnode);

static  void    tree_transplant(tree_t ptree, p_node_t pnode, p_node_t tranp);

static  size_t  tree_get_height_node(p_node_t p_node);
static  int     tree_get_balance(p_node_t p_node);

static  p_node_t tree_get_max_node(p_node_t pnode);
static  p_node_t tree_get_min_node(p_node_t pnode);
static  p_node_t tree_create_node(data_t new_data);

void*   Xcalloc(size_t no_elements, size_t size_per_element);

#endif  /* _AVL_H */
