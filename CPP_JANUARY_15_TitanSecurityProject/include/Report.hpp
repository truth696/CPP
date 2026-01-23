#pragma once
#include <iostream>
#include "Sensors.hpp"
#include "ISystem.hpp"

class Report {
public:
    virtual ~Report() = default;
    void generateReport(ISystem* s);
};