#include "vector_heder.hpp"
#include <iostream>

bool test_init() {
    MyVector v;
    myvector_init(&v, 5);
    bool ok = (v.size == 0 && v.capacity == 5 && v.data != 0);
    myvector_destroy(&v);
    return ok;
}

bool test_init_value() {
    MyVector v;
    myvector_init(&v, 3, 7);
    bool ok = (v.size == 3 && v.capacity == 3);
    for (size_t i = 0; i < v.size && ok; ++i)
        if (v.data[i] != 7) ok = false;
    myvector_destroy(&v);
    return ok;
}

bool test_push_pop() {
    MyVector v;
    myvector_init(&v, 2);
    myvector_push_back(&v, 10);
    myvector_push_back(&v, 20);
    bool ok = (myvector_size(&v) == 2);
    myvector_pop_back(&v);
    ok = ok && (myvector_size(&v) == 1);
    myvector_destroy(&v);
    return ok;
}

bool test_insert_erase() {
    MyVector v;
    myvector_init(&v, 2);
    myvector_push_back(&v, 1);
    myvector_push_back(&v, 3);
    myvector_insert(&v, 1, 2); // вставка 2 между 1 и 3
    bool ok = (v.data[1] == 2 && myvector_size(&v) == 3);
    myvector_erase(&v, 1); // удаление 2
    ok = ok && (v.data[1] == 3 && myvector_size(&v) == 2);
    myvector_destroy(&v);
    return ok;
}

bool test_clear() {
    MyVector v;
    myvector_init(&v, 3, 5);
    myvector_clear(&v);
    bool ok = true;
    for (size_t i = 0; i < v.size; ++i)
        if (v.data[i] != 0) ok = false;
    myvector_destroy(&v);
    return ok;
}

int main() {
    struct Test {
        const char* name;
        bool (*func)();
    };

    Test tests[] = {
        {"test_init", test_init},
        {"test_init_value", test_init_value},
        {"test_push_pop", test_push_pop},
        {"test_insert_erase", test_insert_erase},
        {"test_clear", test_clear}
    };

    int n = sizeof(tests)/sizeof(tests[0]);
    for (int i = 0; i < n; ++i) {
        if (!tests[i].func()) {
            std::cout << "Не прошло: " << tests[i].name << std::endl;
            return 1;
        }
    }

    std::cout << "Все прошло!" << std::endl;
    return 0;
}
