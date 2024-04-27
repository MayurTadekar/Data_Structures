/**
 * S.G.M.P
 * @file: BinaryTree.hpp
 * @brief: C++ implementation of a binary tree data structure.
 * 
 * @details This file contains the C++ implementation of a binary tree,
 *          including classes and methods for creating, manipulating,
 *          and traversing binary tree structures. It provides functionalities
 *          such as locating nodes, finding minimum and maximum elements,
 *          and iterating through the tree in preorder, inorder, and postorder.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @date: 22 April 2024 (Monday) 09:44:03 PM
 * @copyright © 2020-2023 MarshallingVoid
 */


#pragma once

#include <string>
#include <sstream>

#include "stack.hpp"
#include "DataNotFoundException.hpp"
#include "TreeEmptyException.hpp"

template <class T>
class BinaryTree;

/**
 * @brief Node class for a binary tree.
 * 
 * @details This class represents a node in a binary tree data structure.
 *          It stores data and pointers to its left child, right child, and parent nodes.
 *          The class provides methods to access and modify these pointers, as well as
 *          utilities to determine if the node is a root or an external node.
 * 
 * @tparam T The type of data stored in the node.
 */
template<class T>
class TNode
{
private:
	typedef	TNode<T>*	Node;

	T 	m_data;
	Node	m_left;
	Node	m_right;
	Node	m_parent;

	/**
	 * @brief Identifier: TNode (constructor)
	 * @details Constructs a node with the given data and initializes its pointers.
	 * 
	 * @param data The data to be stored in the node.
	 */
	TNode(T data) : m_data(data), 
	m_left(nullptr),
	m_right(nullptr),
	m_parent(nullptr) {}

public:
	
	/**
	 * @brief Identifier: data (getter)
	 * @details Accessor function for the data stored in the node.
	 * 
	 * @return The data stored in the node.
	 */
	inline T 	data() const { return(this->m_data); }

	/**
	 * @brief Identifier: data (setter)
	 * @details Mutator function to set the data stored in the node.
	 * 
	 * @param data The data to be set in the node.
	 */
	inline void data(T data) { m_data = data; }

	
	/**
	 * @brief Identifier: left (getter)
	 * @details Accessor function for retrieving the left child of the node.
	 * 
	 * @return A pointer to the left child node.
	 */
	inline Node left() const { return(this->m_left); } 

	/**
	 * @brief Identifier: left (setter)
	 * @details Mutator function to set the left child of the node.
	 * 
	 * @param node A pointer to the node to be set as the left child.
	 */
	void left(Node node) 
	{
		m_left = node;
		if(node)
			node->m_parent = this;
	}
	
	/**
	 * @brief Identifier: right (getter)
	 * @details Accessor function for retrieving the right child of the node.
	 * 
	 * @return A pointer to the right child node.
	 */
	inline Node right() const { return(this->m_right); }

	/**
	 * @brief Identifier: right (setter)
	 * @details Mutator function to set the right child of the node.
	 * 
	 * @param node A pointer to the node to be set as the right child.
	 */
	void right(Node node)
	{
		m_right = node;
		if(node)
			node->m_parent = this;
	}

	/**
	 * @brief Identifier: parent (getter)
	 * @details Accessor function for retrieving the parent of the node.
	 * 
	 * @return A pointer to the parent node.
	 */
	inline Node parent() const { return(this->m_parent); }

	/**
	 * @brief Identifier: parent (setter)
	 * @details Mutator function to set the parent of the node.
	 * 
	 * @param node A pointer to the node to be set as the parent.
	 */
	inline void parent(Node node) { m_parent = node; }

	/**
	 * @brief Identifier: isRoot
	 * @details Checks if the node is a root node.
	 * 
	 * @return True if the node is a root node, false otherwise.
	 */
	inline bool	isRoot() const { return(NULL == this->m_parent); }
	
	/**
	 * @brief Identifier: isExternal
	 * @details Checks if the node is an external node (i.e., a leaf node).
	 * 
	 * @return True if the node is an external node, false otherwise.
	 */
	inline bool isExternal() const { return( NULL == this->m_left && NULL == this->m_right); }

	template<class T>
	friend class BinaryTree;	
};

/**
 * @class BinaryTree
 * @brief Template class representing a binary tree data structure.
 * 
 * @details This class represents a binary tree data structure, which consists of nodes connected
 *          in a hierarchical manner. Each node has at most two children, referred to as the left
 *          child and right child. The class provides various methods to manipulate the binary tree,
 *          such as inserting and removing nodes, locating nodes with specific data, finding minimum
 *          and maximum nodes, and traversing the tree in different orders (preorder, inorder, and postorder).
 * 
 * @tparam T The type of data stored in the binary tree nodes.
 */
template<class T>
class BinaryTree
{
protected:
	typedef TNode<T>* Node;

	Node	m_root;
	size_t	m_size;

	/**
	 * @identifier CreateNode
	 * @brief Creates a new node with the specified data.
	 * 
	 * @param data The data to be stored in the new node.
	 * @return Pointer to the newly created node.
	 */
	inline Node CreateNode(T data) { return(new TNode<T>(data)); }

public:
	/**
	 * @identifier BinaryTreeConstructor
	 * @brief Default constructor for the BinaryTree class.
	 * 
	 * @details Initializes the root pointer to nullptr and sets the size of the tree to zero.
	 */
	BinaryTree() : m_root(nullptr) 
	{
	    m_size = 0;
	}

	/**
	 * @identifier BinaryTreeDestructor
	 * @brief Destructor for the BinaryTree class.
	 * 
	 * @details Cleans up resources associated with the BinaryTree object.
	 */
	~BinaryTree() {}

	/**
	 * @identifier LocateNode
	 * @brief Locates a node with the specified data in the binary tree.
	 * @param e_data The data to be located.
	 * @return Pointer to the node containing the specified data.
	 * @throws TreeEmptyException If the tree is empty.
	 * @throws DataNotFoundException If the desired data is not found.
	 */
	Node LocateNode(T e_data)
	{
		// Code
		if(!m_root)
		{
			std::stringstream ss;
			ss << __LINE__;

			std::string s("Root not found i.e Tree is Empty");
			
			std::string s1;
			ss >> s1;
			throw TreeEmptyException( (s + " in " + __FILE__ + " (" + s1 + ")\n") );
		}

		Node runner = m_root;

		while(true)
		{
			if(runner->data() == e_data)
				return(runner);
			else if(runner->data() > e_data)
				runner = runner->right();
			else 
				runner = runner->left();
		
			if(runner->isExternal())
				break;
		}
		std::stringstream ss;
		ss << __LINE__;

		std::string s("Desired data not found.");
		
		std::string s1;
		ss >> s1;
		throw DataNotFoundException( (s + " in " + __FILE__ + " (" + s1 + ")\n") );
	}

	/**
	* @identifier Minimum
	* @brief Finds the minimum node in the subtree rooted at the specified node.
	* @param node The root of the subtree.
	* @return Pointer to the minimum node.
	*/
	Node Minimum(Node node) 
	{
		// Code
		Node runner = node;

		while(runner->left())
		{
			runner = runner->left();
		}

		return(runner);
	}

	/**
	 * @identifier Maximum
	 * @brief Finds the maximum node in the subtree rooted at the specified node.
	 * @param node The root of the subtree.
	 * @return Pointer to the maximum node.
	 */
	Node Maximum(Node node)
	{
		// Code
		Node runner = node;

		while(runner->right())
		{
			runner = runner->right();
		}

		return(runner);
	}

	/**
	 * @identifier Successor
	 * @brief Finds the successor of the specified node in the binary tree.
	 * @param node The node for which the successor is to be found.
	 * @return Pointer to the successor node.
	 */
	Node Successor(Node node)
	{
		// Code
		Node succ = nullptr;
		if(node->right())
			return(Minimum(node->right()));
		succ = node->parent();
		while(succ != nullptr && succ->right() == node)
		{
			node = succ;
			succ = node->parent();
		}

		return(succ);
	}

	/**
	 * @identifier Predecessor
     * @brief Finds the predecessor of the specified node in the binary tree.
     * @param node The node for which the predecessor is to be found.
     * @return Pointer to the predecessor node.
     */
	Node Predecessor(Node node)
	{
		// Code
		Node pred = nullptr;
		if(node->left())
			return(Maximum(node->left()));
		pred = node->parent();
		while(pred != nullptr && pred->left() == node)
		{
			node = pred;
			pred = node->parent();
		}
		return(pred);
	}

	/**
	 * @identifier Insert
	 * @brief Inserts a new node with the given data into the binary tree.
	 * 
	 * @details This function inserts a new node containing the specified data into the binary tree.
	 *          The data is inserted according to the rules of the binary tree structure.
	 * 
	 * @param data The data to be inserted into the tree.
	 * @return An integer representing the success or failure of the insertion operation.
	 */
	int Insert(T data) {}

	/**
	 * @identifier Remove
	 * @brief Removes a node with the specified data from the binary tree.
	 * 
	 * @details This function removes a node containing the specified data from the binary tree,
	 *          maintaining the binary tree properties after removal.
	 * 
	 * @param data The data of the node to be removed from the tree.
	 * @return The data of the removed node, or a default value if the node was not found.
	 */
	T Remove(T data) {}

	/************** Inorder Iterator **************/

	/**
	 * @identifier Iterator
	 * @brief Iterator class for traversing a binary tree.
	 * 
	 * @details This class provides an iterator interface for traversing a binary tree
	 *          in preorder, inorder, or postorder fashion. It maintains a stack to keep track
	 *          of the nodes during traversal and supports increment operations to move to the
	 *          next node in the specified traversal order.
	 */
	class Iterator
	{
	private:
		/**
		 * @brief Enumerates the types of iterators supported: Preorder, Inorder, and Postorder.
		 */
		enum class ITERATOR_TYPE
		{
		    ITR_PREORDER = 1, ///< Preorder traversal type.
		    ITR_INORDER,      ///< Inorder traversal type.
		    ITR_POSTORDER     ///< Postorder traversal type.
		};
		
		Node itr;
		Stack<Node>* stack;
		ITERATOR_TYPE type;
		
	public:
		/**
		 * @brief Constructs an iterator with the specified node as the starting point.
		 * 
		 * @param node The starting node of the iterator.
		 */
		Iterator(Node node) : itr(node) 
		{
			// Code
			type = ITERATOR_TYPE::ITR_INORDER;
			stack = nullptr;
			
			if(nullptr == node)
			{
				itr = nullptr;
				return;
			}

			stack = new Stack<Node>();
			while(true)
			{
				if(itr->left())
				{
					stack->Push(itr);
					itr = itr->left();
				}
				else
					break;
			}
		}

		/**
		 * @brief Constructs a preorder iterator with the specified node as the starting point.
		 * 
		 * @param node The starting node of the iterator.
		 * @param value Unused parameter for distinguishing constructor overloads.
		 */
		Iterator(Node node, int value) : itr(node)
		{
			// Code
			stack = new Stack<Node>();
			stack->Push(itr);
			type = ITERATOR_TYPE::ITR_PREORDER;
		}

		/**
		 * @brief Constructs a postorder iterator with the specified node as the starting point.
		 * 
		 * @param node The starting node of the iterator.
		 * @param v1 Unused parameter for distinguishing constructor overloads.
		 * @param v2 Unused parameter for distinguishing constructor overloads.
		 */
		Iterator(Node node, int v1, int v2) : itr(node)
		{
			// Code
			type = ITERATOR_TYPE::ITR_POSTORDER;
			stack = new Stack<Node>();
			stack->Push(itr);
			while(true)
			{
				while(itr->left())
				{
					itr = itr->left();
					stack->Push(itr);
				}

				if(itr->right())
				{
					itr = itr->right();
					stack->Push(itr);
				}

				if(!itr->left() && !itr->right())
				break;
			}
		}
		
		/**
		 * @brief Destructor for the iterator.
		 * 
		 * @details Frees any resources held by the iterator.
		 */
		~Iterator() 
		{ 
			itr = nullptr;
		}

		/**
		 * @brief Dereference operator to access the data of the current node.
		 * 
		 * @return Reference to the data stored in the current node.
		 */
		inline T operator*() const { return(itr->data()); }

		/**
		 * @brief Equality comparison operator.
		 * 
		 * @param it The iterator to compare with.
		 * @return True if the iterators point to the same node, false otherwise.
		 */
		bool operator==(Iterator& it)
		{
			// Code
			return(itr == it.itr);
		}

		/**
		 * @brief Inequality comparison operator.
		 * 
		 * @param it The iterator to compare with.
		 * @return True if the iterators point to different nodes, false otherwise.
		 */
		bool operator!=(Iterator& it)
		{
			// Code
			return(!(*this == it));
		}

		/**
		 * @brief Prefix increment operator.
		 * 
		 * @return Reference to the incremented iterator.
		 */
		Iterator& operator++()
		{
			// Code
			switch(type)
			{
			case ITERATOR_TYPE::ITR_INORDER:
				if(itr->right())
				{
					itr = itr->right();
					while(itr->left())
					{
						stack->Push(itr);
						itr = itr->left();
					}
				}
				else if(stack->Size())
					itr = stack->Pop();
				else
					itr = nullptr;

				return(*this);

			case ITERATOR_TYPE::ITR_PREORDER:
				if( itr->left() )
				{
					itr = itr->left();
					stack->Push(itr);
				}
				else
				{
					if( stack->Peek() == itr )
					{
						stack->Pop();
					}

					while(!itr->right())
					{
						itr = stack->Pop();
						if(nullptr == itr)
							return(*this);
					}
					itr = itr->right();
					stack->Push(itr);
				}
				return(*this);

			case ITERATOR_TYPE::ITR_POSTORDER:

				if(nullptr == stack->Peek())
				{
					itr = nullptr;
					return(*this);
				}
				
				if(itr == stack->Peek())
				{
					stack->Pop();
				}

				if(stack->Peek()->right() == itr)
				{
					itr = stack->Pop();
					return(*this);
				}
				else
				{
					itr = stack->Peek();
				}

				if(itr->right())
				{
					itr = itr->right();
					stack->Push(itr);

					while(true)
					{
						while(itr->left())
						{
							itr = itr->left();
							stack->Push(itr);
						}

						if(itr->right())
						{
							itr = itr->right();
							stack->Push(itr);
						}

						if(!itr->left() && !itr->right())
							break;
					}
				}
				return(*this);

			default:
				return(*this);
			}
		}

		/**
		 * @brief Postfix increment operator.
		 * 
		 * @param value Dummy parameter for postfix increment.
		 * @return A copy of the iterator before the increment.
		 */
		Iterator operator++(int value)
		{
			// Code
			Iterator temp;
			temp.itr = itr;
				std::cout << "1" << std::endl;

			++(*this);

			return(temp);
		}
	};

	/**
	 * @brief Returns an iterator pointing to the beginning of an inorder traversal of the binary tree.
	 * 
	 * @return Iterator pointing to the beginning of an inorder traversal.
	 */
	Iterator beginIn()
	{
		return(Iterator(m_root));
	}

	/**
	 * @brief Returns an iterator pointing to the beginning of a preorder traversal of the binary tree.
	 * 
	 * @return Iterator pointing to the beginning of a preorder traversal.
	 */
	Iterator beginPre()
	{
		return(Iterator(m_root, 1));
	}

	/**
	 * @brief Returns an iterator pointing to the beginning of a postorder traversal of the binary tree.
	 * 
	 * @return Iterator pointing to the beginning of a postorder traversal.
	 */
	Iterator beginPost()
	{
		return(Iterator(m_root, 1, 1));
	}

	/**
	 * @brief Returns an iterator pointing to the end of the binary tree traversal.
	 * 
	 * @return Iterator pointing to the end of the binary tree traversal.
	 */
	Iterator end()
	{
		return(Iterator(nullptr));
	}

	/**
	 * @brief Prints the binary tree in inorder traversal.
	 * 
	 * @details This function prints the binary tree in inorder traversal format.
	 *          It iterates through the tree using inorder traversal and prints each node's data.
	 */
	void Inorder()
	{
		// Code
		std::cout << "Tree: {START}|";
		for(auto itr = beginIn(); itr != end(); ++itr)
		{
			std::cout << *itr << "|";
		}
		std::cout << "{END}" << std::endl << std::endl;
	}

	/**
	 * @brief Prints the binary tree in preorder traversal.
	 * 
	 * @details This function prints the binary tree in preorder traversal format.
	 *          It iterates through the tree using preorder traversal and prints each node's data.
	 */
	void Preorder()
	{
		// Code
		std::cout << "Tree: {START}|";
		for(auto itr = beginPre(); itr != end(); ++itr)
		{
			std::cout << *itr << "|";
		}
		std::cout << "{END}" << std::endl << std::endl;
	}

	/**
	 * @brief Prints the binary tree in postorder traversal.
	 * 
	 * @details This function prints the binary tree in postorder traversal format.
	 *          It iterates through the tree using postorder traversal and prints each node's data.
	 */
	void Postorder()
	{
		// Code
		std::cout << "Tree: {START}|";
		for(auto itr = beginPost(); itr != end(); ++itr)
		{
			std::cout << *itr << "|";
		}
		std::cout << "{END}" << std::endl << std::endl;
	}
};

/**
 * @brief Overloaded stream insertion operator for printing the binary tree.
 * 
 * @details This operator allows printing the binary tree by iterating through its nodes
 *          using inorder traversal and printing each node's data to the output stream.
 * 
 * @tparam T The type of data stored in the binary tree.
 * @param os The output stream where the binary tree will be printed.
 * @param tree The binary tree to be printed.
 * @return Reference to the output stream.
 */
template<class T>
std::ostream& operator<<(std::ostream& os, BinaryTree<T>& tree)
{
	// Code
	os << "Tree: {START}|";
	for(auto itr = tree.beginIn(); itr != tree.end(); ++itr)
	{
		os << *itr << "|";
	}
	os << "{END}" << std::endl << std::endl;
	return(os);
}
