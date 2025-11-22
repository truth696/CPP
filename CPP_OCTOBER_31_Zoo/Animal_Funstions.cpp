#include "Animal_Classes.hpp"

void Lion::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Mamal" << std::endl;
    std::cout << "Animal species: Lion" << std::endl;
    std::cout << "Roar" << roarPower << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Tiger::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Mamal" << std::endl;
    std::cout << "Animal species: Tiger" << std::endl;
    std::cout << "Jump Height: " << jumpHeight << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Elephant::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Mamal" << std::endl;
    std::cout << "Animal species: Elephant" << std::endl;
    std::cout << "Trunk length: " << trunkLength << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Snake::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Reptile" << std::endl;
    std::cout << "Animal species: Snake" << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Crocodile::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Reptile" << std::endl;
    std::cout << "Animal species: Crocodile" << std::endl;
    std::cout << "Bite force " << biteForce << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Eagle::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Bird" << std::endl;
    std::cout << "Animal species: Eagle" << std::endl;
    std::cout << "VisionRange " << visionRange << std::endl;
    std::cout << "Wingspan" << wingSpan << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Parrot::PrintInfo() const{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Animal class: Bird" << std::endl;
    std::cout << "Animal species: Parrot" << std::endl;
    std::cout << "Wingspan" << wingSpan << std::endl;
    std::cout << "Hunger: " << hunger << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Animal::PrintInfo() const {
    switch (KindOf()) {
        case Kind::Lion:
            static_cast<const Lion* const>(this)->PrintInfo();
            break;

        case Kind::Elephant:
            static_cast<const Elephant* const>(this)->PrintInfo();
            break;

        case Kind::Tiger:
            static_cast<const Tiger* const>(this)->PrintInfo();
            break;

        case Kind::Eagle:
            static_cast<const Eagle* const>(this)->PrintInfo();
            break;

        case Kind::Parrot:
            static_cast<const Parrot* const>(this)->PrintInfo();
            break;

        case Kind::Snake:
            static_cast<const Snake* const>(this)->PrintInfo();
            break;

        case Kind::Crocodile:
            static_cast<const Crocodile* const>(this)->PrintInfo();
            break;
        default:
            std::cout << "Unknown kind" << std::endl;
        break;
    }
}

void Animal::Feed() {
    if (!hunger) { 
        std::cout << "Your animal is full" << std::endl;
        return;
    }
    std::cout << "Before your health: " << health << std::endl;
    if (health == 100) std::cout << "Your health if full" << std::endl;
    else health += 10;
    std::cout << "After your health: " << health << std::endl;
    std::cout << "Before hunger: " << hunger << std::endl;
    hunger -= 10;
    std::cout << "After hunger: " << hunger << std::endl;

}

Kind Animal::KindOf() const {  return kind;  }

void Reptile::Sunbathe() const{ std::cout << "Warm.. Warm.. Warm.." << std::endl; }

void Lion::Roar() const { std::cout << "Roar this lion is " << roarPower << std::endl; }

void Lion::MakeSound() const {
    std::cout << "Just listen" << std::endl;
    system ("afplay /Users/mikael/Downloads/the-lion-purrs-and-fawns-with-the-cubs.mp3 &");
}

void Tiger::Jump() const { std::cout << "Your tiger jump " << jumpHeight << " meters" << std::endl; }

void Tiger::MakeSound() const {
    std::cout << "Just listen" << std::endl;
    system ("afplay /Users/mikael/Downloads/terrible-tiger-roar.mp3 &");
}

void Elephant::UseTrunk() const { std::cout << "Water! Water! Water!" << std::endl; }

void Elephant::MakeSound() const {
    std::cout << "Just listen" << std::endl;
    system("afplay /Users/mikael/Downloads/elephant-sound-short.mp3 &");
}

void Eagle::Soar() { std::cout << "I'm trying to find a victim" << std::endl; }

void Eagle::MakeSound() const{
    std::cout << "Eagle presents just listen" << std::endl;
    system("afplay /Users/mikael/Downloads/the-eerie-scream-of-a-bird-of-prey.mp3 &");
    // system("afplay /Users/mikael/Downloads/blatnoy-udar-blatnoy-udar-dolya.mp3 &");

}

void Parrot::Speak() const {
    for (int i = 0; i < vocabulary.size(); ++i) std::cout << vocabulary[i] << " ";
}

void Parrot::MakeSound() const {
    std::cout << "Just listen" << std::endl;
    system("afplay /Users/mikael/Downloads/the-cooing-and-whistling-of-a-parrot.mp3 &");
    
}

void Snake::Hiss() {
    std::cout << "hssss...." << std::endl;
}

void Snake::MakeSound() const {
    std::cout << "just listen" << std::endl;
    system("afplay /Users/mikael/Downloads/the-hiss-of-a-poisonous-black-cobra.mp3 &");
}

void Crocodile::Snap() const{ 
    std::cout << "Your crocodile can bite with " << biteForce << " force" << std::endl; }

void Crocodile::MakeSound() const {
    std::cout << "just listen" << std::endl;
    system("afplay /Users/mikael/Downloads/crocodile-sounds-in-the-wild.mp3 &");
}



//Lion
void Lion::Swim() const {
    std::cout << "Lion swims" << std::endl;
}
void Lion::Walk() const {
    std::cout << "Lion walks" <<std::endl;
}
void Lion::Feddble() const{
    std::cout << "Lion feddble" << std::endl;
}

//Elephant
void Elephant::Walk() const{ 
    std::cout << "Elephant walks" <<std::endl;
}
void Elephant::Feddble() const{
    std::cout << "Elephant feddble" << std::endl;
}

//Tiger
void Tiger::Walk() const {
    std::cout << "Tiger walks" <<std::endl;
}
void Tiger::Swim() const {
    std::cout << "Tiger swims" << std::endl;
}
void Tiger::Feddble() const {
    std::cout << "Tiger feddble" << std::endl;
}

//Eagle
void Eagle::Fly() const {
    std::cout << "Eagle flies" << std::endl;
}
void Eagle::Feddble() const{
    std::cout << "Eagle feddble" << std::endl;
}
void Eagle::Walk() const{
    std::cout << "Eagle walks" <<std::endl;
}

//Parrot
void Parrot::Fly() const {
    std::cout << "Parrot flies" << std::endl;
}
void Parrot::Feddble() const{
    std::cout << "Parrot feddble" << std::endl;
}
void Parrot::Walk() const{
    std::cout << "Parrot walks" <<std::endl;
}

//Snake 
void Snake::Feddble() const {
    std::cout << "Snake feddble" << std::endl;
}
void Snake::Swim() const {
    std::cout << "Snake swims" << std::endl;
}

//Corcodile 
void Crocodile::Feddble() const{
    std::cout << "Crocodile feddble" << std::endl;
}    
void Crocodile::Swim() const{
    std::cout << "Crocodile swims" << std::endl;
}    