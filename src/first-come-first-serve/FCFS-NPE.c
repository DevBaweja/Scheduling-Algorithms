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
    int AT, BT, ST, CT, TAT, WT, RT;
    int AT_new;
    int BT_left, BT_temp;
    int priority;
} Process;

// Node
typedef struct Node
{
    Process p;
    struct Node *next;
} Node;

// Queue
typedef struct Queue
{
    Node *front, *rear;
} Queue;

Queue *readyQueue = NULL;

// A utility function to create an empty queue
Queue *createQueue()
{
    Queue *readyQueue = (Queue *)malloc(sizeof(Queue));
    readyQueue->front = readyQueue->rear = NULL;
    return readyQueue;
}

// A utility function to create a new linked list node
Node *newNode(Process p)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->p = p;
    node->next = NULL;
    return node;
}

// Enqueue
void enqueue(Queue *readyQueue, Process p)
{
    // Create a new node
    Node *node = newNode(p);

    // If queue is empty, then new node is front and rear both
    if (readyQueue->rear == NULL)
    {
        readyQueue->front = readyQueue->rear = node;
        return;
    }

    // Add the new node at the end of queue and change rear
    readyQueue->rear->next = node;
    readyQueue->rear = node;
}

// Dequeue
void dequeue(Queue *readyQueue)
{
    // If queue is empty, return NULL.
    if (readyQueue->front == NULL)
        return;

    // Store previous front and move front one node ahead
    Node *node = readyQueue->front;

    readyQueue->front = readyQueue->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (readyQueue->front == NULL)
        readyQueue->rear = NULL;

    free(node);
}

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
            processes[index].ST = 0;
            processes[index].CT = 0;
            processes[index].TAT = 0;
            processes[index].WT = 0;
            processes[index].RT = 0;
            processes[index].AT_new = processes[index].AT;
            processes[index].BT_left = processes[index].BT;
            processes[index].BT_temp = 0;
            processes[index].priority = 0;
        }
}
// Set TAT
void set_TAT(Process *p)
{
    p->TAT = p->CT - p->AT;
}
// Set WT
void set_WT(Process *p)
{
    p->WT = p->TAT - p->BT;
}

// Set CT
void set_CT(Process *p, int CT)
{
    p->CT = CT;
    set_TAT(p);
    set_WT(p);
}

// Set RT
void set_RT(Process *p)
{
    p->RT = p->ST - p->AT;
}
// Set ST
void set_ST(Process *p, int ST)
{
    p->ST = ST;
    set_RT(p);
}

// First Come First Serve
void fcfs_npe()
{
    // Init Queue
    readyQueue = createQueue();
}

int main()
{
    char *filename = "FCFS-NPE.csv";
    // Read File
    readFile(filename);
    // Parse Inputs
    parseInputs();

    set_ST(&processes[1], 5);
    set_CT(&processes[1], 7);

    printf("AT: %d ", processes[1].AT);
    printf("BT: %d ", processes[1].BT);
    printf("ST: %d ", processes[1].ST);
    printf("CT: %d ", processes[1].CT);
    printf("TAT: %d ", processes[1].TAT);
    printf("WT: %d ", processes[1].WT);
    printf("RT: %d ", processes[1].RT);

    printf("AT New: %d ", processes[1].AT_new);
    printf("BT Temp: %d ", processes[1].BT_temp);
    printf("BT Left: %d ", processes[1].BT_left);

    printf("Priority: %d ", processes[1].priority);

    // Algorithm
    fcfs_npe();
}
