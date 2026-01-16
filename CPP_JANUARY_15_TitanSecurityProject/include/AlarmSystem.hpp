#pragma once
#include "IAlarms.hpp"
#include "LogFile.hpp"
#include <iostream>

class AlarmSystem : public IAlarms, public LogFile {
public:
    void triggerAlarm(std::string severity,std::string notifyWho) override;
};
