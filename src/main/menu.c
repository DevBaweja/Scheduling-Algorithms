#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Temp Inputs
char **PIDtemp;
char **ATtemp;
char **BTtemp;
char **Ptemp;
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
    Ptemp = (char **)malloc(TOTAL + 1);

    // Read content from file
    char content[SIZE];
    int pos;
    for (pos = 0; strcmp(fgets(content, sizeof(content), (FILE *)fp), "EOF") != 0; pos++)
    {
        char *token;
        token = strtok(content, ":");
        PIDtemp[pos] = (char *)malloc(strlen(token) + 1);
        strcpy(PIDtemp[pos], token);

        char *args[3];
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

        // Memory Allocation
        Ptemp[pos] = (char *)malloc(strlen(args[2]) + 1);
        // Copying
        strcpy(Ptemp[pos], args[2]);
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
    int BT_left, BT_temp;
    int priority, priority_temp;
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

// A utility function to create an empty queue
Queue *createQueue()
{
    Queue *readyQueue = (Queue *)malloc(sizeof(Queue));
    readyQueue->front = readyQueue->rear = NULL;
    return readyQueue;
}

Queue *readyQueue = NULL;

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
Process dequeue(Queue *readyQueue)
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

    return node->p;
}
// Processes
Process *processes = NULL;

// Parse Inputs
void parseInputs()
{
    processes = (Process *)malloc(TOTAL * sizeof(Process));
    // Allocate Memory
    int index;

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
        processes[index].BT_left = processes[index].BT;
        processes[index].BT_temp = processes[index].BT;
        processes[index].priority = atoi(Ptemp[index]);
        processes[index].priority_temp = processes[index].priority;
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
// Getting Index of Process
int getProcessIndex(Process p)
{
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        if (p.PID == processes[index].PID)
            return index;
    }
}

int maximumArrivalTime()
{
    int maxAT = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        int AT = processes[index].AT;
        if (maxAT < AT)
            maxAT = AT;
    }
    return maxAT;
}

int minimumBurstTime(int limit)
{
    int minBT = 0;
    int minIndex = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        if (processes[index].AT == limit)
        {
            int BT = processes[index].BT_temp;
            if ((minBT == 0 || BT < minBT) && BT != 0)
            {
                minBT = BT;
                minIndex = index;
            }
        }
    }
    return minIndex;
}

int maximumPriority(int limit)
{
    int maxPriority = 0;
    int maxIndex = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        if (processes[index].AT == limit)
        {
            int priority = processes[index].priority_temp;
            if ((maxPriority == 0 || priority > maxPriority) && priority != 0)
            {
                maxPriority = priority;
                maxIndex = index;
            }
        }
    }
    return maxIndex;
}

void aggregate()
{
    // Average TAT, WT, RT
    float avgTAT = 0, avgWT = 0, avgRT = 0;
    // Avg
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        avgTAT += processes[index].TAT;
        avgWT += processes[index].WT;
        avgRT += processes[index].RT;
    }
    avgTAT = avgTAT / TOTAL;
    avgWT = avgWT / TOTAL;
    avgRT = avgRT / TOTAL;

    // Table
    for (index = 0; index < TOTAL; index++)
    {
        printf("Process: %s ", processes[index].PID);
        printf("AT: %d ", processes[index].AT);
        printf("BT: %d ", processes[index].BT);
        printf("ST: %d ", processes[index].ST);
        printf("CT: %d ", processes[index].CT);
        printf("TAT: %d ", processes[index].TAT);
        printf("WT: %d ", processes[index].WT);
        printf("RT: %d ", processes[index].RT);
        printf("Priority: %d ", processes[index].priority);
        printf("\n");
    }
    printf("Average : \n");
    printf("Turn Around Time: %.2f ", avgTAT);
    printf("Waiting Time: %.2f ", avgWT);
    printf("Response Time: %.2f ", avgRT);
}

// First Come First Serve
void fcfs_npe()
{
    // Init Queue
    readyQueue = createQueue();
    // Enqueue Processes according to AT
    int timeline;
    timeline = 0;
    int maxAT = maximumArrivalTime();
    // Adding process according to Arrival Time
    while (timeline <= maxAT)
    {
        int index;
        for (index = 0; index < TOTAL; index++)
            if (timeline == processes[index].AT)
                enqueue(readyQueue, processes[index]);
        timeline++;
    }

    // Dequeue Process
    timeline = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        Process p = dequeue(readyQueue);
        // Waiting for process to arrive
        while (timeline < p.AT)
            timeline++;
        // Getting index of process
        int processIndex = getProcessIndex(p);
        // Setting Start Time
        set_ST(&processes[processIndex], timeline);
        while (p.BT_left > 0)
        {
            p.BT_left--;
            timeline++;
        }
        set_CT(&processes[processIndex], timeline);
    }

    // Calculate Aggregate
    aggregate();
}
// Shortest Job First
void sjf_npe()
{
    // Init Queue
    readyQueue = createQueue();
    // Enqueue Processes according to AT
    int timeline;
    timeline = 0;
    int maxAT = maximumArrivalTime();
    while (timeline <= maxAT)
    {
        int index;
        for (index = 0; index < TOTAL; index++)
        {
            if (timeline == processes[index].AT)
            {
                // Getting Process with minimum Burst Time
                int processIndex = minimumBurstTime(timeline);
                processes[processIndex].BT_temp = 0;
                enqueue(readyQueue, processes[processIndex]);
            }
        }
        timeline++;
    }

    // Dequeue Process
    timeline = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        Process p = dequeue(readyQueue);
        // Waiting for process to arrive
        while (timeline < p.AT)
            timeline++;

        int processIndex = getProcessIndex(p);
        // Setting Start Time
        set_ST(&processes[processIndex], timeline);
        while (p.BT_left > 0)
        {
            p.BT_left--;
            timeline++;
        }
        set_CT(&processes[processIndex], timeline);
    }

    // Calculate Aggregate
    aggregate();
}
// Priority
void priority_npe()
{
    // Init Queue
    readyQueue = createQueue();
    // Enqueue Processes according to AT
    int timeline;
    timeline = 0;
    int maxAT = maximumArrivalTime();
    // Adding process according to Arrival Time
    while (timeline <= maxAT)
    {
        int index;
        for (index = 0; index < TOTAL; index++)
        {
            if (timeline == processes[index].AT)
            {
                // Getting Process with maximum Priority
                int processIndex = maximumPriority(timeline);
                processes[processIndex].priority_temp = 0;
                enqueue(readyQueue, processes[processIndex]);
            }
        }
        timeline++;
    }

    // Dequeue Process
    timeline = 0;
    int index;
    for (index = 0; index < TOTAL; index++)
    {
        Process p = dequeue(readyQueue);
        // Waiting for process to arrive
        while (timeline < p.AT)
            timeline++;
        // Getting index of process
        int processIndex = getProcessIndex(p);
        // Setting Start Time
        set_ST(&processes[processIndex], timeline);
        while (p.BT_left > 0)
        {
            p.BT_left--;
            timeline++;
        }
        set_CT(&processes[processIndex], timeline);
    }

    // Calculate Aggregate
    aggregate();
}
// Round Robin
void rr_pe()
{
    // Init Queue
    readyQueue = createQueue();
    // Enqueue Processes according to AT
    int timeline;
    timeline = 0;
    int maxAT = maximumArrivalTime();
    // Adding process according to Arrival Time
    while (timeline <= maxAT)
    {
        int index;
        for (index = 0; index < TOTAL; index++)
            if (timeline == processes[index].AT)
                enqueue(readyQueue, processes[index]);
        timeline++;
    }

    // Dequeue Process
    timeline = 0;
    int quantam = 2;
    while (1)
    {
        Process p = dequeue(readyQueue);
        // Waiting for process to arrive
        while (timeline < p.AT)
            timeline++;
        // Getting index of process
        int processIndex = getProcessIndex(p);
        // Setting Start Time
        if (processes[processIndex].ST == 0)
            set_ST(&processes[processIndex], timeline);
        if (processes[processIndex].BT_left > quantam)
        {
            // Increase timeline by quantam
            timeline = timeline + quantam;
            processes[processIndex].BT_left -= quantam;
            enqueue(readyQueue, processes[processIndex]);
        }
        else
        {
            // Increase timeline by remaining Burst Time
            timeline = timeline + processes[processIndex].BT_left;
            processes[processIndex].BT_left = 0;
            set_CT(&processes[processIndex], timeline);
        }
        if (readyQueue->front == NULL)
            break;
    }

    // Calculate Aggregate
    aggregate();
}

// Main
int main()
{
    char *filename = "input.csv";
    // Read File
    readFile(filename);
    int choice;
    while (1)
    {
        // Clearing
        readyQueue = NULL, processes = NULL;
        // Parse Inputs
        parseInputs();

        printf("<== Scheduling Algorithm ==>\n");
        printf("1. First Come First Serve \n");
        printf("2. Shortest Job First \n");
        printf("3. Priority \n");
        printf("4. Round Robin \n");
        printf("0. Exit \n");
        printf("Enter Your choice: \n");

        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            fcfs_npe();
            break;
        case 2:
            sjf_npe();
            break;
        case 3:
            priority_npe();
            break;
        case 4:
            rr_pe();
            break;
        default:
            printf("Invalid Choice");
        }
        printf("\n\n");
    }
}
