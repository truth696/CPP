#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class President : public Employee , public ISalaried{
private:
    int achivments;
    virtual double CalculateSalary() const noexcept override{ return -1; }
public:
    President(std::string name = "Unknow") : Employee(name) { achivments = Achivments::achivments(); }
    virtual void printInfo() const noexcept override;
    inline virtual bool hasSalary() const noexcept override{ return false; }
};