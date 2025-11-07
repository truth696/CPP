#include <iostream>

enum class Role {QA, Designer, DevOps, Software_Engineer, Security_Specialist, Project_Manager, Unknow};

class Counter{
    static int _id;
    friend class Employee;
public:
    Counter(int x = 0) { _id = x; }
};


class Employee{
    std::string name;
    int id;
    int projects;
    int experience;
    Role role;
    double salary;
protected:
    void setSalary(double amount) { salary = amount; } 
public:
    Employee(std::string _name, size_t _projects, size_t _experience, Role _role) : name(_name), projects(_projects), experience(_experience), role(_role) { id = ++Counter::_id; } 
    inline Role getRole () const { return role; }
    inline int getExperince() const { return experience; }
    inline int getProjects () const { return projects; }
    inline int getId() const { return id; }
    inline std::string getName() const { return name; }
    double getSalary() const { return salary; }
    virtual void CalculateTotalSalary() { }
    virtual void printInfo() const {};
    virtual ~Employee() = default;
};

class Intern : public Employee{
    Employee* mentor;
public:
    Intern(std::string _name = "Unkown", size_t _projects = 0, size_t _experience = 0, Role _role = Role::Unknow, Employee* _mentor = nullptr) : Employee(_name, _projects, _experience, _role), mentor(_mentor) { setSalary(200); }
    virtual void printInfo() const override;
};

class Junior : public Employee{
    Employee* Team_Lead;
public:
    virtual void CalculateTotalSalary() override{ 
        if (getProjects() > 4) setSalary(550);
        else setSalary(400);
    }
    Junior(std::string _name = "Unkown", size_t _projects = 0, size_t _experience = 0, Role _role = Role::Unknow, Employee* _Team_Lead = nullptr) :  Employee(_name, _projects, _experience, _role), Team_Lead(_Team_Lead) { CalculateTotalSalary(); }
    virtual void printInfo() const override;
};

class Middle : public Employee {
    Employee* Team_Lead;
public:
    virtual void CalculateTotalSalary() override{ 
        if (getProjects() > 4 && getExperince() > 2) setSalary(1000);
        else setSalary(800);
    }
    Middle(std::string _name = "Unkown", size_t _projects = 0, size_t _experience = 0, Role _role = Role::Unknow, Employee* _Team_Lead = nullptr) :  Employee(_name, _projects, _experience, _role), Team_Lead(_Team_Lead) { CalculateTotalSalary(); }
    virtual void printInfo() const override;  
};

class Senior : public Employee{
   std::vector<Employee*> list_of_subordinates;
public:
    virtual void CalculateTotalSalary() override{ 
        if (getProjects() > 10 && getExperince() > 5 && list_of_subordinates.size() > 5) setSalary(3000);
        else setSalary(2500);
    }
    Senior(std::string _name = "Unkown", size_t _projects = 0, size_t _experience = 0, Role _role = Role::Unknow, std::initializer_list<Employee*> list = {}) :  Employee(_name, _projects, _experience, _role) { 
        CalculateTotalSalary();
        for (Employee* e : list) list_of_subordinates.push_back(e);
    }
    void addEmployee(Employee* e) { list_of_subordinates.push_back(e); }
    void fireEmployee(Employee* e);
    virtual void printInfo() const override;   
};

class Department{
    std::vector<Employee*> staff;
public:
    void addEmployer(Employee* emp) { staff.push_back(emp); }
    void fireWorker(Employee* emp);
    double CalculateTotalPayRoll();
    void printInfo();
};