#include <iostream>


using Fn = void (*)(void *);


class Base{
    double k;
public:
    virtual void foo() {
        std::cout << "base foo" << std::endl;
    }
    virtual void hoo() {
        std::cout << "base hoo " << std::endl;
    }
};

class Derived : public Base {
    double l;
public:
    virtual void foo() override{
        std::cout << "derived foo" << std::endl;
    }
    virtual void hoo() override{
        std::cout << "derived hoo" << std::endl;
    }

};

int main() {
    Base* b = new Derived;
    void** vtbale = *(void***)b;

    Fn f1 = (Fn)(vtbale[0]);
    Fn f2 = (Fn)(vtbale[1]);
    f2(b);
    f1(b);
    
}