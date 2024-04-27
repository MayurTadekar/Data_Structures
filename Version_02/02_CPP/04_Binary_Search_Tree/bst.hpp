/**
 * S.G.M.P
 * @file: bst.hpp
 * @brief: Defines the BinarySearchTree class, which represents a binary search tree.
 * 
 * @details This file declares the BinarySearchTree class, which is derived from the BinaryTree class.
 *          The BinarySearchTree class implements methods for inserting and removing elements from
 *          the binary search tree while maintaining the properties of a binary search tree.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 09:42:40 PM
 */

#pragma once

// Headers
#include "binarytree.hpp"

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
	/**
     * @brief Constructs an empty binary search tree.
     */
    BinarySearchTree() {}

    /**
     * @brief Destroys the binary search tree.
     */
    ~BinarySearchTree() {}

	/**
     * @brief Inserts a new element into the binary search tree.
     * 
     * @param data The data to be inserted into the tree.
     * @return An integer indicating the status of the insertion operation.
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
						runner->left(CreateNode(data));
						break;
					}
				}
				else
				{
					if(runner->right())
						runner = runner->right();
					else
					{
						runner->right(CreateNode(data));
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
 * @tparam T The type of data stored in the binary search tree.
 * @param os The output stream.
 * @param tree The binary search tree to be outputted.
 * @return The output stream.
 */
template<class T>
std::ostream& operator<<(std::ostream& os, BinarySearchTree<T>* tree)
{
	os << (*tree);
	return(os);
}
