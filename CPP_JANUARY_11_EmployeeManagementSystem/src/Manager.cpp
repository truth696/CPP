#include <iostream>
#include "Manager.h"

double Manager::CalculateSalary() const noexcept { return salary + (achivments * 25);}

void Manager::printInfo() const noexcept {
    Employee::printInfo();
    std::cout << "Salary >> " << salary << "$" << std::endl;
    std::cout << "Achivmnets >> " << achivments << std::endl; 
    std::cout << "Manager" << std::endl;
}