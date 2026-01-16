#pragma once
#include <fstream>
#include <string>
#include "ILogFile.hpp"

class LogFile: public ILogFile {
    std::ofstream logFile;
public:
    void logToFile(std::string) override;
};