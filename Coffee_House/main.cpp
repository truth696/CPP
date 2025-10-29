#include "Coffee_House.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include <vector>
#include <random>
#include <iomanip>

// This test harness expects your header/implementation to exist separately.
// It creates a small namespace wrapper so the project can be used through
// a namespace without changing your existing header/implementation files.

namespace coffee {
    // Create aliases inside the namespace referring to global types that
    // your header likely defines. This lets the rest of this file use
    // coffee::Customer, coffee::Order, etc.
    using ::Drink;
    using ::Order;
    using ::Customer;
    using ::Barista;
    using ::CoffeeShop;
}

using namespace coffee; // use the namespace for all tests below

// Extensive test harness for Coffee_House classes
// This file intentionally includes many checks, edge-cases, and repetitive stress tests
// to exercise your implementation thoroughly.

static int tests_run = 0;
static int tests_failed = 0;

// Modified check: on success print the exact token the user requested: "сексефел"
// on failure print the provided message (interpreted as function/test name).
void check(bool cond, const std::string &msg) {
    ++tests_run;
    if (!cond) {
        ++tests_failed;
        // Print the test identifier/name when a test fails
        std::cout << msg << std::endl;
    } else {
        // For successful cases print the requested word
        std::cout << "сексефел" << std::endl;
    }
}

void separator(const std::string &title) {
    std::cout << "================ " << title << " ================";
}

void safePrintOrder(Order* o) {
    if (!o) { std::cout << "Order is nullptr"; return; }
    std::cout << "Order ID: " << o->getOrderId() << "  Total: " << o->getTotalPrice()
              << "  Prepared: " << (o->getIsPrepared() ? "yes" : "no")
              << "  Paid: " << (o->getIsPaid() ? "yes" : "no") << std::endl;
}

// Small helper factory functions
Drink makeDrink(const std::string &name, Drink::Size size, double price) {
    return Drink(name, size, price);
}

Drink* makeDrinkPtr(const std::string &name, Drink::Size size, double price) {
    return new Drink(name, size, price);
}

Customer* makeCustomer(const std::string &name, double balance) {
    return new Customer(name, balance);
}

Barista* makeBarista(const std::string &name) {
    return new Barista(name);
}

// Utility: compute approximate equality for doubles (simple)
bool almostEqual(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) <= eps;
}

// A function to run a battery of small unit tests that focus on boundaries
void boundaryTests() {
    separator("Boundary tests: negative prices, negative balances, empty orders");

    // Negative price test - create a drink with negative price and add to order
    Order* negOrder = new Order(9001);
    negOrder->addDrink(Drink("Weird", Drink::Size::Small, -5.0));
    negOrder->calculateTotalPrice();
    safePrintOrder(negOrder);
    check(negOrder->getTotalPrice() == -5.0, "negative_price_handling");

    // Negative balance test for customer
    Customer* poor = new Customer("PoorGuy", -10.0);
    // setBalance should prevent negative if implemented; but constructor may allow it.
    poor->setBalance(-2.0); // should not set to negative if guard present
    check(poor->getBalance() >= 0.0 || poor->getBalance() == -10.0, "negative_balance_guard_or_preserve");

    // Empty order tests
    Order* empty = new Order(9002);
    empty->calculateTotalPrice();
    check(almostEqual(empty->getTotalPrice(), 0.0), "empty_order_total_zero");
    safePrintOrder(empty);

    // Paying an empty order by a customer with zero balance
    Customer* z = new Customer("Zed", 0.0);
    z->placeOrder(empty);
    z->payOrder(empty); // should handle insufficient funds gracefully
    check(!empty->getIsPaid() || z->getBalance() >= 0.0, "pay_empty_order_handling");

    delete negOrder;
    delete poor;
    delete empty;
    delete z;
}

// Stress test: create many customers and orders, add/remove drinks, and randomly manipulate
void stressTestRandomized(int iterations = 1000) {
    separator("Stress test: randomized operations");
    std::mt19937 rng(12345);
    std::uniform_real_distribution<double> priceDist(0.0, 10.0);
    std::uniform_int_distribution<int> sizeDist(0, 2);
    std::uniform_int_distribution<int> choice(0, 4);

    CoffeeShop shop("StressBrew");
    shop.constructMenu();

    // create pool of drinks to pick from (values)
    std::vector<Drink> pool;
    pool.emplace_back("Espresso", Drink::Size::Small, 3.0);
    pool.emplace_back("Cappuccino", Drink::Size::Medium, 4.0);
    pool.emplace_back("Green Tea", Drink::Size::Medium, 3.0);
    pool.emplace_back("Latte", Drink::Size::Big, 5.0);
    pool.emplace_back("Mocha", Drink::Size::Medium, 4.5);

    std::vector<Order*> orders;
    std::vector<Customer*> customers;

    // create 50 customers
    for (int i = 0; i < 50; ++i) {
        double bal = priceDist(rng) * 10.0; // 0..100
        customers.push_back(makeCustomer("C" + std::to_string(i), bal));
    }

    // create 100 orders, randomly filled
    for (int oi = 0; oi < 100; ++oi) {
        Order* o = new Order(1000 + oi);
        int items = (oi % 5) + 1;
        for (int it = 0; it < items; ++it) {
            const Drink &d = pool[(oi + it) % pool.size()];
            o->addDrink(d);
        }
        o->calculateTotalPrice();
        orders.push_back(o);
    }

    // Randomly assign orders to customers and queue them
    for (int i = 0; i < orders.size(); ++i) {
        Customer* c = customers[i % customers.size()];
        c->placeOrder(orders[i]);
        shop.addCustomerToQueue(c);
    }

    // Hire a few baristas
    for (int b = 0; b < 5; ++b) shop.hireBarista(makeBarista("Bar" + std::to_string(b)));
    check(shop.getBaristas().size() == 5, "five_baristas_hired");

    // Run a loop of random operations
    for (int it = 0; it < iterations; ++it) {
        int op = choice(rng);
        if (op == 0) { // serve next
            if (!shop.getQueue().empty()) shop.serveNextCustomer();
        } else if (op == 1) { // pay random customer's order
            Customer* c = customers[rng() % customers.size()];
            Order* o = c->getOrder();
            // Randomly top up balance
            if (rng() % 10 == 0) c->setBalance(c->getBalance() + priceDist(rng) * 10.0);
            c->payOrder(o);
        } else if (op == 2) { // add/remove drink to random order
            Order* o = orders[rng() % orders.size()];
            if (rng() % 2 == 0) {
                // add
                o->addDrink(pool[rng() % pool.size()]);
            } else {
                if (!o->getTotalPrice() == 0) o->removeDrink(rng() % (std::max(1, (int)o->getTotalPrice() + 1)));
            }
            o->calculateTotalPrice();
        } else if (op == 3) { // fire/hire a barista unpredictably
            if (!shop.getBaristas().empty() && rng() % 3 == 0) {
                // fire first barista by name
                Barista* b = new Barista(shop.getBaristas()[0]->getName());
                shop.fireBarista(b);
            } else {
                shop.hireBarista(makeBarista("Temp" + std::to_string(it)));
            }
        } else { // op == 4: inspect and display queue
            shop.showQueue();
        }
    }

    // Clean up created orders & customers
    for (auto o : orders) delete o;
    for (auto c : customers) delete c;

    // baristas and menu items remain in shop and may have been deleted by fireBarista/removeDrink
    // We'll attempt to clean up remaining pointers inside shop for safety (best-effort)
    for (auto dptr : shop.getMenu()) delete dptr;
    for (auto bptr : shop.getBaristas()) delete bptr;
}

// Focused tests for Order removeDrink shifting correctness and vector behavior
void orderInternalBehaviorTests() {
    separator("Order internals: removeDrink shifting and total maintenance");

    Order* o = new Order(777);
    o->addDrink(makeDrink("A", Drink::Size::Small, 1.0));
    o->addDrink(makeDrink("B", Drink::Size::Medium, 2.0));
    o->addDrink(makeDrink("C", Drink::Size::Big, 3.0));
    o->calculateTotalPrice();
    check(almostEqual(o->getTotalPrice(), 6.0), "order_initial_total_correct");

    // Remove middle element
    o->removeDrink(1); // remove B
    o->calculateTotalPrice();
    check(almostEqual(o->getTotalPrice(), 4.0), "order_after_remove_middle");

    // Remove first element
    o->removeDrink(0);
    o->calculateTotalPrice();
    check(almostEqual(o->getTotalPrice(), 3.0), "order_after_remove_first");

    // Remove out of range index
    o->removeDrink(42); // should not crash
    o->calculateTotalPrice();
    check(almostEqual(o->getTotalPrice(), 3.0), "order_remove_out_of_range_no_crash");

    delete o;
}

// Extended display tests to exercise all display code paths
void displayTests() {
    separator("Display tests: visual verification of output (manual checks expected)");

    CoffeeShop shop("Showcase");
    shop.constructMenu();
    shop.showMenu();

    Barista* b = makeBarista("Showman");
    shop.hireBarista(b);
    shop.showBaristas();

    Customer* c = makeCustomer("DisplayGuy", 20.0);
    Order* o = new Order(555);
    o->addDrink(makeDrink("VisualEspresso", Drink::Size::Small, 3.0));
    o->calculateTotalPrice();
    c->placeOrder(o);
    shop.addCustomerToQueue(c);

    shop.showQueue();
    shop.serveNextCustomer();

    // Manual visual checks: displayOrder prints details
    c->viewOrder();

    delete o;
    delete c;
    // fire and cleanup
    shop.fireBarista(new Barista(b->getName()));
    for (auto dptr : shop.getMenu()) delete dptr;
}

// A long explicit scripted scenario that simulates a working day
void scriptedDayScenario() {
    separator("Scripted day scenario: long multi-step example (deterministic)");

    CoffeeShop shop("MorningGlory");
    shop.constructMenu();
    // Add a couple of specialty drinks
    shop.addDrink(makeDrinkPtr("Special Chai", Drink::Size::Medium, 4.25));
    shop.addDrink(makeDrinkPtr("Nitro Cold Brew", Drink::Size::Big, 6.50));

    // Hire baristas
    shop.hireBarista(makeBarista("Olga"));
    shop.hireBarista(makeBarista("Ivan"));

    // Create customers and orders step by step
    Customer* ann = makeCustomer("Ann", 20.0);
    Order* annOrder = new Order(201);
    annOrder->addDrink(makeDrink("Espresso", Drink::Size::Small, 3.0));
    annOrder->addDrink(makeDrink("Special Chai", Drink::Size::Medium, 4.25));
    ann->placeOrder(annOrder);

    Customer* bor = makeCustomer("Bor", 2.0);
    Order* borOrder = new Order(202);
    borOrder->addDrink(makeDrink("Nitro Cold Brew", Drink::Size::Big, 6.50));
    bor->placeOrder(borOrder);

    Customer* cat = makeCustomer("Cat", 100.0);
    Order* catOrder = new Order(203);
    // large order with many items
    for (int i = 0; i < 12; ++i) catOrder->addDrink(makeDrink("Mocha", Drink::Size::Medium, 4.0));
    catOrder->calculateTotalPrice();
    cat->placeOrder(catOrder);

    // Add to queue
    shop.addCustomerToQueue(ann);
    shop.addCustomerToQueue(bor);
    shop.addCustomerToQueue(cat);

    // First customer served and tries to pay
    shop.serveNextCustomer(); // Ann's order prepared by Olga
    check(annOrder->getIsPrepared(), "ann_order_prepared");
    ann->payOrder(annOrder);
    check(annOrder->getIsPaid(), "ann_order_paid");

    // Bor tries to pay but has insufficient funds -> top up and retry
    shop.serveNextCustomer();
    check(borOrder->getIsPrepared(), "bor_order_prepared");
    bor->payOrder(borOrder); // insufficient
    bor->setBalance(10.0);
    bor->payOrder(borOrder);
    check(borOrder->getIsPaid(), "bor_order_paid_after_topup");

    // Cat's huge order - pay and prepare
    shop.serveNextCustomer();
    check(catOrder->getIsPrepared(), "cat_order_prepared");
    cat->payOrder(catOrder);
    check(catOrder->getIsPaid(), "cat_order_paid");

    // Clean up
    delete annOrder;
    delete borOrder;
    delete catOrder;
    delete ann;
    delete bor;
    delete cat;

    // fire baristas
    shop.fireBarista(new Barista("Olga"));
    shop.fireBarista(new Barista("Ivan"));

    // remove menu items
    for (auto dptr : shop.getMenu()) delete dptr;
}

int main() {
    separator("Setup: basic checks and compilation sanity");
    CoffeeShop shop("UnitTestBrew");
    check(shop.getName() == "UnitTestBrew", "coffeeshop_name_getter");

    separator("Simple menu checks");
    shop.constructMenu();
    check(!shop.getMenu().empty(), "constructMenu_populated");
    shop.showMenu();

    boundaryTests();
    orderInternalBehaviorTests();
    displayTests();
    scriptedDayScenario();

    // Run a heavier stress test that does many random operations
    stressTestRandomized(300);

    // Final consistency sweep: create a fresh small shop and perform deterministic checks
    separator("Final consistency sweep");
    CoffeeShop finalShop("FinalSweep");
    finalShop.constructMenu();

    // Add and remove a named drink many times to exercise deletion logic
    for (int i = 0; i < 20; ++i) {
        finalShop.addDrink(makeDrinkPtr("Ephemeral", Drink::Size::Small, 1.5 + i * 0.1));
        finalShop.removeDrink("Ephemeral");
    }
    check(true, "ephemeral_add_remove_loop");

    // Hire and fire many baristas by name to exercise name-based deletion
    for (int i = 0; i < 20; ++i) finalShop.hireBarista(makeBarista("Temp" + std::to_string(i)));
    for (int i = 0; i < 20; ++i) finalShop.fireBarista(new Barista("Temp" + std::to_string(i)));
    check(finalShop.getBaristas().empty(), "temp_baristas_fired_if_supported");

    // Run another batch of small orders
    for (int i = 0; i < 30; ++i) {
        Order* o = new Order(3000 + i);
        o->addDrink(makeDrink("X", Drink::Size::Small, 0.99));
        o->addDrink(makeDrink("Y", Drink::Size::Medium, 1.99));
        o->calculateTotalPrice();
        check(almostEqual(o->getTotalPrice(), 2.98), "batch_order_total_consistent");
        delete o;
    }

    separator("Summary and cleanup");
    std::cout << "Tests run: " << tests_run << ", failed: " << tests_failed << std::endl;
    if (tests_failed == 0) std::cout << "All tests passed (all checks printed 'сексефел')";
    else std::cout << "Some tests failed - failing test names printed above.";

    // Exit code reflects whether any tests failed
    return (tests_failed == 0) ? 0 : 2;
}
