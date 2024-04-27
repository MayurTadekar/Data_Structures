/**
 * S.G.M.P
 * @file: DataNotFoundException.hpp
 * @brief: This file declares the DataNotFoundException class, which is a custom exception class derived from std::exception.
 * It is thrown when data is not found in a container or data structure.
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 24 April 2024 (Wednesday) 03:42:15 PM
 */

#pragma once

// Headers
#include <iostream>
#include <exception>

/**
 * @brief Class: DataNotFoundException
 * @details Represents an exception thrown when data is not found.
 * 
 * @details This class inherits from std::exception and is used to indicate that
 * data was not found in a container or data structure.
 */
class DataNotFoundException : public std::exception
{
public:
	/**
     * @brief Function: DataNotFoundException
     * @details Constructs a DataNotFoundException object with the given error message.
     * 
     * @param msg The error message associated with the exception.
     */
	DataNotFoundException(std::string msg) : errorMessage(msg) {}
	
	/**
     * @brief Function: ~DataNotFoundException
     * @details Destroys the DataNotFoundException object.
     */
	~DataNotFoundException() {}

	/**
     * @brief Function: Description
     * @details Gets the description of the exception.
     * 
     * @return A string containing the error message associated with the exception.
     */
	inline std::string Description() const { return(errorMessage); }

private:
	std::string errorMessage;
};
