

#pragma	once

#define 	SUCCESS 	0
#define 	FAILURE 	1

template<typename T>
void 	merge(	T* ptr,
				long first, 
				long mid,
				long last)
{

	long 	leftSize = mid - first + 1;
	long 	rightSize = last - mid;

	T* 	leftArr = new T[leftSize];
	T* 	rightArr = new T[rightSize];

	for( long i = 0; i < leftSize; ++i )
		leftArr[i] = ptr[first + i];

	for( long j = 0; j < rightSize; ++j)
		rightArr[j] = ptr[mid + 1 + j];

	long i = 0;
	long j = 0;
	long k = first;

	while( k <= last )
	{
		if( i < leftSize &&
			j < rightSize )
		{	
			if( leftArr[i] < rightArr[j])
			{
				ptr[k] = leftArr[i];
				++i;
			}
			else
			{
				ptr[k] = rightArr[j];
				++j;
			}
		}
		else
		{
			if( i < leftSize )
			{
				ptr[k] = leftArr[i];
				++i;
			}

			if( j < rightSize )
			{
				ptr[k] = rightArr[j];
				++j;
			}
		}
		++k;
	} 
	delete [] leftArr;
	delete [] rightArr;
}


template<typename T>
void 	merge_sort(	T* ptr, 
					long first,
					long last)
{
	if( first >= last )
		return;

	long mid = (first + last) / 2;

	merge_sort(ptr, first, mid);
	merge_sort(ptr, mid + 1, last);
	merge(ptr, first, mid, last);
}


template<typename T>
void 	Merge_Sort(	T* ptr,
					size_t size)
{
	merge_sort(ptr, 0, size-1);
}


