#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ofstream input("input.txt", std::ios::trunc | std::ios::out);
    std::ofstream output("output.txt", std::ios::trunc | std::ios::out);
    if (!input || !output) std::perror("File doesn't open");

    std::ifstream read_input("input.txt");
    if (!read_input) std::perror("File doesn't readble");

    input << "hello\n";
    input << "world\n";
    input << "how\n";
    input << "where\n";
    input.flush();

    std::string buffer;

    while (std::getline(read_input, buffer))
    {
        buffer.push_back('\n');
        output << buffer;
    }


    output.close();
    input.close();
    read_input.close();
    return 0;
}