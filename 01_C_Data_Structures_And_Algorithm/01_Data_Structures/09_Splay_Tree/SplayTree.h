

#ifndef     _SPLAY_TREE
#define     _SPLAY_TREE

//  Literals and Macros
#define     SUCCESS     0
#define     FAILURE     1


struct  Node;

typedef     struct Node     node_tree_t;
typedef     struct Node*    p_node_tree_t;
typedef     struct Node**   pp_node_tree_t;

struct Dummy;

typedef     struct Dummy    dummy_t;
typedef     struct Dummy*   p_dummy_t;
typedef     struct Dummy**  pp_dummy_t;

typedef     p_dummy_t       tree_t;

typedef     void*   data_t;
typedef     int     status_t;

typedef     status_t(*COMPARE_PROC)(data_t, data_t);
//typedef     void(*SHOWDATA_PROC)(data_t);
typedef     void(*DELETEDATA_PROC)(data_t);

struct Node
{
    data_t  data;
    p_node_tree_t    pleft, pright, parent;
};
#define     SIZE_NODE   (sizeof(node_tree_t))

struct Dummy
{
    p_node_tree_t proot;
    size_t  nr_elements;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

//  Tree auxillary functions
static  void*   Xcalloc(size_t nr_elements, size_t size_element);

static  p_node_tree_t    create_node(data_t data);

static  void    transplant(tree_t tree, p_node_tree_t u, p_node_tree_t v);

static 	void    tree_inorder_non_recursive(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);
static 	void	tree_preorder_non_recursive(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);
static 	void	tree_postorder_non_recursive(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);

static  void    inorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);
static  void    preorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);
static  void    postorder_run(p_node_tree_t pnode, SHOWDATA_PROC pshowdata);

static  p_node_tree_t    find_node(tree_t tree, data_t data, COMPARE_PROC pcompare);

static  p_node_tree_t    successor(p_node_tree_t pnode);   

static  void    left_rotate(tree_t tree, p_node_tree_t pnode);
static  void    right_rotate(tree_t tree, p_node_tree_t pnode);

static  void    splay(tree_t tree, p_node_tree_t pnode);

static  void    postorder_destroy(p_node_tree_t pnode, DELETEDATA_PROC pdeletedata);

//  Tree Interface Functions
extern  tree_t  tree_create();

extern  void    tree_insert(tree_t tree, data_t data, COMPARE_PROC pcompare);

extern  data_t  tree_remove(tree_t tree, data_t rdata, COMPARE_PROC pcompare);


extern	void		tree_in_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC pshowdata);
extern	void		tree_pre_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC pshowdata);
extern	void		tree_post_order_traversal_non_recursive(tree_t ptree, SHOWDATA_PROC pshowdata);

extern  void    tree_inorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata);
extern  void    tree_preorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata);
extern  void    tree_postorder_traversal(tree_t tree, SHOWDATA_PROC pshowdata);


extern  void    tree_destroy(tree_t* ptree, DELETEDATA_PROC pdeletedata);

#endif      /* _SPLAY_TREE */


