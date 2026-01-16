#pragma once
#include <iostream>
#include "ISystem.hpp"

class ISensor{
public:
    virtual void pollSensors(ISystem* s) = 0;
    virtual void SimulatesimulateSensorInput(size_t index, int value) = 0; 
    virtual int getNames() = 0;
};