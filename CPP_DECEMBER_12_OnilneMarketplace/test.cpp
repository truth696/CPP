#include <iostream>
#include  <iomanip>

struct Base1 {
    double x;
    double y;
    Base1() : x(9), y(5) {}
    virtual void foo() {
        std::cout << "Hello";
    }
};

struct Base2 : Base1{
    double x;
    double y;
    double z;
    Base2() : x(20), y(12), z(13){}
};

struct Derived: Base2 {
    virtual void foo() {
        std::cout << "Hello";
    }
};

int main(){
    Base1* ptr = new Derived;
    std::cout << ptr->x << ptr->y << std::endl;
    std::cout << dynamic_cast<Base2*>(ptr)->x << dynamic_cast<Base2*>(ptr)->y << dynamic_cast<Base2*>(ptr)-> z;
return 0;
}
