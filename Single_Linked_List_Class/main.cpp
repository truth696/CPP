#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include "List.hpp"

// Запускает тест в дочернем процессе, чтобы поймать падения/exit/signals.
// Возвращает true если тест успешно завершился с кодом 0.
bool run_isolated_test(const std::string& name, const std::function<bool()>& fn) {
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Fork failed for test " << name << ": " << strerror(errno) << "\n";
        return false;
    }

    if (pid == 0) {
        // child
        bool ok = false;
        try {
            ok = fn();
        } catch (...) {
            _exit(127);
        }
        _exit(ok ? 0 : 2);
    } else {
        // parent
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 0) {
                std::cout << "✅ " << name << " - success\n";
                return true;
            } else if (code == 127) {
                std::cout << "❌ " << name << " - failed: child threw/terminated with exception (exit 127)\n";
                return false;
            } else {
                std::cout << "❌ " << name << " - failed (child exit code " << code << ")\n";
                return false;
            }
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            std::cout << "💥 " << name << " - crashed with signal " << sig << "\n";
            return false;
        } else {
            std::cout << "❌ " << name << " - unknown child status\n";
            return false;
        }
    }
}

// --- тесты ---

bool test_initializer_and_access() {
    SingleList a = {1,2,3,4};
    if (a.size() != 4) return false;
    if (a[0] != 1 || a[1] != 2 || a[2] != 3 || a[3] != 4) return false;
    return true;
}

bool test_push_pop_front_back_and_single_pop_back() {
    SingleList s;
    s.push_back(1);
    s.push_back(2);
    s.push_front(0); // 0,1,2
    if (s.size() != 3) return false;
    if (s[0] != 0 || s[1] != 1 || s[2] != 2) return false;

    s.pop_front(); // 1,2
    if (s.size() != 2 || s[0] != 1) return false;

    s.pop_back(); // 1
    if (s.size() != 1 || s[0] != 1) return false;

    s.pop_back();
    if (s.size() != 0) return false;

    s.pop_back();
    s.pop_front();

    return true;
}

bool test_copy_and_deep_copy() {
    SingleList a = {10,20,30};
    SingleList b(a); // copy ctor
    if (!(a == b)) return false;

    a[1] = 999;
    if (b[1] != 20) return false;
    return true;
}

bool test_assignment_and_self_assignment() {
    SingleList a = {1,2,3};
    SingleList b;
    b = a; // copy assign
    if (!(b == a)) return false;

    // удалено явное a = a; чтобы не получать варнинг компилятора

    SingleList c = {7,8,9};
    SingleList d;
    d = std::move(c);
    if (c) return false;
    if (!d) return false;
    if (d.size() != 3) return false;

    // удалено d = std::move(d); чтобы не получать варнинг

    return true;
}

bool test_plus_and_plus_equal_and_empty_cases() {
    SingleList a = {1,2};
    SingleList b = {3,4};
    SingleList c = a + b;
    if (c.size() != 4) return false;
    if (c[0] != 1 || c[3] != 4) return false;

    SingleList d = a;
    d += b;
    if (d.size() != 4) return false;

    SingleList empty;
    SingleList e = a + empty;
    if (e.size() != a.size()) return false;
    SingleList f = empty + a;
    if (f.size() != a.size()) return false;
    return true;
}

bool test_equality_and_inequality() {
    SingleList a = {1,2,3};
    SingleList b = {1,2,3};
    SingleList c = {1,2,4};

    if (!(a == b)) return false;
    if (a != b) return false;
    if (!(a != c)) return false;
    return true;
}

bool test_streams_and_vector_conversion() {
    SingleList a = {5,6,7};
    std::stringstream ss;
    ss << a;
    if (ss.str() != "5 6 7 ") return false;

    std::stringstream in("9 8 7");
    SingleList r;
    in >> r;
    if (r.size() != 3) return false;
    if (r[0] != 9 || r[2] != 7) return false;

    std::vector<int> vec = static_cast<std::vector<int>>(a);
    if (vec.size() != 3) return false;
    if (vec[0] != 5) return false;

    return true;
}

bool test_bool_and_not_operators_and_clear() {
    SingleList empty;
    SingleList s = {1};
    if (!s) return false;
    s.clear();
    if (s) return false;
    if (s.size() != 0) return false;
    return true;
}

bool test_increment_decrement_ops() {
    SingleList a = {1,2};
    ++a;
    if (a.size() != 3) return false;
    if (a[a.size()-1] != 0) return false;

    SingleList old = a++;
    if (a.size() != old.size() + 1) return false;

    --a;
    SingleList old2 = a--;
    if (a.size() != old2.size() - 1) return false;

    return true;
}

bool test_crash_and_exit_cases() {
    {
        SingleList s;
        s.push_back(42);
        s.pop_back();
        if (s.size() != 0) return false;
    }

    {
        SingleList s = {1};
        if (s[0] != 1) return false;
    }

    {
        std::stringstream ss("1 2 3");
        SingleList s;
        ss >> s;
        if (s.size() != 3) return false;
    }

    return true;
}

int main(){
    int total = 0;
    int failed = 0;
    std::vector<std::string> failed_tests;

    auto run = [&](const std::string& name, const std::function<bool()>& fn){
        ++total;
        bool ok = run_isolated_test(name, fn);
        if (!ok) {
            ++failed;
            failed_tests.push_back(name);
        }
    };

    run("initializer_and_access", test_initializer_and_access);
    run("push_pop_front_back_and_single_pop_back", test_push_pop_front_back_and_single_pop_back);
    run("copy_and_deep_copy", test_copy_and_deep_copy);
    run("assignment_and_self_assignment", test_assignment_and_self_assignment);
    run("plus_and_plus_equal_and_empty", test_plus_and_plus_equal_and_empty_cases);
    run("equality_and_inequality", test_equality_and_inequality);
    run("streams_and_vector_conversion", test_streams_and_vector_conversion);
    run("bool_not_and_clear", test_bool_and_not_operators_and_clear);

    // — здесь был баг: вызывалась несуществующая функция test_increment_and_decrement_ops
    run("increment_and_decrement", test_increment_decrement_ops);

    run("crash_and_exit_cases", test_crash_and_exit_cases);

    std::cout << "\n=============================\n";
    if (failed == 0) {
        std::cout << "✅✅ All heavy tests passed (" << total << ")\n";
    } else {
        std::cout << "❌ " << failed << " test(s) failed out of " << total << "\n";
        std::cout << "Failed tests:\n";
        for (const auto& name : failed_tests) {
            std::cout << " - " << name << "\n";
        }
    }

    return (failed == 0) ? 0 : 1;
}
