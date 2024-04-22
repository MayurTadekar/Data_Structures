/**
 * S.G.M.P
 * @file: queue.hpp
 * @brief: Implementation if header file of DCLL based Queue
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @Copyright ©2020-2023 MarshallingVoid
 * @date: 22 April 2024 (Monday) 12:11:40 PM
 */

// Headers
#include	"dcll.hpp"

template <class T>
class Queue : protected DCLL<T>
{
public:
	Queue() {}

	~Queue() {}

	int	Enqueue(T data)
	{
		// Code
		return(InsertFront(data));
	}	

	T 	Dequeue()
	{
		// Code
		return(RemoveBack());
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Queue<T>* queue)
{
	//	Code
	os << "Queue: ";
	os << (*(DCLL<T>*)queue);

	return(os);
}
