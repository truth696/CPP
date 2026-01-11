#pragma once
#include <iostream> 
#include <vector>
#include <memory> 
#include "Employee.h"
#include "PayrollService.h"

class EmployeeRepository : public PayrollService{
private:
    std::vector<std::shared_ptr<Employee>> database;
public:
    void addEmployee(std::shared_ptr<Employee> e) noexcept;
    void removeEmployee (size_t id) noexcept;
    void listAllEmployee() const noexcept; 
};