#include "Animal_Classes.hpp"
#include <vector>
#include <functional>
#include <iostream>

struct TestCase {
    std::string name;
    std::function<void()> fn;
    std::vector<std::vector<std::string>> expected_groups;
    bool allow_empty_output = false;
};

int main() {
    std::vector<TestCase> tests;

    // Lion
    tests.push_back(TestCase{
        "Lion.Roar",
        [](){ Lion l("Simba", 7); l.Roar(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Roar this lion is" } }
    });

    tests.push_back(TestCase{
        "Lion.MakeSound",
        [](){ Lion l("Simba"); l.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Just listen" } }
    });

    tests.push_back(TestCase{
        "Lion.Swim",
        [](){ Lion l; l.Swim(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Lion swims" } }
    });

    tests.push_back(TestCase{
        "Lion.Walk",
        [](){ Lion l; l.Walk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Lion walks" } }
    });

    tests.push_back(TestCase{
        "Lion.Feddble",
        [](){ Lion l; l.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Lion feddble" } }
    });

    // Tiger
    tests.push_back(TestCase{
        "Tiger.Jump",
        [](){ Tiger t("Shere Khan", 5); t.Jump(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Your tiger jump", "meters" } }
    });

    tests.push_back(TestCase{
        "Tiger.MakeSound",
        [](){ Tiger t; t.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Just listen" } }
    });

    tests.push_back(TestCase{
        "Tiger.Swim",
        [](){ Tiger t; t.Swim(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Tiger swims" } }
    });

    tests.push_back(TestCase{
        "Tiger.Walk",
        [](){ Tiger t; t.Walk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Tiger walks" } }
    });

    tests.push_back(TestCase{
        "Tiger.Feddble",
        [](){ Tiger t; t.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Tiger feddble" } }
    });

    // Elephant
    tests.push_back(TestCase{
        "Elephant.UseTrunk",
        [](){ Elephant e; e.UseTrunk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Water! Water! Water!" } }
    });

    tests.push_back(TestCase{
        "Elephant.MakeSound",
        [](){ Elephant e; e.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Just listen" } }
    });

    tests.push_back(TestCase{
        "Elephant.Walk",
        [](){ Elephant e; e.Walk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Elephant walks" } }
    });

    tests.push_back(TestCase{
        "Elephant.Feddble",
        [](){ Elephant e; e.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Elephant feddble" } }
    });

    // Eagle
    tests.push_back(TestCase{
        "Eagle.Soar",
        [](){ Eagle e; e.Soar(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "I'm trying to find a victim" } }
    });

    tests.push_back(TestCase{
        "Eagle.MakeSound",
        [](){ Eagle e; e.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Just listen" } }
    });

    tests.push_back(TestCase{
        "Eagle.Fly",
        [](){ Eagle e; e.Fly(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Eagle flies" } }
    });

    tests.push_back(TestCase{
        "Eagle.Walk",
        [](){ Eagle e; e.Walk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Eagle walks" } }
    });

    tests.push_back(TestCase{
        "Eagle.Feddble",
        [](){ Eagle e; e.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Eagle feddble" } }
    });

    // Parrot
    tests.push_back(TestCase{
        "Parrot.Speak",
        [](){ Parrot p("Polly", "Caw"); p.Speak(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Caw" } }
    });

    tests.push_back(TestCase{
        "Parrot.MakeSound",
        [](){ Parrot p; p.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Just listen" } }
    });

    tests.push_back(TestCase{
        "Parrot.Fly",
        [](){ Parrot p; p.Fly(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Parrot flies" } }
    });

    tests.push_back(TestCase{
        "Parrot.Walk",
        [](){ Parrot p; p.Walk(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Parrot walks" } }
    });

    tests.push_back(TestCase{
        "Parrot.Feddble",
        [](){ Parrot p; p.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Parrot feddble" } }
    });

    // Snake
    tests.push_back(TestCase{
        "Snake.Hiss",
        [](){ Snake s; s.Hiss(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "hssss" } }
    });

    tests.push_back(TestCase{
        "Snake.MakeSound",
        [](){ Snake s; s.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "just listen" } }
    });

    tests.push_back(TestCase{
        "Snake.Swim",
        [](){ Snake s; s.Swim(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Snake swims" } }
    });

    tests.push_back(TestCase{
        "Snake.Feddble",
        [](){ Snake s; s.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Snake feddble" } }
    });

    // Crocodile
    tests.push_back(TestCase{
        "Crocodile.Snap",
        [](){ Crocodile c("Croc", 201); c.Snap(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Your crocodile can bite" } }
    });

    tests.push_back(TestCase{
        "Crocodile.MakeSound",
        [](){ Crocodile c; c.MakeSound(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "just listen" } }
    });

    tests.push_back(TestCase{
        "Crocodile.Swim",
        [](){ Crocodile c; c.Swim(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Crocodile swims" } }
    });

    tests.push_back(TestCase{
        "Crocodile.Feddble",
        [](){ Crocodile c; c.Feddble(); },
        std::vector<std::vector<std::string>>{ std::vector<std::string>{ "Crocodile feddble" } }
    });

    // Запуск всех тестов
    bool all_passed = true;
    for (auto& t : tests) {
        try {
            std::cout << "Running: " << t.name << std::endl;
            t.fn();
        } catch (std::exception& e) {
            std::cout << "ERROR in " << t.name << ": " << e.what() << std::endl;
            all_passed = false;
        } catch (...) {
            std::cout << "UNKNOWN ERROR in " << t.name << std::endl;
            all_passed = false;
        }
    }

    if (all_passed)
        std::cout << "\nALL TESTS SUCCESSFUL ✅" << std::endl;
    else
        std::cout << "\nSOME TESTS FAILED ❌" << std::endl;

    return 0;
}

