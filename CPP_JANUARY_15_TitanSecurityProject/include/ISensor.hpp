#pragma once
#include <iostream>
#include "ISystem.hpp"

class ISensor{
public:
    virtual ~ISensor() = default;
    virtual void pollSensors(ISystem* s) = 0;
    virtual void SimulatesimulateSensorInput(size_t index, int value) = 0; 
    virtual int getNames() = 0;
    virtual void DoorSensor(int data, bool armed) = 0;
    virtual void MotionSensor(int data, std::string armed) = 0;
    virtual void HeatSensor(int data) = 0;
};