

#pragma		once 

template<typename T>
long 	Partition(	T* base, 
					long first,
					long last)
{
	long pivot = last;
	long i = first - 1;

	for( long j = first; j < last; ++j )
	{
		if( base[j] < base[pivot] )
		{
			i++;
			T t = base[i];
			base[i] = base[j];
			base[j] = t;
		}
	}
	T t = base[i+1];
	base[i+1] = base[last];
	base[last] = t;

	return(i+1);
}

template<typename T>
void 	quicksort(	T* base,
					long first,
					long last)
{
	if( first < last )
	{
		long mid = Partition(base, first, last);
		quicksort(base, first, mid - 1);
		quicksort(base, mid + 1, last);
	}
}

//template<typename T>
#define 	QuickSort(base, size)	{ quicksort(base, 0, size-1);	}


