#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int choice;
    while (1)
    {
        printf("<== Scheduling Algorithm ==>\n");
        printf("1. First Come First Serve \n");
        printf("2. Shortest Job First \n");
        printf("0. Exit \n\n");
        printf("Enter Your choice: ");
        scanf("%d ", &choice);
        switch (choice)
        {
        case 0:
            exit(0);

        case 1:
            fcfs();
            break;

        case 2:
            sjf();
            break;
        default:
            printf("Invalid Choice");
        }
    }
}
