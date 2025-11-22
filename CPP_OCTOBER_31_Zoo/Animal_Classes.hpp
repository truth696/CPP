#pragma once
#include "Generalization.hpp"


class IFly{
public:
    virtual void Fly() const = 0;
    virtual ~IFly() = default;
};

class ISwim{
public:
    virtual void Swim() const = 0 ;
    virtual ~ISwim() = default;
};

class IWalk{
public:
    virtual void Walk() const = 0;
    virtual ~IWalk() = default;
};

class IVoice{
    public:
    virtual void MakeSound() const = 0;
    virtual ~IVoice() = default;
}; 

class IFeedable{
    public:
    virtual void Feddble() const = 0;
    virtual ~IFeedable() = default;
};





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


class Lion : public Mamal , public IVoice, public IFeedable, public ISwim, public IWalk{
    int roarPower;
    public:
        Lion() : roarPower(3) {}
        Lion(const std::string _name,  size_t _roarPower = 3) : Mamal(_name,  Kind::Lion) , roarPower(_roarPower) {}
        void Roar() const; 
        virtual void MakeSound() const override;
        virtual void Swim() const override;
        virtual void Walk() const override;
        virtual void Feddble() const override;
        void PrintInfo() const;
        
};
    
    
class Tiger : public Mamal, public IVoice, public IFeedable, public ISwim, public IWalk {
    double jumpHeight;
    public:
        Tiger() : jumpHeight(1.0) {}
        Tiger(const std::string _name, size_t _jumpHeight = 1.0) : Mamal(_name, Kind::Tiger) , jumpHeight(_jumpHeight) {} 
        void Jump() const;
        virtual void MakeSound() const override;
        virtual void Swim() const override;
        virtual void Walk() const override;
        virtual void Feddble() const override;
        void PrintInfo() const;
};
    
class Elephant : public Mamal ,public IVoice, public IFeedable, public IWalk{
    double trunkLength;
    public:
        Elephant() : trunkLength(2.0) { }
        Elephant(const std::string _name, size_t length = 2.0) : Mamal(_name, Kind::Elephant) , trunkLength(length) { }
        void UseTrunk() const;
        virtual void MakeSound() const override;
        virtual void Walk() const override;
        virtual void Feddble() const override;
        void PrintInfo() const;
};
    
class Eagle : public Bird, public IVoice, public IFeedable, public IFly,  public IWalk{
    double visionRange;
    public:
        Eagle() : visionRange(15.5) { }
        Eagle(const std::string _name, size_t vison = 15) : Bird(_name, Kind::Eagle) , visionRange(vison) {}   
        void Soar();
        virtual void MakeSound() const override;
        virtual void Fly() const override;
        virtual void Feddble() const override;
        virtual void Walk() const override;
        void PrintInfo() const;
    
};
    
class Parrot : public Bird, public IVoice, public IFeedable, public IFly,  public IWalk{
    std::vector<std::string> vocabulary; 
    public:
    Parrot() {}
    Parrot(const std::string _name, const std::string _word = "Hello") : Bird(_name, Kind::Parrot) { vocabulary.push_back(_word); }
    void Speak() const;
    virtual void MakeSound() const override;
    virtual void Fly() const override;
    virtual void Feddble() const override;
    virtual void Walk() const override;
    void PrintInfo() const;
};
    
class Snake : public Reptile, public IVoice, public IFeedable, public ISwim{
    const bool poisonous;
    public:
    Snake() : poisonous(false) { }
    Snake(const std::string _name, bool _poisnous = false) : Reptile(_name, Kind::Snake), poisonous(_poisnous) { } 
    void Hiss();
    virtual void MakeSound() const override;
    virtual void Feddble() const override;
    virtual void Swim() const override;
    void PrintInfo() const;
};
    
class Crocodile : public Reptile, public IVoice, public IFeedable, public ISwim {
    int biteForce;
public :
    Crocodile() : biteForce(0) { }
    Crocodile(const std::string _name, size_t bite = 0) : Reptile(_name,  Kind::Crocodile), biteForce(bite) { }
    void Snap() const;
    virtual void MakeSound() const override;
    virtual void Feddble() const override;
    virtual void Swim() const override;
    void PrintInfo() const;
};
