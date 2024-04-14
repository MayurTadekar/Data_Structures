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

template <class T>
class Stack : private DCLL<T>
{
private:
	typedef int ret_t;

public:
	/**
	 * Function: Stack
	 * 
	 * Description: Constructor for the Stack class.
	 * 
	 * @param None
	 * @return None
	 */
	Stack() {}

	/**
	 * Function: ~Stack
	 * 
	 * Description: Destructor for the Stack class.
	 * 
	 * @param None
	 * @return None
	 */
	~Stack() {}

	/**
	 * Function: Push
	 * 
	 * Description: Pushes data onto the top of the stack.
	 * 
	 * @param T data Data to be pushed onto the stack.
	 * @return ret_t Returns SUCCESS upon successful insertion. Returns FAILURE otherwise.
	 */
	ret_t Push(T data)
	{
	    return InsertBack(data);
	}

	/**
	 * Function: Pop
	 * 
	 * Description: Pops data from the top of the stack.
	 * 
	 * @param None
	 * @return T Returns the data popped from the stack.
	 */
	T Pop()
	{
	    return RemoveBack();
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, Stack<T>& stack);
};

/**
 * Function: operator<<
 * 
 * Description: Overloaded output stream insertion operator for Stack class.
 * 
 * @param std::ostream& os Reference to the output stream.
 * @param Stack<T>& stack Reference to the Stack object to be outputted.
 * @return std::ostream& Reference to the output stream.
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
