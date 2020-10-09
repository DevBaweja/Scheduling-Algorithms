#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **PID;
char **AT;
char **BT;
int TOTAL;
void readFile(char *filename)
{
    FILE *fp, *fptotal;

    char *mode = "r";
    fp = fopen(filename, mode);
    fptotal = fopen(filename, mode);

    if (fp == NULL || fptotal == NULL)
    {
        printf("Cann't open file!");
        exit(-1);
    }

    // Read Content
    int SIZE = 1000;
    char line[SIZE];

    // Determining TOTAL
    TOTAL = 0;
    while (strcmp(fgets(line, sizeof(line), (FILE *)fptotal), "EOF") != 0)
        TOTAL++;

    PID = (char **)malloc(TOTAL + 1);
    AT = (char **)malloc(TOTAL + 1);
    BT = (char **)malloc(TOTAL + 1);

    // Read content from file
    char content[SIZE];
    int pos;
    for (pos = 0; strcmp(fgets(content, sizeof(content), (FILE *)fp), "EOF") != 0; pos++)
    {
        char *token;
        token = strtok(content, ":");
        PID[pos] = (char *)malloc(strlen(token) + 1);
        strcpy(PID[pos], token);

        char *args[2];
        // Spliting with delimiter of :
        int index;
        for (index = 0; (token = strtok(NULL, ":")) != NULL; index++)
            strcpy(args[index], token);

        // Memory Allocation
        AT[pos] = (char *)malloc(strlen(args[0]) + 1);
        // Copying
        strcpy(AT[pos], args[0]);

        // Memory Allocation
        BT[pos] = (char *)malloc(strlen(args[1]) + 1);
        // Copying
        strcpy(BT[pos], args[1]);
    }
    // Close file
    fclose(fptotal);
    fclose(fp);
}

int main()
{
    // Read File
    readFile("../../input/FCFS-NPE.csv");
    // Parse
    printf("%d", TOTAL);
}
