#include <iostream>
#include <unistd.h>
#include <thread>


int main() {
    for (int i : {1,2,3,4,5}){
        pid_t pid = fork();
        if (!pid) {
            std::cout << "children here with this process id >> " << getpid() << std::endl;
            exit(10);
        } else if (pid > 0) {
            wait(NULL);
            std::cout << " parent " << std::endl;
        } else std::perror(" std::cout << \"Hello Wolrd! \" << std::endl; ");
    }
}