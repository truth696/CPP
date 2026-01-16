#pragma once
#include "Counter_id.h"
#include "Employee.h"
#include "ISalaried.h"

class President : public Employee{
private:
    int achivments;
public:
    President(std::string name = "Unknow") : Employee(name) { achivments = Achivments::achivments(); }
    virtual void printInfo() const noexcept override;
};