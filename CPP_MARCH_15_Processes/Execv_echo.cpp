#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (!pid) {
        execv("/bin/echo", argv);
        exit(20);

    } else if (pid > 0) {
        wait(NULL);
        std::cout << "Children finished" << std::endl;

    } else std::perror(" std::cout << \"Hello Wolrd! \" << std::endl; ");
}
