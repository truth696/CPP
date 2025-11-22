#include "Vtable.hpp"

void Virtualizable::registerVirtual (std::string name, FnPtr fn) {
    names.push_back(name);
    funcs.push_back(fn);
}

void Virtualizable::callVirtual (std::string name) { for (int i = 0; i < name.size(); ++i) if (names[i] == name) (this->*funcs[i])(); }

void Derived::bar () {
    std::cout << "Hello, Derived" << std::endl;
} 

void Derived::foo () {
    std::cout << "Hello, Derived2" << std::endl;
}

void Base::bar () {
    std::cout << "Hello, Base" << std::endl;
} 

void Base::foo () {
    std::cout << "Hello, 2 Base" << std::endl;
}
