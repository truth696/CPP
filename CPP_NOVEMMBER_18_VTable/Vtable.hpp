#include <iostream>
#include <string>
#pragma once 

class Virtualizable;
class Derived;
class Base;
using FnPtr = void (Virtualizable::*)();


class Virtualizable{
private:
    std::vector <std::string> names;
    std::vector <FnPtr> funcs;
protected:
    std::string _typeid;
public:
    void registerVirtual(std::string name, FnPtr fn);
    void callVirtual(std::string name);
    std::string type() { return _typeid; }
    Virtualizable(std::string _typeid_ = "Virtualizable", std::string name1 = "", FnPtr fn1 = nullptr, std::string name2 = "", FnPtr fn2 = nullptr) : _typeid(_typeid_) {
        registerVirtual(name1, fn1);
        registerVirtual(name2, fn2);
    }
};

template<typename T>
T* dynamicCast(Virtualizable* type_cast) {
    if(type_cast->type() == T::type()) return static_cast<T*>(type_cast);
    return nullptr;
}


class Base : public Virtualizable {
public:
    static std::string type() { return "Base"; }
    Base(std::string _typeid_ = type(), std::string name1 = "foo", FnPtr fn1 = (FnPtr)&Base::foo, std::string name2 = "bar", FnPtr fn2 = (FnPtr)&Base::bar) : Virtualizable (_typeid_, name1, fn1, name2,  fn2) { }
    void foo();
    void bar();
};

class Derived: public Base{
public:
    static std::string type() { return "Derived"; }
    Derived(std::string _typeid_ = type(), std::string name1 = "foo", FnPtr fn1 = (FnPtr)&Derived::foo,  std::string name2 = "bar", FnPtr fn2 = (FnPtr)&Derived::bar) : Base (_typeid_, name1, fn1, name2, fn2) { }
    void foo ();
    void bar();
    
};

