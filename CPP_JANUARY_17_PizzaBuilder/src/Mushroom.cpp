#include "Mushroom.hpp"

std::string Mushroom::description() const noexcept { return p->description() + " Mushroom"; }
double Mushroom::cost() const noexcept { return p->cost() + 2.55; }
