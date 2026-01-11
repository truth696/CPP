#include "EmployeeRepository.h"


void EmployeeRepository::addEmployee(std::shared_ptr<Employee> e) noexcept { 
    for (size_t i{}; i < database.size(); ++i) {
        if(database[i]->getID() == e->getID()){
            std::cout << "This employe yet work in our company" << std::endl;
            return;
        }
    }
    database.push_back(e);
 }
void EmployeeRepository::removeEmployee (size_t id) noexcept{
    if (database.empty()) {
        std::cout << "We haven't any empolyee" << std::endl;
        return;
    }
    for (size_t i{}; i < database.size(); ++i) {
        if(database[i]->getID() == id){
            database.erase(database.begin() + i);
            std::cout << "Your employee successfuly fired" << std::endl;
            return;
        }
    }
    std::cout << "We hane't employee with this ID" << std::endl;
}

void EmployeeRepository::listAllEmployee() const noexcept{
    if (database.empty()) {
        std::cout << "We haven't any empolyee" << std::endl;
        return;
    }
    for (size_t i{}; i < database.size(); ++i){
        std::cout << "Employee № " << i+1 << std::endl;
        database[i]->printInfo();
    }
    std::cout << "We have total " << database.size() << " employee" << std::endl; 
}
