# 🍕 Pizza Builder - Decorator Pattern Implementation

A C++ implementation of the Decorator Pattern for building customizable pizzas. This project demonstrates how to dynamically add toppings and sauces to pizzas at runtime without modifying existing code.

## 📋 Table of Contents
- [Overview](#overview)
- [Architecture](#architecture)
  - [Advantages & Disadvantages](#advantages--disadvantages)
- [Important Code Highlight](#important-code-highlight)
- [SOLID Principles](#solid-principles)
- [Main Function Actions](#main-function-actions)
- [Usage](#usage)

---

## 🎯 Overview

This project implements the **Decorator Pattern** to create a flexible pizza customization system. You can stack multiple decorators (toppings, sauces) on base pizzas to create complex combinations.

---

## 🏗️ Architecture

### Project Structure Tree

```
CPP_JANUARY_17_PizzaBuilder/
├── 📁 include/
│   ├── Pizza.hpp          (Abstract base class - Component)
│   ├── Decorator.hpp      (Base decorator - Decorator)
│   ├── TypeofPizza.hpp    (Concrete component - Margherita)
│   ├── Cheese.hpp         (Concrete decorator)
│   ├── Mushroom.hpp       (Concrete decorator)
│   └── Sauces.hpp         (Concrete decorator)
├── 📁 src/
│   ├── main.cpp
│   ├── TypeofPizza.cpp
│   ├── Cheese.cpp
│   ├── Mushroom.cpp
│   └── Sauces.cpp
└── Makefile
```

### Class Hierarchy Tree

```
                Pizza (Interface)
                    |
        ┌───────────┴───────────┐
        |                       |
   Margherita            BaseDecorator
  (Component)           (Decorator)
                            |
            ┌───────────────┼───────────────┐
            |               |               |
        Cheese          Mushroom         Sauce
     (Decorator)      (Decorator)     (Decorator)
```

### ⚖️ Advantages & Disadvantages

| Aspect | Advantages ✅ | Disadvantages ❌ |
|--------|--------------|------------------|
| **Flexibility** | Can combine decorators in any order at runtime | Need to create many small classes |
| **Extensibility** | Easy to add new toppings without changing existing code | Complex nesting can be hard to read/debug |
| **Composition** | Build complex objects from simple parts | Performance overhead from multiple indirections |
| **Single Responsibility** | Each decorator has one clear purpose | Memory overhead from chaining unique_ptrs |
| **Type Safety** | Compile-time type checking with C++ | More boilerplate code compared to simple inheritance |
| **Testing** | Easy to test each decorator independently | Requires understanding of the pattern |

---

## ⭐ Important Code Highlight

The **core of the Decorator Pattern** lies in the `BaseDecorator` class and how decorators wrap pizzas:

```cpp
// BaseDecorator.hpp - The foundation of our decorator pattern
class BaseDecorator : public Pizza {
protected:
    virtual ~BaseDecorator() = default;
    std::unique_ptr<Pizza> p;  // 🔑 Key: Wraps a Pizza component
};
```

**Why this matters:** Each decorator holds a reference to a `Pizza` object, allowing decorators to be chained together. When you call `description()` or `cost()`, each decorator adds its own functionality before/after delegating to the wrapped pizza.

**Usage Example:**
```cpp
// Creating a pizza with multiple decorators
std::unique_ptr<Pizza> myPizza(
    std::make_unique<Sauce>(
        std::make_unique<Mushroom>(
            std::make_unique<Cheese>(
                std::make_unique<Margherita>()
            )
        )
    )
);
```

This creates: **Margherita + Cheese + Mushroom + Sauce** 🍕🧀🍄🥫

---

## 🎓 SOLID Principles

This project follows several **SOLID principles**:

### 1. **Single Responsibility Principle (SRP)** ✅
- Each class has one responsibility:
  - `Pizza` → Defines the interface
  - `Margherita` → Represents a specific pizza type
  - `Cheese`, `Mushroom`, `Sauce` → Each adds one specific topping/sauce

### 2. **Open/Closed Principle (OCP)** ✅
- **Where:** The decorator pattern implementation in `Decorator.hpp` and concrete decorators
- **Why:** You can add new toppings (e.g., `Pepperoni`) without modifying existing pizza classes or decorators. Just create a new decorator class inheriting from `BaseDecorator`.

### 3. **Liskov Substitution Principle (LSP)** ✅
- **Where:** All decorators inherit from `Pizza` interface
- **Why:** Any decorator or concrete pizza can be used wherever a `Pizza` object is expected. They all implement `description()` and `cost()` correctly.

### 4. **Interface Segregation Principle (ISP)** ✅
- **Where:** The `Pizza` interface defines only essential methods (`description()`, `cost()`)
- **Why:** Clients depend only on what they need, not on unnecessary methods.

### 5. **Dependency Inversion Principle (DIP)** ✅
- **Where:** Decorators depend on the `Pizza` abstraction (`std::unique_ptr<Pizza>`) not concrete implementations
- **Why:** High-level modules (decorators) don't depend on low-level modules (specific pizza types). Both depend on the `Pizza` abstraction.

---

## 📄 Main Function Actions

The `main()` function demonstrates the complete pizza ordering workflow with file operations and time management:

### 1. **Create Pizza with Decorators** 🍕
```cpp
std::unique_ptr<Pizza> myPizza(
    std::make_unique<Sauce>(
        std::make_unique<Mushroom>(
            std::make_unique<Cheese>(
                std::make_unique<Margherita>()
            )
        )
    )
);
```

### 2. **Get Current Time** ⏰
```cpp
time_t now = time(nullptr);  // Gets current system time
```

### 3. **Create and Write to `offer.txt` File** 📝
The program creates/overwrites an `offer.txt` file and writes:
- Pizza description (all toppings combined)
- Total cost
- Ready time (current time + 600 seconds = **10 minutes**)

```cpp
logToFile.open("offer.txt", std::ios_base::trunc); 
logToFile << "Pizza Description: " << myPizza->description() << std::endl;
logToFile << "Total Cost: " << myPizza->cost() << "$" << std::endl;
logToFile << "Your offer should be ready in " << ctime(&(now += 600));
```

### 4. **Read and Print Offer Information** 🖨️
After writing, the program reads the file line by line and prints all information to the console.

### 5. **Display Reminder** 🔔
When the program detects the line containing "Your", it prints a reminder message with the pickup time:
```
Don't forget take your order in [time]
```

**Complete Flow:**
1. Create pizza → 2. Get current time → 3. Write to file → 4. Read from file → 5. Print to console → 6. Show reminder

---

## 🚀 Usage

Build and run the project:

```bash
make
./pizza_builder
```

The program creates a pizza with multiple toppings and writes the order details to `offer.txt`.

---

## 📝 License

This is an educational project demonstrating design patterns in C++.
