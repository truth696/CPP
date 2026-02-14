//  #include <iostream>
// #include <vector>
// #include "TemplateList.hpp"

// int main()
// {
//     std::cout << "=== TEST 1: initializer_list constructor ===\n";
//     List<int> a({1, 2, 3, 4});
//     std::cout << "Size of a: " << a.size() << "\n";

//     std::cout << "\n=== TEST 2: push_back ===\n";
//     a.push_back(5);
//     a.push_back(6);
//     std::cout << "Size of a after push_back: " << a.size() << "\n";

//     std::cout << "\n=== TEST 3: push_front ===\n";
//     a.push_front(100);
//     std::cout << "Size of a after push_front: " << a.size() << "\n";

//     std::cout << "\n=== TEST 4: pop_front ===\n";
//     a.pop_front();
//     std::cout << "Size of a after pop_front: " << a.size() << "\n";

//     std::cout << "\n=== TEST 5: pop_back ===\n";
//     a.pop_back();
//     std::cout << "Size of a after pop_back: " << a.size() << "\n";

//     std::cout << "\n=== TEST 6: insert ===\n";
//     a.insert(1, 999);
//     std::cout << "Size of a after insert: " << a.size() << "\n";

//     std::cout << "\n=== TEST 7: erase ===\n";
//     a.erase(1);
//     std::cout << "Size of a after erase: " << a.size() << "\n";

//     std::cout << "\n=== TEST 8: copy constructor ===\n";
//     List<int> b(a);
//     std::cout << "Size of b: " << b.size() << "\n";

//     std::cout << "\n=== TEST 9: copy assignment ===\n";
//     List<int> c({10, 20, 30});
//     c = a;
//     std::cout << "Size of c: " << c.size() << "\n";

//     std::cout << "\n=== TEST 10: move constructor ===\n";
//     List<int> d(std::move(a));
//     std::cout << "Size of d: " << d.size() << "\n";
//     std::cout << "Size of a after move: " << a.size() << "\n";

//     std::cout << "\n=== TEST 11: move assignment ===\n";
//     List<int> e({7, 8, 9});
//     e = std::move(d);
//     std::cout << "Size of e: " << e.size() << "\n";
//     std::cout << "Size of d after move assignment: " << d.size() << "\n";

//     std::cout << "\n=== TEST 12: clear ===\n";
//     e.clear();
//     std::cout << "Size of e after clear: " << e.size() << "\n";

//     std::cout << "\n=== END TESTS ===\n";
//     return 0;
// }
// main.cpp
// Big test harness for your List<T> (no iterators needed).
// Compile: g++ -std=c++20 -O0 -g main.cpp && ./a.out
//
// Assumes List<T> has:
//  - ctors: default, initializer_list, vector, copy, move
//  - operators: copy/move assignment
//  - methods: size(), empty(), back(), push_back, push_front, pop_back, pop_front,
//            insert(pos, value), erase(pos), clear(), swap(List&)
// If something is missing, comment out the corresponding tests.

#include <cassert>
#include <cstddef>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "TemplateList.hpp"

static int g_failures = 0;

#define CHECK_TRUE(expr)                                                      \
    do {                                                                      \
        if (!(expr)) {                                                        \
            ++g_failures;                                                     \
            std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << "  "     \
                      << #expr << "\n";                                       \
        }                                                                     \
    } while (0)

#define CHECK_EQ(a, b)                                                        \
    do {                                                                      \
        auto _a = (a);                                                        \
        auto _b = (b);                                                        \
        if (!(_a == _b)) {                                                    \
            ++g_failures;                                                     \
            std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << "  "     \
                      << #a << " == " << #b << "  (got " << _a << " vs "      \
                      << _b << ")\n";                                         \
        }                                                                     \
    } while (0)

#define SECTION(name)                                                         \
    do {                                                                      \
        std::cout << "\n==== " << (name) << " ====\n";                        \
    } while (0)

// Helper: drain List by popping back, return elements in popped order.
// (This requires pop_back + back + size)
template <class T>
static std::vector<T> drain_back(List<T>& lst) {
    std::vector<T> out;
    while (!lst.empty()) {
        out.push_back(lst.back());
        lst.pop_back();
    }
    return out; // order = reverse of list order
}

// Helper: compare only size/back against a reference container
template <class T>
static void check_size_and_back(List<T>& lst, const std::vector<T>& ref) {
    CHECK_EQ(lst.size(), ref.size());
    CHECK_EQ(lst.empty(), ref.empty());
    if (!ref.empty()) CHECK_EQ(lst.back(), ref.back());
}

// Basic: build list using push_back, check size/back after each op
static void test_push_back_basic() {
    SECTION("push_back basic");
    List<int> lst;
    std::vector<int> ref;

    CHECK_TRUE(lst.empty());
    CHECK_EQ(lst.size(), 0u);

    for (int i = 1; i <= 50; ++i) {
        lst.push_back(i);
        ref.push_back(i);
        check_size_and_back(lst, ref);
    }
}

// Basic: pop_back sequence
static void test_pop_back_basic() {
    SECTION("pop_back basic");
    List<int> lst;
    std::vector<int> ref;

    for (int i = 0; i < 30; ++i) {
        lst.push_back(i * 10);
        ref.push_back(i * 10);
    }

    for (int k = 0; k < 30; ++k) {
        check_size_and_back(lst, ref);
        lst.pop_back();
        ref.pop_back();
    }

    CHECK_TRUE(lst.empty());
    CHECK_EQ(lst.size(), 0u);
}

// push_front: we can at least check size and that back stays correct for some patterns
static void test_push_front_basic() {
    SECTION("push_front basic");
    List<int> lst;
    std::deque<int> ref; // front insert easy

    // Push front into empty list should not crash
    for (int i = 1; i <= 20; ++i) {
        lst.push_front(i);
        ref.push_front(i);
        CHECK_EQ(lst.size(), ref.size());
        CHECK_EQ(lst.empty(), ref.empty());
        // back should equal deque.back()
        CHECK_EQ(lst.back(), ref.back());
    }
}

// pop_front: validate size/back vs deque
static void test_pop_front_basic() {
    SECTION("pop_front basic");
    List<int> lst;
    std::deque<int> ref;

    for (int i = 1; i <= 25; ++i) {
        lst.push_back(i);
        ref.push_back(i);
    }
    CHECK_EQ(lst.back(), ref.back());

    for (int k = 0; k < 24; ++k) {
        lst.pop_front();
        ref.pop_front();
        CHECK_EQ(lst.size(), ref.size());
        CHECK_EQ(lst.empty(), ref.empty());
        CHECK_EQ(lst.back(), ref.back());
    }

    // now 1 element left
    CHECK_EQ(lst.size(), 1u);
    lst.pop_front();
    CHECK_TRUE(lst.empty());
}

// initializer_list ctor: validate by draining
static void test_initializer_list_ctor() {
    SECTION("initializer_list ctor");
    List<int> lst({1, 2, 3, 4, 5});
    CHECK_EQ(lst.size(), 5u);
    CHECK_EQ(lst.back(), 5);

    auto drained = drain_back(lst);
    // drained is reverse: 5,4,3,2,1
    std::vector<int> expected = {5, 4, 3, 2, 1};
    CHECK_EQ(drained.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) CHECK_EQ(drained[i], expected[i]);

    CHECK_TRUE(lst.empty());
}

// vector ctor: validate by draining
static void test_vector_ctor() {
    SECTION("vector ctor");
    std::vector<int> v;
    for (int i = 10; i <= 19; ++i) v.push_back(i);
    List<int> lst(v);
    CHECK_EQ(lst.size(), v.size());
    CHECK_EQ(lst.back(), v.back());

    auto drained = drain_back(lst); // reverse
    CHECK_EQ(drained.size(), v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        CHECK_EQ(drained[i], v[v.size() - 1 - i]);
    }
}

// copy ctor: validate by draining both
static void test_copy_ctor() {
    SECTION("copy ctor");
    List<int> a({7, 8, 9, 10});
    List<int> b(a);

    CHECK_EQ(a.size(), 4u);
    CHECK_EQ(b.size(), 4u);
    CHECK_EQ(a.back(), 10);
    CHECK_EQ(b.back(), 10);

    auto da = drain_back(a);
    auto db = drain_back(b);
    CHECK_EQ(da.size(), db.size());
    for (size_t i = 0; i < da.size(); ++i) CHECK_EQ(da[i], db[i]);
}

// move ctor: just ensure moved-to has content and moved-from is empty (best-effort)
static void test_move_ctor() {
    SECTION("move ctor");
    List<int> a({1, 2, 3});
    List<int> b(std::move(a));

    CHECK_EQ(b.size(), 3u);
    CHECK_EQ(b.back(), 3);

    // moved-from should be empty in a well-behaved move
    CHECK_TRUE(a.empty());
    CHECK_EQ(a.size(), 0u);

    auto db = drain_back(b);
    std::vector<int> expected = {3, 2, 1};
    CHECK_EQ(db.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) CHECK_EQ(db[i], expected[i]);
}

// copy assignment
static void test_copy_assignment() {
    SECTION("copy assignment");
    List<int> a({5, 6, 7});
    List<int> b({100, 200});
    b = a;

    CHECK_EQ(b.size(), 3u);
    CHECK_EQ(b.back(), 7);

    auto da = drain_back(a);
    auto db = drain_back(b);
    CHECK_EQ(da.size(), db.size());
    for (size_t i = 0; i < da.size(); ++i) CHECK_EQ(da[i], db[i]);
}

// move assignment
static void test_move_assignment() {
    SECTION("move assignment");
    List<int> a({11, 22, 33, 44});
    List<int> b({1});

    b = std::move(a);
    CHECK_EQ(b.size(), 4u);
    CHECK_EQ(b.back(), 44);

    CHECK_TRUE(a.empty());
    CHECK_EQ(a.size(), 0u);

    auto db = drain_back(b);
    std::vector<int> expected = {44, 33, 22, 11};
    CHECK_EQ(db.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) CHECK_EQ(db[i], expected[i]);
}

// clear: must leave empty and reusable
static void test_clear_reuse() {
    SECTION("clear + reuse");
    List<int> lst({1, 2, 3, 4});
    CHECK_EQ(lst.size(), 4u);

    lst.clear();
    CHECK_TRUE(lst.empty());
    CHECK_EQ(lst.size(), 0u);

    // reuse
    lst.push_back(9);
    lst.push_front(8);
    CHECK_EQ(lst.size(), 2u);
    CHECK_EQ(lst.back(), 9);
}

// swap: validate size/back
static void test_swap() {
    SECTION("swap");
    List<int> a({1, 2, 3});
    List<int> b({10, 20});

    a.swap(b);
    CHECK_EQ(a.size(), 2u);
    CHECK_EQ(b.size(), 3u);
    CHECK_EQ(a.back(), 20);
    CHECK_EQ(b.back(), 3);
}

// insert/erase: verify size and back for cases that affect tail
static void test_insert_erase_tail_effects() {
    SECTION("insert/erase (tail effects)");
    List<int> lst({1, 2, 3});
    CHECK_EQ(lst.back(), 3);

    // insert at end should change back
    lst.insert(lst.size(), 99);
    CHECK_EQ(lst.back(), 99);

    // erase last should restore back
    lst.erase(lst.size() - 1);
    CHECK_EQ(lst.back(), 3);

    // insert at 0 should not change back
    lst.insert(0, -5);
    CHECK_EQ(lst.back(), 3);

    // erase at 0 should not change back
    lst.erase(0);
    CHECK_EQ(lst.back(), 3);
}

// Randomized stress: keep a reference vector, but only check size/back frequently.
// We avoid verifying full order since we have no iterators.
static void test_random_stress(int seed) {
    SECTION("random stress (size/back invariants)");
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> valDist(-100000, 100000);
    std::uniform_int_distribution<int> opDist(0, 7);

    List<int> lst;
    std::vector<int> ref;

    const int OPS = 20000;
    for (int step = 1; step <= OPS; ++step) {
        int op = opDist(rng);

        // Keep operations valid
        if (ref.empty()) {
            op = op % 3; // prefer pushes/insert
        }

        switch (op) {
            case 0: { // push_back
                int v = valDist(rng);
                lst.push_back(v);
                ref.push_back(v);
                break;
            }
            case 1: { // push_front
                int v = valDist(rng);
                lst.push_front(v);
                ref.insert(ref.begin(), v);
                break;
            }
            case 2: { // insert somewhere
                int v = valDist(rng);
                size_t pos = (ref.empty() ? 0u : (size_t)(rng() % (ref.size() + 1)));
                lst.insert(pos, v);
                ref.insert(ref.begin() + (long)pos, v);
                break;
            }
            case 3: { // pop_back
                lst.pop_back();
                ref.pop_back();
                break;
            }
            case 4: { // pop_front
                lst.pop_front();
                ref.erase(ref.begin());
                break;
            }
            case 5: { // erase
                size_t pos = (size_t)(rng() % ref.size());
                lst.erase(pos);
                ref.erase(ref.begin() + (long)pos);
                break;
            }
            case 6: { // clear sometimes
                if ((rng() % 50) == 0) {
                    lst.clear();
                    ref.clear();
                }
                break;
            }
            case 7: { // copy/move roundtrip
                if ((rng() % 40) == 0) {
                    List<int> cpy(lst);          // copy ctor
                    List<int> tmp(std::move(cpy)); // move ctor
                    // tmp should have same size as lst
                    CHECK_EQ(tmp.size(), ref.size());
                    if (!ref.empty()) CHECK_EQ(tmp.back(), ref.back());
                }
                break;
            }
        }

        // periodic invariants
        if ((step % 200) == 0) {
            check_size_and_back(lst, ref);
        }
    }

    check_size_and_back(lst, ref);

    // Final heavy check: drain and compare full sequence (reverse)
    // This requires that pop_back/back reflect correct order.
    auto drained = drain_back(lst);
    CHECK_EQ(drained.size(), ref.size());
    for (size_t i = 0; i < ref.size(); ++i) {
        CHECK_EQ(drained[i], ref[ref.size() - 1 - i]);
    }
}

// Strings test: ensure templates work with non-trivial type
static void test_strings() {
    SECTION("strings");
    List<std::string> lst;
    lst.push_back("a");
    lst.push_back(std::string("b"));
    lst.push_front("z");

    CHECK_EQ(lst.size(), 3u);
    CHECK_EQ(lst.back(), "b");

    lst.pop_front();
    CHECK_EQ(lst.size(), 2u);
    CHECK_EQ(lst.back(), "b");

    lst.insert(2, "tail");
    CHECK_EQ(lst.back(), "tail");
    lst.erase(2);
    CHECK_EQ(lst.back(), "b");

    lst.clear();
    CHECK_TRUE(lst.empty());
}

// Many small edge cases
static void test_edge_cases() {
    SECTION("edge cases");
    List<int> a;
    CHECK_TRUE(a.empty());

    // single-element behavior
    a.push_back(1);
    CHECK_EQ(a.size(), 1u);
    CHECK_EQ(a.back(), 1);

    a.pop_front();
    CHECK_TRUE(a.empty());

    a.push_front(2);
    CHECK_EQ(a.size(), 1u);
    CHECK_EQ(a.back(), 2);

    a.pop_back();
    CHECK_TRUE(a.empty());

    // insert into empty at 0
    a.insert(0, 10);
    CHECK_EQ(a.size(), 1u);
    CHECK_EQ(a.back(), 10);

    // erase only element
    a.erase(0);
    CHECK_TRUE(a.empty());

    // swap with empty
    List<int> b({1, 2, 3});
    a.swap(b);
    CHECK_EQ(a.size(), 3u);
    CHECK_TRUE(b.empty());
    CHECK_EQ(a.back(), 3);
}

int main() {
    std::cout << "Running List<T> tests...\n";

    test_push_back_basic();
    test_pop_back_basic();
    test_push_front_basic();
    test_pop_front_basic();

    test_initializer_list_ctor();
    test_vector_ctor();

    test_copy_ctor();
    test_move_ctor();
    test_copy_assignment();
    test_move_assignment();

    test_clear_reuse();
    test_swap();

    test_insert_erase_tail_effects();
    test_edge_cases();
    test_strings();

    test_random_stress(12345);
    test_random_stress(777);
    test_random_stress(20260214);

    if (g_failures == 0) {
        std::cout << "\n✅ ALL TESTS PASSED\n";
        return 0;
    } else {
        std::cout << "\n❌ FAILURES: " << g_failures << "\n";
        return 1;
    }
}
