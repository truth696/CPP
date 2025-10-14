#include <iostream>
#include "Rational.hpp"

int main() {
    Rational a(1, 2);   // 1/2
    Rational b(3, 4);   // 3/4

    std::cout << "a = " << a;
    std::cout << "b = " << b;

    Rational sum = a + b;
    Rational diff = a - b;
    Rational prod = a * b;
    Rational div = a / b;

    std::cout << "a + b = " << sum;
    std::cout << "a - b = " << diff;
    std::cout << "a * b = " << prod;
    std::cout << "a / b = " << div;

    if (a == b) std::cout << "a == b\n";
    else std::cout << "a != b\n";

    std::cout << "++a = " << ++a;
    std::cout << "a++ = " << a++;
    std::cout << "После a++: " << a;

    // Проверка корректности вычислений
    bool ok = true;

    // Ожидаемые значения:
    Rational expected_sum(5, 4);   // 1/2 + 3/4 = 5/4
    Rational expected_diff(-1, 4); // 1/2 - 3/4 = -1/4
    Rational expected_prod(3, 8);  // 1/2 * 3/4 = 3/8
    Rational expected_div(2, 3);   // (1/2) / (3/4) = 2/3

    if (sum != expected_sum) ok = false;
    if (diff != expected_diff) ok = false;
    if (prod != expected_prod) ok = false;
    if (div != expected_div) ok = false;

    std::cout << "\n------------------------------\n";
    if (ok) std::cout << "✅ SUCCESSFUL\n";
    else    std::cout << "❌ FAILED\n";
    std::cout << "------------------------------\n";

    return 0;
}
