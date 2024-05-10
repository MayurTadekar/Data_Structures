/**
 * S.G.M.P
 * @file TreeEmptyException.hpp
 * @brief Defines the TreeEmptyException class, which represents an exception thrown when a tree is empty.
 * 
 * @details This file declares the TreeEmptyException class, which is a custom exception class used to
 * indicate that an operation was attempted on an empty tree.
 * 
 * @author Mayur S. Tadekar (mrtadekar@gmail.com)
 * @copyright © 2020-2023 MarshallingVoid
 * @date 24 April 2024 (Wednesday) 04:20:20 PM
 */

// Headers
#include <iostream>

/**
 * @brief Represents an exception thrown when a tree is empty.
 * 
 * @details This exception is thrown when an operation is attempted on an empty tree,
 * such as trying to access or remove elements from an empty tree.
 */
class TreeEmptyException
{
public:
    /**
     * @brief Constructs a TreeEmptyException object.
     */
    TreeEmptyException() {}

    /**
     * @brief Constructs a TreeEmptyException object with the given error message.
     * 
     * @param msg The error message associated with the exception.
     */
    TreeEmptyException(std::string msg) : errorMessage(msg) {}

    /**
     * @brief Destroys the TreeEmptyException object.
     */
    ~TreeEmptyException() {}

    /**
     * @brief Gets the description of the exception.
     * 
     * @return A string containing the error message associated with the exception.
     */
    inline std::string Description() const { return errorMessage; }

private:
    std::string errorMessage; ///< The error message associated with the exception.
};
