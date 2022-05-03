

#ifndef     _RB_TREE
#define     _RB_TREE

//  Literals and Macros

#define     SUCCESS     0
#define     FAILURE     1

#define     TREE_EMPTY      2
#define     NO_DATA_FOUND   3

#define     SAME_DATA   0
#define     SMALL_DATA  1
#define     BIG_DATA    2

#define     RED         1
#define     BLACK       2

//  Typedefs and Types

struct  node_tree;

typedef     struct node_tree     node_tree_t;
typedef     struct node_tree*    p_node_tree_t;
typedef     struct node_tree**   pp_node_tree_t;

struct  Dummy;

typedef     struct Dummy    dummy_t;
typedef     struct Dummy*   p_dummy_t;
typedef     struct Dummy**  pp_dummy_t;

typedef     p_dummy_t     rbtree_t;
typedef     pp_dummy_t    p_rbtree_t;

typedef     void*   data_t;
typedef     int     status_t;
typedef     int     bool_t;
typedef     int     color_t;

struct node_tree
{
    data_t  data;
    color_t color;
    p_node_tree_t    pleft, pright, parent;
};
#define     SIZE_NODE   (sizeof(node_tree_t))

struct Dummy
{
    p_node_tree_t    proot;
    size_t      nr_elements;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

typedef     bool_t(*COMPARE_PROC)(data_t tree_data, data_t n_data);

//typedef     void(*SHOWDATA_PROC)(data_t data);

typedef     void(*DELETE_DATA_PROC)(data_t data);

//  Tree Interface Functions

extern  rbtree_t    create_tree();
extern  status_t    tree_insert(rbtree_t tree, data_t ndata, COMPARE_PROC p_compare_proc);
extern  data_t      tree_remove(rbtree_t tree, data_t rdata, COMPARE_PROC p_compare_proc);

extern  void        tree_inorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc);
extern  void        tree_preorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc);
extern  void        tree_postorder_traversal(rbtree_t tree, SHOWDATA_PROC p_showdata_proc);

extern	void		tree_in_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc);
extern	void		tree_pre_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc);
extern	void		tree_post_order_traversal_non_recursive(rbtree_t ptree, SHOWDATA_PROC show_data_proc);

extern  size_t      tree_height(rbtree_t tree);

extern  void        tree_destroy(p_rbtree_t ptree, DELETE_DATA_PROC p_deletedata_proc);

//  Tree Auxillary Functions

static  p_node_tree_t    tree_successor(p_node_tree_t pnode_tree);
static  p_node_tree_t    tree_pred(p_node_tree_t pnode_tree);

static  void        right_rotate(rbtree_t tree, p_node_tree_t pnode_tree);
static  void        left_rotate(rbtree_t tree, p_node_tree_t pnode_tree);

static  void        inorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc);
static  void        preorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc);
static  void        postorder_run(p_node_tree_t pnode_tree, SHOWDATA_PROC p_showdata_proc);

static 	void		tree_inorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc);
static 	void		tree_preorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc);
static 	void		tree_postorder_non_recursive(p_node_tree_t pnode_tree, SHOWDATA_PROC show_data_proc);

static  void        insert_fixup(rbtree_t tree, p_node_tree_t pnode_tree);
static  void        delete_fixup(rbtree_t tree, p_node_tree_t pnode_tree);

static  void        transplant(rbtree_t tree, p_node_tree_t u, p_node_tree_t v);

static  int         node_tree_height(p_node_tree_t pnode_tree);

static  void        post_order_data_delete(p_node_tree_t pnode_tree, DELETE_DATA_PROC p_deletedata_proc);

static  p_node_tree_t    create_node_tree(data_t data);

static  void*       Xcalloc(size_t nr_elememts, size_t size_of_element);

#endif      /* _RB_TREE */

