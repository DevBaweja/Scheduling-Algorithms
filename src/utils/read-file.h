// Modular Re usable components
#include <stdio.h>
#include <string.h>

void readFile(char *filename)
{
    FILE *fp = NULL;
    char *path = strcat("../../input/", filename);
    char *mode = "r";
    fp = fopen(path, mode);
}