#pragma once
#include <iostream>

class Pizza {
public:
    virtual ~Pizza() = default;
    virtual std::string description() const noexcept = 0;
    virtual double cost() const noexcept = 0;
};