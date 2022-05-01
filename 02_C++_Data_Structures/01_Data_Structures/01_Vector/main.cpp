

#include    <iostream>

#include    "vector.h"

Vector<int> vec;

int main(void)
{
    std::cout << vec.size() << std::endl;
    std::cout << vec.capacity() << std::endl;

    for(size_t i = 0; i < 10; ++i)
        vec.push_back( (i+1) * 10 );
    
    for(size_t i = 0; i < 10; ++i)
        std::cout << "-" << vec[i];
    std::cout << std::endl;

    for(size_t i = 0; i < 5; ++i)
        std::cout << "Deleting-" << vec.pop_back() << std::endl;

    for(size_t i = 0; i < vec.size(); ++i)
        std::cout << "-" << vec[i];
    std::cout << std::endl;

    for(auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << "-" << *it;
    std::cout << std::endl;
    
    
    return(0);
}

