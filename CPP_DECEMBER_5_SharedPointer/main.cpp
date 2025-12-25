#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <cstddef>
#include "SharedPointer.hpp"

struct Test { int x; Test(int v=0):x(v){} ~Test(){} };

void assert_ok(bool cond, const std::string& fn){
    if(!cond){
        std::cout<<fn;
        exit(0);
    }
}

void t_ctor(){
    shared_ptr<int> p(new int(5));
    assert_ok(p.use_count()==1,"t_ctor");
}

void t_null_ctor(){
    shared_ptr<int> p(nullptr);
    assert_ok(p.use_count()==0,"t_null_ctor");
}

void t_deref(){
    shared_ptr<int> p(new int(7));
    assert_ok(*p==7,"t_deref");
}

void t_arrow(){
    shared_ptr<Test> p(new Test(10));
    assert_ok(p->x==10,"t_arrow");
}

void t_copy_ctor(){
    shared_ptr<int> a(new int(1));
    shared_ptr<int> b(a);
    assert_ok(a.use_count()==2,"t_copy_ctor");
    assert_ok(b.use_count()==2,"t_copy_ctor");
}

void t_copy_assign(){
    shared_ptr<int> a(new int(3));
    shared_ptr<int> b;
    b = a;

    assert_ok(a.use_count()==2,"t_copy_assign");
    assert_ok(b.use_count()==2,"t_copy_assign");
}

void t_copy_chain(){
    shared_ptr<int> a(new int(11));
    shared_ptr<int> b(a);
    shared_ptr<int> c(b);
    assert_ok(a.use_count()==3,"t_copy_chain");
    assert_ok(b.use_count()==3,"t_copy_chain");
    assert_ok(c.use_count()==3,"t_copy_chain");
}

void t_move_ctor(){
    shared_ptr<int> a(new int(55));
    
    int* old = a.get();
    
    shared_ptr<int> b(std::move(a));
    assert_ok(!a,"t_move_ctor");
    
    assert_ok(b.get()==old,"t_move_ctor");
    
    assert_ok(b.use_count()==1,"t_move_ctor");
    // std::cout << "aed" << std::endl;


}

void t_move_assign(){

    shared_ptr<int> a(new int(78));

    shared_ptr<int> b;
    int* old=a.get();
    b=std::move(a);
    assert_ok(!a,"t_move_assign");
    assert_ok(b.get()==old,"t_move_assign");
    assert_ok(b.use_count()==1,"t_move_assign");
}

void t_reset(){
    shared_ptr<int> a(new int(9));
    a.reset();
    assert_ok(!a,"t_reset");
}

void t_reset_chain(){
    shared_ptr<int> a(new int(6));
    shared_ptr<int> b(a);
    shared_ptr<int> c(b);
    a.reset();
    assert_ok(b.use_count()==2,"t_reset_chain");
    b.reset();
    assert_ok(c.use_count()==1,"t_reset_chain");
    c.reset();
}

void t_unique_true(){
    shared_ptr<int> a(new int(111));
    assert_ok(a.unique()==true,"t_unique_true");
}

void t_unique_false(){
    shared_ptr<int> a(new int(222));
    shared_ptr<int> b(a);
    assert_ok(a.unique()==false,"t_unique_false");
    assert_ok(b.unique()==false,"t_unique_false");
}

void t_operator_bool(){
    shared_ptr<int> a(new int(3));
    assert_ok(bool(a)==true,"t_operator_bool");
    a.reset();
    assert_ok(bool(a)==false,"t_operator_bool");
}

void t_get(){
    shared_ptr<int> a(new int(5));
    assert_ok(*a.get()==5,"t_get");
}

void t_many_copies(){
    shared_ptr<int> a(new int(100));
    for(int i=0;i<100;i++){
        shared_ptr<int> b(a);
        assert_ok(a.use_count()>=1,"t_many_copies");
    }
}

void t_many_moves(){
    shared_ptr<int> a(new int(200));
    for(int i=0;i<100;i++){
        shared_ptr<int> b(std::move(a));
        a=b;
    }
    assert_ok(a.use_count()==1,"t_many_moves");
}

void t_vector_store(){
    shared_ptr<int> a(new int(300));
    std::vector<shared_ptr<int>> v;
    for(int i=0;i<150;i++) v.push_back(a);
    assert_ok(a.use_count()==151,"t_vector_store");
    for(int i=0;i<150;i++) v[i].reset();
    assert_ok(a.use_count()==1,"t_vector_store");
    a.reset();
}

void t_swap(){
    shared_ptr<int> a(new int(1));
    shared_ptr<int> b(new int(2));
    int* pa=a.get();
    int* pb=b.get();
    a.swap(b);
    assert_ok(a.get()==pb,"t_swap");
    assert_ok(b.get()==pa,"t_swap");
}

void t_chain_modify(){
    shared_ptr<int> a(new int(5));
    shared_ptr<int> b(a);
    *b=10;
    assert_ok(*a==10,"t_chain_modify");
}

void t_stress(){
    for(int i=0;i<300;i++){
        shared_ptr<int> a(new int(i));
        shared_ptr<int> b(a);
        shared_ptr<int> c(b);
        assert_ok(a.use_count()==3,"t_stress");
    }
}

void t_big_alloc(){
    shared_ptr<int> a(new int(123));
    {
        shared_ptr<int> b(a);
        {
            shared_ptr<int> c(b);
            {
                shared_ptr<int> d(c);
                assert_ok(d.use_count()==4,"t_big_alloc1");
            }
            assert_ok(b.use_count()==3,"t_big_alloc2");
        }
        assert_ok(a.use_count()==2,"t_big_alloc3");
    }
    assert_ok(a.use_count()==1,"t_big_alloc_end");
    a.reset();
}

void t_loop_moves(){
    shared_ptr<int> cur(new int(5));
    for(int i=0;i<200;i++){
        shared_ptr<int> nxt(std::move(cur));
        cur=nxt;
    }
    assert_ok(cur.use_count()==1,"t_loop_moves");
}

void t_bulk(){
    for(int i=0;i<200;i++){
        shared_ptr<int> a(new int(i));
        for(int j=0;j<5;j++){
            shared_ptr<int> b(a);
            assert_ok(a.use_count()>=1,"t_bulk");
        }
    }
}

void t_operators(){
    shared_ptr<int> a(new int(9));
    shared_ptr<int> b(a);
    *b = 77;
    assert_ok(*a == 77, "t_operators");
}


void call_all(){
    
    t_ctor(); 
    t_null_ctor(); 
    t_deref(); 
    t_arrow(); 
    t_copy_ctor(); 
    t_copy_assign(); 
    t_copy_chain();
    t_move_ctor(); 
    t_move_assign(); 
    t_reset(); 
    t_reset_chain(); 
    t_unique_true(); 
    t_unique_false();
    t_operator_bool(); 
    t_get();
    t_many_copies();
    t_many_moves();
    t_vector_store();
    t_swap();
    t_chain_modify();
    t_stress(); 
    t_big_alloc();
    t_loop_moves();
    t_bulk(); 
    t_operators();
}

int main(){

    call_all();
    std::cout<<"Narek liked";
}
