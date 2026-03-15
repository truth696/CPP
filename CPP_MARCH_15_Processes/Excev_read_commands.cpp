#include <iostream>
#include <unistd.h>
#include <string>

void delete_spaces(std::string& str) {
    int i{};
    
    while(i < str.size()){
        if (str[i] == ' ' || str[i] == '\n' || str[i] == ',' || str[i] == '/') str.erase(i);
        ++i;
    }
}

void before_exit(std::string& str) {
    size_t index = str.find("exit"); 
    if (index == std::string::npos) return;
    str.substr(0, index + 4);
}

int main() {
    std::string command;
    bool exit = false;

    std::cout << "Hello Dear User, please input the command" << std::endl;
    while (command != "exit")  {
        std::cout << " >> ls\n >> pwd\n >> echo\n >> ping\n >> sl\n >> exit" << std::endl; 
        std::cin >> command;
        while (command.find("ls") == std::string::npos && command.find("pwd") == std::string::npos && command.find("echo") == std::string::npos && command.find("ping") == std::string::npos && command.find("exit") == std::string::npos && command.find("sl") == std::string::npos) {
            std::cout << "Please input correct command" << std::endl;
            std::cout << " >> ls\n >> pwd\n >> echo\n >> ping\n >> sl\n >> exit" << std::endl; 
            std::cin >> command;
        }
        delete_spaces(command);
        before_exit(command);
        if (command == "exit") return 0;
        if (command.find("exit")) exit = true;

        if (command.find("ls") != std::string::npos) {
            pid_t pid = fork();
            if (!pid){
                char* argv[] = {(char*)" ", (char*)NULL};
                int index = command.find("ls");
                command.substr(index, command.size() - index);
                execv("/bin/ls", argv);
            
                std::perror("Not Found");
            }
        } else if (command.find("pwd") != std::string::npos) {
            pid_t pid = fork();
            if (!pid){
                char* argv[] = {(char*)" ", (char*)NULL};
                int index = command.find("pwd");
                command.substr(index, command.size() - index);
                execv("/bin/pwd", argv);
            
                std::perror("Not Found");
            }
        } else if (command.find("echo") != std::string::npos) {
            char msg[128];
            pid_t pid = fork();
            if (!pid) {
                int index = command.find("echo");
                command.substr(index, command.size() - index);
                std::cout << "Please input message for print\n >> ";
                std::cin >> msg;


                char* argv[] = {(char*)"echo", msg, (char*)NULL};
                execv("/bin/echo", argv);
                
                std::perror("Not Found");
            }
        } else if (command.find("ping") != std::string::npos) {
            pid_t pid = fork();
            if (!pid){
                int index = command.find("ping");
                command.substr(index, command.size() - index);
                char* argv[] = {(char*)"ping", (char*)"-c", (char*)"5", (char*)"8.8.8.8", (char*)NULL};
                execv("/sbin/ping", argv);

                std::perror("Not Found");
            }
        } else if (command.find("sl") != std::string::npos) {
            pid_t pid = fork();
            if (!pid) {
                int index = command.find("sl");
                command.substr(index, command.size() - index);
                char* argv[] = {(char*)"sl", (char*)NULL};
                execv("/opt/homebrew/bin/sl", argv);

                std::perror("Not Found");
            }
        }
        wait(NULL);
        std::cout << "Successful" << std::endl;
    }
}