#pragma once
#include <string>

class ISystem{
public:
    virtual bool getArmed() = 0;
    virtual std::string getMode() = 0;
    virtual void SetMode(std::string mode) = 0;
};