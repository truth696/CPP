#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class SalesPerson : public Employee , public ISalaried{
private:
    double salary;
    int achivments;
public:
    SalesPerson(std::string name = "Unknow") : Employee(name) , salary(Salary::salary_sales_person()) { achivments = Achivments::achivments(); }
    inline virtual double CalculateSalary() const noexcept override;
    virtual void printInfo() const noexcept override;
};