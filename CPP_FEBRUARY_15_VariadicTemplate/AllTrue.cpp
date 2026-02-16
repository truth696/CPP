#include <iostream>

template <typename T, typename... Types>
auto allTrue(
    T tmp,
    Types... args
)
{
    if constexpr (sizeof...(args)) return (bool)tmp ? allTrue(args...) : false;
    return (bool)tmp;
}

template <typename T, typename... Types>
auto allTrueFold(
    T tmp,
    Types... args
)
{
    return (tmp && ... && args);
}

int main()
{
    std::cout << std::boolalpha;

    std::cout << "allTrue(true)             = " << allTrue(true) << '\n';
    std::cout << "allTrueFold(true)         = " << allTrueFold(true) << '\n';

    std::cout << "allTrue(false)            = " << allTrue(false) << '\n';
    std::cout << "allTrueFold(false)        = " << allTrueFold(false) << '\n';

    std::cout << "allTrue(1, 1, 1)          = " << allTrue(1, 1, 1) << '\n';
    std::cout << "allTrueFold(1, 1, 1)      = " << allTrueFold(1, 1, 1) << '\n';

    std::cout << "allTrue(1, 0, 1)          = " << allTrue(1, 0, 1) << '\n';
    std::cout << "allTrueFold(1, 0, 1)      = " << allTrueFold(1, 0, 1) << '\n';

    std::cout << "allTrue(0, 0, 0)          = " << allTrue(0, 0, 0) << '\n';
    std::cout << "allTrueFold(0, 0, 0)      = " << allTrueFold(0, 0, 0) << '\n';

    std::cout << "allTrue(5, 2, 3, 1)       = " << allTrue(5, 2, 3, 1) << '\n';
    std::cout << "allTrueFold(5, 2, 3, 1)   = " << allTrueFold(5, 2, 3, 1) << '\n';

    std::cout << "allTrue(5, 2, 0, 1)       = " << allTrue(5, 2, 0, 1) << '\n';
    std::cout << "allTrueFold(5, 2, 0, 1)   = " << allTrueFold(5, 2, 0, 1) << '\n';
}

