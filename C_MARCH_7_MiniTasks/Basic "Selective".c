#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#define FILE_NAMEIN "Basic Selective Input.txt" 
#define FILE_NAMEOUT "Basic Selective OutPut.txt" 


bool have_traget(const char* buffer, size_t size)
{
    int i = 0;
    while (i < size)
    {
        if (buffer[i] == 'x' || buffer[i] == 'X') return true;
        ++i;
    }
    return false;
}

int main() 
{
    FILE* in = fopen(FILE_NAMEIN, "w+");
    FILE* out = fopen(FILE_NAMEOUT, "w+");
    
    if (!in) {
        printf("Couldnt open %s file:", FILE_NAMEIN);
        return -1;
    }
    if (!out) {
        printf("Couldnt open %s file:", FILE_NAMEOUT);
        return -1;
    }

    fwrite("hello1x\n", 8, 1, in);
    fwrite("hello3x\n", 8, 1, in);
    fwrite("hello2\n", 7, 1, in);
    fseek(in, 0, SEEK_SET);
    
    char buff[50];
    size_t size = 50;

    while (fgets(buff, 9, in)) 
    {
        if (!have_traget(buff, size)) fputs(buff, out);
    }



    fclose(in);
    fclose(out);
    return 0;
}