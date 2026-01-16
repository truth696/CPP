#pragma once
#include <string>

class IAlarms {
public:
    virtual void triggerAlarm(std::string severity, std::string notifyWho) = 0;
};
