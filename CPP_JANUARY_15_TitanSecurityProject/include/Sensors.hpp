#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "AlarmSystem.hpp"
#include "Report.hpp"
#include "ISensor.hpp"
#include "LogToFile.hpp"


class Sensors : public ISensor, public AlarmSystem{
    std::vector<std::string> sensorNames;
    std::vector<std::string> sensorTypes;
    std::vector<int> sensorData;
    std::vector<std::string> sensorLocations;
public:
    virtual ~Sensors() = default;
    void pollSensors(ISystem* s) override;
    int getNames() override { return sensorNames.size(); }
    void SimulatesimulateSensorInput(size_t index, int value) override;
    virtual void DoorSensor(int data, bool armed) override;
    virtual void MotionSensor(int data, std::string mode) override;
    virtual void HeatSensor(int data) override;
    Sensors();
};
