#pragma once 
#include <iostream>
#include <string>

class Student{
public:     
    Student(const std::string& _name, size_t _age, double _gpa){
        set_name(_name);
        set_age(_age);
        set_gpa(_gpa);
    }

    void set_name(const std::string& _name){
        name_ = _name;
    }
    std::string name() const { return name_; } 

    void set_age(size_t _age){
        if (_age >= 100) throw std::logic_error("Invalid number");
        age_ = _age;
    }
    size_t age() const { return age_; }

    void set_gpa(double _gpa){
        if (gpa_ < 0 || gpa_ > 100) throw std::logic_error("Invalid number");
        gpa_ = static_cast<double> (static_cast<int>(_gpa * 100) / 100);
    }
    double gpa() const { return gpa_; }

    void PrintInfo() const {
        std::cout << "name: " << name_ << std::endl;
        std::cout << "age: " << age_ << std::endl;
        std::cout << "gpa: " << gpa_ << std::endl;
    }

private:
    std::string name_;
    size_t age_;
    double gpa_;

};  