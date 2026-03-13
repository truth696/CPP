#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ofstream file("fruits.txt", std::ios::app);
    if (!file) std::perror("File does't open"); 
    std::ifstream read_file("fruits.txt", std::ios::in);
    if (!read_file) std::perror("File does't open"); 

    file << "Apple\n";
    file << "Banana\n";
    file << "Pineapple\n";
    file << "Orange\n";

    std::string buffer;
    file.flush();
    while (read_file >> buffer)
    {
        std::cout << buffer << " ";
    }


    file.close();
    read_file.close();
return 0;
}