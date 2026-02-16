#include <iostream>

template <typename T, typename... Types>
auto sum (
    T tmp,
    Types... args
)
{
    if constexpr (sizeof...(args)) return  (tmp + sum(args...));
    else return tmp;
}

template <typename T, typename... Types>
auto sumFold(
    T tmp,
    Types... args
)
{
    return (tmp + ... + args);
}

int main()
{
    std::cout << "sum(5)                = " << sum(5) << '\n';
    std::cout << "sumFold(5)            = " << sumFold(5) << '\n';

    std::cout << "sum(1,2,3,4,5)        = " << sum(1,2,3,4,5) << '\n';
    std::cout << "sumFold(1,2,3,4,5)    = " << sumFold(1,2,3,4,5) << '\n';

    std::cout << "sum(1.5,2.0,3.25)     = " << sum(1.5,2.0,3.25) << '\n';
    std::cout << "sumFold(1.5,2.0,3.25) = " << sumFold(1.5,2.0,3.25) << '\n';

    std::cout << "sum(10,-3,7)          = " << sum(10,-3,7) << '\n';
    std::cout << "sumFold(10,-3,7)      = " << sumFold(10,-3,7) << '\n';
}
