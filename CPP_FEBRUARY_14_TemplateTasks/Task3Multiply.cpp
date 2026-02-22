#include <iostream>
#include <vector>
#include <string>

template <typename T, typename N>
T multiply(
    T arg1, N arg2
)
{
    std::cout << "Unknonw type" << std::endl;
}

template <>
int multiply<int,int>(
    int x,
    int y
) 
{
    return x * y; 
}

template <>
double multiply<double, double>(
    double x,
    double y
) 
{
    return (static_cast<double> (static_cast<int> ((x * y) * 100))) / 100;
}

template <>
std::string multiply<std::string, int>(
    std::string arg1,
    int arg2
)
{
    std::string cpy = arg1;
    for(;arg2 != 0; --arg2) 
    {
        for(auto i : cpy) arg1.push_back(i); 
    }

    return arg1;
}


int main() {
    std::cout << multiply(5,5) << std::endl;
    std::cout << multiply(5.34534534,5.234121) << std::endl;
    std::string st = "hello"; 
    std::cout << multiply(st,5) << std::endl;
}

