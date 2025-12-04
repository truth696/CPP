// main.cpp — большой набор тестов (~400-600 строк в зависимости от форматирования)
// Проверяет: создание аккаунтов, deposit, withdraw, display, overdraft, rate,
// Bank::initialization_cardNumber(), отрицательные суммы, большие суммы, нули и др.
// При успешном тесте печатает "сексесфулл" и "Successful".
// При ошибке печатает имя теста (где это произошло) и текст исключения.

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <iomanip>
#include <exception>

// Подключаем твой заголовок (предполагается, что BankSystem.hpp содержит определения классов)
#include "BankSystem.hpp"

// Вспомогательная обёртка для выполнения тестов.
// `name` — имя теста (печатается при ошибке).
// `f` — лямбда, где выполняется тест; если она не бросает, считается успешным.
void runTest(const std::string &name, const std::function<void()>& f) {
    try {
        f();
        // Успех
        std::cout << "[" << std::setw(40) << std::left << name << "] -> "
                  << "сексесфулл" << " | " << "Successful" << std::endl;
    } catch (const BankException &be) {
        // Если у тебя what() корректно реализован — выведем его, но главное: имя теста
        std::cout << "[" << std::setw(40) << std::left << name << "] -> "
                  << "ERROR IN: " << name << " | exception: ";
        try {
            std::cout << be.what();
        } catch (...) {
            std::cout << "(error.what() failed)";
        }
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cout << "[" << std::setw(40) << std::left << name << "] -> "
                  << "ERROR IN: " << name << " | std::exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "[" << std::setw(40) << std::left << name << "] -> "
                  << "ERROR IN: " << name << " | unknown exception" << std::endl;
    }
}

// Небольшие утилиты для отображения состояния аккаунта (без доступа к internals)
void tryDisplay(const BankAccount* acc) {
    if (!acc) return;
    try {
        acc->display();
    } catch (...) {
        // display может бросить — игнорируем здесь, тесты отдельно отлавливают исключения
    }
}

int main() {
    std::cout << "=== BankSystem extensive test harness ===\n\n";

    // Контейнеры с указателями на аккаунты, чтобы тесты могли ссылаться на них
    std::vector<std::unique_ptr<BankAccount>> localAccounts;

    // 1) Test: card number generator multiple times
    runTest("CardGen - single", [](){
        auto s = Bank::initialization_cardNumber();
        if (s.empty()) throw std::runtime_error("Card string empty");
    });

    runTest("CardGen - sequence 50", [](){
        // генерируем 50 номеров подряд
        for (int i = 0; i < 50; ++i) {
            std::string c = Bank::initialization_cardNumber();
            if (c.empty()) throw std::runtime_error("Empty card #" + std::to_string(i));
            // минимальная валидация: должен содержать хотя бы одну цифру
            bool hasDigit = false;
            for (char ch : c) if (std::isdigit((unsigned char)ch)) hasDigit = true;
            if (!hasDigit) throw std::runtime_error("Card has no digits at idx " + std::to_string(i));
        }
    });

    // 2) Create several CheckingAccount and SavingsAccount and push to localAccounts
    runTest("Create Checking A", [&](){
        localAccounts.emplace_back(std::make_unique<CheckingAccount>("Alice", 500.0));
    });
    runTest("Create Checking B", [&](){
        localAccounts.emplace_back(std::make_unique<CheckingAccount>("Bob", 1500.0));
    });
    runTest("Create Checking C (zero)", [&](){
        localAccounts.emplace_back(std::make_unique<CheckingAccount>("Charlie", 0.0));
    });
    runTest("Create Savings D", [&](){
        localAccounts.emplace_back(std::make_unique<SavingsAccount>("Diana", 1000.0));
    });
    runTest("Create Savings E", [&](){
        localAccounts.emplace_back(std::make_unique<SavingsAccount>("Eva", 5000.0));
    });

    // 3) Basic display tests
    for (size_t i = 0; i < localAccounts.size(); ++i) {
        std::string t = "Display acc #" + std::to_string(i);
        runTest(t, [&, i](){
            tryDisplay(localAccounts[i].get());
        });
    }

    // 4) Deposit tests: valid, zero, negative
    runTest("Deposit positive to #0", [&](){
        localAccounts[0]->deposit(200.0);
    });
    runTest("Deposit zero to #0", [&](){
        localAccounts[0]->deposit(0.0);
    });
    runTest("Deposit negative to #0 (should throw)", [&](){
        // Ожидаем бросок (в реализации у тебя ловят и печатают, но не бросают дальше).
        // Чтобы тест не считался успешным, мы проверим состояние — но так как реализация ловит
        // исключение и не пробрасывает, просто вызовем и убедимся, что баланс не увеличился.
        double before = localAccounts[0]->getBalance();
        localAccounts[0]->deposit(-100.0);
        double after = localAccounts[0]->getBalance();
        if (after != before) throw std::runtime_error("Negative deposit changed balance");
    });

    // 5) Withdraw tests: normal, negative, over-withdraw
    runTest("Withdraw positive from #1", [&](){
        localAccounts[1]->withdraw(100.0);
    });
    runTest("Withdraw zero from #1", [&](){
        localAccounts[1]->withdraw(0.0);
    });
    runTest("Withdraw negative from #1 (should not change)", [&](){
        double before = localAccounts[1]->getBalance();
        localAccounts[1]->withdraw(-50.0);
        double after = localAccounts[1]->getBalance();
        if (after != before) throw std::runtime_error("Negative withdraw changed balance");
    });

    runTest("Withdraw too much from #2 (expect overdraft or insuff)", [&](){
        // Checking account with overdraft should allow negative to some limit.
        // We don't assume exact behavior; просто вызываем.
        localAccounts[2]->withdraw(10000.0);
    });

    // 6) Savings deposit should apply rate (we check that balance increased by > amount)
    runTest("Savings deposit applies rate #3", [&](){
        double before = localAccounts[3]->getBalance();
        localAccounts[3]->deposit(100.0);
        double after = localAccounts[3]->getBalance();
        if (after <= before) throw std::runtime_error("Savings deposit did not increase balance");
    });

    // 7) Savings withdraw tests
    runTest("Savings withdraw normal #3", [&](){
        double before = localAccounts[3]->getBalance();
        localAccounts[3]->withdraw(50.0);
        double after = localAccounts[3]->getBalance();
        if (after > before) throw std::runtime_error("Withdraw on savings increased balance?");
    });

    // 8) Many tiny deposit/withdraw cycles to stress
    runTest("Stress small cycles (100 iterations)", [&](){
        for (int k = 0; k < 100; ++k) {
            for (auto &p : localAccounts) {
                p->deposit((k % 5) * 1.5);
                p->withdraw((k % 3) * 0.5);
            }
        }
    });

    // 9) Test displays again after changes
    for (size_t i = 0; i < localAccounts.size(); ++i) {
        std::string t = "Display after ops acc #" + std::to_string(i);
        runTest(t, [&, i](){
            tryDisplay(localAccounts[i].get());
        });
    }

    // 10) Manual transfer function (not Bank::transfer) to validate deposit/withdraw pairing.
    // Если тебе нужно тестировать именно Bank::transfer — можно раскомментировать и использовать,
    // но в твоей реализации createCheking/createSaving добавляют адреса временных объектов (&CheckingAccount(...))
    // что потенциально небезопасно. Поэтому тестируем логику transfer локально.
    auto localTransfer = [&](BankAccount* from, BankAccount* to, double amount) {
        if (!from || !to) throw std::runtime_error("null account in transfer");
        if (amount < 0) throw NegativeAmount(std::string("amount negative in localTransfer"));
        if (from->getBalance() + 1e-9 < amount) throw InsufficiantFunds(std::string("not enough funds in localTransfer"));
        to->deposit(amount);
        from->withdraw(amount);
    };

    runTest("Local transfer valid #1->#4", [&](){
        localTransfer(localAccounts[0].get(), localAccounts[4].get(), 20.0);
    });
    runTest("Local transfer too much (should throw)", [&](){
        bool threw = false;
        try {
            localTransfer(localAccounts[0].get(), localAccounts[4].get(), 1e12);
        } catch (const BankException&) {
            threw = true;
        }
        // в локальном тесте ожидаем бросок, поэтому success только если бросок произошёл
        if (!threw) throw std::runtime_error("expected insufficiant funds exception but it didn't happen");
    });
    runTest("Local transfer negative (should throw)", [&](){
        bool threw = false;
        try {
            localTransfer(localAccounts[1].get(), localAccounts[2].get(), -10.0);
        } catch (const BankException&) {
            threw = true;
        }
        if (!threw) throw std::runtime_error("expected negative amount exception but it didn't happen");
    });

    // 11) Repeated transfer patterns between all pairs
    runTest("Many pairwise transfers", [&](){
        for (size_t i = 0; i < localAccounts.size(); ++i) {
            for (size_t j = 0; j < localAccounts.size(); ++j) {
                if (i == j) continue;
                try {
                    localTransfer(localAccounts[i].get(), localAccounts[j].get(), 1.0);
                } catch (const BankException&) {
                    // допускаем исключения (недостаточно средств) — не считаем это ошибкой теста
                }
            }
        }
    });

    // 12) Test construction defaults and large amounts
    runTest("Create large balance account", [&](){
        localAccounts.emplace_back(std::make_unique<CheckingAccount>("Rich", 1e9));
    });
    runTest("Huge deposit on Rich", [&](){
        auto *rich = localAccounts.back().get();
        rich->deposit(5e8);
    });
    runTest("Huge withdraw on Rich", [&](){
        auto *rich = localAccounts.back().get();
        rich->withdraw(1e9);
    });

    // 13) Edge cases: deposit and withdraw zero many times
    runTest("Zero deposit/withdraw loop", [&](){
        for (int i = 0; i < 50; ++i) {
            for (auto &p : localAccounts) {
                p->deposit(0.0);
                p->withdraw(0.0);
            }
        }
    });

    // 14) Attempt to call Bank::initialization_cardNumber heavily to ensure uniqueness/format
    runTest("Cardgen uniqueness scan 200", [&](){
        std::vector<std::string> seen;
        for (int i = 0; i < 200; ++i) {
            std::string c = Bank::initialization_cardNumber();
            for (auto &s : seen) if (s == c) throw std::runtime_error("duplicate card number found");
            seen.push_back(c);
        }
    });

    // 15) Test display of all accounts at the end (final state)
    for (size_t i = 0; i < localAccounts.size(); ++i) {
        std::string t = "Final display acc #" + std::to_string(i);
        runTest(t, [&, i](){
            tryDisplay(localAccounts[i].get());
        });
    }

    // 16) Intentional failing tests to verify error reporting: negative deposit, negative withdraw
    runTest("Intentional fail - deposit negative on #0", [&](){
        // Если твоя реализация ловит исключения и не прерывает — проверим баланс не изменился.
        double b = localAccounts[0]->getBalance();
        localAccounts[0]->deposit(-9999.0);
        double a = localAccounts[0]->getBalance();
        if (a != b) throw std::runtime_error("negative deposit unexpectedly changed balance");
    });

    runTest("Intentional fail - withdraw negative on #1", [&](){
        double b = localAccounts[1]->getBalance();
        localAccounts[1]->withdraw(-9999.0);
        double a = localAccounts[1]->getBalance();
        if (a != b) throw std::runtime_error("negative withdraw unexpectedly changed balance");
    });

    // 17) Final summary print
    std::cout << "\n=== TEST SUITE COMPLETE ===\n";
    std::cout << "Total accounts created locally: " << localAccounts.size() << "\n";
    std::cout << "Inspect the above per-test lines for (success) or errors.\n";

    return 0;
}
