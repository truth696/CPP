#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

enum class Kind { 
    Animal, Mammal, Bird, Reptile,
    Lion, Tiger, Elephant,
    Eagle, Parrot,
    Snake, Crocodile
};

class Counter {
    inline static int _id;
    friend class Animal;
};

class Animal {
    protected:
    std::string name;
    size_t hunger; 
    size_t health;
    Kind kind;
    int id;
    
    public:
    //ctor
    Animal() : name("Unknow"), kind(Kind::Animal), hunger(20), health(100){ 
        kind = Kind::Animal; 
        this->id = ++Counter::_id;
    }
    Animal(const std::string _name, Kind k = Kind::Animal) : name(_name), kind(k), hunger(0), health(100){
        this->id = ++Counter::_id;
    }
    //memfu
    void PrintInfo() const;
    void Feed();
    Kind KindOf() const;
    inline int getID() const { return id; }
};

