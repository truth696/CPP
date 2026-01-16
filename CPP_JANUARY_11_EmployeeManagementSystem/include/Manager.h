#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class Manager : public Employee , public ISalaried{
private:
    double salary;
    int achivments;
public:
    Manager(std::string name = "Unknow") : Employee(name) , salary(Salary::salary_manager()) { achivments = Achivments::achivments(); }
    inline virtual double CalculateSalary() const noexcept override;
    virtual void printInfo() const noexcept override;

};