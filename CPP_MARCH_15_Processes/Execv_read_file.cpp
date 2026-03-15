#include <iostream>
#include <unistd.h>
#include <fstream>

int lines_count = 0;
int words_count = 0; 

int main() {
    std::ofstream file("test.txt" , std::ios::out | std::ios::trunc);
    std::ifstream read_file("test.txt", std::ios::in);

    if (!file || !read_file) std::perror(" std::cout << \"Hello Wolrd! \" << std::endl; ");

    file << "Hello World\n";
    file << "C++\n";
    file << "yeap\n";

    read_file.seekg(0);

    pid_t pid = fork();

    file.flush();
    if (!pid) {
        std::string buffer;
        while (read_file >> buffer) ++words_count;
        exit(words_count);
    } else if (pid > 0) {
        std::string buffer;
        wait(&words_count);
        read_file.seekg(0);
        while(std::getline(read_file, buffer)) ++lines_count;
    }

    std::cout << "count of words >> " << WEXITSTATUS(words_count) << std::endl;
    std::cout << "count of lines >> " << lines_count << std::endl;


    return 0;
}