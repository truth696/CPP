#pragma once
#include <fstream>
#include <string>

class ILogFile {
public:
    virtual void logToFile(std::string) = 0;
};