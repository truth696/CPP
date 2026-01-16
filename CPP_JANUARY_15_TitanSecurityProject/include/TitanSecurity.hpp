#pragma once
#include <string>
#include "Sensors.hpp"
#include "ISystem.hpp"
#include "AlarmSystem.hpp"


class TitanSystem : public Sensors, public ISystem{
protected:
    std::string currentMode;
    bool systemArmed;
public:
    void SetMode(std::string mode) override;
    bool getArmed() override {return systemArmed;}
    std::string getMode() override { return currentMode; }
    TitanSystem() : currentMode("Day"), systemArmed(false) {}
};