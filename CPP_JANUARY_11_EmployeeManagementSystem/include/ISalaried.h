#pragma once

class ISalaried {
public:
    virtual double CalculateSalary() const noexcept = 0;
};