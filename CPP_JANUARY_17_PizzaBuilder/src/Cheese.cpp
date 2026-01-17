#include "Cheese.hpp"

std::string Cheese::description() const noexcept { return p->description() + " Cheese"; }
double Cheese::cost() const noexcept { return p->cost() + 1.50; }

