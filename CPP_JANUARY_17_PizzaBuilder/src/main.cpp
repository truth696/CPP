#include <iostream>
#include <memory>
#include <fstream>
#include "Pizza.hpp"
#include "Cheese.hpp"
#include "Mushroom.hpp"
#include "Sauces.hpp"
#include "TypeofPizza.hpp"


int main() {
    std::ifstream readFromFile;
    std::ofstream logToFile;
    std::unique_ptr<Pizza> myPizza (std::make_unique<Sauce> ( std::make_unique<Mushroom> ( std::make_unique<Cheese>( std::make_unique<Margherita>() ) ) ) );
    time_t now = time(nullptr);
    logToFile.open("offer.txt", std::ios_base::trunc); 
    if (logToFile.is_open()){
        logToFile << "Pizza Description: " << myPizza->description() << std::endl;
        logToFile << "Total Cost: " << myPizza->cost() << "$" << std::endl;
        logToFile << "Your offer should be ready in ";
        logToFile << ctime(&(now += 600));
    }
    logToFile.close();
    std::string line;
    readFromFile.open("offer.txt", std::ios_base::in); 
    while (std::getline(readFromFile, line)) {
        std::cout << line << std::endl; 
        if (line.find("Your") != std::string::npos) std::cout << "Don't forget take your order in " << line.substr(size_t(line.find("in") + 3)) << std::endl;
    }
    readFromFile.close();
}
