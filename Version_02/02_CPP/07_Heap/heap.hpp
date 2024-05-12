/**
 * @file heap.hpp
 * @brief This file contains the implementation of a Heap data structure 
 * 			using a doubly linked list as the underlying container.
 *        It provides functionalities for insertion, removal, and printing of elements in the heap.
 *
 * @details The Heap class is implemented as a template class 
 * 			that inherits privately from the Doubly Circular Linked List (DCLL) class.
 *          It includes macros for calculating parent, left child, and right child indices, 
 * 			along with helper functions for heapify operations.
 *          The class provides public methods for inserting elements into the heap, 
 * 			removing elements from the heap, and printing the heap.
 * @author Mayur S. Tadekar (mrtadekar@gmail.com)
 * @copyright ©2020-2023 MarshallingVoid
 * @date 11 May 2024 (Saturday) 03:56:05 AM
 */

#pragma once

#include <iostream>
#include <stdlib.h>

#include "dcll.hpp"

#define	LARGET_POWER_OF_2(v)	{				\
									v--;		\
									v |= 1;		\
									v |= 2;		\
									v |= 4;		\
									v |= 8;		\
									v |= 16;	\
									v |= 32;	\
									v++;		\
								}

/**
 * @class Heap
 * @brief 	Implements a Heap data structure using 
 * 			a doubly linked list as the underlying container.
 * @tparam T The type of elements stored in the heap.
 * @details Inherits privately from the Doubly Circular Linked List (DCLL) class.
 */
template <class T>
class Heap : private DCLL<T>  
{
private:

	// Macro to calculate the parent index of a node in a heap
	#define PARENT(i) ((i-1) >> 1)

	// Macro to calculate the left child index of a node in a heap
	#define LEFT(i) ((i<<1) + 1)

	// Macro to calculate the right child index of a node in a heap
	#define RIGHT(i) ((i<<1) + 2)
	
	/**
	 * @brief Performs heapify operation after inserting an element into the heap.
	 * @details Compares the newly inserted element with its parent 
	 * 			and swaps if necessary to maintain the heap property.
	 * @tparam COMPARE The type of comparison function used for heapify operation.
	 * @param index The index of the newly inserted element.
	 * @param heapifyFunc The comparison function used for heapify operation.
	 */
	template <class COMPARE>
	void 	InsertHeapify(long long index, COMPARE heapifyFunc)
	{
		// Code
		long long parent = PARENT(index);

		if(heapifyFunc((*this)[index], (*this)[parent]))
		{
			Swap(index, parent);
		}
	}

	/**
	 * @brief Performs heapify operation after removing an element from the heap.
	 * @details Compares the children of the removed element 
	 * 			and swaps if necessary to maintain the heap property.
	 * @tparam COMPARE The type of comparison function used for heapify operation.
	 * @param index The index of the removed element.
	 * @param heapifyFunc The comparison function used for heapify operation.
	 */
	template <class COMPARE>
	void RemoveHeapify(long long index, COMPARE heapifyFunc)
	{
		// Code
		long long large = index;

		while(true)
		{
			long long left = LEFT(index);
			long long right = RIGHT(index);

			if(left >= Size() || right >= Size())
				break;

			if(heapifyFunc((*this)[left], (*this)[index]))
			{
				large = left;
			}

			if(heapifyFunc((*this)[right], (*this)[large]))
			{
				large = right;
			}

			if(large != index)
			{
				Swap(large, index);
				index = large;
			}
		}
	}

public:
	Heap()
	{
		// Code
	}

	/**
	 * @brief Inserts an element into the heap and performs heapify operation to maintain the heap property.
	 * @details Inserts the element at the end of the heap and performs heapify operation upwards to maintain the heap property.
	 * @tparam COMPARE The type of comparison function used for heapify operation.
	 * @param element The element to be inserted into the heap.
	 * @param heapifyFunc The comparison function used for heapify operation.
	 */
	template <class COMPARE>
	void Insert(T element, COMPARE heapifyFunc)
	{
		// Code
		InsertBack(element);

		for(long long le = Size()-1; le > 0; le = PARENT(le))
		{
			InsertHeapify(le, heapifyFunc);
		}
	}

	/**
	 * @brief Removes a specific element from the heap and performs heapify operation to maintain the heap property.
	 * @details Searches for the element in the heap, swaps it with the last element, removes it, and performs heapify operation downwards to maintain the heap property.
	 * @tparam COMPARE The type of comparison function used for heapify operation.
	 * @param element The element to be removed from the heap.
	 * @param heapifyFunc The comparison function used for heapify operation.
	 */
	template <class COMPARE>
	void Remove(T element, COMPARE heapifyFunc)
	{
		// Code
		long long index = 0;
		for(index; index < Size(); ++index)
		{
			if((*this)[index] == element)
				break;
		}

		if(index == Size())
		{
			std::cerr << "ERROR: Data not found" << std::endl;
			return;
		}

		Swap(index, Size()-1);
		RemoveBack();

		RemoveHeapify(index, heapifyFunc);
	}

	/**
	 * @brief Prints the elements of the heap.
	 * @details Prints all elements of the heap in the order they appear in the underlying container.
	 */
	void Print()
	{
		// Code
		std::cout << "START|";
		for(long long le = 0; le < Size(); ++le)
		{
			std::cout << (*this)[le] << "|";
		}
		std::cout << "END" << std::endl;
	}
};

