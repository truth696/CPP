#include "EmployeePayroll.hpp"

int Counter::_id = 0;

void Intern::printInfo() const{
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Id: " << getId() << std::endl;
    std::cout << "Projects: " << getProjects() << std::endl;
    std::cout << "Expereince: " << getExperince() << std::endl;
    std::cout << "Intern" << std::endl;
    std::cout << "Role: ";
    switch (getRole()) {
        case Role::Designer:
            std::cout << "Designer" << std::endl;
            break;
        case Role::DevOps:
            std::cout << "Development & Operations" << std::endl;
            break;
        case Role::Project_Manager:
            std::cout << "Project Manager" << std::endl;
            break;
        case Role::QA:
            std::cout << "Quality Assurance" << std::endl;
            break;
        case Role::Security_Specialist:
            std::cout << "Security Specialist" << std::endl;
            break;
        case Role::Software_Engineer:
            std::cout << "Software Engineer" << std::endl;
            break;
        default:
            std::cout << "Unknow" << std::endl;
    }
    std::cout << "Salary: " << getSalary() << std::endl;
    if (mentor) std::cout << "Mentor name: " << mentor->getName() << std::endl;
}

void Junior::printInfo() const{
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Id: " << getId() << std::endl;
    std::cout << "Projects: " << getProjects() << std::endl;
    std::cout << "Expereince: " << getExperince() << std::endl;
    std::cout << "Junior" << std::endl;
    std::cout << "Role: ";
    switch (getRole()) {
        case Role::Designer:
            std::cout << "Designer" << std::endl;
            break;
        case Role::DevOps:
            std::cout << "Development & Operations" << std::endl;
            break;
        case Role::Project_Manager:
            std::cout << "Project Manager" << std::endl;
            break;
        case Role::QA:
            std::cout << "Quality Assurance" << std::endl;
            break;
        case Role::Security_Specialist:
            std::cout << "Security Specialist" << std::endl;
            break;
        case Role::Software_Engineer:
            std::cout << "Software Engineer" << std::endl;
            break;
        default:
            std::cout << "Unknow" << std::endl;
    }
    std::cout << "Salary: " << getSalary() << std::endl;
    if (Team_Lead) std::cout << "Team Lead name: " << Team_Lead->getName() << std::endl;
}

void Middle::printInfo() const{
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Id: " << getId() << std::endl;
    std::cout << "Projects: " << getProjects() << std::endl;
    std::cout << "Expereince: " << getExperince() << std::endl;
    std::cout << "Middle" << std::endl;
    std::cout << "Role: ";
    switch (getRole()) {
        case Role::Designer:
            std::cout << "Designer" << std::endl;
            break;
        case Role::DevOps:
            std::cout << "Development & Operations" << std::endl;
            break;
        case Role::Project_Manager:
            std::cout << "Project Manager" << std::endl;
            break;
        case Role::QA:
            std::cout << "Quality Assurance" << std::endl;
            break;
        case Role::Security_Specialist:
            std::cout << "Security Specialist" << std::endl;
            break;
        case Role::Software_Engineer:
            std::cout << "Software Engineer" << std::endl;
            break;
        default:
            std::cout << "Unknow" << std::endl;
    }
    std::cout << "Salary: " << getSalary() << std::endl;
    if (Team_Lead)std::cout << "Team Lead name: " << Team_Lead->getName() << std::endl;
}

void Senior::fireEmployee(Employee* e) {
    if (list_of_subordinates.empty()) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    for (int i = 0; i < list_of_subordinates.size(); ++i){
        if(list_of_subordinates[i]->getId() == e->getId()) {
            list_of_subordinates.erase(list_of_subordinates.begin() + i);
            return;
        }
    }

    std::cout << "We haven't employer with this id" << std::endl;
}

void Senior::printInfo() const {
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Id: " << getId() << std::endl;
    std::cout << "Projects: " << getProjects() << std::endl;
    std::cout << "Expereince: " << getExperince() << std::endl;
    std::cout << "Senior" << std::endl;
    std::cout << "Role: ";
    switch (getRole()) {
        case Role::Designer:
            std::cout << "Designer" << std::endl;
            break;
        case Role::DevOps:
            std::cout << "Development & Operations" << std::endl;
            break;
        case Role::Project_Manager:
            std::cout << "Project Manager" << std::endl;
            break;
        case Role::QA:
            std::cout << "Quality Assurance" << std::endl;
            break;
        case Role::Security_Specialist:
            std::cout << "Security Specialist" << std::endl;
            break;
        case Role::Software_Engineer:
            std::cout << "Software Engineer" << std::endl;
            break;
        default:
            std::cout << "Unknow" << std::endl;
    }
    std::cout << "Salary: " << getSalary() << std::endl;
    if (list_of_subordinates.empty()) {
        std::cout << "This senior haven't subordinates" << std::endl;
        return;
    }
    std::cout << "Subordinates: ";
    for (Employee* e: list_of_subordinates) { std::cout << e->getName() << std::endl; }

}

void Department::fireWorker(Employee* emp) {
    if (staff.empty()) {
        std::cout << "Staff is empty" << std::endl;
        return ;
    }

    for (int i = 0; i < staff.size(); ++i) {
        if (staff[i]->getId() == emp->getId()) {
            staff.erase(staff.begin() + i);
            return;
        }
    }
    std::cout << "We haven't this worker" << std::endl;
}

double Department::CalculateTotalPayRoll() {
    if (staff.empty()){
        std::cout << "Staff is empty" << std::endl;
        return 0;
    }
    double amount = 0;
    for (Employee* e : staff) amount += e->getSalary();
    return amount;
}

void Department::printInfo() {
    std::cout << "Number of all employees: " << staff.size() << std::endl;
    std::cout << "Number of all payroll: " << CalculateTotalPayRoll() << std::endl;
}