

#ifndef		_LIST_H
#define		_LIST_H

/*	CONSTANT LITERALS & MACROS	*/
#define 	SUCCESS 				0
#define 	FAILURE 				1
#define 	E_LIST_EMPTY 			2
#define 	E_LIST_NOT_PRESENT 		3
#define     E_DATA_NOT_PRESENT      4
#define 	E_DATA_ALREADY_PRESENT	5
#define 	E_POSITION_OUT_OF_LIMIT	6


/* 	TYPE & TYPEDEFS 	*/
struct 	node;
typedef		struct node		node_t;
typedef 	struct node*	p_node_t;
typedef 	struct node** 	pp_node_t;

struct dummy;
typedef     struct dummy    dummy_t;
typedef     struct dummy*   p_dummy_t;
typedef     struct dummy**  pp_dummy_t;   

typedef     p_node_t   p_list_t;    
typedef     pp_node_t  pp_list_t;    

typedef 	void* 	data_t;
typedef 	data_t* p_data_t;

typedef 	int 	ret_t; 

typedef 	size_t 	len_t;

typedef 	void* 	list_t;

struct node
{
	data_t	data;
	p_node_t 	pnext, pprev;
};
#define 	SIZE_NODE	(sizeof(node_t))

struct dummy
{
    size_t noOfNodes;
    p_node_t list;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

typedef enum bool_t
{
	false = 0,
	true 
}bool_t;

/*	INTERFACE FUNCTION	*/
extern 	list_t	list_create(void);

/***************************************************************************\
 *
 * 	functions for data insertion in list
 * 	
 * 	input parameters:-
 * 	> list 	:-	pointer for list.
 * 	> data 		:- 	data to insert in list.
 * 	> edata 	:-	existing data in list.
 * 	> idata 	:-	data to insert in list.
 * 	> position 	:-	position of data.
 *  NOTE: Position starts from 0.
 *  > p_equality_compare_proc	:-	function pointer to a function that takes 2 data and 
 *  					returns the result of comparison of both data.
 * 
 *	return values:
 * 	> SUCCESS	:- 	successfull insertion 
 * 	> E_LIST_EMPTY 	:-	failure when list has no data.
 * 	> E_LIST_NOT_PRESENT	:-	failure when list not present.
 * 	> E_DATA_NOT_PRESENT 	:-	failure when data not present.
 * 	> E_POSITION_OUT_OF_BOUND	:-	failure when position is greater than total
 * 									data present.
 * 
\***************************************************************************/
extern	ret_t 	list_insert_front(list_t list, data_t data);
extern 	ret_t 	list_insert_back(list_t list, data_t data);
extern 	ret_t 	list_insert_position(list_t list, data_t data, size_t position);
extern 	ret_t 	list_insert_after(list_t list, data_t edata, data_t idata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));
extern	ret_t 	list_insert_before(list_t list, data_t edata, data_t idata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));
extern 	ret_t 	list_insert(list_t list, data_t data);


/***************************************************************************\
 *
 * 	functions for data removal from list
 * 	
 * 	input parameters:-
 * 	> list 	:-	pointer for list.
 * 	> pdata 	:- 	pointer to data to give away the removed data.
 * 	> edata 	:-	existing data in list.
 * 	> position 	:-	position of data.
 *  NOTE: Position starts from 0.
 *  > p_equality_compare_proc	:-	function pointer to a function that takes 2 data and 
 *  					returns the result of comparison of both data.
 * 
 *	return values:
 * 	> SUCCESS	:- 	successfull insertion 
 * 	> E_LIST_EMPTY 	:-	failure when list has no data.
 * 	> E_LIST_NOT_PRESENT	:-	failure when list not present.
 * 	> E_DATA_NOT_PRESENT 	:-	failure when data not present.
 * 	> E_POSITION_OUT_OF_BOUND	:-	failure when position is greater than total
 * 									data present.
 * 
\***************************************************************************/
extern 	ret_t  	list_remove_front(list_t list, p_data_t pdata); 
extern 	ret_t 	list_remove_back(list_t list, p_data_t pdata);
extern 	ret_t 	list_remove_position(list_t list, size_t position, p_data_t pdata);
extern 	ret_t 	list_remove_after(list_t list, data_t edata, p_data_t pdata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));
extern 	ret_t 	list_remove_before(list_t list, data_t edata, p_data_t pdata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));
extern 	ret_t 	list_remove(list_t list, data_t edata, p_data_t pdata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));

extern 	len_t 	list_length(list_t list);
extern 	bool_t 	list_contains(list_t list, data_t edata, bool_t (*p_equality_compare_proc)(data_t data1, data_t data2));
extern 	ret_t 	list_show(list_t list, void(*p_show_data)(data_t));
extern 	ret_t 	list_is_empty(list_t list);

extern	list_t 	list_merge(list_t list1, list_t list2, bool_t (*p_inequality_compare_proc)(data_t, data_t));
extern 	list_t 	list_concate(list_t list1, list_t list2);
extern 	list_t 	list_reverse(list_t list);

extern 	ret_t  	list_append(list_t list1, list_t list2);
extern 	ret_t 	list_destroy(pp_list_t pplist, void(*p_delete_data)(data_t));


#endif		/*	_LIST_H */

