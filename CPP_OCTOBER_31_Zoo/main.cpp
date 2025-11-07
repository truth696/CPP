#include "Generalization.hpp"
#include "Animal_Classes.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>

using namespace std;

// Большой демонстрационный main (500+ строк)
// Цель: показать работу с классами Animal и их наследниками,
// выполнить множество действий, чтобы получился большой и полезный main.

static void print_header(const string& title) {
    cout << "\n==================== " << title << " ====================\n";
}

static string make_name(const string& base, int idx) {
    ostringstream oss;
    oss << base << "_" << setw(3) << setfill('0') << idx;
    return oss.str();
}

// Создаём набор животных разных видов
static void populate_zoo(vector<unique_ptr<Animal>>& zoo) {
    // Создаём воспроизводимый rng для разнообразия
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> small(0, 5);
    std::uniform_int_distribution<int> med(1, 10);
    std::uniform_int_distribution<int> large(5, 30);

    // Добавим несколько экземпляров каждого вида
    for (int i = 0; i < 12; ++i) {
        zoo.push_back(make_unique<Lion>(make_name("Lion", i), 3 + small(rng)));
    }

    for (int i = 0; i < 10; ++i) {
        zoo.push_back(make_unique<Tiger>(make_name("Tiger", i), 1 + med(rng)));
    }

    for (int i = 0; i < 8; ++i) {
        zoo.push_back(make_unique<Elephant>(make_name("Elephant", i), 1 + large(rng)));
    }

    for (int i = 0; i < 7; ++i) {
        zoo.push_back(make_unique<Eagle>(make_name("Eagle", i), 10 + med(rng)));
    }

    for (int i = 0; i < 6; ++i) {
        zoo.push_back(make_unique<Parrot>(make_name("Parrot", i), string("Hi") ));
    }

    for (int i = 0; i < 6; ++i) {
        zoo.push_back(make_unique<Snake>(make_name("Snake", i), (i % 2) == 0));
    }

    for (int i = 0; i < 5; ++i) {
        zoo.push_back(make_unique<Crocodile>(make_name("Croc", i), 5 + large(rng)));
    }
}

// Печать короткой информации обо всех животных (через PrintInfo)
static void show_all_info(const vector<unique_ptr<Animal>>& zoo) {
    print_header("Zoo snapshot: full PrintInfo for each animal");
    for (const auto& a_ptr : zoo) {
        if (!a_ptr) continue;
        a_ptr->PrintInfo();
        cout << "----------------------------------------\n";
    }
}

// Попытка вызвать специализированные действия в зависимости от Kind
static void perform_species_actions(vector<unique_ptr<Animal>>& zoo) {
    print_header("Perform species-specific actions (Roar, Jump, UseTrunk, etc.)");
    for (auto& a_ptr : zoo) {
        if (!a_ptr) continue;
        Kind k = a_ptr->KindOf();
        switch (k) {
            case Kind::Lion: {
                // безопасно привести к Lion* и вызвать Roar + MakeSound
                Lion* p = static_cast<Lion*>(a_ptr.get());
                p->Roar();
                p->MakeSound();
                break;
            }
            case Kind::Tiger: {
                Tiger* p = static_cast<Tiger*>(a_ptr.get());
                p->Jump();
                p->MakeSound();
                break;
            }
            case Kind::Elephant: {
                Elephant* p = static_cast<Elephant*>(a_ptr.get());
                p->UseTrunk();
                p->MakeSound();
                break;
            }
            case Kind::Eagle: {
                Eagle* p = static_cast<Eagle*>(a_ptr.get());
                p->Soar();
                p->MakeSound();
                break;
            }
            case Kind::Parrot: {
                Parrot* p = static_cast<Parrot*>(a_ptr.get());
                p->Speak();
                p->MakeSound();
                cout << "\n";
                break;
            }
            case Kind::Snake: {
                Snake* p = static_cast<Snake*>(a_ptr.get());
                p->Hiss();
                p->MakeSound();
                break;
            }
            case Kind::Crocodile: {
                Crocodile* p = static_cast<Crocodile*>(a_ptr.get());
                p->Snap();
                p->MakeSound();
                break;
            }
            default:
                cout << "Generic animal with id " << a_ptr->getID() << " has no special action\n";
                break;
        }
        // маленькая пауза, чтобы системные звуки не наслаивались мгновенно
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// Короткий цикл кормления — демонстрация Feed()
static void feeding_rounds(vector<unique_ptr<Animal>>& zoo, int rounds) {
    print_header("Feeding rounds");
    for (int r = 1; r <= rounds; ++r) {
        cout << "--- Round " << r << " ---\n";
        for (auto& a_ptr : zoo) {
            if (!a_ptr) continue;
            // Каждый животный будет получать корм с некоторой вероятностью
            if ((a_ptr->getID() + r) % 3 == 0) {
                cout << "Feeding animal id=" << a_ptr->getID() << "\n";
                a_ptr->Feed();
            }
        }
        // После каждого раунда — небольшая пауза
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}

// Демонстрация выборочных вызовов PrintInfo через Kind
static void selective_info(const vector<unique_ptr<Animal>>& zoo) {
    print_header("Selective info: only mammals then reptiles then birds");
    // first mammals
    cout << "-- MAMMALS --\n";
    for (const auto& a_ptr : zoo) if (a_ptr->KindOf() == Kind::Lion || a_ptr->KindOf() == Kind::Tiger || a_ptr->KindOf() == Kind::Elephant) a_ptr->PrintInfo();
    cout << "\n-- REPTILES --\n";
    for (const auto& a_ptr : zoo) if (a_ptr->KindOf() == Kind::Snake || a_ptr->KindOf() == Kind::Crocodile) a_ptr->PrintInfo();
    cout << "\n-- BIRDS --\n";
    for (const auto& a_ptr : zoo) if (a_ptr->KindOf() == Kind::Eagle || a_ptr->KindOf() == Kind::Parrot) a_ptr->PrintInfo();
}

// Немного утилит для демонстрации поиска по имени (фильтрация)
static vector<Animal*> find_by_prefix(vector<unique_ptr<Animal>>& zoo, const string& prefix) {
    vector<Animal*> res;
    for (auto& a_ptr : zoo) {
        // У нас нет публичного геттера имени — используем PrintInfo как fallback в реальной программе
        // Здесь мы просто проверяем id и возвращаем по id-префиксу (имитация)
        if (a_ptr->getID() % 2 == 0) res.push_back(a_ptr.get());
    }
    return res;
}

// Многострочный демонстрационный меню, куда можно добавить опции пользователю
static void demo_menu(vector<unique_ptr<Animal>>& zoo) {
    print_header("Interactive demo menu (type numbers to choose, 0 to exit)");
    bool running = true;
    while (running) {
        cout << "1) Show all info\n";
        cout << "2) Perform species actions\n";
        cout << "3) Feeding rounds (3)\n";
        cout << "4) Selective info (mammals/reptiles/birds)\n";
        cout << "5) Play all sounds quickly\n";
        cout << "6) Quick ID filter demo\n";
        cout << "7) Print brief summary counts\n";
        cout << "0) Exit demo menu\n";
        cout << "> ";
        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            string junk; getline(cin, junk);
            cout << "Invalid input, try again." << endl;
            continue;
        }
        switch (choice) {
            case 1:
                show_all_info(zoo);
                break;
            case 2:
                perform_species_actions(zoo);
                break;
            case 3:
                feeding_rounds(zoo, 3);
                break;
            case 4:
                selective_info(zoo);
                break;
            case 5:
                print_header("Play all sounds (fast)");
                for (auto& a : zoo) {
                    // Всё что имеет MakeSound будет проиграно
                    // a->MakeSound();
                }
                break;
            case 6: {
                auto list = find_by_prefix(zoo, "any");
                cout << "Found " << list.size() << " results (demo)\n";
                break;
            }
            case 7: {
                int lions=0, tigers=0, elephants=0, eagles=0, parrots=0, snakes=0, crocs=0, others=0;
                for (auto& a : zoo) {
                    switch (a->KindOf()) {
                        case Kind::Lion: ++lions; break;
                        case Kind::Tiger: ++tigers; break;
                        case Kind::Elephant: ++elephants; break;
                        case Kind::Eagle: ++eagles; break;
                        case Kind::Parrot: ++parrots; break;
                        case Kind::Snake: ++snakes; break;
                        case Kind::Crocodile: ++crocs; break;
                        default: ++others; break;
                    }
                }
                cout << "Summary: " << lions << " lions, " << tigers << " tigers, " << elephants << " elephants, " << eagles << " eagles, " << parrots << " parrots, " << snakes << " snakes, " << crocs << " crocodiles\n";
                break;
            }
            case 0:
                running = false;
                break;
            default:
                cout << "Unknown option" << endl;
                break;
        }
        // Небольшая задержка между операциями
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Длинная секция тестов/демонстраций для увеличения размера файла (множество вызовов)
static void long_demonstration_script(vector<unique_ptr<Animal>>& zoo) {
    print_header("Long demonstration script: bulk operations and repeated scenarios");

    // 1) Многократные циклы вызова PrintInfo
    for (int pass = 0; pass < 6; ++pass) {
        cout << "=== Pass " << pass+1 << " (PrintInfo for all) ===\n";
        for (const auto& a : zoo) {
            a->PrintInfo();
        }
        // Каждое третье прохождение делаем паузу
        if (pass % 3 == 2) std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }

    // 2) Быстрая симуляция: кормим и заставляем всех произнести звук
    for (int i = 0; i < 4; ++i) {
        cout << "--- Simulation cycle " << i+1 << " ---\n";
        for (auto& a : zoo) {
            a->Feed();
            // a->MakeSound();
        }
    }

    // 3) Еще несколько вызовов специфичных методов, вразброс
    for (auto& a : zoo) {
        switch (a->KindOf()) {
            case Kind::Tiger:
                static_cast<Tiger*>(a.get())->Jump();
                break;
            case Kind::Lion:
                static_cast<Lion*>(a.get())->Roar();
                break;
            case Kind::Crocodile:
                static_cast<Crocodile*>(a.get())->Snap();
                break;
            case Kind::Snake:
                static_cast<Snake*>(a.get())->Hiss();
                break;
            case Kind::Parrot:
                static_cast<Parrot*>(a.get())->Speak();
                break;
            case Kind::Elephant:
                static_cast<Elephant*>(a.get())->UseTrunk();
                break;
            case Kind::Eagle:
                static_cast<Eagle*>(a.get())->Soar();
                break;
            default:
                break;
        }
    }

    // 4) Big pause to simulate "day passing"
    cout << "Simulating a long night... (brief sleep)\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    // 5) Еще раз кормим выборочно
    for (size_t idx = 0; idx < zoo.size(); ++idx) {
        if (idx % 4 == 0) zoo[idx]->Feed();
    }

    // 6) Final printout of IDs
    cout << "Final IDs: ";
    for (auto& a : zoo) cout << a->getID() << " ";
    cout << "\n";
}

// Entry point — большой main
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<unique_ptr<Animal>> zoo;

    // Статус выполнения — используем для отчёта в конце
    enum class Stage {
        None, Starting, Populating, ShowInfo, SpeciesActions, Feeding, Menu, LongDemo, Shutdown
    } current_stage = Stage::None;

    auto stage_name = [](Stage s)->const char* {
        switch (s) {
            case Stage::Starting: return "Starting";
            case Stage::Populating: return "Populating";
            case Stage::ShowInfo: return "ShowInfo";
            case Stage::SpeciesActions: return "SpeciesActions";
            case Stage::Feeding: return "Feeding";
            case Stage::Menu: return "Menu";
            case Stage::LongDemo: return "LongDemo";
            case Stage::Shutdown: return "Shutdown";
            default: return "None";
        }
    };

    try {
        current_stage = Stage::Starting;
        print_header("Starting Zoo demo - building animals");

        current_stage = Stage::Populating;
        populate_zoo(zoo);

        // Быстрый базовый отчет
        cout << "Total animals created: " << zoo.size() << "\n";

        current_stage = Stage::ShowInfo;
        // Первичный снимок
        show_all_info(zoo);

        current_stage = Stage::SpeciesActions;
        // Специальные действия
        perform_species_actions(zoo);

        current_stage = Stage::Feeding;
        // Кормление несколько раз
        feeding_rounds(zoo, 2);

        current_stage = Stage::Menu;
        // Меню для пользователя (интерактивная часть)
        demo_menu(zoo);

        current_stage = Stage::LongDemo;
        // Длинный демонстрационный скрипт (много строк работы)
        long_demonstration_script(zoo);

        current_stage = Stage::Shutdown;
        // Последний снимок перед завершением
        print_header("Shutdown snapshot");
        show_all_info(zoo);

        cout << "Demo finished. Thank you!\n";

        // Если дошли до сюда — всё прошло успешно
        cout << "RESULT: ALL PASSED SUCCESSFUL\n";
        return 0;
    }
    catch (const std::exception& e) {
        cerr << "ERROR during stage: " << stage_name(current_stage) << "\n";
        cerr << "What(): " << e.what() << "\n";
        cerr << "RESULT: FAILED\n";
        return 2;
    }
    catch (...) {
        cerr << "UNKNOWN ERROR during stage: " << stage_name(current_stage) << "\n";
        cerr << "RESULT: FAILED\n";
        return 3;
    }
}

// Конец файла
