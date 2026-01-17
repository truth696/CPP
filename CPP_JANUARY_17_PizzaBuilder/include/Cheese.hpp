#pragma once
#include "Decorator.hpp"

class Cheese : public BaseDecorator{
    std::unique_ptr<Pizza> p;
public:
    virtual ~Cheese() = default;
    Cheese(std::unique_ptr<Pizza> ptr) : p(std::move(ptr)) {}
    virtual std::string description() const noexcept override;
    virtual double cost ()const noexcept override;
};