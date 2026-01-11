#include "PayrollService.h"
#include "Accountant.h"
#include "Developer.h"
#include "Manager.h"
#include "SalesPerson.h"

void PayrollService::giveSalary(const std::shared_ptr<Employee>& e) const noexcept{
    if (e->hasSalary()) std::cout << "Successfuly!" << std::endl;
    else std::cout << "King don't need salary" << std::endl;
}
