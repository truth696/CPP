#include <iostream>
#include <string>

int main() {
    std::string name; 
    int age; 

    std::cout << "Please input your name" << std::endl;
    std::cin >> name;
    
    std::cout << "Please input your age" << std::endl;
    std::cin >> age;
    
    std::cout << "Hello " << name << "Your age is " << age << std::endl;
   
return 0;
}
