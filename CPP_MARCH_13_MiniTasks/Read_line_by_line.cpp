#include <iostream>
#include <fstream>
#include <string>


int main() 
{
    std::ofstream file("data.txt", std::ios::in | std::ios::trunc);
    if (!file) std::perror("File doesn't open");
    std::ifstream read_file("data.txt", std::ios::in);
    if (!read_file) std::perror("File doesn't open");


    file << "Line 1\n";
    file << "Line 2\n";
    file << "Line 3\n";

    file.seekp(0, std::ios::beg);

    std::string buffer;
    while (std::getline(read_file, buffer))
    {
        std::cout << buffer << std::endl;
    }


    file.close();
    read_file.close();
}