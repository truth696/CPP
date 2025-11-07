#include <iostream>

int main() {
    int x = 0;
    int &r = x;


    std::cout << "Please input number :" << std::endl;
    std::cin >> x;
    
    int y = x; 
    
    std::cout << "Before change X - " << x << " Y - " << y << " R - " << r << std::endl;
    
    std::cout << "Please input number for chage y :" << std::endl;
    std::cin >> y;

    std::cout << "Please input number for chage r :" << std::endl;
    std::cin >> r;
    
    std::cout << "After change X - " << x << " Y - " << y << " R - " << r << std::endl;

return 0;
}
