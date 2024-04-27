/**
 * S.G.M.P
 * @file BinaryTree.hpp
 * @brief Implements a binary tree data structure.
 * 
 * @details This file defines the BinaryTree and Node classes, which together implement
 * a binary tree data structure. The BinaryTree class provides methods for creating,
 * manipulating, and traversing a binary tree, while the Node class represents individual
 * nodes within the tree.
 * 
 * @author Mayur S. Tadekar (mrtadekar@gmail.com)
 * @copyright © 2020-2023 MarshallingVoid
 * @date 22 April 2024 (Monday) 09:44:03 PM
 */

#pragma once

template <class T>
class BinaryTree;

/**
 * @brief Represents a node in a binary tree.
 * 
 * @details This class represents a node in a binary tree data structure. Each node
 * contains a piece of data of type T, along with pointers to its left child, right child,
 * and parent nodes.
 * 
 * @tparam T The type of data stored in the node.
 */
template<class T>
class Node
{
	typedef	Node<T>*	Node;
	
	T 	m_data;
	Node<T>*	m_left;
	Node<T>*	m_right;
	Node<T>*	m_parent;

	/**
	 * @brief Constructs a node with the given data.
	 * 
	 * @param data The data to be stored in the node.
	 */
	Node(T data) : m_data(data), 
	m_left(nullptr),
	m_right(nullptr),
	m_parent(nullptr) {}

	/**
	 * @brief Returns the left child of the node.
	 * 
	 * @return The left child of the node.
	 */
	inline Node left() const { return(this->m_left); } 

	/**
	 * @brief Returns the right child of the node.
	 * 
	 * @return The right child of the node.
	 */
	inline Node right() const { return(this->m_right); }

	/**
	 * @brief Returns the parent of the node.
	 * 
	 * @return The parent of the node.
	 */
	inline Node parent() const { return(this->m_parent); }

	/**
	 * @brief Checks if the node is a root node.
	 * 
	 * @return True if the node is a root node, false otherwise.
	 */
	inline bool	isRoot() const { return(NULL == this->m_parent); }

	/**
	 * @brief Checks if the node is an external node (i.e., a leaf node).
	 * 
	 * @return True if the node is an external node, false otherwise.
	 */
	inline bool isExternal() const { return( NULL == this->m_left && NULL == this->m_right); }

	template<class T>
	friend class BinaryTree;	
}

/**
 * @brief Represents a binary tree data structure.
 * 
 * @details This class implements a binary tree, allowing the storage and manipulation of elements
 * of type T. It provides methods for creating, manipulating, and traversing a binary tree.
 * 
 * @tparam T The type of data stored in the binary tree.
 */
template<class T>
class BinaryTree
{
private:
	typedef Node<T>* Node;

	Node	m_head;
	size_t	m_size;

public:
	/**
	 * @brief Constructs an empty binary tree.
	 */
	BinaryTree() : m_head(new Node((T)0)) {}
	
	/**
	 * @brief Destroys the binary tree.
	 */
	~BinaryTree() {}
}; 
