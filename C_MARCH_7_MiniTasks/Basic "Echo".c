#include <stdio.h>
#include <unistd.h>
#define FILE_NAME "Basic Echo.txt" 

int main() 
{
    FILE* fl = fopen(FILE_NAME, "w+");
    
    if (!fl) {
        printf("Couldnt open %s file:", FILE_NAME);
        return -1;
    }

    fwrite("hello1\n", 7, 1, fl);
    fwrite("hello2\n", 7, 1, fl);
    fwrite("hello3\n", 7, 1, fl);

    fseek(fl, 0, SEEK_SET);
    
    char buff[50];
    fgets(buff, 10, fl);

    fputs("After Read:\n", fl);
    fputs(buff, fl);

    fclose(fl);
    return 0;
}