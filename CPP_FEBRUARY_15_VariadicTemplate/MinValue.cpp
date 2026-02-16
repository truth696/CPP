#include <iostream>

template <typename T, typename... Types>
auto minValue(
    T tmp, 
    Types... args
)
{
    if constexpr (sizeof...(args)) return tmp < minValue(args...) ? tmp : minValue(args...);
    return tmp;
}


//SKIP SKIP SKIP SKIP SKIP
// template <typename T, typename... Types>
// auto minValue(
//     T tmp, 
//     Types... args
// ) 
// {
// }
//SKIP SKIP SKIP SKIP SKIP
