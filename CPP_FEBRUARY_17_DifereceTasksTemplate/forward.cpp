#include <iostream>
#include <type_traits>

namespace mystd {
    template <typename T>
    T&& myforward(typename std::remove_reference_t<T>& arg) {
        return static_cast<T&&>(arg);
    }

    template <typename T>
    T&& myforward(typename std::remove_reference_t<T>&& arg) {
        static_assert(!std::is_lvalue_reference_v<T>, "non rval to lval");
        return static_cast<T&&>(arg);
    }
};

void foo (int& x) { std::cout << "lvalue" << std::endl; }

void foo (int&& x) { std::cout << "rvalue" << std::endl; }

template <typename T>
void check (T&& x) {
    int y{};
    foo(mystd::myforward<T>(x));
    foo(mystd::myforward<T&>(y));
    foo(mystd::myforward<int>(7));
    std::cout << "Def" << std::endl;
    foo(std::forward<T>(x));
    foo(std::forward<T&>(y));
    foo(std::forward<int>(7));
}

int main() {
    int x = 9;
    int& y = x;
    check(y);
}