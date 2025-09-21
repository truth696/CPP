#include <iostream>

void swap (int &a, int &b) {
    a += b;
    b = a - b;
    a = a - b; 
}

int main() {
    int a;
    int b; 
    
    std::cout << "Please input number for a: ";
    std::cin >> a;
    
    std::cout << "Please input number for b: ";
    std::cin >> b;
    
    std::cout << "Before  a - " << a << " b - " << b << std::endl;
    
    swap(a,b);
    
    std::cout << "After a - " << a << " b - " << b << std::endl;

return 0;
}

