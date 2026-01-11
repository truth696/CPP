# 🏢 Employee Management System

A modern C++17 Employee Management System (EMS) designed with object-oriented principles, featuring polymorphic employee types, automatic ID generation, and comprehensive payroll management.

## 📋 Table of Contents

- [Features](#-features)
- [Employee Types](#-employee-types)
- [Architecture](#-architecture)
- [Project Structure](#-project-structure)
- [Building the Project](#-building-the-project)
- [Usage Examples](#-usage-examples)
- [Design Patterns](#-design-patterns)
- [Safety & Best Practices](#-safety--best-practices)

## ✨ Features

- 🔄 **Polymorphic Design** - Extensible employee hierarchy with virtual functions
- 🆔 **Automatic ID Generation** - Unique identifier assignment for each employee
- 💰 **Payroll Management** - Integrated salary calculation and distribution system
- 🗄️ **Employee Repository** - Centralized employee storage and management
- 🛡️ **Memory Safety** - Smart pointer usage prevents memory leaks
- 🎯 **Type Safety** - No dynamic_cast, uses virtual function dispatch

## 👥 Employee Types

| Employee Type | Description | Has Salary | Base Salary |
|--------------|-------------|------------|-------------|
| 👨‍💻 **Developer** | Software development role | ✅ Yes | Base + Achievements |
| 👔 **Manager** | Team management role | ✅ Yes | Base + Achievements |
| 📊 **Accountant** | Financial management role | ✅ Yes | Base + Achievements |
| 💼 **SalesPerson** | Sales and business development | ✅ Yes | Base + Achievements |
| 👑 **President** | Executive leadership role | ❌ No | N/A |

## 🏗️ Architecture

### Class Hierarchy

```
Employee (Base Class)
├── Developer
├── Manager
├── Accountant
├── SalesPerson
└── President
```

### Key Components

- **`Employee`** - Abstract base class providing common interface
- **`ISalaried`** - Interface for salary calculation
- **`EmployeeRepository`** - Manages employee collection and operations
- **`PayrollService`** - Handles salary distribution logic
- **`Counter_id`** - Global ID generator for unique employee identification

### Design Principles

- **Polymorphism** - Virtual functions enable runtime type behavior
- **Interface Segregation** - `ISalaried` interface for salary-related operations
- **RAII** - Resource management through smart pointers
- **Open/Closed Principle** - Extensible without modifying existing code

## 📁 Project Structure

```
CPP_JANUARY_11_EmployeeManagementSystem/
│
├── include/                    # Header files
│   ├── Employee.h             # Base employee class
│   ├── Developer.h            # Developer implementation
│   ├── Manager.h              # Manager implementation
│   ├── Accountant.h           # Accountant implementation
│   ├── SalesPerson.h          # SalesPerson implementation
│   ├── President.h            # President implementation
│   ├── ISalaried.h            # Salary interface
│   ├── EmployeeRepository.h   # Employee storage and management
│   ├── PayrollService.h       # Payroll operations
│   └── Counter_id.h           # ID generation utility
│
├── src/                        # Source files
│   ├── main.cpp               # Application entry point
│   └── *.cpp                  # Implementation files
│
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## 🔨 Building the Project

### Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- Make utility

### Build Instructions

```bash
# Compile the project
make

# Run the executable
./ems

# Clean build artifacts
make clean
```

### Build Configuration

- **C++ Standard**: C++17
- **Compiler Flags**: `-Wall -Wextra` for enhanced warnings
- **Output**: `ems` executable

## 💡 Usage Examples

### Creating Employees

```cpp
#include "EmployeeRepository.h"
#include "Developer.h"
#include "President.h"

EmployeeRepository repository;

// Create employees using smart pointers
auto developer = std::make_shared<Developer>("John Doe");
auto president = std::make_shared<President>("Jane Smith");

// Add to repository
repository.addEmployee(developer);
repository.addEmployee(president);
```

### Managing Employees

```cpp
// List all employees
repository.listAllEmployee();

// Remove employee by ID
repository.removeEmployee(1);

// Process payroll
repository.giveSalary(developer);  // ✅ Salary processed
repository.giveSalary(president);  // 👑 "King don't need salary"
```

### Employee Information

Each employee type implements `printInfo()` to display:
- Employee ID (auto-generated)
- Employee name
- Role-specific information
- Salary details (if applicable)

## 🎨 Design Patterns

| Pattern | Implementation | Purpose |
|---------|---------------|---------|
| **Template Method** | Virtual functions in `Employee` | Polymorphic behavior |
| **Strategy** | `ISalaried` interface | Flexible salary calculation |
| **Repository** | `EmployeeRepository` class | Centralized data access |
| **RAII** | `std::shared_ptr` usage | Automatic memory management |

## 🛡️ Safety & Best Practices

### Memory Management

✅ **Smart Pointers** - `std::shared_ptr` prevents memory leaks  
✅ **Virtual Destructors** - Proper cleanup of polymorphic objects  
✅ **RAII** - Resource acquisition is initialization  

### Code Quality

✅ **No Raw Pointers** - All employee objects use smart pointers  
✅ **No Dynamic Cast** - Type checking via virtual functions  
✅ **Exception Safety** - `noexcept` specifications where appropriate  
✅ **Const Correctness** - Proper use of `const` qualifiers  

### Benefits

- ❌ No double deletion
- ❌ No dangling pointers  
- ❌ No memory leaks
- ✅ Thread-safe reference counting (shared_ptr)
- ✅ Automatic resource cleanup

## 📝 Notes

- The President role does not receive a salary (returns -1 from `CalculateSalary()`)
- Employee IDs are automatically incremented using a global counter
- The repository prevents duplicate entries when adding employees
- Salary calculations include achievement bonuses for salaried employees

## 🔮 Future Enhancements

Potential improvements for future versions:
- 📅 Employee attendance tracking
- 📈 Performance metrics and reporting
- 💾 Persistent storage (database integration)
- 🔍 Advanced search and filtering
- 📊 Comprehensive reporting system

---

**Built with** ❤️ **using C++17**