#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Temp Inputs
char **PIDtemp;
char **ATtemp;
char **BTtemp;
int TOTAL;

// Read File
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

    PIDtemp = (char **)malloc(TOTAL + 1);
    ATtemp = (char **)malloc(TOTAL + 1);
    BTtemp = (char **)malloc(TOTAL + 1);

    // Read content from file
    char content[SIZE];
    int pos;
    for (pos = 0; strcmp(fgets(content, sizeof(content), (FILE *)fp), "EOF") != 0; pos++)
    {
        char *token;
        token = strtok(content, ":");
        PIDtemp[pos] = (char *)malloc(strlen(token) + 1);
        strcpy(PIDtemp[pos], token);

        char *args[2];
        // Spliting with delimiter of :
        int index;
        for (index = 0; (token = strtok(NULL, ":")) != NULL; index++)
        {
            // Allocate Memory
            args[index] = (char *)malloc(strlen(token) + 1);
            // Copying
            strcpy(args[index], token);
        }

        // Memory Allocation
        ATtemp[pos] = (char *)malloc(strlen(args[0]) + 1);
        // Copying
        strcpy(ATtemp[pos], args[0]);

        // Memory Allocation
        BTtemp[pos] = (char *)malloc(strlen(args[1]) + 1);
        // Copying
        strcpy(BTtemp[pos], args[1]);
    }
    // Close file
    fclose(fptotal);
    fclose(fp);
}

// Structure
typedef struct Process
{
    char *PID;
    int AT, BT, CT, TAT, WT, RT;
} Process;

// Processes
Process *processes;

// Parse Inputs
void parseInputs()
{
    processes = (Process *)malloc(TOTAL * sizeof(Process));
    // Allocate Memory
    int index;
    for (index = 0; index < TOTAL; index++)

        for (index = 0; index < TOTAL; index++)
        {
            // Copying PID
            processes[index].PID = PIDtemp[index];
            // Type Cast ATtemp and BTtemp
            processes[index].AT = atoi(ATtemp[index]);
            processes[index].BT = atoi(BTtemp[index]);
        }
}
// Ready Queue
typedef struct readyQueue
{
    Process p;
    struct readyQueue *next;
} readyQueue;

readyQueue *queue = NULL;
// Show Queue
void showQueue(readyQueue *queue)
{
    if (queue == NULL)
    {
        printf("No Element");
    }
    else
    {
        readyQueue *temp = queue;
        while (temp->next != NULL)
        {
            printf("%d ", temp->p.AT);
            temp = temp->next;
        }
        printf("%d ", temp->p.AT);
    }
}
// Enqueue
void enqueue(readyQueue *queue, Process p)
{
    if (queue == NULL)
    {
        queue = (readyQueue *)malloc(sizeof(readyQueue));
        queue->p = p;
        queue->next = NULL;
    }
    else
    {
        readyQueue *temp = queue;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = (readyQueue *)malloc(sizeof(readyQueue));
        temp = temp->next;
        temp->p = p;
        temp->next = NULL;
    }
}
// Dequeue
void dequeue(readyQueue *queue)
{
    if (queue == NULL)
    {
        printf("No Element");
    }
    else
    {
        readyQueue *temp = queue;
        while (temp->next != NULL)
            temp = temp->next;

        if (temp == queue)
            queue = NULL;

        // temp->p = NULL;
        // temp->next = NULL;
    }
}

// First Come First Serve
void fcfs_npe()
{
    // Init Queue
    enqueue(queue, processes[0]);
    enqueue(queue, processes[1]);
    enqueue(queue, processes[2]);
    enqueue(queue, processes[3]);

    showQueue(queue);

    dequeue(queue);
    int time = 0;
}

int main()
{
    char *filename = "FCFS-NPE.csv";
    // Read File
    readFile(filename);
    // Parse Inputs
    parseInputs();

    // Algorithm
    fcfs_npe();
}
