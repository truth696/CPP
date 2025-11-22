#include <iostream> 



class Instruments{
 public: 
    virtual void play() { std::cout << "Instrument is playing a sound." << std::endl; }
    virtual ~Instruments() = default;
    
};

class Orchestar{
    std::vector<Instruments*> vec;
public:
    void add (Instruments* i) { vec.push_back(i); }
    void play() { for(Instruments* i: vec) i->play(); }
    ~Orchestar() { for (Instruments* i : vec) delete i; }
};

class Piano : public Instruments{ 
public:
    virtual void play() override{ std::cout << "Piano is playing a classical melody." << std::endl; }
};

class Violin : public Instruments{
public:
    virtual void play() override { std::cout << "Violin is playing a soothing tune." << std::endl; }
};

class Drum : public Instruments {
public:
    virtual void play() override{ std::cout << "Drum is creating a powerful rhythm." << std::endl; }
};

