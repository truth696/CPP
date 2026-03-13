#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ofstream file("data.txt", std::ios::trunc | std::ios::out);
    if(!file) std::perror("File doesn't open");
    std::ifstream read_file("data.txt", std::ios::in);
    if (!read_file) std::perror("File doesn't open");

    file << "C++ is very powerful";
    file.flush();

    std::string buffer;
    int count = 0;

    while(read_file >> buffer) ++count;

    std::cout << count;

    file.close();
    read_file.close();
    return 0;
}