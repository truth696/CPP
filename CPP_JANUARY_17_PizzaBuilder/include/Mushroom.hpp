#pragma once
#include "Decorator.hpp"

class Mushroom : public BaseDecorator{
    std::unique_ptr<Pizza> p;
public:
    virtual ~Mushroom() = default;
    Mushroom(std::unique_ptr<Pizza> ptr) : p(std::move(ptr)) {}
    virtual std::string description() const noexcept override;
    virtual double cost ()const noexcept override;
};