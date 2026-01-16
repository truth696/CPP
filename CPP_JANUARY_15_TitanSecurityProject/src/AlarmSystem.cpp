#include "IAlarms.hpp"
#include "LogFile.hpp"
#include"AlarmSystem.hpp"

void AlarmSystem::triggerAlarm(std::string severity, std::string notifyWho) {
    std::cout << "!!! ALARM TRIGGERED [" << severity << "] !!!" << std::endl;
    
    // 1. Sound Logic
    if (severity == "High" || severity == "Critical") {
        std::cout << ">>> PLAYING LOUD SIREN SOUND <<<" << std::endl;
    } else {
        std::cout << ">>> Beeping Keypad <<<" << std::endl;
    }

    // 2. Notification Logic 
    if (notifyWho == "Police") {
        std::cout << "Dialing 911..." << std::endl;
    } else if (notifyWho == "FireDept") {
        std::cout << "Dialing Fire Department..." << std::endl;
    } else if (notifyWho == "UserPhone") {
        std::cout << "Sending Push Notification to User..." << std::endl;
    }

    // 3. Logging
    logToFile("ALARM: " + severity + " sent to " + notifyWho);
}