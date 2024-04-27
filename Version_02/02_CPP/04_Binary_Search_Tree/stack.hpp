/**
 * S.G.M.P
 * @file: stack.hpp
 * @brief: Implementation of DCLL based Stack using CPP
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 15 April 2024 (Monday) 01:15:41 AM
 */

#pragma once

// Headers
#include <iostream>

#include "dcll.hpp"

/**
 * @class Stack
 * @brief A stack data structure implemented using a Doubly Circular Linked List (DCLL).
 * @tparam T The type of data stored in the stack.
 */
template <class T>
class Stack : private DCLL<T>
{
private:
	typedef int ret_t;

public:
	/**
     * @brief Constructor for the Stack class.
     */
    Stack() {}

    /**
     * @brief Destructor for the Stack class.
     */
    ~Stack() {}

    /**
     * @brief Pushes data onto the top of the stack.
     * @param data The data to be pushed onto the stack.
     * @return Returns SUCCESS upon successful insertion, otherwise FAILURE.
     */
    ret_t Push(T data)
    {
        return InsertBack(data);
    }

    /**
     * @brief Pops data from the top of the stack.
     * @return Returns the data popped from the stack.
     */
    T Pop()
    {
        return RemoveBack();
    }

    /**
     * @brief Returns the element at the top of the stack without removing it.
     * @return The data at the top of the stack.
     */
    T Peek()
    {
        return ((*this)[Size() - 1]);
    }

    /**
     * @brief Returns the current size of the stack.
     * @return The size of the stack.
     */
    inline size_t Size()
    {
        return ((DCLL<T> *)this)->Size();
    }

    /**
     * @brief Overloaded output stream insertion operator for Stack class.
     * @param os Reference to the output stream.
     * @param stack Reference to the Stack object to be outputted.
     * @return Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, Stack<T> &stack);
};

/**
 * @brief Overloaded output stream insertion operator for Stack class.
 * @param os Reference to the output stream.
 * @param stack Reference to the Stack object to be outputted.
 * @return Reference to the output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Stack<T>& stack)
{
    os << "List: {START}->";
    for(long long le = 0; le < stack.Size(); ++le)
    {
        os << "{" << stack[le] << "}->";
    }
    os << "{END}" << std::endl << std::endl;

    return os;
}
