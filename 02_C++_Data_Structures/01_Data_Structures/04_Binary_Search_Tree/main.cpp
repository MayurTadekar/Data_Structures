

#include	<iostream>

#include	"BST.h"

BinarySearchTree<int> *bst = NULL;

ret_t 	compare(int d1, int d2)
{
	if( d1 > d2 )
		return(SUCCESS);

	return(FAILURE);
}

ret_t 	compare2(int d1, int d2)
{
	if( d1 == d2 )
		return(SAME_DATA);

	if( d1 > d2 )
		return(SMALL_DATA);

	return(BIG_DATA);
}

void 	show(int d1)
{
	std::cout << d1 << " ";
}

void 	show2(int d1)
{
	std::cout << "Delete:" << d1 << std::endl;
}

int main(void)
{

	bst = new BinarySearchTree<int>();

	bst->TreeAddNode(50, compare);
	bst->TreeAddNode(30, compare);
	bst->TreeAddNode(70, compare);
	bst->TreeAddNode(20, compare);
	bst->TreeAddNode(40, compare);
	bst->TreeAddNode(60, compare);
	bst->TreeAddNode(80, compare);
	//bst->TreeAddNode(10, compare);
	bst->TreeAddNode(25, compare);
	bst->TreeAddNode(35, compare);
	bst->TreeAddNode(45, compare);
	bst->TreeAddNode(55, compare);
	bst->TreeAddNode(65, compare);
	bst->TreeAddNode(75, compare);
	//bst->TreeAddNode(85, compare);

	std::cout << "Tree Data:" ;
	bst->TreeInOrder(show);
	std::cout << std::endl;
	
	std::cout << "Tree Data:" ;
	bst->TreeInOrder_Iterative(show);
	std::cout << std::endl;

	std::cout << "Tree Data:" ;
	bst->TreePreOrder(show);
	std::cout << std::endl;
	
	std::cout << "Tree Data:" ;
	bst->TreePreOrder_Iterative(show);
	std::cout << std::endl;

	std::cout << "Tree Data:" ;
	bst->TreePostOrder(show);
	std::cout << std::endl;
	
	std::cout << "Tree Data:" ;
	bst->TreePostOrder_Iterative(show);
	std::cout << std::endl;

	// bst->TreeDeleteNode(75, compare2);
	// std::cout << "Tree Data:";
	// bst->TreeInOrder(show);
	// std::cout << std::endl;

	// bst->TreeDeleteNode(25, compare2);
	// std::cout << "Tree Data:";
	// bst->TreeInOrder(show);
	// std::cout << std::endl;

	// bst->TreeDeleteNode(70, compare2);
	// std::cout << "Tree Data:";
	// bst->TreeInOrder(show);
	// std::cout << std::endl;

	// bst->TreeDeleteNode(50, compare2);
	// std::cout << "Tree Data:";
	// bst->TreeInOrder(show);
	// std::cout << std::endl;
	
	// std::cout << std::endl;
	// std::cout << bst->TreeSearchNode( 50, compare2);
	
	// std::cout << std::endl;
	// std::cout << bst->TreeSearchNode( 40, compare2);

	// std::cout << std::endl;
	// std::cout << std::endl;
	// bst->TreeDestroy(show2);

	// std::cout << "Tree Data:";
	// bst->TreeInOrder(show);
	// std::cout << std::endl;
	
	return(0);
}

