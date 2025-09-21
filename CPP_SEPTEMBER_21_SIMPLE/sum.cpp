#include <iostream>

int add (int a , int b) {
    return a+b;
}

double add (double a, double b) {
    return a+b;
}

int main() {
    int a = 0;  
    int b = 0;
    double c = 0;
    double d = 0;
    
    std::cout << "Please input two intenger number :" << std::endl;
    std::cout << "1) ";
    std::cin >> a;
    std::cout << "2) ";
    std::cin >> b;
    
    std::cout << "Please input two float number :" << std::endl;
    std::cout << "1) ";
    std::cin >> d;
    std::cout << "2) ";
    std::cin >> c;
    
    std::cout << "Your intengers sum : " << add(a,b) << std::endl;
    std::cout << "Your floats sum : " << add(c,d) << std::endl;
    
    return 0;
}
