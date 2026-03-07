#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <string>
#include <cassert>
#include <utility>
#include "TemplateList.hpp"

#define LIST_ASSERT(cond) \
    if (!(cond)) { \
        std::cout << "FAILED: " << #cond << " at line " << __LINE__ << std::endl; \
        std::exit(1); \
    }

#define LIST_PRINT(lst) \
    for (auto x : lst) std::cout << x << " "; \
    std::cout << std::endl;

#define LIST_SECTION(name) \
    std::cout << "\n=== " << name << " ===\n";

#define CHECK(cond, name) \
    if (!(cond)) throw std::runtime_error(name);

static int g_failures = 0;

// ===== Macros =====
#define CHECK_TRUE(expr) \
    do { if (!(expr)) { ++g_failures; std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " " << #expr << "\n"; } } while(0)

#define CHECK_EQ(a,b) \
    do { auto _a=(a); auto _b=(b); if (!(_a==_b)) { ++g_failures; std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " " << #a << " == " << #b << " (got " << _a << " vs " << _b << ")\n"; } } while(0)

#define SECTION(name) \
    do { std::cout << "\n==== " << (name) << " ====\n"; } while(0)

// ===== Helpers =====
template <typename T>
std::vector<T> drain_back(List<T>& lst) {
    std::vector<T> out;
    while (!lst.empty()) {
        out.push_back(lst.back());
        lst.pop_back();
    }
    return out;
}

template <typename T>
void check_size_back(List<T>& lst, const std::vector<T>& ref) {
    CHECK_EQ(lst.size(), ref.size());
    CHECK_EQ(lst.empty(), ref.empty());
    if (!ref.empty()) CHECK_EQ(lst.back(), ref.back());
}

// ===== Basic push/pop tests =====
void test_push_back_basic() {
    SECTION("push_back basic");
    List<int> lst;
    std::vector<int> ref;
    for (int i = 1; i <= 50; ++i) {
        lst.push_back(i);
        ref.push_back(i);
        check_size_back(lst, ref);
    }
}

void test_pop_back_basic() {
    SECTION("pop_back basic");
    List<int> lst;
    std::vector<int> ref;
    for (int i=0;i<30;i++){ lst.push_back(i*10); ref.push_back(i*10);}
    for (int i=0;i<30;i++){
        check_size_back(lst, ref);
        lst.pop_back(); ref.pop_back();
    }
    CHECK_TRUE(lst.empty());
    CHECK_EQ(lst.size(),0u);
}

void test_push_front_basic() {
    SECTION("push_front basic");
    List<int> lst; std::deque<int> ref;
    for (int i=1;i<=20;i++){
        lst.push_front(i); ref.push_front(i);
        CHECK_EQ(lst.size(), ref.size());
        CHECK_EQ(lst.empty(), ref.empty());
        CHECK_EQ(lst.back(), ref.back());
    }
}

void test_pop_front_basic() {
    SECTION("pop_front basic");
    List<int> lst; std::deque<int> ref;
    for (int i=1;i<=25;i++){ lst.push_back(i); ref.push_back(i);}
    CHECK_EQ(lst.back(), ref.back());
    for (int k=0;k<24;k++){
        lst.pop_front(); ref.pop_front();
        CHECK_EQ(lst.size(), ref.size());
        CHECK_EQ(lst.empty(), ref.empty());
        CHECK_EQ(lst.back(), ref.back());
    }
    CHECK_EQ(lst.size(), 1u);
    lst.pop_front();
    CHECK_TRUE(lst.empty());
}

// ===== Constructors & assignment =====
void test_initializer_list_ctor() {
    SECTION("initializer_list ctor");
    List<int> lst({1,2,3,4,5});
    CHECK_EQ(lst.size(), 5u);
    CHECK_EQ(lst.back(), 5);
    auto drained = drain_back(lst);
    std::vector<int> expected{5,4,3,2,1};
    CHECK_EQ(drained.size(), expected.size());
    for (size_t i=0;i<expected.size();i++) CHECK_EQ(drained[i], expected[i]);
    CHECK_TRUE(lst.empty());
}

void test_vector_ctor() {
    SECTION("vector ctor");
    std::vector<int> v{10,11,12,13,14,15,16,17,18,19};
    List<int> lst(v);
    CHECK_EQ(lst.size(), v.size());
    CHECK_EQ(lst.back(), v.back());
    auto drained = drain_back(lst);
    CHECK_EQ(drained.size(), v.size());
    for (size_t i=0;i<v.size();i++) CHECK_EQ(drained[i], v[v.size()-1-i]);
}

void test_copy_ctor() {
    SECTION("copy ctor");
    List<int> a({7,8,9,10});
    List<int> b(a);
    CHECK_EQ(a.size(),4u); CHECK_EQ(b.size(),4u);
    CHECK_EQ(a.back(),10); CHECK_EQ(b.back(),10);
    auto da = drain_back(a); auto db = drain_back(b);
    CHECK_EQ(da.size(), db.size());
    for (size_t i=0;i<da.size();i++) CHECK_EQ(da[i], db[i]);
}

void test_move_ctor() {
    SECTION("move ctor");
    List<int> a({1,2,3});
    List<int> b(std::move(a));
    CHECK_EQ(b.size(),3u); CHECK_EQ(b.back(),3);
    CHECK_TRUE(a.empty()); CHECK_EQ(a.size(),0u);
    auto db = drain_back(b);
    std::vector<int> expected{3,2,1};
    for (size_t i=0;i<expected.size();i++) CHECK_EQ(db[i], expected[i]);
}

void test_copy_assignment() {
    SECTION("copy assignment");
    List<int> a({5,6,7});
    List<int> b({100,200});
    b = a;
    CHECK_EQ(b.size(),3u); CHECK_EQ(b.back(),7);
    auto da = drain_back(a); auto db = drain_back(b);
    CHECK_EQ(da.size(),db.size());
    for (size_t i=0;i<da.size();i++) CHECK_EQ(da[i],db[i]);
}

void test_move_assignment() {
    SECTION("move assignment");
    List<int> a({11,22,33,44});
    List<int> b({1});
    b = std::move(a);
    CHECK_EQ(b.size(),4u); CHECK_EQ(b.back(),44);
    CHECK_TRUE(a.empty()); CHECK_EQ(a.size(),0u);
    auto db = drain_back(b);
    std::vector<int> expected{44,33,22,11};
    for (size_t i=0;i<expected.size();i++) CHECK_EQ(db[i],expected[i]);
}

void test_clear_reuse() {
    SECTION("clear + reuse");
    List<int> lst({1,2,3,4});
    CHECK_EQ(lst.size(),4u);
    lst.clear(); CHECK_TRUE(lst.empty()); CHECK_EQ(lst.size(),0u);
    lst.push_back(9); lst.push_front(8);
    CHECK_EQ(lst.size(),2u); CHECK_EQ(lst.back(),9);
}

void test_swap() {
    SECTION("swap");
    List<int> a({1,2,3}); List<int> b({10,20});
    a.swap(b);
    CHECK_EQ(a.size(),2u); CHECK_EQ(b.size(),3u); CHECK_EQ(a.back(),20); CHECK_EQ(b.back(),3);
}

void test_insert_erase_tail_effects() {
    SECTION("insert/erase tail effects");
    List<int> lst({1,2,3});
    CHECK_EQ(lst.back(),3);
    lst.insert(lst.size(),99); CHECK_EQ(lst.back(),99);
    lst.erase(lst.size()-1); CHECK_EQ(lst.back(),3);
    lst.insert(0,-5); CHECK_EQ(lst.back(),3);
    lst.erase(0); CHECK_EQ(lst.back(),3);
}

void test_random_stress(int seed) {
    SECTION("random stress");
    std::mt19937 rng(seed); std::uniform_int_distribution<int> valDist(-100000,100000);
    std::uniform_int_distribution<int> opDist(0,7);
    List<int> lst; std::vector<int> ref;
    const int OPS = 20000;
    for(int step=1;step<=OPS;step++){
        int op=opDist(rng);
        if(ref.empty()) op%=3;
        switch(op){
            case 0:{ int v=valDist(rng); lst.push_back(v); ref.push_back(v); break;}
            case 1:{ int v=valDist(rng); lst.push_front(v); ref.insert(ref.begin(),v); break;}
            case 2:{ int v=valDist(rng); size_t pos=(ref.empty()?0:(size_t)(rng()% (ref.size()+1))); lst.insert(pos,v); ref.insert(ref.begin()+(long)pos,v); break;}
            case 3:{ lst.pop_back(); ref.pop_back(); break;}
            case 4:{ lst.pop_front(); ref.erase(ref.begin()); break;}
            case 5:{ size_t pos=(size_t)(rng()%ref.size()); lst.erase(pos); ref.erase(ref.begin()+(long)pos); break;}
            case 6:{ if((rng()%50)==0){ lst.clear(); ref.clear();} break;}
            case 7:{ if((rng()%40)==0){ List<int> cpy(lst); List<int> tmp(std::move(cpy)); CHECK_EQ(tmp.size(),ref.size()); if(!ref.empty()) CHECK_EQ(tmp.back(),ref.back()); } break;}
        }
        if(step%200==0) check_size_back(lst,ref);
    }
    check_size_back(lst,ref);
    auto drained=drain_back(lst);
    CHECK_EQ(drained.size(), ref.size());
    for(size_t i=0;i<ref.size();i++) CHECK_EQ(drained[i],ref[ref.size()-1-i]);
}

void test_strings() {
    SECTION("strings");
    List<std::string> lst;
    lst.push_back("a"); lst.push_back(std::string("b")); lst.push_front("z");
    CHECK_EQ(lst.size(),3u); CHECK_EQ(lst.back(),"b");
    lst.pop_front(); CHECK_EQ(lst.size(),2u); CHECK_EQ(lst.back(),"b");
    lst.insert(2,"tail"); CHECK_EQ(lst.back(),"tail");
    lst.erase(2); CHECK_EQ(lst.back(),"b");
    lst.clear(); CHECK_TRUE(lst.empty());
}

void test_edge_cases() {
    SECTION("edge cases");
    List<int> a; CHECK_TRUE(a.empty());
    a.push_back(1); CHECK_EQ(a.size(),1u); CHECK_EQ(a.back(),1);
    a.pop_front(); CHECK_TRUE(a.empty());
    a.push_front(2); CHECK_EQ(a.size(),1u); CHECK_EQ(a.back(),2);
    a.pop_back(); CHECK_TRUE(a.empty());
    a.insert(0,10); CHECK_EQ(a.size(),1u); CHECK_EQ(a.back(),10);
    a.erase(0); CHECK_TRUE(a.empty());
    List<int> b({1,2,3}); a.swap(b);
    CHECK_EQ(a.size(),3u); CHECK_TRUE(b.empty()); CHECK_EQ(a.back(),3);
}

// ===== MAIN =====
int main() {
    std::cout << "Running List<T> mega tests...\n";

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

    List<int> lst;

    std::cout << "=== push_back ===\n";
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    for (auto it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " "; // 1 2 3
    std::cout << "\n";

    std::cout << "=== push_front ===\n";
    lst.push_front(0);
    lst.push_front(-1);

    for (auto it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " "; // -1 0 1 2 3
    std::cout << "\n";

    std::cout << "=== insert by iterator ===\n";
    auto it = lst.begin();
    ++it; // points to 0
    lst.insert(it, 99); // insert 99 before 0

    for (auto val : lst)
        std::cout << val << " "; // -1 99 0 1 2 3
    std::cout << "\n";

    std::cout << "=== insert by position ===\n";
    lst.insert(3, 77); // insert 77 at index 3

    for (auto val : lst)
        std::cout << val << " "; // -1 99 0 77 1 2 3
    std::cout << "\n";

    std::cout << "=== erase by iterator ===\n";
    it = lst.begin();
    ++it; // points to 99
    lst.erase(it);

    for (auto val : lst)
        std::cout << val << " "; // -1 0 77 1 2 3
    std::cout << "\n";

    std::cout << "=== erase by position ===\n";
    lst.erase(2); // remove 77

    for (auto val : lst)
        std::cout << val << " "; // -1 0 1 2 3
    std::cout << "\n";

    std::cout << "=== pop_front and pop_back ===\n";
    lst.pop_front(); // removes -1
    lst.pop_back();  // removes 3

    for (auto val : lst)
        std::cout << val << " "; // 0 1 2
    std::cout << "\n";

    std::cout << "=== iterator increment/decrement ===\n";
    auto it2 = lst.begin();
    std::cout << *it2 << " "; // 0
    ++it2;
    std::cout << *it2 << " "; // 1
    --it2;
    std::cout << *it2 << "\n"; // 0

    std::cout << "=== initializer_list constructor ===\n";
    List<int> lst2{10, 20, 30};
    for (auto val : lst2) std::cout << val << " "; // 10 20 30
    std::cout << "\n";

    std::cout << "=== vector constructor ===\n";
    std::vector<int> vec{5, 6, 7};
    List<int> lst3(vec);
    for (auto val : lst3) std::cout << val << " "; // 5 6 7
    std::cout << "\n";

    std::cout << "=== swap ===\n";
    lst.swap(lst3);
    std::cout << "lst after swap: ";
    for (auto val : lst) std::cout << val << " "; // 5 6 7
    std::cout << "\n";
    std::cout << "lst3 after swap: ";
    for (auto val : lst3) std::cout << val << " "; // 0 1 2
    std::cout << "\n";

    std::cout << "=== clear ===\n";
    lst.clear();
    std::cout << "lst empty? " << lst.empty() << "\n"; // 1

    std::cout << "\n";

    LIST_SECTION("BASIC CONSTRUCTION");
    List<int> a;
    LIST_ASSERT(a.empty());
    LIST_ASSERT(a.size() == 0);

    LIST_SECTION("PUSH BACK");
    for (int i = 0; i < 10; ++i)
        a.push_back(i);

    LIST_ASSERT(a.size() == 10);
    LIST_ASSERT(a.back() == 9);

    LIST_SECTION("ITERATOR FORWARD");
    int counter = 0;
    for (auto it = a.begin(); it != a.end(); ++it)
        LIST_ASSERT(*it == counter++);

    LIST_SECTION("CONST ITERATOR");
    const List<int>& cref = a;
    counter = 0;
    for (auto it = cref.cbegin(); it != cref.cend(); ++it)
        LIST_ASSERT(*it == counter++);

    LIST_SECTION("REVERSE ITERATOR");
    counter = 9;
    for (auto it = a.rbegin(); it != a.rend(); ++it)
        LIST_ASSERT(*it == counter--);

    LIST_SECTION("COPY CONSTRUCTOR");
    List<int> b(a);
    LIST_ASSERT(b.size() == a.size());

    counter = 0;
    for (auto it = b.begin(); it != b.end(); ++it)
        LIST_ASSERT(*it == counter++);

    LIST_SECTION("MOVE CONSTRUCTOR");
    List<int> c(std::move(b));
    LIST_ASSERT(c.size() == 10);
    LIST_ASSERT(b.size() == 0);

    LIST_SECTION("COPY ASSIGNMENT");
    List<int> d;
    d = c;
    LIST_ASSERT(d.size() == 10);

    LIST_SECTION("MOVE ASSIGNMENT");
    List<int> e;
    e = std::move(d);
    LIST_ASSERT(e.size() == 10);
    LIST_ASSERT(d.size() == 0);

    LIST_SECTION("INSERT BY INDEX");
    e.insert(0, 100);
    LIST_ASSERT(*e.begin() == 100);

    e.insert(5, 200);
    LIST_ASSERT(e.size() == 12);

    LIST_SECTION("ERASE BY INDEX");
    e.erase(0);
    LIST_ASSERT(*e.begin() == 0);

    LIST_SECTION("POP FRONT / BACK");
    e.pop_front();
    e.pop_back();
    LIST_ASSERT(e.size() == 9);

    LIST_SECTION("ITERATOR INSERT");
    auto it44332 = e.begin();
    ++it44332;
    e.insert(it44332, 999);
    LIST_ASSERT(e.size() == 10);

    LIST_SECTION("ITERATOR ERASE");
    it = e.begin();
    ++it;
    e.erase(it);
    LIST_ASSERT(e.size() == 9);

    LIST_SECTION("RANGE INSERT");
    List<int> f;
    f.push_back(7);
    f.push_back(8);
    f.push_back(9);

    e.insert(e.begin(), f.begin(), f.end());
    LIST_ASSERT(e.size() == 12);

    LIST_SECTION("RANGE ERASE");
    auto first = e.begin();
    auto last = first;
    for (int i = 0; i < 3; ++i) ++last;
    e.erase(first, last);
    LIST_ASSERT(e.size() == 9);

    LIST_SECTION("REVERSE INSERT");
    auto rit = e.rbegin();
    e.insert(rit, 555);
    LIST_ASSERT(e.size() == 10);

    LIST_SECTION("REVERSE ERASE");
    rit = e.rbegin();
    e.erase(rit);
    LIST_ASSERT(e.size() == 9);

    LIST_SECTION("CONST REVERSE ITERATOR");
    const List<int>& cref2 = e;
    for (auto it2 = cref2.rbegin(); it2 != cref2.rend(); ++it2)
        (void)*it2;

    LIST_SECTION("EMPLACE TEST");
    List<std::string> s;
    s.emplace_back("hello");
    s.emplace_front("world");
    LIST_ASSERT(s.size() == 2);

    LIST_SECTION("SWAP");
    List<int> x;
    x.push_back(1);
    x.push_back(2);

    List<int> y;
    y.push_back(10);

    x.swap(y);
    LIST_ASSERT(x.size() == 1);
    LIST_ASSERT(y.size() == 2);

    LIST_SECTION("CLEAR");
    x.clear();
    LIST_ASSERT(x.empty());

    LIST_SECTION("STRESS TEST");
    List<int> stress;

    for (int i = 0; i < 1000; ++i)
        stress.push_back(i);

    LIST_ASSERT(stress.size() == 1000);

    for (int i = 0; i < 500; ++i)
        stress.pop_front();

    LIST_ASSERT(stress.size() == 500);

    for (int i = 0; i < 500; ++i)
        stress.pop_back();

    LIST_ASSERT(stress.empty());

    LIST_SECTION("SELF ASSIGN");
    stress = stress;
    LIST_ASSERT(stress.empty());

    LIST_SECTION("COMPLEX CHAIN");
    List<int> chain;
    for (int i = 0; i < 20; ++i)
        chain.emplace_back(i);

    auto mid = chain.begin();
    for (int i = 0; i < 10; ++i) ++mid;

    chain.erase(mid);
    chain.insert(chain.begin(), 777);
    chain.erase(chain.begin());

    LIST_ASSERT(chain.size() == 19);

    std::cout << "\nALL TESTS PASSED\n";

    try 
    {
        std::cout << "Inside try\n";

        // ====== TEST 1 ======
        {
            std::cout << "Test 1 start\n";

            List<int> lst;
            lst.push_back(1);
            lst.push_back(2);
            lst.push_back(3);

            std::cout << "Test 1 end\n";
        }

        // ====== TEST 2 ======
        {
            std::cout << "Test 2 start\n";

            List<int> lst;
            lst.push_back(10);
            lst.push_back(20);

            const List<int>& clst = lst;

            std::vector<int> v;
            for (auto it = clst.cbegin(); it != clst.cend(); ++it)
                v.push_back(*it);

            std::cout << "Vector size = " << v.size() << "\n";
            std::cout << "Test 2 end\n";
        }

        std::cout << "successful\n";
    }
    catch (const std::exception& e) 
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\n";
    try
    {
        std::cout << "Inside try\n";
        List<int> lst = {1,2,3,4,5};

        // ===============================
        // iterator: forward iteration
        // ===============================
        {
            std::vector<int> v;
            for (auto it = lst.begin(); it != lst.end(); ++it)
                v.push_back(*it);

            CHECK(v == std::vector<int>({1,2,3,4,5}), "iterator ++");
        }

        // ===============================
        // iterator: post++
        // ===============================
        {
            std::vector<int> v;
            for (auto it = lst.begin(); it != lst.end(); it++)
                v.push_back(*it);

            CHECK(v == std::vector<int>({1,2,3,4,5}), "iterator post++");
        }

        // ===============================
        // iterator: --
        // ===============================
        {
            std::vector<int> v;
            auto it = lst.end();
            --it;
            for (;;)
            {
                v.push_back(*it);
                if (it == lst.begin()) break;
                --it;
            }

            CHECK(v == std::vector<int>({5,4,3,2,1}), "iterator --");
        }

        // ===============================
        // const_iterator
        // ===============================
        {
            const List<int>& clst = lst;

            std::vector<int> v;
            for (auto it = clst.cbegin(); it != clst.cend(); ++it)
                v.push_back(*it);

            CHECK(v == std::vector<int>({1,2,3,4,5}), "const_iterator");
        }

        // ===============================
        // reverse_iterator ++
        // ===============================
        {
            std::vector<int> v;
            for (auto it = lst.rbegin(); it != lst.rend(); ++it)
                v.push_back(*it);

            CHECK(v == std::vector<int>({5,4,3,2,1}), "reverse_iterator ++");
        }

        // ===============================
        // reverse_iterator post++
        // ===============================
        {
            std::vector<int> v;
            for (auto it = lst.rbegin(); it != lst.rend(); it++)
                v.push_back(*it);

            CHECK(v == std::vector<int>({5,4,3,2,1}), "reverse_iterator post++");
        }

        // ===============================
        // reverse_iterator --
        // ===============================
        {
            std::vector<int> v;
            auto it = lst.rend();
            --it;

            for (;;)
            {
                v.push_back(*it);
                if (it == lst.rbegin()) break;
                --it;
            }

            CHECK(v == std::vector<int>({1,2,3,4,5}), "reverse_iterator --");
        }

        // ===============================
        // iterator range insert
        // ===============================
        {
            List<int> a = {10,20};
            List<int> b = {1,2,3};

            a.insert(a.begin(), b.begin(), b.end());

            std::vector<int> v;
            for (auto it = a.begin(); it != a.end(); ++it)
                v.push_back(*it);

            CHECK(v == std::vector<int>({1,2,3,10,20}), "iterator range insert");
        }

        // ===============================
        // reverse_iterator range insert
        // ===============================
        {
            List<int> a = {100};
            List<int> b = {7,8};

            a.insert(a.rbegin(), b.rbegin(), b.rend());

            std::vector<int> v;
            for (auto it = a.begin(); it != a.end(); ++it)
                v.push_back(*it);
        }

        std::cout << "successful" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Inside catch\n";
        std::cout << "failed in: " << e.what() << "\n";
    }

    List<int> lst1;

    std::cout << "=== push_back ===\n";
    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(3);

    for (auto it = lst1.begin(); it != lst1.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";


    std::cout << "=== push_front ===\n";
    lst1.push_front(0);
    lst1.push_front(-1);

    for (auto it = lst1.begin(); it != lst1.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";


    std::cout << "=== reverse iteration ===\n";
    for (auto it = lst1.rbegin(); it != lst1.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";


    std::cout << "=== insert by iterator ===\n";
    auto it1 = lst1.begin();
    ++it1; // указываем на 0
    lst1.insert(it1, 100);

    for (auto x = lst1.begin(); x != lst1.end(); ++x)
        std::cout << *x << " ";
    std::cout << "\n\n";


    std::cout << "=== erase by it1erator ===\n";
    it1 = lst1.begin();
    ++it1; // 100
    lst1.erase(it1);

    for (auto x = lst1.begin(); x != lst1.end(); ++x)
        std::cout << *x << " ";
    std::cout << "\n\n";


    std::cout << "=== insert by index ===\n";
    lst1.insert(2, 555);

    for (auto x = lst1.begin(); x != lst1.end(); ++x)
        std::cout << *x << " ";
    std::cout << "\n\n";


    std::cout << "=== erase by index ===\n";
    lst1.erase(2);

    for (auto x = lst1.begin(); x != lst1.end(); ++x)
        std::cout << *x << " ";
    std::cout << "\n\n";


    std::cout << "=== pop_front / pop_back ===\n";
    lst1.pop_front();
    lst1.pop_back();

    for (auto x = lst1.begin(); x != lst1.end(); ++x)
        std::cout << *x << " ";
    std::cout << "\n\n";


    std::cout << "=== size / empty ===\n";
    std::cout << "Size: " << lst1.size() << "\n";
    std::cout << "Empty: " << std::boolalpha << lst1.empty() << "\n\n";


    std::cout << "=== clear ===\n";
    lst1.clear();
    std::cout << "Size after clear: " << lst1.size() << "\n";
    std::cout << "Empty after clear: " << std::boolalpha << lst1.empty() << "\n";

    if(g_failures==0){ std::cout<<"\n✅ ALL TESTS PASSED\n"; return 0;}
    else{ std::cout<<"\n❌ FAILURES: "<<g_failures<<"\n"; return 1;}
}

