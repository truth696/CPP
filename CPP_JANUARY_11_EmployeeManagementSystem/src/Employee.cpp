#include "Employee.h"

void Employee::printInfo() const noexcept{
    std::cout << "Name >> " << name << std::endl;
    std::cout << "ID >> " << this->id << std::endl;
}