#include <iostream>
#include "UniquePointer.hpp"

int main() {
    unique_ptr<int> ptr;
    unique_ptr<int> ptr2 = std::move(ptr);
    ptr = std::move(ptr2);
    std::cout << ptr.get();
    std::cout << ptr2.release();
    ptr.reset();
}