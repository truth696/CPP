#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream file("data.txt", std::ios::trunc | std::ios::out);
    if (!file) std::perror("File doesn't open");
    std::ifstream read_file("data.txt", std::ios::in);
    if (!read_file) std::perror("File doesn't open");


    file << "C++ is a powerful language";
    file.seekp(0, std::ios::beg);

    char c;

    while (read_file.get(c))
    {
        if ( c != ' ') std::cout <<c;
        else std::cout << '\n';
    }
    

    file.close();
    read_file.close();

    return 0;
}
