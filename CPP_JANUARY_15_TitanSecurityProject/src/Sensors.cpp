#include "Sensors.hpp"

void Sensors::pollSensors(ISystem* s) {
    std::cout << "\n--- Polling Sensors (" << s->getMode() << " Mode) ---" << std::endl;

        for (size_t i = 0; i < sensorNames.size(); i++) {
            std::string name = sensorNames[i];
            std::string type = sensorTypes[i];
            int data = sensorData[i];

            if (type == "DoorSensor") {
                // Simulate reading hardware
                std::cout << "Reading " << name << "... ";
                if (data == 1 && s->getArmed()) {
                     std::cout << "OPEN! Triggering Alarm!" << std::endl;
                     triggerAlarm("High", "Police");
                } else {
                    std::cout << "Secure." << std::endl;
                }
            } 
            else if (type == "MotionSensor") {
                std::cout << "Reading " << name << "... ";
                
                if (data == 1 && s->getMode() == "Away") {
                    std::cout << "MOTION DETECTED!" << std::endl;
                    triggerAlarm("Medium", "UserPhone");
                } else {
                    std::cout << "No Motion." << std::endl;
                }
            } 
            else if (type == "HeatSensor") {
                std::cout << "Reading " << name << "... Temp: " << data << "C. ";
                if (data > 50) {
                    std::cout << "DANGER! FIRE!" << std::endl;
                    triggerAlarm("Critical", "FireDept");
                } else {
                    std::cout << "Normal." << std::endl;
                }
            } 
            else {
                std::cout << "[Warning] Unknown sensor type found in index " << i << std::endl;
            }
        }
}

void Sensors::SimulatesimulateSensorInput(size_t index, int value) {
    if (index >= 0 && index < sensorData.size())  sensorData[index] = value;
}