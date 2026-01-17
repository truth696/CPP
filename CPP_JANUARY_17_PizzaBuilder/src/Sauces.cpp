#include "Sauces.hpp"

std::string Sauce::description() const noexcept { return p->description() + " Sauce"; }
double Sauce::cost() const noexcept { return p->cost() + 3.25; }
