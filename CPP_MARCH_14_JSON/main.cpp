#include "Student.hpp"
#include "Course.hpp"
#include "JsonManager.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


int main() {
    JsonManager manager;
    std::vector<Student> students { Student("Vardan", 23, 100), Student("Vladimir", 44, 23)};
    std::string file_name_s = manager.serialize(students);

    std::vector<Student> res_stu = manager.deserialize_students(file_name_s);
    int i1{};
    while (i1 < res_stu.size()){
        res_stu[i1++].PrintInfo();
    }

    std::vector<Course> courses {Course("C++", 100, true), Course("JS", 0, false)};
    std::string file_name_c = manager.serialize(courses);

    std::vector<Course> res_cour = manager.deserialize_courses(file_name_c);
    int i2{};
    while (i2 < res_cour.size()){
        res_cour[i2++].PrintInfo();
    }

    return 0;
}