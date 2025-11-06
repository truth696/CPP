#pragma once
#include "Zoo.hpp"


class Bird : public Animal{
    protected:
        double wingSpan;
    public:
        Bird() : wingSpan(0) {}
        Bird(const std::string _name, Kind k = Kind::Bird, double _wingSpan = 0) : Animal(_name, k), wingSpan(_wingSpan) {}
        double getWingSpan() { return wingSpan; }
        void Fly(); 
};

class Reptile : public Animal{
    protected:
        const bool coldBlooded;
    public: 
        Reptile() : coldBlooded(true) {}
        Reptile(const std::string _name, Kind k = Kind::Reptile) : Animal(_name, k), coldBlooded(true) {}
        void Sunbathe() const;
};

class Mamal : public Animal{
    protected:
        const bool warmBlooded;
    public:
        Mamal() : warmBlooded(true) {} 
        Mamal(const std::string _name, Kind k = Kind::Mammal) : Animal (_name, k), warmBlooded(true) {}
};


class Lion : public Mamal {
    int roarPower;
    public:
        Lion() : roarPower(3) {}
        Lion(const std::string _name,  size_t _roarPower = 3, Kind k = Kind::Lion) : Mamal(_name, k) , roarPower(_roarPower) {}
        void Roar() const; 
        void MakeSound() const;
        void PrintInfo() const;
        
    };
    
    
    class Tiger : public Mamal {
        double jumpHeight;
        public:
            Tiger() : jumpHeight(1.0) {}
            Tiger(const std::string _name, size_t _jumpHeight = 1.0, Kind k = Kind::Tiger) : Mamal(_name, k) , jumpHeight(_jumpHeight) {} 
            void Jump() const;
            void MakeSound() const;
            void PrintInfo() const;
    };
    
    class Elephant : public Mamal {
        double trunkLength;
        public:
            Elephant() : trunkLength(2.0) { }
            Elephant(const std::string _name, size_t length = 2.0, Kind k = Kind::Elephant) : Mamal(_name, k) , trunkLength(length) { }
            void UseTrunk() const;
            void MakeSound() const;
            void PrintInfo() const;
    };
    
    class Eagle : public Bird {
        double visionRange;
        public:
            Eagle() : visionRange(15.5) { }
            Eagle(const std::string _name, size_t vison = 15, Kind k = Kind::Eagle) : Bird(_name, k) , visionRange(vison) {}   
            void Soar();
            void MakeSound() const;
            void PrintInfo() const;
        
    };
    
    class Parrot : public Bird {
        std::vector<std::string> vocabulary; 
        public:
        Parrot() {}
        Parrot(const std::string _name, const std::string _word = "Hello", Kind k = Kind::Parrot) : Bird(_name, k) { vocabulary.push_back(_word); }
        void Speak() const;
        void MakeSound() const;
        void PrintInfo() const;
    };
    
    class Snake : public Reptile {
        const bool poisonous;
        public:
        Snake() : poisonous(false) { }
        Snake(const std::string _name, bool _poisnous = false , Kind k = Kind::Snake) : Reptile(_name, k), poisonous(_poisnous) { } 
        void Hiss();
        void MakeSound() const;
        void PrintInfo() const;
    };
    
    class Crocodile : public Reptile {
        int biteForce;
        public :
        Crocodile() : biteForce(0) { }
        Crocodile(const std::string _name, size_t bite = 0, Kind k = Kind::Crocodile) : Reptile(_name, k), biteForce(bite) { }
        void Snap() const;
        void MakeSound() const;
        void PrintInfo() const;
};
