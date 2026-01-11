#include <iostream>
#include "Accountant.h"

inline double Accountant::CalculateSalary() const noexcept { return salary + (achivments * 25); }

void Accountant::printInfo() const noexcept {
    Employee::printInfo();
    std::cout << "Salary >> " << salary << "$" << std::endl;
    std::cout << "Achivmnets >> " << achivments << std::endl;
    std::cout << "Accountant" << std::endl; 
}