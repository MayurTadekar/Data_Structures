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

/**
 * Template Class: Queue
 * 
 * Description: Represents a queue data structure implemented using a doubly linked list.
 * 
 * Identifier: Queue
 * 
 * Template Parameter: T - Type of data stored in the queue.
 * 
 * Public Methods:
 *   - Queue(): Default constructor to initialize the queue.
 *   - ~Queue(): Destructor to clean up resources.
 *   - int Enqueue(T data): Adds an element to the back of the queue.
 *   - T Dequeue(): Removes and returns the element from the front of the queue.
 * 
 * Notes: This class extends the DCLL (Doubly Circular Linked List) class and provides queue-specific operations.
 *        It uses the InsertFront and RemoveBack methods from the base class to implement Enqueue and Dequeue operations, respectively.
 */
template <class T>
class Queue : protected DCLL<T>
{
private:
	#define	DTHIS (*(DCLL<T>*)this)

public:
	/**
	 * Constructor: Queue
	 * 
	 * Description: Default constructor to initialize an empty queue.
	 * 
	 * Identifier: Queue
	 * 
	 * Params: None
	 * 
	 * Returns: None
	 * 
	 * Notes: This constructor initializes an empty queue.
	 */
	Queue() {}

	/**
	 * Destructor: ~Queue
	 * 
	 * Description: Destructor to clean up resources allocated for the queue.
	 * 
	 * Identifier: ~Queue
	 * 
	 * Params: None
	 * 
	 * Returns: None
	 * 
	 * Notes: This destructor cleans up resources allocated for the queue, such as freeing memory.
	 */
	~Queue() {}

	/**
	 * Method: Enqueue
	 * 
	 * Description: Adds an element to the front of the queue.
	 * 
	 * Identifier: Enqueue
	 * 
	 * Template Parameter: T - Type of data stored in the queue.
	 * 
	 * Params:
	 *   - data: Data to be enqueued.
	 * 
	 * Returns: Integer representing the status of the enqueue operation.
	 * 
	 * Notes: This method adds the specified data to the front of the queue by calling the InsertFront method.
	 */
	int	Enqueue(T data)
	{
		// Code
		return(InsertFront(data));
	}	

	/**
	 * Method: Dequeue
	 * 
	 * Description: Removes and returns the element from the back of the queue.
	 * 
	 * Identifier: Dequeue
	 * 
	 * Template Parameter: T - Type of data stored in the queue.
	 * 
	 * Params: None
	 * 
	 * Returns: The data removed from the back of the queue.
	 * 
	 * Notes: This method removes and returns the data from the back of the queue by calling the RemoveBack method.
	 */
	T 	Dequeue()
	{
		// Code
		return(RemoveBack());
	}


	T operator[](long long index)
	{
		// Code
		return(DTHIS[index]);
	}

	bool IsEmpty()
	{
		//Code
		return(DTHIS.IsEmpty());
	}	

	size_t Size()
	{
		// Code
		return(DTHIS.Size());
	}
};

/**
 * Function: operator<<
 * 
 * Description: Overloaded stream insertion operator to print the contents of a queue.
 * 
 * Identifier: operator<<
 * 
 * Template Parameter: T - Type of data stored in the queue.
 * 
 * Params:
 *   - os: Reference to the output stream.
 *   - queue: Pointer to the queue to be printed.
 * 
 * Returns: Reference to the output stream.
 * 
 * Notes: This function prints the contents of the queue by calling the overloaded operator<< of the base class DCLL.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Queue<T>* queue)
{
	//	Code
	os << "Queue: ";
	os << (*(DCLL<T>*)queue);

	return(os);
}
