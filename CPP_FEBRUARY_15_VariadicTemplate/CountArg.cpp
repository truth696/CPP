#include <iostream>

template <typename... Types>
auto CountArgs(
    Types... args
)
{ return sizeof...(args); }

template <typename... Types>
auto CountArgsFold(
    Types... args
)
{
    return 1 + CountArgs(args...);
}


int main()
{
    std::cout << "CountArgs: " << CountArgs(1, 2, 3, 4, 5) << '\n';
    std::cout << "CountArgsFold_bad: " << CountArgsFold(1, 2, 3, 4, 5) << '\n';
    std::cout << "CountArgsFold: " << CountArgsFold(1, 2, 3, 4, 5) << '\n';

    std::cout << "Empty:\n";
    std::cout << "CountArgs(): " << CountArgs() << '\n';
    std::cout << "CountArgsFold(): " << CountArgsFold() << '\n';
}