/**
 * S.G.M.P
 * @file: Driver.cpp
 * @brief: Implementation of Driver code for CPP Implementation
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 12 April 2024 (Friday) 06:21:31 PM
 */

// Headers
#include <iostream>

#include "dcll.hpp"

// Global Data Definitions
DCLL<long long>* list = nullptr;

int main(int argc, char** argv)
{
	//	Code
	list = new DCLL<long long>();

	for(long long le = 0; le < 10; ++le)
		list->InsertFront((le+1) * 11);
	std::cout << (*list);

	for(long long le = 0; le < 10; ++le)
		list->InsertBack((le+1) * 22);
	std::cout << (*list);
	
	list->InsertAfter(7171, 77);
	list->InsertAfter(818181, 88);
	std::cout << (*list);
	
	list->InsertBefore(7171, 77);
	list->InsertBefore(818181, 88);
	std::cout << (*list);

	list->InsertAt(7171, 0);
	list->InsertAt(818181, 10);
	std::cout << (*list);

	std::cout << "Removed : " << list->RemoveFront() << std::endl;
	std::cout << "Removed : " << list->RemoveFront() << std::endl;
	std::cout << "Removed : " << list->RemoveFront() << std::endl;
	std::cout << "Removed : " << list->RemoveFront() << std::endl;
	std::cout << (*list);

	std::cout << "Removed : " << list->RemoveBack() << std::endl;
	std::cout << "Removed : " << list->RemoveBack() << std::endl;
	std::cout << "Removed : " << list->RemoveBack() << std::endl;
	std::cout << "Removed : " << list->RemoveBack() << std::endl;
	std::cout << (*list);

	std::cout << "Removed : " << list->RemoveAfter(77) << std::endl;
	std::cout << "Removed : " << list->RemoveAfter(88) << std::endl;
	std::cout << (*list);

	std::cout << "Removed : " << list->RemoveBefore(77) << std::endl;
	std::cout << "Removed : " << list->RemoveBefore(77) << std::endl;
	std::cout << "Removed : " << list->RemoveBefore(88) << std::endl;
	std::cout << (*list);

	std::cout << "Removed : " << list->RemoveAt(0) << std::endl;
	std::cout << "Removed : " << list->RemoveAt(5) << std::endl;
	std::cout << "Removed : " << list->RemoveAt(99) << std::endl;
	std::cout << (*list);

	exit(SUCCESS);
}
