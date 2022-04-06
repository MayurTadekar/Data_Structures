

#pragma	once

#define 	SUCCESS 	0
#define 	FAILURE 	1

#define 	CHILD(p, c) 	( (p*2) + c + 1 )	

template<typename T>
long 	MaxHeapify(	T* ptr,
					size_t size,
					int i,
					size_t ary)
{

	long largest = i;

	for( long k = 0; k < ary; ++k )
	{
		int child = CHILD(i, k);

		if( child < size &&
			ptr[child] > ptr[largest] )
			largest = child;
	}

	if( largest != size )
	{
		T t = ptr[i];
		ptr[i] = ptr[largest];
		ptr[largest] = t;
	}

	return(largest);
}

template<typename T>
void 	Heap_Sort(	T*	ptr,
					size_t size,
					size_t ary)
{

	long oldValue;
	long newValue;

	for( int i = 0 ; i < size; ++i)
		std::cout << ptr[i] << " ";
	std::cout << std::endl;

	for( int i = (size/2) - 1; i >= 0; --i)
	{
		oldValue = i;
		while(true)
		{
			newValue =MaxHeapify(	ptr,
									size,
									oldValue,
									ary);
			if( newValue == oldValue )
				break;

			oldValue = newValue;
		}
	}

	std::cout << std::endl;
	for( int j = size - 1; j >= 0; --j )
	{

		T t = ptr[0];
		ptr[0] = ptr[j];
		ptr[j] = t;

		oldValue = 0;
	
		while(true)
		{
			newValue =MaxHeapify(	ptr,
									j,
									oldValue,
									ary);
			if( newValue == oldValue )
				break;

			oldValue = newValue;
		}
	}

}

