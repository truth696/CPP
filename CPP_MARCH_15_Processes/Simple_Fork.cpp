#include <iostream>
#include <unistd.h>


int main() {
    pid_t pid = fork();
    int s = 0;

    if (!pid) {
        std::cout << "I am child with pid " << getpid() << " and parent " << getppid() << std::endl;
        exit(10);
    } else if (pid > 0) {
        wait(&s);
        std::cout <<  "I am parent with pid " << getpid() << " and child " << pid << std::endl;
    } else std::perror(" std::cout << \"Hello Wolrd! \" << std::endl; ");



}