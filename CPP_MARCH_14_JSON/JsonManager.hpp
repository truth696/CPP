#pragma once
#include "Student.hpp"
#include "Course.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class JsonManager{
public:
    std::string serialize(const std::vector<Student>& students);
    std::string serialize(const std::vector<Course>& courses);
    std::vector<Student> deserialize_students(const std::string& _name);
    std::vector<Course> deserialize_courses(const std::string& _name);
private:
    Student deserialize_student(std::ifstream& read_file);
    Course deserialize_course(std::ifstream& read_file);
};
