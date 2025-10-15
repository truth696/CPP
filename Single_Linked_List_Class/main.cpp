#include <iostream>
#include <vector>
#include "List.hpp"

int main() {
    bool allOk = true;

    SingleList list = {1, 2, 3};

    if (!list) {
        std::cout << "❌ Ошибка: список должен быть не пустым\n";
        allOk = false;
    }

    // Проверка оператора []
    if (list[1] != 2) {
        std::cout << "❌ Ошибка: элемент с индексом 1 должен быть равен 2\n";
        allOk = false;
    }
    list[1] = 42;

    // Проверка вывода
    std::cout << "Список: " << list << "\n";

    // Преобразование к вектору
    std::vector<int> vec = list;
    if (vec.size() != 3 || vec[1] != 42) {
        std::cout << "❌ Ошибка: преобразование в вектор работает неверно\n";
        allOk = false;
    }

    // Проверка ==
    SingleList other = {1, 42, 3};
    if (!(list == other)) {
        std::cout << "❌ Ошибка: списки должны быть равны\n";
        allOk = false;
    }

    // ++
    ++list;
    if (list.size() != 4) {
        std::cout << "❌ Ошибка: оператор ++ не добавил элемент\n";
        allOk = false;
    }

    // --
    list--;
    if (list.size() != 3) {
        std::cout << "❌ Ошибка: оператор -- не удалил элемент\n";
        allOk = false;
    }

    // clear + проверка bool
    list.clear();
    if (list) {
        std::cout << "❌ Ошибка: список должен быть пуст после clear()\n";
        allOk = false;
    }

    // ✅ Финальный вывод
    if (allOk) {
        std::cout << "✅ Всё прошло успешно!\n";
    } else {
        std::cout << "❌ Были ошибки во время выполнения\n";
    }

    return allOk ? 0 : 1;
}
