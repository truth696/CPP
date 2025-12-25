#include <iostream>


using Fn = void (*)(void *);


class Base{
    double k;
public:
    virtual void foo() {
        std::cout << "'foo1" << std::endl;
    }
    virtual void hoo() {
        std::cout << "'hoo1" << std::endl;
    }
};

class Derived : public Base {
    double l;
public:
    virtual void foo() override{   
        std::cout << "'foo2" << std::endl;

    }
    virtual void hoo() override{
        std::cout << "'hoo2" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived;
    void** vtable = *(void***)ptr;
    Fn f1 = (Fn)vtable[0];
    Fn f2 = (Fn)vtable[0];
    f1(vtable);
    f2(vtable);
}







