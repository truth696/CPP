#pragma once
#include <iostream>
#include "Sensors.hpp"
#include "ISystem.hpp"

class IReport {
public:
    void generateReport(ISystem* s);
};