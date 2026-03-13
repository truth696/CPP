#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ofstream file ("data.txt", std::ios::trunc | std::ios::out);
    if (!file) std::perror("File doesn't open");
    std::ifstream read_file("data.txt");
    if (!read_file) std::perror("File doesn't readble");

    file << "C++ programming language";

    std::string result;
    std::string compare; 

    file.flush();
    while (read_file >> compare)
    {
        if (compare.size() > result.size()) result = compare;
    }
    
    std::cout << result << " " << result.size();
}