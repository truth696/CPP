#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class Developer : public Employee , public ISalaried{
private:
    double salary;
    int achivments;
public:
    Developer(std::string name = "Unknow") : Employee(name) , salary(Salary::salary_developer()) { achivments = Achivments::achivments(); }
    inline virtual double CalculateSalary() const noexcept override;
    virtual void printInfo() const noexcept override;
    inline virtual bool hasSalary() const noexcept override { return true; }
};