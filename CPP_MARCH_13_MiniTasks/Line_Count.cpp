#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream input ("input.txt", std::ios::trunc | std::ios::out);
    std::ofstream output ("output.txt", std::ios::trunc | std::ios::out);
    if (!input || !output) std::perror("File(s) doesn't open");

    std::ifstream read_input ("input.txt");
    if (!read_input) std::perror("File doesn't readble");

    input << "Hello\n";
    input << "World\n";
    input << "C++\n";
    input.flush();

    std::string buffer;
    int count = 0;

    while(std::getline(read_input, buffer))
    {
        output << ++count;
        output << ": ";
        buffer.push_back('\n');
        output << buffer;
    }

    input.close();
    output.close();
    read_input.close();
    return 0;
}