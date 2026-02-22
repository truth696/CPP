#include <iostream>
#include <vector>

template <typename T>
T* sort(T* arr, size_t size) {
    for (int i{}; i < size; ++i)
    {
        for (int j = size - 1; j > i; --j) if (arr[i] > arr[j]) std::swap (arr[i], arr[j]);
    }

    return arr;
}

int main() {
    std::vector<int> vec = {5,5,6,3,2,5,3};
    sort(vec.data(), vec.size());
    for (auto i : vec) std::cout << i;
}

