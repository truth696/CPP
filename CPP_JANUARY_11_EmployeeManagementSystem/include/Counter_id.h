#pragma once
#include <iostream>
#include <random>

struct Counter {
    static size_t id;
    Counter() { ++id; }
};


struct Achivments {
    static int achivments() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> res(0, 1099);

        return res(gen);
    }
};

struct Salary{
    static int salary_accountant() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> res(500, 1500);

        return res(gen);
    }

    static int salary_developer() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> res(1000, 10000);

        return res(gen);
    }

    static int salary_manager() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> res(800, 2300);

        return res(gen);
    }

    static int salary_sales_person() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> res(1000, 4000);

        return res(gen);
    }
};
