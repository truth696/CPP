#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class Accountant : public Employee , public ISalaried{
private:
    double salary;
    int achivments;
public:
    Accountant(std::string name = "Unknow") : Employee(name) , salary(Salary::salary_accountant()) { achivments = Achivments::achivments(); }
    inline virtual double CalculateSalary() const noexcept override;
    virtual void printInfo() const noexcept override;
};