#pragma once
#include <iostream>
#include "Sensors.hpp"
#include "ISystem.hpp"

class IReport {
public:
    virtual ~IReport() = default;
    void generateReport(ISystem* s);
};