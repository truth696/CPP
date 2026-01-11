#include <iostream>
#include "Developer.h"

double Developer::CalculateSalary() const noexcept { return salary + (achivments * 25);}

void Developer::printInfo() const noexcept {
    Employee::printInfo();
    std::cout << "Salary >> " << salary << "$" << std::endl;
    std::cout << "Achivmnets >> " << achivments << std::endl; 
    std::cout << "Developer" << std::endl;
}