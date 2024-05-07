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

#include "avl.h"

// Global Data Definitions
AVLTree tree = NULL;

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

void print_inorder(AVLTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = avl_inorder_iterator(tree);
	printf("{START}-");
	while(!avl_iterator_end(itr))
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

void print_preorder(AVLTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = avl_preorder_iterator(tree);
	printf("{START}-");
	while(!avl_iterator_end(itr))
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

void print_postorder(AVLTree tree)
{
	// Code
	PIterator itr = NULL; 
	itr = avl_postorder_iterator(tree);
	printf("{START}-");
	while(!avl_iterator_end(itr))
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

	avl_insert(tree, (data_t)(long long)1, compare);
	avl_insert(tree, (data_t)(long long)2, compare);
	avl_insert(tree, (data_t)(long long)3, compare);
	avl_insert(tree, (data_t)(long long)4, compare);
	avl_insert(tree, (data_t)(long long)5, compare);
	avl_insert(tree, (data_t)(long long)6, compare);
	avl_insert(tree, (data_t)(long long)7, compare);
	avl_insert(tree, (data_t)(long long)8, compare);
	avl_insert(tree, (data_t)(long long)9, compare);
	avl_insert(tree, (data_t)(long long)10, compare);

	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	avl_remove(tree,(data_t)(long long)4, compare);

	printf("\nAfter Remove\n");
	print_inorder(tree);
	print_preorder(tree);
	print_postorder(tree);

	avl_destroy(&tree, delete_data);

	return(0);
}
