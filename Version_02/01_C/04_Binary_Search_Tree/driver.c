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

#include "bst.h"

// Global Data Definitions
BinarySearchTree tree = NULL;

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

void print_inorder(BinarySearchTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = bst_inorder_iterator(tree);
	printf("{START}-");
	while(!bst_iterator_end(itr))
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

void print_preorder(BinarySearchTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = bst_preorder_iterator(tree);
	printf("{START}-");
	while(!bst_iterator_end(itr))
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

void print_postorder(BinarySearchTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = bst_postorder_iterator(tree);
	printf("{START}-");
	while(!bst_iterator_end(itr))
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

	bst_insert(tree, (data_t)(long long)15, compare);
	bst_insert(tree, (data_t)(long long)6, compare);
	bst_insert(tree, (data_t)(long long)18, compare);
	bst_insert(tree, (data_t)(long long)3, compare);
	bst_insert(tree, (data_t)(long long)7, compare);
	bst_insert(tree, (data_t)(long long)17, compare);
	bst_insert(tree, (data_t)(long long)20, compare);

	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	bst_remove(tree,(data_t)(long long)15, compare);

	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	bst_destroy(&tree, delete_data);

	return(0);
}
