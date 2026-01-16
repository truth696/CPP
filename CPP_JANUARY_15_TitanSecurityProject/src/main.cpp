#include "TitanSecurity.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        TitanSystem homeSecurity;

        std::cout << "--- Titan Security System v1.0 ---\n";


        homeSecurity.SetMode("Away");

        // 3. Simulate "Normal" Check
        homeSecurity.pollSensors(&homeSecurity);

        // 4. Intruder scenario!
        std::cout << "\n[SIMULATION] Intruder breaks open the front door...\n";
        homeSecurity.SimulatesimulateSensorInput(0, 1); // Index 0 is Door, set to 1 (Open)
        
        homeSecurity.pollSensors(&homeSecurity);

        // 5. Fire scenario!
        std::cout << "\n[SIMULATION] Kitchen catches fire...\n";
        homeSecurity.SimulatesimulateSensorInput(2, 60); // Index 2 is Heat, set to 60C
        
        homeSecurity.pollSensors(&homeSecurity);

    } catch (const std::exception& e) {
        std::cout << "CRITICAL ERROR: " << e.what() << std::endl;
    }

    return 0;
}