#include <iostream>
#include "SalesPerson.h"

double SalesPerson::CalculateSalary() const noexcept { return salary + (achivments * 25);}

void SalesPerson::printInfo() const noexcept {
    Employee::printInfo();
    std::cout << "Salary >> " << salary << "$" << std::endl;
    std::cout << "Achivmnets >> " << achivments << std::endl; 
    std::cout << "Sales Perosn" << std::endl;
}
