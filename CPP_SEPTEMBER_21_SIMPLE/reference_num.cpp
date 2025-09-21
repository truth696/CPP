#include <iostream>

int main () {
    int x = 0;
    int &a = x;
    int &b = x;
    
    std::cout << "Please input number for x: " << std::endl;
    std::cin >> x;
    
    std::cout << "Before change A - " << a << " B - " << b << std::endl;

    std::cout << "Please input number for change x: " << std::endl;
    std::cin >> a;
    
    std::cout << "After change A - " << a << " B - " << b << std::endl;

return 0;
}
