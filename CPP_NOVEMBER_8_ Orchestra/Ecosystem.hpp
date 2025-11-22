#include <string>
#include <iostream>

class Serializable{
    public:
    virtual std::string serialize() const = 0;
};

class Entity{
protected:
    std::string name;
    int energy;
public:
    Entity(std::string _name = "Unknow", int _energy = 5) : name(_name) , energy(_energy) {} 

    virtual void act() { }
    virtual void move() { }
    virtual int info() const { return energy; }
    virtual ~Entity() = default;
};

class Entits{
    std::vector<Entity*> vec;
public:
    void add (Entity* i) { vec.push_back(i); }
    void play() { 
        for(Entity* i: vec) {
            i->move();
            i->act();
            Serializable* ptr = dynamic_cast<Serializable*>(i);
            if(ptr) std::cout << ptr->serialize() << std::endl;
            else std::cout << "Can't serialize this entity..." << std::endl;
        }
    }
    ~Entits() { for(Entity* i : vec) delete i; }
};

class Animal : public Entity, public Serializable{
    public:
        Animal() : Entity("Animal") {}
    virtual void act () override { std::cout << "Wolf hunts for food" << std::endl; }
    virtual void move () override { std::cout << "Chap chap chap" << std::endl; }
        virtual int info () const override { return energy;}
        virtual std::string serialize() const override { return name; }
};


class Drone : public Entity, public Serializable{
    public:
        Drone() : Entity("Drone") {}
        virtual void act () override { std::cout << "Drone scans the area." << std::endl; }
        virtual void move () override { std::cout << "Bzz bzz bzz " << std::endl; }
        virtual int info () const override { return energy; }
        virtual std::string serialize() const override{ return name; }
};

class Robot : public Entity{
    public:
        Robot() : Entity("Robot") {}
        virtual void act () override { std::cout << "Robot optimizes logistics." << std::endl; }
        virtual void move () override { std::cout << "Chap bzz Chap bzz" << std::endl; }
        virtual int info () const override { return energy; }
};



