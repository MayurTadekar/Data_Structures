/**
 * S.G.M.P
 * @file: driver.c
 * @brief:
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 27 April 2024 (Saturday) 03:53:56 PM
 */

// Headers 
#include <stdio.h>
#include <stdlib.h>

#include "rbt.h"

// Global Data Definitions
RBTree tree = NULL;

ret_t compare(data_t d1, data_t d2)
{
	// Code
	if((long long )d1 == (long long)d2)
		return(CMP_SAME);
	else if((long long)d1 < (long long)d2)
		return(CMP_LESS);
		
	return(CMP_GREAT);
}

void print(data_t data)
{
	printf("%lld", (long long)data);
}

void print_inorder(RBTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = rbt_inorder_iterator(tree);
	printf("{START}-");
	while(!rbt_iterator_end(itr))
	{
		printf("{");
		printf("%lld", (long long)itr_data(itr));
		printf("}-");
		itr_next(itr);
	}
	printf("{END}\n");
	destroy_itr(&itr);
	itr = NULL;
}

void print_preorder(RBTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = rbt_preorder_iterator(tree);
	printf("{START}-");
	while(!rbt_iterator_end(itr))
	{
		printf("{");
		printf("%lld", (long long)itr_data(itr));
		printf("}-");
		itr_next(itr);
	}
	printf("{END}\n");
	destroy_itr(&itr);
	itr = NULL;
}

void print_postorder(RBTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = rbt_postorder_iterator(tree);
	printf("{START}-");
	while(!rbt_iterator_end(itr))
	{
		printf("{");
		printf("%lld", (long long)itr_data(itr));
		printf("}-");
		itr_next(itr);
	}
	printf("{END}\n");
	destroy_itr(&itr);
	itr = NULL;
}

void 	delete_data(data_t data)
{
	// Code
	printf("Deleting = %lld\n", (long long)data);
}

// Entry Point Function
int main(int argc, char** argv)
{
	// Code
	tree = create_tree();

	rbt_insert(tree, (data_t)(long long)1, compare);
	rbt_insert(tree, (data_t)(long long)2, compare);
	rbt_insert(tree, (data_t)(long long)3, compare);
	rbt_insert(tree, (data_t)(long long)4, compare);
	rbt_insert(tree, (data_t)(long long)5, compare);
	rbt_insert(tree, (data_t)(long long)6, compare);
	rbt_insert(tree, (data_t)(long long)7, compare);
	rbt_insert(tree, (data_t)(long long)8, compare);
	rbt_insert(tree, (data_t)(long long)9, compare);
	rbt_insert(tree, (data_t)(long long)10, compare);

	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	rbt_remove(tree,(data_t)(long long)4, compare);

	printf("\nAfter Remove\n");
	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	rbt_destroy(&tree, delete_data);

	return(0);
}
