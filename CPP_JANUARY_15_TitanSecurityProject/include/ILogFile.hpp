#pragma once
#include <fstream>
#include <string>

class ILogFile {
public:
    virtual ~ILogFile() = default;
    virtual void logToFile(std::string) = 0;
};