#pragma once
#include "Pizza.hpp"
#include <memory>
#include <iostream>
#include <string>
 
class BaseDecorator : public Pizza{
protected:
    virtual ~BaseDecorator() = default;
    std::unique_ptr <Pizza> p;
};
