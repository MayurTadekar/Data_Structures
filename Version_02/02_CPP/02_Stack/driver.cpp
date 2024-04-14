/**
 * S.G.M.P
 * @file: Driver.cpp
 * @brief: Driver source code for stack using DCLL
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 15 April 2024 (Monday) 01:22:03 AM
 */

// Header
#include <iostream>

#include "stack.hpp"

// Global Data Definition
Stack<long long>* stack = nullptr;

/**
 * Function: main
 * 
 * Description: Entry point function for the program.
 * 
 * @param int argc Number of command-line arguments.
 * @param char** argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char** argv)
{
    Stack<long long>* stack = new Stack<long long>();

    for(long long le = 0; le < 5; ++le)
    {
        stack->Push((le+1) * 22);
    }

    std::cout << (*stack) << std::endl;

    stack->Pop();
    stack->Pop();

    std::cout << (*stack);

    delete stack;
    stack = nullptr;

    exit(EXIT_SUCCESS);
}

