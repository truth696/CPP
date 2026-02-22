#include <iostream>
#include <vector>
#include <string>


template <typename T>
auto sumContainer(
    T& arg
)
{
    auto cont = arg[0];
    cont = 0;
    for (auto i : arg) cont += i;

    return cont;
}


int main() {
    std::vector<int> vec = {1,3,4,5,6};
    std::string str = "hello";
    std::cout << (int)(sumContainer(str)) << std::endl;
    std::cout << sumContainer(vec) << " ";
}
