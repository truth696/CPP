#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#define FILENAME "result.txt"

bool same(const char* buffer, size_t size, const char* buffer2, size_t size2)
{
    int i = 0;

    while (buffer[i] != '\0' && buffer2[i] != '\0')
    {
        if (buffer[i] != buffer2[i]) return false;
        ++i;
    }

    return true;
}

int main()
{
    FILE* fl = fopen(FILENAME, "w");
    FILE* inp1 =  fopen("File1.txt", "r");
    FILE* inp2 =  fopen("File2.txt", "r");

    if (!(inp1 && inp2 && fl)) perror("Files cannot opened");

    char buffer[120];
    char buffer2[120];
    int sizeformalloc = 0;
    int choose = -1;

    while (fgets(buffer, 20, inp1) && fgets(buffer2, 20, inp2))
    {
        if (same(buffer, 20, buffer2, 20))
        {
            fputs(buffer2, fl);
        } else 
        {
            printf("Please choose the line\n1) %s\n2) %s", buffer, buffer2);
            scanf("%d", &choose);
            while (choose < 0 && choose > 2)
            {
                printf("Please input correct number\n1) %s\n2) %s", buffer, buffer2);
                scanf("%d", &choose);
            }
            if (choose == 1) 
            {
                fputs(buffer, fl);
            }
            else 
            {
                fputs(buffer2, fl);
            }
        }
    }

    fclose(fl);
    fclose(inp1);
    fclose(inp2);
}