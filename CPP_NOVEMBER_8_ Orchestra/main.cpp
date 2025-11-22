#include <iostream>
#include <vector>
#include "Orchrestra.hpp"
#include "Ecosystem.hpp"

int main() {
    Orchestar o;
    o.add(new Piano);
    o.add(new Violin);
    o.add(new Drum);
    o.play();

    std::cout << "---------------" << std::endl;
    
    Entits obj;
    obj.add(new Robot);
    obj.add(new Animal);
    obj.add(new Drone);
    obj.play();
}