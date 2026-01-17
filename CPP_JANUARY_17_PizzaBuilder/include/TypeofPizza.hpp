#pragma once
#include "Pizza.hpp"

class Margherita : public Pizza {
public:
    virtual ~Margherita() = default;
    virtual std::string description() const noexcept override;
    virtual double cost ()const noexcept override;
};
