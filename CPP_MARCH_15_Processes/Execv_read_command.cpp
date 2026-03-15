#include <iostream>
#include <unistd.h>
#include <string>

int main() {
    std::string command;

    std::cout << "Hello Dear User, please input the command" << std::endl;
    while (command != "exit") {
        std::cout << " >> ls\n >> pwd\n >> echo\n >> ping\n >> sl\n >> exit" << std::endl; 
        std::cin >> command;
        while (command != "ls" && command != "pwd" && command != "echo" && command != "ping" && command != "exit" && command != "sl") {
            std::cout << "Please input correct command" << std::endl;
            std::cout << " >> ls\n >> pwd\n >> echo\n >> ping\n >> sl\n >> exit" << std::endl; 
            std::cin >> command;
        }
        if (command == "exit") return 0;

        pid_t pid = fork();
        if (!pid){
            if (command == "ls") {
                char* argv[] = {(char*)" ", (char*)NULL};
                execv("/bin/ls", argv);

                std::perror("Not Found");
            } else if (command == "pwd") {
                char* argv[] = {(char*)" ", (char*)NULL};
                execv("/bin/pwd", argv);

                std::perror("Not Found");
            } else if (command == "echo") {
                char msg[128];

                std::cout << "Please input message for print\n >> ";
                std::cin >> msg;


                char* argv[] = {(char*)"echo", msg, (char*)NULL};
                execv("/bin/echo", argv);
                
                std::perror("Not Found");
            } else if (command == "ping") {
                char* argv[] = {(char*)"ping", (char*)"-c", (char*)"5", (char*)"8.8.8.8", (char*)NULL};
                execv("/sbin/ping", argv);

                std::perror("Not Found");
            } else if (command == "sl") {
                char* argv[] = {(char*)"sl", (char*)NULL};
                execv("/opt/homebrew/bin/sl", argv);

                std::perror("Not Found");
            }
        } else if (pid > 0) {
            wait(NULL);
            std::cout << "Successful" << std::endl;
        } else std::perror(" std::cout << \"Hello Wolrd! \" << std::endl; ");
    }
}