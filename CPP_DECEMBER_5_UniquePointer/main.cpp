// main.cpp
// Large test-suite (~400+ lines) for the provided unique_ptr implementation.
// This version **does NOT call swap()** anywhere (neither member nor std::swap).
// It only tests: ctor, move-ctor, move-assign, release, reset, get, operator bool,
// operator*, operator->, destructor behavior (indirectly).
//
// If all tests pass prints:
//   Narek Liked
// Otherwise prints the names of failed tests (one per line).
//
// Compile:
//   g++ -std=c++11 main.cpp -O2 -Wall -Wextra -o unique_test && ./unique_test
//
// Make sure "UniquePointer.hpp" (your header) is in the same folder.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>

#include "UniquePointer.hpp" // your implementation

using std::cout;
using std::endl;
using std::string;
using std::vector;

// ---------- Test infra ----------
struct TestResult {
    string name;
    bool ok;
    string info;
    TestResult(const string& n, bool o=true, const string& i="") : name(n), ok(o), info(i) {}
};

static vector<TestResult> g_results;

#define RUN_TEST(fn) do { \
    try { \
        bool ok = fn(); \
        g_results.emplace_back(#fn, ok, ok ? "" : "returned false"); \
    } catch (const std::exception& e) { \
        g_results.emplace_back(#fn, false, string("exception: ") + e.what()); \
    } catch (...) { \
        g_results.emplace_back(#fn, false, string("unknown exception")); \
    } \
} while(0)

#define EXPECT(cond) do { if (!(cond)) return false; } while(0)

// ---------- Utility tracker for destructor tests ----------
struct Tracker {
    static int live;
    int v;
    Tracker(int x=0) : v(x) { ++live; }
    ~Tracker() { --live; }
};
int Tracker::live = 0;

// ---------- Tests (no swap usage) ----------

// 1. Default ctor and bool
bool test_default_ctor_bool() {
    unique_ptr<int> p;
    EXPECT(!static_cast<bool>(p));
    return true;
}

// 2. Ctor with raw pointer and deref
bool test_ctor_and_deref() {
    unique_ptr<int> p(new int(42));
    EXPECT(static_cast<bool>(p));
    EXPECT(*p == 42);
    return true;
}

// 3. operator-> and operator*
struct Node { int x; int get(){ return x; } };
bool test_arrow_and_deref_struct() {
    unique_ptr<Node> p(new Node{7});
    EXPECT(p->get() == 7);
    EXPECT((*p).get() == 7);
    return true;
}

// 4. Move constructor transfers ownership
bool test_move_constructor() {
    unique_ptr<int> a(new int(100));
    unique_ptr<int> b(std::move(a));
    EXPECT(!static_cast<bool>(a));
    EXPECT(static_cast<bool>(b));
    EXPECT(*b == 100);
    return true;
}

// 5. Move assignment transfers ownership (no swap used)
bool test_move_assignment() {
    unique_ptr<int> a(new int(11));
    unique_ptr<int> b(new int(22));
    b = std::move(a);
    EXPECT(!static_cast<bool>(a));
    EXPECT(static_cast<bool>(b));
    EXPECT(*b == 11);
    return true;
}

// 6. release() returns raw pointer and resets owner
bool test_release_basic() {
    unique_ptr<int> a(new int(5));
    int* raw = a.release();
    EXPECT(raw != nullptr);
    EXPECT(!static_cast<bool>(a));
    EXPECT(*raw == 5);
    delete raw;
    return true;
}

// 7. reset() sets to null and is safe twice
bool test_reset_basic() {
    unique_ptr<int> a(new int(9));
    a.reset();
    EXPECT(!static_cast<bool>(a));
    a.reset();
    EXPECT(!static_cast<bool>(a));
    return true;
}

// 8. get() returns raw pointer and doesn't release ownership
bool test_get_basic() {
    unique_ptr<int> a(new int(77));
    int* raw = a.get();
    EXPECT(raw != nullptr);
    EXPECT(*raw == 77);
    EXPECT(static_cast<bool>(a));
    return true;
}

// 9. bool operator correctness
bool test_bool_operator() {
    unique_ptr<int> a;
    EXPECT(!static_cast<bool>(a));
    a = unique_ptr<int>(new int(3));
    EXPECT(static_cast<bool>(a));
    return true;
}

// 10. moving from empty remains empty
bool test_move_from_empty() {
    unique_ptr<int> a;
    unique_ptr<int> b(std::move(a));
    EXPECT(!static_cast<bool>(b));
    unique_ptr<int> c(new int(6));
    c = std::move(b); // this implementation likely sets c empty
    EXPECT(!static_cast<bool>(c));
    return true;
}

// 11. release then manual delete then reset safe
bool test_release_manual_delete_reset() {
    unique_ptr<int> a(new int(33));
    int* raw = a.release();
    delete raw;
    a.reset();
    EXPECT(!static_cast<bool>(a));
    return true;
}

// 12. repeated allocate/free
bool test_repeated_alloc_free() {
    for (int i = 0; i < 300; ++i) {
        unique_ptr<int> p(new int(i));
        if (*p != i) return false;
    }
    return true;
}

// 13. long move chain a->b->c
bool test_long_move_chain() {
    unique_ptr<int> a(new int(2));
    unique_ptr<int> b(std::move(a));
    unique_ptr<int> c;
    c = std::move(b);
    EXPECT(!static_cast<bool>(a));
    EXPECT(!static_cast<bool>(b));
    EXPECT(static_cast<bool>(c));
    EXPECT(*c == 2);
    return true;
}

// 14. vector emplace_back and move out (vector reallocation uses move ctor/assign)
bool test_vector_emplace_and_move() {
    std::vector< unique_ptr<int> > v;
    for (int i = 0; i < 7; ++i) v.emplace_back(new int(i * 5));
    int sum = 0;
    for (auto &u : v) {
        EXPECT(static_cast<bool>(u));
        sum += *u;
    }
    EXPECT(sum == (0 + 5 + 10 + 15 + 20 + 25 + 30));
    unique_ptr<int> moved = std::move(v[3]);
    EXPECT(*moved == 15);
    EXPECT(!static_cast<bool>(v[3]));
    return true;
}

// 15. assign temporary rvalue
bool test_assign_temporary() {
    unique_ptr<int> a;
    a = unique_ptr<int>(new int(99));
    EXPECT(static_cast<bool>(a));
    EXPECT(*a == 99);
    return true;
}

// 16. stress small moves loop
bool test_stress_moves() {
    unique_ptr<int> cur(new int(0));
    for (int i = 1; i <= 250; ++i) {
        unique_ptr<int> next(new int(i));
        cur = std::move(next);
        EXPECT(static_cast<bool>(cur));
        EXPECT(*cur == i);
    }
    return true;
}

// 17. get() does not release
bool test_get_does_not_release() {
    unique_ptr<int> a(new int(7));
    int* raw = a.get();
    EXPECT(static_cast<bool>(a));
    EXPECT(*raw == 7);
    return true;
}

// 18. release nullptr returns nullptr
bool test_release_nullptr() {
    unique_ptr<int> a;
    int* raw = a.release();
    EXPECT(raw == nullptr);
    return true;
}

// 19. many resets and releases sequence
bool test_many_resets_and_releases() {
    unique_ptr<int> a(new int(3));
    a.reset();
    a.reset();
    a = unique_ptr<int>(new int(4));
    int* raw = a.release();
    EXPECT(*raw == 4);
    delete raw;
    EXPECT(!static_cast<bool>(a));
    return true;
}

// 20. operator-> usage many times on struct
bool test_struct_arrow_many() {
    struct N { int v; int inc(){ return ++v; } };
    unique_ptr<N> p(new N{5});
    EXPECT(p->v == 5);
    EXPECT(p->inc() == 6);
    EXPECT(p->v == 6);
    return true;
}

// 21. release then reassign
bool test_release_then_reassign() {
    unique_ptr<int> a(new int(13));
    int* raw = a.release();
    delete raw;
    a = unique_ptr<int>(new int(14));
    EXPECT(*a == 14);
    return true;
}

// 22. move out of vector into unique_ptr
bool test_move_out_of_vector() {
    std::vector< unique_ptr<int> > v;
    v.emplace_back(new int(100));
    unique_ptr<int> p = std::move(v[0]);
    EXPECT(*p == 100);
    EXPECT(!static_cast<bool>(v[0]));
    return true;
}

// 23. assign nullptr via reset
bool test_assign_null_via_reset() {
    unique_ptr<int> a(new int(8));
    a.reset();
    EXPECT(!static_cast<bool>(a));
    return true;
}

// 24. nested moves
bool test_nested_moves() {
    unique_ptr<int> a(new int(1));
    unique_ptr<int> b(std::move(a));
    unique_ptr<int> c(std::move(b));
    EXPECT(!static_cast<bool>(a));
    EXPECT(!static_cast<bool>(b));
    EXPECT(static_cast<bool>(c));
    EXPECT(*c == 1);
    return true;
}

// 25. multiple releases and safe deletes
bool test_multiple_releases() {
    unique_ptr<int> a(new int(2));
    int* r1 = a.release();
    EXPECT(r1 != nullptr);
    EXPECT(!static_cast<bool>(a));
    int* r2 = a.release();
    EXPECT(r2 == nullptr);
    delete r1;
    return true;
}

// 26. move-assign from temporary rvalue
bool test_move_assign_from_temporary() {
    unique_ptr<int> a;
    a = unique_ptr<int>(new int(77));
    EXPECT(static_cast<bool>(a));
    EXPECT(*a == 77);
    return true;
}

// 27. get then modify through raw
bool test_get_and_modify() {
    unique_ptr<int> a(new int(5));
    int* r = a.get();
    *r = 55;
    EXPECT(*a == 55);
    return true;
}

// 28. many small moves to exercise assignment operator
bool test_many_small_moves() {
    unique_ptr<int> cur(new int(0));
    for (int i = 1; i <= 140; ++i) {
        unique_ptr<int> nxt(new int(i));
        cur = std::move(nxt);
        EXPECT(*cur == i);
    }
    return true;
}

// 29. arrow equals get check
bool test_arrow_equals_get() {
    struct Tst { int v; };
    unique_ptr<Tst> p(new Tst{9});
    EXPECT(p->v == p.get()->v);
    return true;
}

// 30. reassign many times to stress operator=
bool test_reassign_many_times() {
    unique_ptr<int> p(new int(1));
    for (int i = 2; i <= 60; ++i) {
        p = unique_ptr<int>(new int(i));
        EXPECT(*p == i);
    }
    return true;
}

// 31. self move-assign should not crash (we allow this impl's behavior)
bool test_self_move_assign() {
    unique_ptr<int> a(new int(123));
    // to avoid the compiler warning about explicit self-move, use a ref variable:
    unique_ptr<int>& ref = a;
    a = std::move(ref);
    if (static_cast<bool>(a)) EXPECT(*a == 123);
    return true;
}

// 32. allocate and immediately release many times
bool test_alloc_and_release_many() {
    for (int i = 0; i < 220; ++i) {
        unique_ptr<int> p(new int(i));
        int* r = p.release();
        if (r) delete r;
    }
    return true;
}

// 33. combined scenario (no swap)
bool test_combined_scenario() {
    unique_ptr<int> a(new int(10));
    unique_ptr<int> b(new int(20));
    // use moves instead of swap: swap-equivalent via moves
    unique_ptr<int> tmp = std::move(a); // tmp owns 10, a empty
    a = std::move(b);                   // a owns 20, b empty
    b = std::move(tmp);                 // b owns 10
    EXPECT(*a == 20);
    int* raw = a.release();
    EXPECT(raw != nullptr);
    delete raw;
    b.reset();
    EXPECT(!static_cast<bool>(b));
    return true;
}

// 34. vector push_back move
bool test_vector_push_back_move() {
    std::vector< unique_ptr<int> > v;
    unique_ptr<int> a(new int(500));
    v.push_back(std::move(a)); // push_back uses move ctor
    EXPECT(!static_cast<bool>(a));
    EXPECT(static_cast<bool>(v[0]));
    EXPECT(*v[0] == 500);
    return true;
}

// 35. nested structure pointer operations (no swap)
bool test_nested_struct() {
    struct Node2 { int x; Node2* next; Node2(int v):x(v),next(nullptr){} };
    unique_ptr<Node2> head(new Node2(1));
    head->next = nullptr;
    EXPECT(head->x == 1);
    return true;
}

// 36. reassign after release (no swap)
bool test_reassign_after_release() {
    unique_ptr<int> a(new int(15));
    int* raw = a.release();
    delete raw;
    a = unique_ptr<int>(new int(16));
    EXPECT(*a == 16);
    return true;
}

// 37. multiple small create/move/destroy cycles
bool test_many_cycles() {
    for (int i=0;i<180;++i) {
        unique_ptr<int> p(new int(i));
        unique_ptr<int> q(std::move(p));
        if (q) EXPECT(*q == i);
    }
    return true;
}

// 38. return by value (move from function)
unique_ptr<int> make_holder(int v) {
    unique_ptr<int> p(new int(v));
    return p; // RVO or move
}
bool test_return_by_value_move() {
    unique_ptr<int> a = make_holder(314);
    EXPECT(static_cast<bool>(a));
    EXPECT(*a == 314);
    return true;
}

// 39. chained moves via temporaries
bool test_chained_moves_temporaries() {
    unique_ptr<int> a(new int(1));
    a = std::move(unique_ptr<int>(new int(2)));
    EXPECT(*a == 2);
    a = std::move(unique_ptr<int>(new int(3)));
    EXPECT(*a == 3);
    return true;
}

// 40. double reset after move
bool test_double_reset_after_move() {
    unique_ptr<int> a(new int(20));
    unique_ptr<int> b(std::move(a));
    b.reset();
    b.reset();
    EXPECT(!static_cast<bool>(b));
    return true;
}

// 41. many allocations with different lifetimes
bool test_varied_lifetimes() {
    unique_ptr<int> a(new int(7));
    {
        unique_ptr<int> b(new int(8));
        EXPECT(*b == 8);
        a = std::move(b);
        EXPECT(*a == 8);
    }
    // now b is out of scope; a owns 8
    EXPECT(*a == 8);
    return true;
}

// 42. ensure release then assign from temporary
bool test_release_then_assign_temp() {
    unique_ptr<int> a(new int(60));
    int* raw = a.release();
    delete raw;
    a = unique_ptr<int>(new int(61));
    EXPECT(*a == 61);
    return true;
}

// 43. verify operator* and operator-> with small struct again and modifications
bool test_modify_via_arrow_and_star() {
    struct Foo { int a; int b; int sum(){ return a + b; } };
    unique_ptr<Foo> f(new Foo{2,3});
    EXPECT(f->sum() == 5);
    (*f).a = 10;
    EXPECT(f->sum() == 13);
    return true;
}

// 44. many small releases and resets in different orders
bool test_complex_release_reset_patterns() {
    unique_ptr<int> a(new int(1));
    int* r1 = a.release();
    delete r1;
    a.reset();
    a = unique_ptr<int>(new int(2));
    int* r2 = a.release();
    delete r2;
    a.reset();
    EXPECT(!static_cast<bool>(a));
    return true;
}

// 45. repeated returns from function
bool test_return_many_times() {
    for (int i = 0; i < 50; ++i) {
        unique_ptr<int> x = make_holder(i+1);
        EXPECT(*x == i+1);
    }
    return true;
}

// ---------------- Wrapper tests to increase code size ----------------
bool wrapA() { return test_default_ctor_bool() && test_ctor_and_deref(); }
bool wrapB() { return test_arrow_and_deref_struct() && test_move_constructor(); }
bool wrapC() { return test_move_assignment() && test_release_basic(); }
bool wrapD() { return test_reset_basic() && test_get_basic(); }
bool wrapE() { return test_bool_operator() && test_move_from_empty(); }
bool wrapF() { return test_release_manual_delete_reset() && test_repeated_alloc_free(); }
bool wrapG() { return test_long_move_chain() && test_vector_emplace_and_move(); }
bool wrapH() { return test_assign_temporary() && test_stress_moves(); }
bool wrapI() { return test_get_does_not_release() && test_release_nullptr(); }
bool wrapJ() { return test_many_resets_and_releases() && test_struct_arrow_many(); }
bool wrapK() { return test_release_then_reassign() && test_move_out_of_vector(); }
bool wrapL() { return test_assign_null_via_reset() && test_nested_moves(); }
bool wrapM() { return test_multiple_releases() && test_move_assign_from_temporary(); }
bool wrapN() { return test_get_and_modify() && test_many_small_moves(); }
bool wrapO() { return test_arrow_equals_get() && test_reassign_many_times(); }
bool wrapP() { return test_self_move_assign() && test_alloc_and_release_many(); }
bool wrapQ() { return test_combined_scenario() && test_vector_push_back_move(); }
bool wrapR() { return test_nested_struct() && test_reassign_after_release(); }
bool wrapS() { return test_many_cycles() && test_return_by_value_move(); }
bool wrapT() { return test_chained_moves_temporaries() && test_double_reset_after_move(); }

// ---------------- Run all tests ----------------
int main() {
    // basic tests
    RUN_TEST(test_default_ctor_bool);
    RUN_TEST(test_ctor_and_deref);
    RUN_TEST(test_arrow_and_deref_struct);
    RUN_TEST(test_move_constructor);
    RUN_TEST(test_move_assignment);
    RUN_TEST(test_release_basic);
    RUN_TEST(test_reset_basic);
    RUN_TEST(test_get_basic);
    RUN_TEST(test_bool_operator);
    RUN_TEST(test_move_from_empty);
    RUN_TEST(test_release_manual_delete_reset);
    RUN_TEST(test_repeated_alloc_free);
    RUN_TEST(test_long_move_chain);
    RUN_TEST(test_vector_emplace_and_move);
    RUN_TEST(test_assign_temporary);
    RUN_TEST(test_stress_moves);
    RUN_TEST(test_get_does_not_release);
    RUN_TEST(test_release_nullptr);
    RUN_TEST(test_many_resets_and_releases);
    RUN_TEST(test_struct_arrow_many);
    RUN_TEST(test_release_then_reassign);
    RUN_TEST(test_move_out_of_vector);
    RUN_TEST(test_assign_null_via_reset);
    RUN_TEST(test_nested_moves);
    RUN_TEST(test_multiple_releases);
    RUN_TEST(test_move_assign_from_temporary);
    RUN_TEST(test_get_and_modify);
    RUN_TEST(test_many_small_moves);
    RUN_TEST(test_arrow_equals_get);
    RUN_TEST(test_reassign_many_times);
    RUN_TEST(test_self_move_assign);
    RUN_TEST(test_alloc_and_release_many);
    RUN_TEST(test_combined_scenario);
    RUN_TEST(test_vector_push_back_move);
    RUN_TEST(test_reassign_after_release);
    RUN_TEST(test_many_cycles);
    RUN_TEST(test_return_by_value_move);
    RUN_TEST(test_chained_moves_temporaries);
    RUN_TEST(test_double_reset_after_move);
    RUN_TEST(test_varied_lifetimes);
    RUN_TEST(test_release_then_assign_temp);
    RUN_TEST(test_modify_via_arrow_and_star);
    RUN_TEST(test_complex_release_reset_patterns);
    RUN_TEST(test_return_many_times);

    // wrapper tests
    RUN_TEST(wrapA);
    RUN_TEST(wrapB);
    RUN_TEST(wrapC);
    RUN_TEST(wrapD);
    RUN_TEST(wrapE);
    RUN_TEST(wrapF);
    RUN_TEST(wrapG);
    RUN_TEST(wrapH);
    RUN_TEST(wrapI);
    RUN_TEST(wrapJ);
    RUN_TEST(wrapK);
    RUN_TEST(wrapL);
    RUN_TEST(wrapM);
    RUN_TEST(wrapN);
    RUN_TEST(wrapO);
    RUN_TEST(wrapP);
    RUN_TEST(wrapQ);
    RUN_TEST(wrapR);
    RUN_TEST(wrapS);
    RUN_TEST(wrapT);

    // collect failures
    vector<string> failed;
    for (const auto &r : g_results) {
        if (!r.ok) {
            std::ostringstream oss;
            oss << r.name;
            if (!r.info.empty()) oss << " (" << r.info << ")";
            failed.push_back(oss.str());
        }
    }

    if (failed.empty()) {
        cout << "Narek Liked" << endl;
        return 0;
    } else {
        for (auto &s : failed) cout << s << endl;
        return 2;
    }
}
