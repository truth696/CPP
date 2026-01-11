#pragma once
#include <iostream>
#include "Employee.h"

struct PayrollService {
    void giveSalary(const std::shared_ptr<Employee>& e) const noexcept;
};