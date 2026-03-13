#include <iostream>
#include <fstream>
#include <string>


int main() 
{
    std::ofstream file("hello.txt", std::ios::trunc | std::ios::out);
    if (!file) std::perror("File doesn't open");

    file << "Hello\n";
    file << "this is my firts file\n";
    file << "C++ is cool\n";

    file.close();

    return 0;
}
