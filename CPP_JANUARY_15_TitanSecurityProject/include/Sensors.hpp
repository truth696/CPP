#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "AlarmSystem.hpp"
#include "IReport.hpp"
#include "ISensor.hpp"
#include "LogFile.hpp"


class Sensors : public ISensor, public AlarmSystem{
    std::vector<std::string> sensorNames;
    std::vector<std::string> sensorTypes;
    std::vector<int> sensorData;
    std::vector<std::string> sensorLocations;
public:
    void pollSensors(ISystem* s) override;
    void SimulatesimulateSensorInput(size_t index, int value) override;
    int getNames() override { return sensorNames.size(); }
    Sensors() {
        sensorNames.push_back("Front Door");
        sensorTypes.push_back("DoorSensor");
        sensorData.push_back(0); // Closed
        sensorLocations.push_back("Entry");

        sensorNames.push_back("Living Room Motion");
        sensorTypes.push_back("MotionSensor");
        sensorData.push_back(0); // No motion
        sensorLocations.push_back("Living Room");

        sensorNames.push_back("Kitchen Heat");
        sensorTypes.push_back("HeatSensor");
        sensorData.push_back(25); // 25 degrees Celsius
        sensorLocations.push_back("Kitchen");
    }
};