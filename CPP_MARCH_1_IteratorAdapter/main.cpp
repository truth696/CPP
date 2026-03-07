#include <iostream>
#include <list>
#include "Iterators.hpp"

int main() {
    std::vector<int> vec;
    auto it = back_inserter(vec);

    *it = 1;
    *it = 2;
    *it = 3;

    std::cout << "vector ";
    for (int n : vec) std::cout << n << " "; // 1 2 3
    std::cout <<  "\n";

    std::list<int> lst;
    auto it2 = front_inserter(lst);

    *it2 = 1;
    *it2 = 2;
    *it2 = 3;

    std::cout << "list ";
    for (int x : lst) std::cout << x << " ";  // 3 2 1
    std::cout <<  "\n";

    std::vector<int> v = {1, 2, 5, 6};

    // Вставим элементы перед третьим элементом (перед 5)
    auto it4 = inserter(v, v.begin() + 2);

    *it = 3;  // вставка 3 перед 5
    *it = 4;  // вставка 4 перед 5

    for (int x : v)
        std::cout << x << " "; // 1 2 3 4 5 6

    std::vector<std::string> v2 = {"a", "b", "c"};
    std::vector<std::string> dst;

    move_iterator<std::vector<std::string>::iterator> mit_begin(v2.begin());
    move_iterator<std::vector<std::string>::iterator> mit_end(v2.end());

    for (auto fit = mit_begin; fit != mit_end; ++fit)
        dst.push_back(*fit); // элементы перемещаются

    for (auto& s : dst) std::cout << s << " "; // a b c

}
