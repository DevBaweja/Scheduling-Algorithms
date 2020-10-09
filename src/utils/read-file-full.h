#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **PID;
char **AT;
char **BT;
int TOTAL;

/*
char *join(char *s1, char *s2)
{
    char *s3;
    int k = 0;
    int i = 0, j = 0;
    while (s1[i] != '\0')
    {
        s3[k++] = s1[i++];
        printf("no");
    }
    while (s2[j] != '\0')
        s3[k++] = s2[j++];
    return s3;
}
*/

void readFile(char *path)
{
    char filename[1000];
    // strcpy(filename, strcat("../../input/", path));

    FILE *fp, *fptemp;

    fp = fopen(filename, "r");
    fptemp = fopen(filename, "r");

    if (!fp && !fptemp)
    {
        printf("Cann't open file!");
        exit(0);
    }
    int SIZE = 1000;
    char temp[SIZE];
    TOTAL = 0;
    while (strcmp(fgets(temp, sizeof(temp), (FILE *)fptemp), "EOF") != 0)
        TOTAL++;
    PID = (char **)malloc(TOTAL + 1);
    AT = (char **)malloc(TOTAL + 1);
    BT = (char **)malloc(TOTAL + 1);

    // Read content from file
    char content[SIZE];
    for (int pos = 0; strcmp(fgets(content, sizeof(content), (FILE *)fp), "EOF") != 0; pos++)
    {
        char *token;
        token = strtok(content, ":");
        PID[pos] = (char *)malloc(strlen(token) + 1);
        strcpy(PID[pos], token);

        char *args[2];
        // Spliting with delimiter of :
        for (int index = 0; (token = strtok(NULL, ":")) != NULL; index++)
            strcpy(args[index], token);

        // Memory Allocation
        AT[pos] = (char *)malloc(strlen(args[0]) + 1);
        strcpy(AT[pos], args[0]);

        BT[pos] = (char *)malloc(strlen(args[1]) + 1);
        strcpy(BT[pos], args[1]);
    }
    // Close file
    fclose(fptemp);
    fclose(fp);
}
