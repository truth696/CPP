// #include <iostream>
// #include <memory>



// using Fn = void (*)(void *);


// class Base{
//     double k;
// public:
//     virtual void foo() {
//         std::cout << "'foo1" << std::endl;
//     }
//     virtual void hoo() {
//         std::cout << "'hoo1" << std::endl;
//     }
// };

// class Derived : public Base {
//     double l;
// public:
//     virtual void foo() override{   
//         std::cout << "'foo2" << std::endl;

//     }
//     virtual void hoo() override{
//         std::cout << "'hoo2" << std::endl;
//     }
// };

// int main() {
//     Base* ptr = new Derived;
//     void** vtable = *(void***)ptr;
//     Fn f1 = (Fn)vtable[0];
//     Fn f2 = (Fn)vtable[1];
//     f1(vtable);
//     f2(vtable);
// }











// #include <stdexcept>
// #include <exception>
// #include <iostream>
// struct A : std::exception{
//     A() {std::cout << "A  def ctor" << std::endl;}
//     A(const A& oth) {std::cout << "A copy ctor" << std::endl;}
//     A(A&& oth) {std::cout << "A move ctor" << std::endl;}
//     ~A() { std::cout << "ya umer" << std::endl;}
//     const char* what() const noexcept override{ 
//         return "A exeption yo";
//     }
// };
// int main() {
//     try {
//         A a;
//         A b;
//         A c;
//         A d;
//         throw a;
//     } catch (std::exception e) {
//         std::cout << e.what() << std::endl;
//     }

//     std::cout << "main umeraet" << std::endl;
// }



// #include <iostream>

// class Base {
//     Base () {}
//     double l;
//     friend Derived;
// };

// class Derived: virtual private Base{
//     public:
//     Derived() {}
//     double d;
// };

// class MostDerived: Derived{
//     MostDerived() {}
// };

// int main() {
//     MostDerived d;

// }


// #include <iostream>
// #include <memory>


// int main () {?
    // try{
    //     throw;
    // }catch (double e){
    //     std::cout << "double";

    // } catch (int e) {
    //     std::cout << "int";
    // } catch (...) {
    //     std::cout << "elipsis";
    // }

    // int x = 0 ;
    // int* y = const_cast<int*> (&x); 
// }
#include <iostream>

class Base {
    double l;
};

class Derived : public Base {
    virtual void foo () { }
    double k;
};

int main() {
    Base* ptr = new Derived;
    Derived* ptr_p = dynamic_cast<Derived*> (ptr);
    std::cout << "hello";
}







