/**
 * S.G.M.P
 * @file: Driver.cpp
 * @brief: Main driver program for testing Binary Search Tree operations.
 * 
 * @details This file serves as the main driver program for testing the operations
 *          of the Binary Search Tree implementation. It includes the necessary
 *          header file and defines the entry point function 'main' where various
 *          operations such as insertion, removal, and traversal of the Binary Search Tree
 *          are performed and tested.
 * 
 * @author: Mayur S. Tadekar (mrtadekar@gmail.com)
 * @Copyright © 2020-2023 MarshallingVoid
 * @date: 24 April 2024 (Wednesday) 09:03:12 AM
 */

// Headers
#include "bst.hpp"

// Global Data Definitions
BinarySearchTree<long long>* bst = nullptr;

/**
 * @brief Entry point for Binary Search Tree driver program.
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
    bst = new BinarySearchTree<long long>(); // Create a new instance of BinarySearchTree

    // Perform some operations on the Binary Search Tree
    bst->Remove(15); // Example removal operation

    bst->Insert(15);
    bst->Insert(6);
    bst->Insert(18);
    bst->Insert(3);
    bst->Insert(7);
    bst->Insert(17);
    bst->Insert(20);
    bst->Insert(2);
    bst->Insert(4);
    bst->Insert(13);
    bst->Insert(9);

    // Print the Binary Search Tree in different traversal orders
    bst->Preorder();
    bst->Inorder();
    bst->Postorder();

    // Perform more operations and print the Binary Search Tree again
    bst->Remove(150);
    bst->Remove(15);

    bst->Preorder();
    bst->Inorder();
    bst->Postorder();

    // Clean up and exit
    delete(bst); // Delete the BinarySearchTree instance
    return(0); // Return from the main function
}

