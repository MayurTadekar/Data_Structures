

#pragma	once

#define 	SUCCESS 	0
#define 	FAILURE 	1

template<typename T>
void 	InsertionSort(	T* basePtr,
						size_t size)
{

	for( long i = 1; i < size; ++i )
	{
		T key = basePtr[i];
		long j = i - 1;

		while( 	j >= 0	&&
				*basePtr[j] > *key)
		{
			basePtr[j+1] = basePtr[j];
			j = j - 1;
		}
		basePtr[j+1] = key;
	}
}
