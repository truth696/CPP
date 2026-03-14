#pragma once 
#include <iostream>
#include <string>

class Course{
public:
    Course(const std::string& _title, double _credit, bool _mandatory){
        set_title(_title);
        set_credit(_credit);
        set_mandatory(_mandatory);
    }
    
    void set_title(const std::string& _title) {
        title_ = _title;
    }
    std::string title() const { return title_; } 
    
    void set_credit(double _credit){
        if (_credit < 0) throw std::logic_error("Invalid number");
        credit_ = _credit;
    }
    double credit() const { return credit_; }

    void set_mandatory(bool _mandatory){
        mandatory_ = _mandatory;
    } 
    
    bool mandatory() const { return mandatory_;}

    void PrintInfo() const {
        std::cout << "title: " << title_ << std::endl;
        std::cout << "credit: " << credit_ << std::endl;
        std::cout << std::boolalpha << "mandatory: " << mandatory_ << std::endl;
    }
private:
    std::string title_;
    size_t credit_;
    bool mandatory_;
};