/**
 * S.G.M.P
 * @file: rbt.hpp
 * @brief: Defines the RedBlackTree class, which represents a self balanced binary search tree.
 * 
 * @details This file declares the RedBlackTree class, which is derived from the BinaryTree class.
 *          The RedBlackTree class implements methods for inserting and removing elements from
 *          the binary search tree while maintaining the properties of a binary search tree.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 09 May 2024 (Thursday) 09:02:03 AM
 */

#pragma once

// Headers
#include "binarytree.hpp"

template <class T>
class RedBlackTree : public BinaryTree<T>
{
private:

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
	 * @brief Performs fixup operations after deletion to maintain the red-black tree properties.
	 * @details This function adjusts the red-black tree structure after a node deletion 
	 * 			to ensure that the red-black tree properties are preserved. 
	 * 			It iteratively fixes violations by performing rotations and color adjustments 
	 * 			starting from the specified node and moving up the tree.
	 * @param node Pointer to the node from which fixup operations start.
	 */
	void InsertFixup(Node node)
	{
		// Code
		while(	node->parent() && 
				COLOR::RED == node->parent()->color() &&
				node->parent()->parent())
		{
			// Code
			Node uncle;
			if(node->parent() == node->parent()->parent()->left())
			{
				uncle = node->parent()->parent()->right();

				if(uncle && COLOR::RED == uncle->color())
				{
					node->parent()->color(COLOR::BLACK);
					uncle->color(COLOR::BLACK);
					node->parent()->parent()->color(COLOR::RED);
					node = node->parent()->parent();
				}
				else
				{
					if(node == node->parent()->right())
					{
						node = node->parent();
						LeftRotate(node);
					}
					node->parent()->color(COLOR::BLACK);
					node->parent()->parent()->color(COLOR::RED);
					node = RightRotate(node->parent()->parent());
				}
			}
			else
			{
				uncle = node->parent()->parent()->left();

				if(uncle && COLOR::RED == uncle->color())
				{
					uncle->color(COLOR::BLACK);
					node->parent()->color(COLOR::BLACK);
					node->parent()->parent()->color(COLOR::RED);
					node = node->parent()->parent();
				}
				else
				{
					if(node == node->parent()->left())
					{
						node = node->parent();
						RightRotate(node);
					}
					node->parent()->color(COLOR::BLACK);
					node->parent()->parent()->color(COLOR::RED);
					node = LeftRotate(node->parent()->parent());
				}
			}
		}

		if(!node->parent())
			m_root = node;
		m_root->color(COLOR::BLACK);
	}

	/**
	 * @brief Performs fixup operations after deletion to maintain the red-black tree properties.
	 * @details This function adjusts the red-black tree structure after a node deletion 
	 * 			to ensure that the red-black tree properties are preserved. 
	 * 			It iteratively fixes violations by performing rotations and color adjustments 
	 * 			starting from the specified node and moving up the tree.
	 * 
	 * If the color of the node and its parent are both black, it enters a loop to fix violations until the root is reached 
	 * or a color violation is resolved. 
	 * It handles two cases depending on whether 
	 * the node is a left child or a right child of its parent.
	 * 
	 * @param node Pointer to the node from which fixup operations start.
	 */
	void DeleteFixup(Node node)
	{
		// Code
		while(node->parent() && COLOR::BLACK == node->color())
		{
			if(node == node->parent()->left())
			{
				Node sibling = node->parent()->right();

				if(sibling && COLOR::RED == sibling->color())
				{
					sibling->color(COLOR::BLACK);
					node->parent()->color(COLOR::RED);
					LeftRotate(node->parent());
					sibling = node->parent()->right();
				}
				else if( sibling && 
					(nullptr == sibling->left() || COLOR::BLACK == sibling->left()->color()) &&
					(nullptr == sibling->right() || COLOR::BLACK == sibling->right()->color()) )
				{
					sibling->color(COLOR::RED);
					node = node->parent();
				}
				else 
				{
					if(nullptr == sibling->right() || COLOR::BLACK == sibling->right()->color())
					{
						sibling->left()->color(COLOR::BLACK);
						sibling->color(COLOR::RED);
						RightRotate(sibling);
						sibling = node->parent()->right();
					}

					sibling->color(node->parent()->color());
					node->parent()->color(COLOR::BLACK);
					sibling->right()->color(COLOR::BLACK);
					LeftRotate(node->parent());
					node = m_root;
				}
			}
			else
			{
				Node sibling = node->parent()->left();

				if(sibling && COLOR::RED == sibling->color())
				{
					sibling->color(COLOR::BLACK);
					node->parent()->color(COLOR::RED);
					RightRotate(node->parent());
					sibling = node->parent()->left();
				}
				else if(sibling &&
						(nullptr == sibling->left() || COLOR::BLACK == sibling->left()->color() )	&&
						(nullptr == sibling->right() || COLOR::BLACK == sibling->right()->color() ) )
				{
					sibling->color(COLOR::RED);
					node = node->parent();
				}
				else
				{
					if(nullptr == sibling->left() || COLOR::BLACK == sibling->left()->color())
					{
						sibling->right()->color(COLOR::BLACK);
						sibling->color(COLOR::RED);
						LeftRotate(sibling);
						sibling = node->parent()->left();
					}
					sibling->color(node->parent()->color());
					node->parent()->color(COLOR::BLACK);
					sibling->left()->color(COLOR::BLACK);
					RightRotate(node->parent());
					node = m_root;
				}
			}
		}
		node->color(COLOR::BLACK);
	}

public:
	/**
     * @brief Constructs an empty binary search tree.
     */
    RedBlackTree() {}

    /**
     * @brief Destroys the binary search tree.
     */
    ~RedBlackTree() {}

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
						InsertFixup(node);
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
						InsertFixup(node);
						break;
					}
				}
			}
		}
			
		m_root->color(COLOR::BLACK);

		m_size++;
		return(SUCCESS);
	}
 	
 	/**
	 * @brief Removes a node with the specified data from the red-black tree.
	 * @details This function removes a node containing the specified data from the red-black tree. 
	 * 			It first locates the node with the given data and then performs deletion based on the position of the node in the tree. 
	 * 			After deletion, it adjusts the tree structure and updates the size of the tree.
	 * 
	 * If the node to be removed has both left and right children, 
	 * it replaces its data with either the maximum value from its right subtree (predecessor) 
	 * or the minimum value from its left subtree (successor) and 
	 * then deletes the predecessor or successor node recursively. 
	 * If the node to be removed has only one child or no children, 
	 * it simply removes the node and adjusts the tree structure accordingly.
	 * 
	 * @param data The data to be removed from the red-black tree.
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
					else
					{
						DeleteFixup(node);
						if(node->parent()->left() == node)
						{
							node->parent()->left(nullptr);
						}
						else
						{
							node->parent()->right(nullptr);
						}
					}
					break;
				}
			}

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
std::ostream& operator<<(std::ostream& os, RedBlackTree<T>* tree)
{
	os << (*tree);
	return(os);
}
