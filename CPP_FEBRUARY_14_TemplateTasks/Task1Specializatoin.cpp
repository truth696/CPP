#include <iostream>
#include <string>

template <typename T>
void printValue (
    T arg
)
{
    std::cout << "Uknown type" << std::endl;
}

template <>
void printValue<int>(
    int arg
)
{
    std::cout << "Intenger <" << arg << ">" << std::endl; 
}

template <>
void printValue<double> (
    double arg
) 
{
    std::cout << "Double <" << (static_cast<double> (static_cast<int> (arg * 100))) / 100 << ">" << std::endl;
}

template <>
void printValue<const char*>(
    const char* arg
)
{
    for (; *arg != '\0'; ++arg)
    {
        std::cout << (char)(((*arg >= 'a' && *arg <= 'z') ? (*arg - 32) : *arg)) << std::endl;
    }
}


int main() 
{
    int x = 5;
    double y = 3.1415;
    const char* p = "lsakdjf";
    std::string f = "hellllooo";

    printValue(5);
    printValue(y);
    printValue(p);
    printValue(f);

}