# 🔒 Titan Security System

A modern, object-oriented security system built with C++ following SOLID principles. The Titan Security System monitors multiple sensor types, triggers alarms, and logs events for comprehensive home security management.

---

## 📋 Table of Contents

- [Features](#-features)
- [Advantages](#-advantages)
- [Project Structure](#-project-structure)
- [Architecture & Design Principles](#-architecture--design-principles)
- [Quick Start](#-quick-start)
- [Usage Example](#-usage-example)
- [Building the Project](#-building-the-project)

---

## ✨ Features

- 🎯 **Multiple Sensor Types**: Door, Motion, and Heat sensors
- 🚨 **Intelligent Alarm System**: Severity-based alarm triggering
- 📝 **Event Logging**: Comprehensive logging to files
- 🔄 **Mode Management**: Day/Away security modes
- 🛡️ **Extensible Architecture**: Interface-based design for easy extension

---

## 🎯 Advantages

### Design & Architecture Advantages

| Aspect | Advantage | Description |
|--------|-----------|-------------|
| 🔌 **Interface Segregation** | Clean abstractions | Small, focused interfaces (`ISystem`, `ISensor`, `IAlarms`) enable loose coupling |
| 🎨 **Single Responsibility** | Maintainable code | Each class has one clear purpose (Sensors poll, AlarmSystem triggers, LogFile logs) |
| 🔄 **Open/Closed Principle** | Extensible | New sensor types can be added without modifying existing code |
| 🔀 **Dependency Inversion** | Testable | Dependencies on abstractions allow easy mocking and testing |
| 🧩 **Polymorphism** | Flexible behavior | Runtime polymorphism enables dynamic behavior selection |
| 📦 **Modularity** | Clear separation | Clear separation between sensor management, alarms, and logging |

### Technical Advantages

| Feature | Benefit | Impact |
|---------|---------|--------|
| 💾 **Header-Only Interfaces** | Fast compilation | Interfaces can be included without implementation overhead |
| 🎯 **Type Safety** | Reduced errors | Strong typing with C++ prevents runtime type errors |
| 📚 **Reusability** | DRY principle | Components can be reused across different security configurations |
| 🔧 **Easy Testing** | Quality assurance | Interface-based design facilitates unit testing and mocking |
| 🚀 **Performance** | Efficient execution | Compiled C++ code provides high performance for real-time monitoring |

---

## 📁 Project Structure

```
TitanSecurityProject/
│
├── 📂 include/                    # Header files (interfaces & implementations)
│   ├── 🔵 IAlarms.hpp            # Alarm interface (abstraction)
│   ├── 🔵 ILogFile.hpp           # Logging interface (abstraction)
│   ├── 🔵 IReport.hpp            # Reporting interface (abstraction)
│   ├── 🔵 ISensor.hpp            # Sensor interface (abstraction)
│   ├── 🔵 ISystem.hpp            # System interface (abstraction)
│   ├── 🟢 AlarmSystem.hpp        # Alarm implementation
│   ├── 🟢 LogFile.hpp            # Logging implementation
│   ├── 🟢 Sensors.hpp            # Sensor management implementation
│   └── 🟢 TitanSecurity.hpp      # Main system class
│
├── 📂 src/                        # Source files (implementations)
│   ├── 🟡 AlarmSystem.cpp        # Alarm system logic
│   ├── 🟡 IReport.cpp            # Report generation
│   ├── 🟡 LogFile.cpp            # File logging operations
│   ├── 🟡 main.cpp               # Application entry point
│   ├── 🟡 Sensors.cpp            # Sensor polling logic
│   └── 🟡 TitanSecurty.cpp       # System mode management
│
├── 🔧 Makefile                   # Build configuration
└── 📖 README.md                  # Project documentation
```

**Legend:**
- 🔵 = Interface (Abstract class)
- 🟢 = Implementation header
- 🟡 = Implementation source

---

## 🏗️ Architecture & Design Principles

### Object-Oriented Programming (OOP) 🎯

The Titan Security System leverages core OOP principles:

#### **1. Encapsulation 📦**
- **Data hiding**: Sensor data (`sensorNames`, `sensorData`) is private within the `Sensors` class
- **Controlled access**: Public interfaces provide controlled access to functionality
- **Information hiding**: Implementation details are hidden behind abstractions

#### **2. Inheritance 🔗**
- **Interface inheritance**: `TitanSystem` implements `ISystem` interface
- **Multiple inheritance**: `Sensors` inherits from both `ISensor` and `AlarmSystem`
- **Code reuse**: Common functionality is shared through base classes

#### **3. Polymorphism 🔄**
- **Virtual functions**: Interfaces use pure virtual functions (`= 0`)
- **Runtime binding**: `pollSensors(ISystem* s)` accepts any `ISystem` implementation
- **Dynamic dispatch**: Behavior determined at runtime based on object type

#### **4. Abstraction 🎨**
- **Abstract interfaces**: `ISystem`, `ISensor`, `IAlarms` define contracts
- **Implementation hiding**: Users interact with interfaces, not concrete classes
- **Conceptual modeling**: Classes represent real-world security system concepts

---

### SOLID Principles 🏛️

The project architecture follows all five SOLID principles:

#### **1. S - Single Responsibility Principle ✅**
Each class has one reason to change:

| Class | Responsibility |
|-------|---------------|
| `Sensors` | Manage sensor polling and data collection |
| `AlarmSystem` | Handle alarm triggering logic |
| `LogFile` | Manage file logging operations |
| `TitanSystem` | Control system mode and armed state |

#### **2. O - Open/Closed Principle ✅**
- **Open for extension**: New sensor types can be added by implementing `ISensor`
- **Closed for modification**: Existing code doesn't need changes when adding new features
- **Interface-based**: Extensions work through well-defined interfaces

#### **3. L - Liskov Substitution Principle ✅**
- **Substitutability**: Any `ISystem` implementation can replace another without breaking functionality
- **Behavioral compatibility**: Derived classes maintain the contract of base interfaces
- **Type safety**: Interfaces ensure consistent behavior across implementations

#### **4. I - Interface Segregation Principle ✅**
Small, focused interfaces instead of large monolithic ones:

- `ISystem` → System mode management (3 methods)
- `ISensor` → Sensor operations (3 methods)
- `IAlarms` → Alarm triggering (1 method)
- `ILogFile` → Logging operations

#### **5. D - Dependency Inversion Principle ✅**
- **Abstraction dependency**: `pollSensors(ISystem* s)` depends on `ISystem` abstraction
- **No concrete coupling**: High-level modules don't depend on low-level implementations
- **Inversion of control**: Dependencies flow toward abstractions

---

## 🚀 Quick Start

### Prerequisites
- C++17 compatible compiler (g++, clang++, etc.)
- Make utility

### Building

```bash
# Clone or navigate to the project directory
cd CPP_JANUARY_15_TitanSecurityProject

# Build the project
make

# Run the executable
./ems
```

### Cleaning Build Artifacts

```bash
make clean
```

---

## 💻 Usage Example

Here's a minimal example demonstrating how to use the Titan Security System:

```cpp
#include "TitanSecurity.hpp"
#include <iostream>

int main() {
    // 🏠 Create a security system instance
    TitanSystem homeSecurity;
    
    // 🔧 Set system mode to "Away"
    homeSecurity.SetMode("Away");
    
    // 📊 Poll all sensors for current status
    homeSecurity.pollSensors(&homeSecurity);
    
    // 🔔 Simulate a sensor event (Door opens)
    homeSecurity.SimulatesimulateSensorInput(0, 1);
    
    // 📊 Poll sensors again to detect the event
    homeSecurity.pollSensors(&homeSecurity);
    
    return 0;
}
```

### Example Output

```
--- Titan Security System v1.0 ---
System Mode: Away
System Armed: true
Polling 3 sensors...
[Event] Front Door opened (Entry)
🚨 ALARM TRIGGERED: Security Breach
```

---

## 🎓 Key Design Patterns

The project demonstrates several design patterns:

- **Strategy Pattern**: Different alarm behaviors based on system mode
- **Observer Pattern**: Sensors notify the system of state changes
- **Dependency Injection**: `ISystem*` injected into `pollSensors()`
- **Template Method**: Interface defines structure, implementations fill details

---

## 🔍 System Modes

The Titan Security System supports multiple operational modes:

| Mode | Description | Armed State |
|------|-------------|-------------|
| `Day` | Daytime mode with reduced sensitivity | `false` |
| `Away` | Full security when occupants are away | `true` |
| `Night` | Night mode with motion sensor activation | `true` |

---

## 📝 Sensor Types

| Sensor Type | Index | Data Type | Example Values |
|-------------|-------|-----------|----------------|
| 🚪 Door Sensor | 0 | Boolean (0/1) | 0 = Closed, 1 = Open |
| 👁️ Motion Sensor | 1 | Boolean (0/1) | 0 = No Motion, 1 = Motion Detected |
| 🔥 Heat Sensor | 2 | Integer (Celsius) | 25 = Normal, 60+ = Fire Risk |

---

## 🛠️ Extension Points

To extend the system, you can:

1. **Add new sensor types**: Implement `ISensor` interface
2. **Create custom alarms**: Implement `IAlarms` interface
3. **Add logging backends**: Implement `ILogFile` interface
4. **Extend system modes**: Modify `TitanSystem::SetMode()` logic

---

## 📄 License

This project is part of a security system implementation demonstration.

---

## 👨‍💻 Author

Titan Security Project - OOP & SOLID Principles Demonstration

---

**Built with ❤️ using Modern C++ and SOLID Design Principles** 🏛️
