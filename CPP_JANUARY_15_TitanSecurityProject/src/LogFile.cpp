#include "LogToFile.hpp"
#include <iostream>

void LogToFile::logTo(std::string message) {
        logFile.open("system_log.txt", std::ios_base::app); 
        if (logFile.is_open()) {
            // Get current time
            time_t result = time(nullptr);
            logFile << ctime(&result) << " - " << message << "\n";
            logFile.close();
        } else {
            std::cerr << "Failed to write to log file." << std::endl;
        }
}