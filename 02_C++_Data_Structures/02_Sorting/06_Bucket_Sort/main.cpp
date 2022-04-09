

#include    <iostream>

#include    "bucket_sort.h"

class Int
{
private:
    int data;

public:

    Int() : data(0) {}
    Int(int data) : data(data) {}

    int operator*()
    {
        return(data);
    }

    bool operator<(Int& i)
    {
        return(data < i.data);
    }

    friend std::ostream& operator<<(std::ostream& out, Int& i)
    {
        out << i.data;
        return(out);
    }
};

int main(void)
{

    Int arr[] = { Int(10) };

    BucketSort(arr, 10);

    for( int i = 0; i < 10; ++i )
        std::cout << arr[i] << " ";

    return(0);
}

