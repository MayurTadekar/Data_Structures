/**
 * S.G.M.P
 * @file: bst.hpp
 * @brief: Defines the AVLTree class, which represents a binary search tree.
 * 
 * @details This file declares the AVLTree class, which is derived from the BinaryTree class.
 *          The AVLTree class implements methods for inserting and removing elements from
 *          the binary search tree while maintaining the properties of a binary search tree.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 07 May 2024 (Tuesday) 02:51:26 PM
 */

#pragma once

// Headers
#include "binarytree.hpp"

template <class T>
class AVLTree : public BinaryTree<T>
{
private:

	/**
	 * @brief Calculates the height of the subtree rooted at the given node.
	 * @details This function recursively computes the height of the subtree by comparing the heights of its left and right subtrees.
	 * @param node The root node of the subtree.
	 * @return The height of the subtree.
	 */
	int Height(Node node)
	{
		// Code
		if(nullptr == node)
			return(0);
		else
		{
			int left_height = Height(node->left());
			int right_height = Height(node->right());

			if( left_height >= right_height)
				return(left_height+1);
			else
				return(right_height+1);
		}
	}

	/**
	 * @brief Calculates the balance factor of the given node.
	 * @details The balance factor of a node is defined as the difference between the height of its left and right subtrees.
	 * @param node The node for which the balance factor is calculated.
	 * @return The balance factor of the node.
	 */
	int BalanceFactor(Node node)
	{
		// Code
		int left_height = Height(node->left());
		int right_height = Height(node->right());

		return(left_height - right_height);
	}

	/**
	 * @brief Performs a left rotation on the subtree rooted at the given node.
	 * @details This function performs a left rotation to balance the subtree by adjusting the pointers appropriately.
	 * @param node The root node of the subtree where left rotation is performed.
	 * @return The new root node after left rotation.
	 */
	Node LeftRotate(Node node)
	{
		// Code
		Node right = node->right();

		node->right(right->left());

		right->parent(node->parent());
		if(node->parent())
		{
			if(node == node->parent()->left())
				node->parent()->left(right);
			else
				node->parent()->right(right);
		}
		right->left(node);

		return(right);
	}

	/**
	 * @brief Performs a right rotation on the subtree rooted at the given node.
	 * @details This function performs a right rotation to balance the subtree by adjusting the pointers appropriately.
	 * @param node The root node of the subtree where right rotation is performed.
	 * @return The new root node after right rotation.
	 */
	Node RightRotate(Node node)
	{
		// Code
		Node left = node->left();

		node->left(left->right());
		

		left->parent(node->parent());
		if(node->parent())
		{
			if(node == node->parent()->left())
				node->parent()->left(left);
			else
				node->parent()->right(left);
		}
		left->right(node);

		return(left);
	}
	
	/**
	 * @brief Performs appropriate rotation(s) to balance the subtree rooted at the given node.
	 * @details This function checks the balance factor of the node and performs rotations accordingly to balance the subtree.
	 * @param node The root node of the subtree to be balanced.
	 * @return The new root node of the balanced subtree.
	 */
	Node Rotate(Node node)
	{
		int balance_factor = BalanceFactor(node);

		if(balance_factor < -1)
		{
			if(nullptr == node->right()->right())
				RightRotate(node->right());

			return(LeftRotate(node));
		}
		else if(balance_factor > 1)
		{
			if(nullptr == node->left()->left())
				LeftRotate(node->left());

			return(RightRotate(node));
		}

		return(node);
	}

	/**
	 * @brief Performs AVL balancing on the subtree rooted at the given node.
	 * @details This function iteratively applies rotation(s) to balance the subtree until the root of the subtree is reached.
	 * @param node The root node of the subtree to be balanced.
	 */
	void AVL(Node node)
	{
		// Code
		Node runner = node;

		while(true)
		{
			runner = Rotate(runner);
			if(nullptr == runner->parent())
				break;

			runner = runner->parent();
		}
		m_root = runner;
	}

public:
	/**
     * @brief Constructs an empty binary search tree.
     */
    AVLTree() {}

    /**
     * @brief Destroys the binary search tree.
     */
    ~AVLTree() {}

	/**
	 * @brief Inserts a new node with the given data into the binary search tree.
	 * @details If the tree is empty, creates a new root node with the given data.
	 *          Otherwise, traverses the tree to find the appropriate position for
	 *          the new node based on the value of the data.
	 *          Performs AVL balancing after insertion.
	 * @param data The data to be inserted into the tree.
	 * @return An integer representing the success of the operation (e.g., SUCCESS or an error code).
	 */
	int Insert(T data)
	{
		// Code
		Node runner = m_root;

		if(!m_root)
		{
			m_root = CreateNode(data);
		}
		else
		{
			while(true)
			{
				if(data < runner->data())
				{
					if(runner->left())
						runner = runner->left();
					else
					{	
						Node node = CreateNode(data);
						runner->left(node);
						AVL(node);
						break;
					}
				}
				else
				{
					if(runner->right())
						runner = runner->right();
					else
					{
						Node node = CreateNode(data);
						runner->right(node);
						AVL(node);
						break;
					}
				}
			}
		}
		
		m_size++;
		return(SUCCESS);
	}
 	
 	/**
     * @brief Removes an element from the binary search tree.
     * 
     * @param data The data to be removed from the tree.
     * @return The data that was removed from the tree.
     */
	T Remove(T data) 
	{
		// Code
		try 
		{
			Node node = LocateNode(data);

			T deleteData = node->data();

			while(true)
			{
				if(node->right())
				{
					Node pred = Minimum(node->right());

					node->data(pred->data());
					node = pred;

				}
				else if(node->left())
				{
					Node succ = Maximum(node->left());

					node->data(succ->data());
					node = succ;
				}
				else
				{
					if(nullptr == node->parent())
					{
						m_root = nullptr;
					}
					if(node->parent()->left() == node)
					{
						node->parent()->left(nullptr);
					}
					else
					{
						node->parent()->right(nullptr);
					}
					break;
				}
			}

			AVL(node->parent());

			delete(node);
			m_size--;
			return(deleteData);
		}
		catch(DataNotFoundException e)
		{
			std::cout << "Exception for (" << data << "): " << e.Description() << std::endl;
			return((T)0);
		}
		catch(TreeEmptyException e)
		{
			std::cout << "Exception: " << e.Description() << std::endl;
			return((T)0);
		}
	}
};

/**
 * @brief Overloaded stream insertion operator for outputting a binary search tree.
 * 
 * @tparam T The type of data stored in the AVL Tree.
 * @param os The output stream.
 * @param tree The binary search tree to be outputted.
 * @return The output stream.
 */
template<class T>
std::ostream& operator<<(std::ostream& os, AVLTree<T>* tree)
{
	os << (*tree);
	return(os);
}
