

#ifndef		_TREE_H
#define		_TREE_H

//	Constant Literals and Macros
#define		SUCCESS		0
#define 	FAILURE		1

#define		SAME_DATA	1
#define		BIG_DATA	2
#define		SMALL_DATA	3

//	Typedefs and Struct Type Declaration

struct 	_node;
typedef		struct _node	node_t;
typedef		struct _node*	p_node_t;
typedef		struct _node**	pp_node_t;

struct _dummy;
typedef 	struct _dummy 	dummy_t;
typedef 	struct _dummy* 	p_dummy_t;
typedef 	struct _dummy**	pp_dummy_t;

typedef 	struct _dummy* 	tree_t;

typedef 	int 	ret_t;
typedef 	int 	status_t;

typedef 	void* 	data_t;

typedef		status_t(*p_compare_proc)(data_t e_data, data_t n_data);

typedef 	void(*p_show_data_proc)(data_t e_data);
typedef 	void(*p_delete_data_proc)(data_t e_data);

//	Struct Type Definition
struct _node
{
	data_t	data;
	size_t	height;
	p_node_t 	p_left, p_right, p_parent;
};
#define		SIZE_NODE		(sizeof(node_t))

struct _dummy
{
	p_node_t 	root;
};
#define		SIZE_DUMMY		(sizeof(dummy_t))


//	Tree Interface Functions
extern	tree_t		tree_create(void);
extern	status_t	tree_insert(tree_t ptree, data_t data, p_compare_proc compare_proc);
extern	data_t		tree_delete(tree_t ptree, data_t data, p_compare_proc compare_proc);

extern	void		tree_in_order_traversal(tree_t ptree, p_show_data_proc show_data_proc);
extern	void		tree_pre_order_traversal(tree_t ptree, p_show_data_proc show_data_proc);
extern	void		tree_post_order_traversal(tree_t ptree, p_show_data_proc show_data_proc);

extern	data_t		tree_search(tree_t ptree, data_t s_data, p_compare_proc compare_proc);

extern	data_t 		tree_get_successor(tree_t ptree, data_t data, p_compare_proc compare_proc);
extern	data_t 		tree_get_predecessor(tree_t ptree, data_t data, p_compare_proc compare_proc);

extern 	status_t	tree_destroy(tree_t* pptree, p_delete_data_proc delete_data_proc);


//	Tree Auxillary Functions
static 	void* 		Xmalloc(size_t size);

static 	p_node_t 	tree_create_node(data_t data);

static	status_t	tree_check_root(tree_t ptree);
static	size_t 		tree_height(p_node_t pnode);

static	status_t 	tree_generic_insert(p_node_t pnode, p_node_t n_node, p_compare_proc compare_proc);
static	data_t 		tree_generic_delete(tree_t ptree, p_node_t pnode);

static	void 		tree_transplant(tree_t ptree, p_node_t pnode, p_node_t t_pnode); 	

static 	p_node_t 	tree_find_node(tree_t ptree, data_t data, p_compare_proc compare_proc);

static	p_node_t 	tree_successor(p_node_t pnode);
static	p_node_t 	tree_predecessor(p_node_t pnode);

static 	void		tree_inorder(p_node_t pnode, p_show_data_proc show_data_proc);
static 	void		tree_preorder(p_node_t pnode, p_show_data_proc show_data_proc);
static 	void		tree_postorder(p_node_t pnode, p_show_data_proc show_data_proc);

static 	void		tree_postorder_destroy(tree_t ptree, p_node_t pnode, p_delete_data_proc delete_data_proc);

#endif	/* _TREE_H */

/* TODO FUNCTIONS  
1)	Convert a list to BST
2)	Convert a BST to sorted data list
3)	Convert a BST to sorted data vector
*/