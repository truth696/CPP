#include <iostream>

template <typename... Types>
void printAllFold(
    Types... args
)
{
    ((std::cout << args << "\n"), ...);
} 

template <typename T, typename... Types>
void printAll(
    T arg, 
    Types... args
)
{
    std::cout << arg << std::endl;
    if constexpr (sizeof...(args)) 
    {
        printAll(args...);
    }
} 

int main()
{
    std::cout << "=== printAllFold ===\n";
    printAllFold(1, 2, 3, 4, 5);

    std::cout << "\n=== printAll (recursive) ===\n";
    printAll(10, 20, 30, 40, 50);

    std::cout << "\n=== mixed types ===\n";
    printAllFold(1, 2.5, "hello", 'A');
    printAll(1, 2.5, "hello", 'A');
}
