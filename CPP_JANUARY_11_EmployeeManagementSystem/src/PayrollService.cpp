#include "PayrollService.h"
#include "Accountant.h"
#include "Developer.h"
#include "Manager.h"
#include "SalesPerson.h"

void PayrollService::giveSalary(const std::shared_ptr<Employee>& emp) const noexcept{
    if (dynamic_cast<const Accountant*>(emp.get()) || dynamic_cast<const Developer*>(emp.get())  || dynamic_cast<const Manager*>(emp.get()) || dynamic_cast<const SalesPerson*>(emp.get())) std::cout << "Successfuly!" << std::endl;
    else std::cout << "King don't need salary" << std::endl;
}
