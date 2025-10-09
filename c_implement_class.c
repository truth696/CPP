#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define size 50

typedef struct {
    char name[size];
    int age;
    double height;
    
    
} Person;

const char* get_Name (const Person* const this) { return this->name; }

const int getAge (const Person* const this) { return this->age; }

const double getHeight(const Person* const this) { return this->height; }

void setName (Person* const this, char* n) { strcpy(this->name, n); }

void setAge (Person* const this, int a) { this->age = a; }

void setHeight (Person* const this, double h) { this->height = h; }

void printInfo (const Person* const this) {
    printf ("Name: %s ",this->name);
    printf("Age : %d ", this->age);
    printf("Height: %f\n", this->height);
}

void printInfo_h (const Person* const this, bool showHeight) {
    printf("Name: %s ", this->name);
    printf("Age : %d ", this->age);
    if (showHeight) printf("Height: %f\n", this->height);
   }


void ctor (Person* const this) {
    strcpy(this->name, "Unknown");
    this->age = 0;
    this->height = 0.0;
}

void set_person(Person* const this, char* n, int a, double h) {
    strcpy(this->name, n);
    this->age = a;
    this->height = h;
}

int main() {
    Person p1;
    ctor (&p1);
    set_person(&p1, "Bob", 19, 1.75);
    printInfo (&p1);
    printInfo_h (&p1, true);
    setAge (&p1, 20);
    printf ("Update age: %d", getAge (&p1));
return 0;    
}