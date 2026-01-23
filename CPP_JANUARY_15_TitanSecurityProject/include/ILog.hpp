#pragma once
#include <fstream>
#include <string>

class ILog {
public:
    virtual ~ILog() = default;
    virtual void logTo(std::string) = 0;
};