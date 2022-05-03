

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include	"tree.h"

struct data_node
{
	int data;
};
#define		SIZE_DATA 	(sizeof(struct data_node))

typedef struct data_node 	datan_t;
typedef struct data_node*	pdatan_t;

status_t compare(data_t e_data, data_t n_data)
{
	if( ((pdatan_t)e_data)->data == ((pdatan_t)n_data)->data )
		return(SAME_DATA);

	if( ((pdatan_t)e_data)->data < ((pdatan_t)n_data)->data )
		return(BIG_DATA);
	else
		return(SMALL_DATA);
}

void show_data(data_t data)
{
	printf("%d", ((pdatan_t)data)->data);
}

void delete_data(data_t data)
{
	printf("%d ", ((pdatan_t)data)->data);
	free(data);
}

tree_t tree = NULL;

int main(void)
{
	tree = tree_create();

	srand( time(0) );
	for( int i = 0; i < 10; ++i )
	{
		pdatan_t p = (pdatan_t) malloc(SIZE_DATA);
		p->data = rand() % 100 + 1;

		if( FAILURE ==  tree_insert(tree, p, compare) )
		{
			--i;
			continue;
		}

		fprintf(stdout, "\n-");
		show_data(p);
	}
	
	// pdatan_t p = (pdatan_t) malloc(SIZE_DATA);
	// p->data = 50;
	// tree_insert(tree, p, compare);

	fprintf(stdout,"InOrder:");
	tree_in_order_traversal(tree, show_data);
	tree_in_order_traversal_non_recursive(tree, show_data);
	fprintf(stdout,"\n");
	
	fprintf(stdout,"PreOrder:");
	tree_pre_order_traversal(tree, show_data);
	tree_pre_order_traversal_non_recursive(tree, show_data);
	fprintf(stdout,"\n");

	tree_post_order_traversal(tree, show_data);
	tree_post_order_traversal_non_recursive(tree, show_data);

	// srand( time(0) );
	// for( int i = 0; i < 4; ++i )
	// {
	// 	datan_t p = {rand() % 100 + 1};
	// 	pdatan_t pd = tree_delete(tree, &p, compare);

	// 	if ( NULL != pd )
	// 	{
	// 		fprintf(stdout, "\n");
	// 		show_data(pd);
	// 	}
	// }

	// tree_in_order_traversal(tree, show_data);
	// tree_pre_order_traversal(tree, show_data);
	// tree_post_order_traversal(tree, show_data);
	
	tree_destroy(&tree, delete_data);
	// tree_in_order_traversal(tree, show_data);
	// tree_pre_order_traversal(tree, show_data);
	// tree_post_order_traversal(tree, show_data);	

	return(SUCCESS);
}
