#pragma once
#include <fstream>
#include <string>
#include "ILog.hpp"

class LogToFile: public ILog {
    std::ofstream logFile;
public:
    virtual ~LogToFile() = default;
    void logTo(std::string) override;
};