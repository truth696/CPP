🧾 Employee Management System (EMS)

This is a C++ project for managing employees in a company.
It supports multiple employee types, automatic ID generation, salary management, and safe memory handling.

────────────────────────────
📁 Project Structure

Makefile  
ems   → compiled executable  

include/  
  Accountant.h  
  Counter_id.h        → unique ID generator  
  Developer.h  
  Employee.h         → base class  
  EmployeeRepository.h  
  ISalaried.h  
  Manager.h  
  PayrollService.h  
  President.h  
  SalesPerson.h  

src/  
  *.cpp   → implementations  
  main.cpp → entry point  

────────────────────────────
🧠 Architecture

All employees inherit from the base class `Employee`.

Each employee decides:
- whether they receive a salary 💰  
- how they print their information 🧾  

This is implemented using virtual functions and dynamic dispatch.

────────────────────────────
🆔 Unique IDs

Every new employee gets a unique ID:

Employee → id = ++Counter::id  

The counter is global and shared between all employees.

────────────────────────────
📦 EmployeeRepository

Employees are stored as:

vector<shared_ptr<Employee>>

This provides:
✔ no delete  
✔ no double free  
✔ no memory leaks  
✔ safe sharing of employees  

────────────────────────────
💰 PayrollService

Salary logic does NOT use dynamic_cast ❌  
Instead it relies on a virtual function:

Employee::hasSalary()

If hasSalary() == true → salary is given 💵  
If false → “King don’t need salary” 👑  

This makes the system:
✔ extensible  
✔ clean  
✔ decoupled from concrete types  

────────────────────────────
🚀 Build & Run

make  
./ems  

────────────────────────────
🧪 Example

auto dev  = make_shared<Developer>("Hayk");  
auto king = make_shared<President>("Vardan");  

repo.addEmployee(dev);  
repo.addEmployee(king);  

repo.giveSalary(dev);   → Successfully 💰  
repo.giveSalary(king);  → King don’t need salary 👑  

────────────────────────────
🔒 Safety

The project uses:
✔ std::shared_ptr  
✔ virtual destructors  
✔ polymorphism  

This guarantees:
❌ no double delete  
❌ no dangling pointers  
❌ no memory leaks  

────────────────────────────
🔥 Summary

This is a modern C++ Employee Management System
built with proper OOP design and safe memory management.

