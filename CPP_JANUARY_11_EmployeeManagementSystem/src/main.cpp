#include "Employee.h" 
#include "Accountant.h" 
#include "Counter_id.h" 
#include "Developer.h" 
#include "EmployeeRepository.h" 
#include "ISalaried.h" 
#include "Manager.h"
#include "PayrollService.h"
#include "President.h" 
#include "SalesPerson.h"

int main() {
    EmployeeRepository obj;

    auto dev1  = std::make_shared<Developer>("Hayk");
    auto dev2  = std::make_shared<Developer>("Miqo");
    auto dev3  = std::make_shared<Developer>("Gugo");
    auto dev4  = std::make_shared<Developer>("Narek");
    auto acc1  = std::make_shared<Accountant>("Vahe");
    auto sep1  = std::make_shared<SalesPerson>("Nikol");
    auto pres1 = std::make_shared<President>("Vardan");

    obj.addEmployee(dev1);
    obj.addEmployee(dev2);
    obj.addEmployee(dev3);
    obj.addEmployee(dev4);
    obj.addEmployee(dev2);
    obj.addEmployee(dev3);
    obj.addEmployee(dev4);
    obj.addEmployee(acc1);
    obj.addEmployee(sep1);
    obj.addEmployee(pres1);
    obj.listAllEmployee();
    obj.removeEmployee(0);
    obj.removeEmployee(3);
    obj.removeEmployee(4);
    obj.removeEmployee(5);
    obj.giveSalary(dev3);
    obj.giveSalary(dev2);
    obj.giveSalary(sep1);
    obj.giveSalary(pres1);

    return 0;
}
