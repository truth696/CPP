#include "JsonManager.hpp"

// std::string JsonManager::serialize(const std::vector<Student>& students) {
//     std::string result;
//         if (students.empty()) {
//             result.append("[\n]");
//             return result;
//         }
//         result.append("[\n");
//         for (int i{}; i < students.size(); ++i){
//             result.append(" {\n  \"name\" : \"");
//             result.append(students[i].name());
//             result.append("\",\n");
//             result.append("  \"age\" : \"");
//             result.append(std::to_string(students[i].age()));
//             result.append("\",\n");
//             result.append("  \"gpa\" : \"");
//             result.append(std::to_string(students[i].gpa()));
//             result.append("\"\n");
//             if(i == students.size() - 1) result.append(" }\n");
//             else result.append(" },\n");
//         }
//         result.append("]\n");
//     return result;
// }


std::string JsonManager::serialize(const std::vector<Student>& students) {
    std::ofstream file("students.json", std::ios::out | std::ios::trunc);
    std::ifstream read_file("students.json", std::ios::in);
    if (!file || !read_file) std::perror("File doesn't open");
    if (students.empty()){
        file << "[\n]";
        return "students.json";
    }
    
    int i{};
    file << "[\n";
    while (i < students.size()){
        file << " {\n  \"name\" : \"";
        file << students[i].name();
        file << "\",\n";
        file << "  \"age\" : ";
        file << students[i].age();
        file << ",\n";
        file << "  \"gpa\" : ";
        file << students[i].gpa();
        file << "\n";
        if(i == students.size() - 1) file << " }\n]";
        else file << " },\n";
        ++i;
    }

    return "students.json";
}

Student JsonManager::deserialize_student(std::ifstream& read_file){
    std::string buffer;
    std::string name;
    size_t age = 0;
    double gpa = -1;
    size_t index = 0;

    while (std::getline(read_file, buffer)){
            if (buffer.find("name") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find('"', colon) + 1; 
                size_t end = buffer.find('"', start); 

                name = buffer.substr(start, end - start);
            }
            else if (buffer.find("age") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find(' ', colon) + 1;
                size_t end = buffer.find(',', start);

                std::string number = buffer.substr(start, end - start);
                age = std::stoi(number);
            }
            else if (buffer.find("gpa") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find(' ', colon) + 1;
                size_t end = buffer.find(' ', start);

                std::string gpa_str = buffer.substr(start, end - start);
                gpa = std::stod(gpa_str); 
                
            }
            else if (buffer.find("}") != std::string::npos) return Student(name, age, gpa);
    }
    return Student(name, age, gpa);

}

std::vector<Student> JsonManager::deserialize_students(const std::string& file_name){
    std::ifstream read_file(file_name, std::ios::in);
    if (!read_file) std::perror ("File doesn't open");

    std::string buffer;
    std::vector<Student> students;

    while (read_file.peek() != EOF){
        auto student = deserialize_student(read_file);
        if (student.age() > 0) students.push_back(student);
    }

    return students;
}

std::string JsonManager::serialize(const std::vector<Course>& courses){
    std::ofstream file("courses.json", std::ios::out | std::ios::trunc);
    std::ifstream read_file("courses.json", std::ios::in);
    if (!file || !read_file) std::perror("File doesn't open");
    if (courses.empty()){
        file << "[\n]";
        return "courses.json";
    }
    
    int i{};
    file << "[\n";
    while (i < courses.size()){
        file << " {\n  \"title\" : \"";
        file << courses[i].title();
        file << "\",\n";
        file << "  \"credit\" : ";
        file << courses[i].credit();
        file << ",\n";
        file << "  \"mandatory\" : ";
        file << std::boolalpha << courses[i].mandatory();
        file << "\n";
        if(i == courses.size() - 1) file << " }\n]";
        else file << " },\n";
        ++i;
    }

    return "courses.json";
}

std::vector<Course> JsonManager::deserialize_courses(const std::string& file_name){
    std::ifstream read_file(file_name, std::ios::in);
    if (!read_file) std::perror ("File doesn't open");

    std::string buffer;
    std::vector<Course> courses;

    while (read_file.peek() != EOF){
        auto course = deserialize_course(read_file);
        if (course.credit() != std::string::npos) courses.push_back(course);
    }

    return courses;
}

Course JsonManager::deserialize_course(std::ifstream& read_file){
    std::string buffer;
    std::string name;
    bool mandatory = false;
    size_t credit = std::string::npos;
    size_t index = 0;

    while (std::getline(read_file, buffer)){
            if (buffer.find("title") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find('"', colon) + 1; 
                size_t end = buffer.find('"', start); 

                name = buffer.substr(start, end - start);
            }
            else if (buffer.find("credit") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find(' ', colon) + 1;
                size_t end = buffer.find(',', start);

                std::string number = buffer.substr(start, end - start);
                credit = std::stoi(number);
            }
            else if (buffer.find("mandatory") != std::string::npos){
                size_t colon = buffer.find(':');
                size_t start = buffer.find(' ', colon) + 1;
                size_t end = buffer.find(' ', start);

                std::string mand = buffer.substr(start, end - start);
                if (mand == "false") mandatory = false;
                else mandatory = true;
            }
            else if (buffer.find("}") != std::string::npos) return Course(name, credit, mandatory);
    }
    return Course(name, credit, mandatory);

}
