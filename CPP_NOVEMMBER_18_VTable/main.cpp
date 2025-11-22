#include <iostream>
#include "Vtable.hpp"

int main() {
    Derived derivedObj;
    Base* ptr = &derivedObj;
    ptr->callVirtual("foo");
    ptr->callVirtual("bar");
    Virtualizable* v = new Derived;
    Base* ptr2 = new Base;

    if (Derived* d = dynamicCast<Derived>(v)) {
        std::cout << "Work1" << std::endl;
    }

    if (Base* b = dynamicCast<Base>(v)) {
        std::cout << "Work2" << std::endl;
    }

    if (Base* b = dynamicCast<Base>(ptr2)) {
        std::cout << "Work3" << std::endl;
    }


}

