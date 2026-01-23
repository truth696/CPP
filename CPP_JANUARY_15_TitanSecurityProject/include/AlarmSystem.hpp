#pragma once
#include "IAlarms.hpp"
#include "LogToFile.hpp"
#include <iostream>

class AlarmSystem : public IAlarms, public LogToFile {
public:
    virtual ~AlarmSystem() = default;
    void triggerAlarm(std::string severity,std::string notifyWho) override;
};
