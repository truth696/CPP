#include <iostream>

template <typename T, typename... Types>
auto anyTrue(
    T tmp, 
    Types... args
)
{
    if constexpr (sizeof...(args)) return (bool)tmp || anyTrue(args...);
    return (bool)tmp;
}

template <typename T, typename... Types>
auto anyTrueFold(
    T tmp, 
    Types... args
)
{
    return (tmp || ... || args);
}


int main()
{
    std::cout << std::boolalpha;

    std::cout << "anyTrue(true)      = " << anyTrue(true) << '\n';
    std::cout << "anyTrueFold(true)  = " << anyTrueFold(true) << '\n';

    std::cout << "anyTrue(false)     = " << anyTrue(false) << '\n';
    std::cout << "anyTrueFold(false) = " << anyTrueFold(false) << '\n';

    std::cout << "anyTrue(0, 0, 0)        = " << anyTrue(0, 0, 0) << '\n';
    std::cout << "anyTrueFold(0, 0, 0)    = " << anyTrueFold(0, 0, 0) << '\n';

    std::cout << "anyTrue(0, 0, 5, 0)     = " << anyTrue(0, 0, 5, 0) << '\n';
    std::cout << "anyTrueFold(0, 0, 5, 0) = " << anyTrueFold(0, 0, 5, 0) << '\n';
}