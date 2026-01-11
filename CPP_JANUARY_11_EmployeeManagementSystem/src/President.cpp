#include <iostream>
#include "President.h"

void President::printInfo() const noexcept {
    Employee::printInfo();
    std::cout << "King do'nt need salary" << std::endl;
    std::cout << "Achivmnets >> " << achivments << std::endl; 
    std::cout << "President" << std::endl;
}