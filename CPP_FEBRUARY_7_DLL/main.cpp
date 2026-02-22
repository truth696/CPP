#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <string>
#include <cassert>
#include <utility>
#include "TemplateList.hpp"

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

    if(g_failures==0){ std::cout<<"\n✅ ALL TESTS PASSED\n"; return 0;}
    else{ std::cout<<"\n❌ FAILURES: "<<g_failures<<"\n"; return 1;}
}