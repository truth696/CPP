#pragma once
#include "Decorator.hpp"

class Sauce: public BaseDecorator{
    std::unique_ptr<Pizza> p;
public:
    virtual ~Sauce() = default;
    Sauce(std::unique_ptr<Pizza> ptr) : p(std::move(ptr)) {}
    virtual std::string description() const noexcept override;
    virtual double cost ()const noexcept override;
};