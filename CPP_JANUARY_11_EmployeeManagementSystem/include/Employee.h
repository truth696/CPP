#pragma once
#include <iostream>
#include <string>
#include "Counter_id.h"
#include "ISalaried.h"

class Employee {
private:
    std::string name;
    size_t id;
protected:
    Employee(std::string name) noexcept : name(name){ this->id = ++Counter::id; }
public:
    inline std::string getName() const noexcept { return name; }
    inline size_t getID() const noexcept { return id; }
    virtual void printInfo() const noexcept;
    virtual ~ Employee() = default;
    virtual bool hasSalary() const noexcept = 0;
};  
