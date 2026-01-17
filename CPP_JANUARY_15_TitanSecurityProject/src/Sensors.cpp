#include "Sensors.hpp"


Sensors::Sensors() {
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

void Sensors::pollSensors(ISystem* s) {
    std::cout << "\n--- Polling Sensors (" << s->getMode() << " Mode) ---" << std::endl;
    
        for (size_t i = 0; i < sensorNames.size(); i++) {
            
            if (sensorTypes[i] == "DoorSensor") {
                std::cout << "Reading " << sensorNames[i] << "... ";
                DoorSensor(sensorData[i], s->getArmed());
            } 
            else if (sensorTypes[i] == "MotionSensor") {
                std::cout << "Reading " << sensorNames[i] << "... ";
                MotionSensor(sensorData[i], s->getMode());
            } 
            else if (sensorTypes[i] == "HeatSensor") {
                std::cout << "Reading " << sensorNames[i] << "... Temp: " << sensorData[i] << "C. ";
                HeatSensor(sensorData[i]);
            } 
            else {
                std::cout << "[Warning] Unknown sensor type found in index " << i << std::endl;
            }
        }
}

void Sensors::SimulatesimulateSensorInput(size_t index, int value){
     if (index >= 0 && index < sensorData.size())  sensorData[index] = value;
}

void Sensors::DoorSensor(int data, bool armed){
    if (data == 1 && armed) {
            std::cout << "OPEN! Triggering Alarm!" << std::endl;
            triggerAlarm("High", "Police");
    } else {
        std::cout << "Secure." << std::endl;
    }
}

void Sensors::MotionSensor(int data, std::string mode) {
    if (data == 1 && mode == "Away") {
        std::cout << "MOTION DETECTED!" << std::endl;
        triggerAlarm("Medium", "UserPhone");
    } else {
        std::cout << "No Motion." << std::endl;
    }
}

void Sensors::HeatSensor(int data) {
    if (data > 50) {
        std::cout << "DANGER! FIRE!" << std::endl;
        triggerAlarm("Critical", "FireDept");
    } else {
        std::cout << "Normal." << std::endl;
    }
}

