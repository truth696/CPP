#include <iostream>

class B{
public:
  virtual void foo() = 0;
};

class A: public B{
public:
  virtual void foo() {
    std::cout << "Hlelo";
  }
};


int main() {
}
