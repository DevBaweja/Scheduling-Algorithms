// Modular Re usable components
#include <stdio.h>
#include <stdlib.h>

char **PID;
char **AT;
char **BT;
int TOTAL = 0;

void readFile(char *filename)
{
    // Open File
    FILE *fp, *fptemp = NULL;
    char *mode = "r";
    fp = fopen(filename, mode);
    fptemp = fopen(filename, mode);

    if (fp == NULL || fptemp == NULL)
    {
        puts("Cann't open file!");
        exit(1);
    }
    // Read Content
    int SIZE = 1000;
    char line[SIZE];
    // Determining TOTAL
    while (strcmp(fgets(line, sizeof(line), (FILE *)fptemp), "EOF") != 0)
        TOTAL++;

    PID = (char **)malloc(TOTAL + 1);
    AT = (char **)malloc(TOTAL + 1);
    BT = (char **)malloc(TOTAL + 1);

    /*
    {
        {'1', '0'}, {'1'}, {'1', '3', '1'}, { '1', '5', '3', '2' }
    }
    */
    char content[SIZE];
    int pos;
    for (pos = 0; strcmp(fgets(content, sizeof(content), (FILE *)fp), "EOF") != 0; pos++)
    {
        puts(content);
    }
}