

#pragma     once

template<typename T>
void    SelectionSort(T* arr, size_t size)
{
    int min_idx;

    for( int i = 0; i < size; ++i )
    {
        min_idx = i;
        for( int j = i + 1; j < size; ++j )
        {
            if( arr[j] < arr[min_idx] )
                min_idx = j;
        }
        T t = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = t;
    }
}

