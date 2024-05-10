/**
 * S.G.M.P
 * @file: Driver.cpp
 * @brief: Main driver program for testing RedBlack Tree operations.
 * 
 * @details This file serves as the main driver program for testing the operations
 *          of the RedBlack Tree implementation. It includes the necessary
 *          header file and defines the entry point function 'main' where various
 *          operations such as insertion, removal, and traversal of the RedBlack Tree
 *          are performed and tested.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright © 2020-2023 MarshallingVoid
 * @date: 07 May 2024 (Tuesday) 04:04:42 PM
 */

// Headers
#include "rbt.hpp"

// Global Data Definitions
RedBlackTree<long long>* tree = nullptr;

/**
 * @brief Entry point for RedBlack Tree driver program.
 * 
 * @details Creates and tests a BinarySearchTree instance,
 *          performing insertion, removal, and traversal operations.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * 
 * @return Exit status of the program. Zero indicates success.
 */
int main(int argc, char** argv)
{
    // Code
    tree = new RedBlackTree<long long>(); // Create a new instance of BinarySearchTree

    // Perform some operations on the RedBlack Tree
    tree->Insert(1);
    tree->Insert(2);
    tree->Insert(3);
    tree->Insert(4);
    tree->Insert(5);
    tree->Insert(6);
    tree->Insert(7);
    tree->Insert(8);
    tree->Insert(9);
    tree->Insert(10);
    tree->Insert(11);
    tree->Insert(12);
    tree->Insert(13);

    // Print the RedBlack Tree in different traversal orders
    tree->Preorder();
    tree->Inorder();
    tree->Postorder();

    // Perform more operations and print the RedBlack Tree again
    // tree->Remove(150);
    tree->Remove(10);

    tree->Preorder();
    tree->Inorder();
    tree->Postorder();

    // Clean up and exit
    delete(tree); // Delete the RedBlackTree instance
    return(0); // Return from the main function
}

