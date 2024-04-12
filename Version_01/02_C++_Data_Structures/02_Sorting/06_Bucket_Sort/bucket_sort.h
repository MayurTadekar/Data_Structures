

#include    <vector>

#include    "merge_sort.h"

template<typename T>
void BucketSort(T* arr, size_t size)
{
    std::vector<T> *b = new std::vector<T>[size]();

    for( int i = 0; i < size; ++i )
    {
        int bi = size * *arr[i];
        b[bi].push_back(arr[i]);
    }

    for( int i = 0; i < size; ++i )
        merge_sort(b[i].data(), 0, b[i].size() - 1);

    int index = 0;
    for( int i = 0; i < size; ++i )
    {
        for(int j = 0; j < b[i].size(); ++j)
        {
            arr[index] = b[i][j];
        }
    }
}

