#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process
{
    int pid;      // Process ID
    int at;       // Arrival time
    int bt;       // Original burst time
    int rt;       // Remaining time
    int wt;       // Waiting time
    int tat;      // Turnaround time
    int ct;       // Completion time
    bool inQueue; // Flag to check if process is in ready queue
};
typedef struct process pr;

// Queue implementation for ready queue
struct queue
{
    int front, rear, size;
    int capacity;
    int *array;
};

// Function to create a queue of given capacity
struct queue *createQueue(int capacity)
{
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Queue operations
bool isFull(struct queue *queue)
{
    return (queue->size == queue->capacity);
}

bool isEmpty(struct queue *queue)
{
    return (queue->size == 0);
}

void enqueue(struct queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct queue *queue)
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Round Robin scheduling function
void roundRobin(pr *proc, int n, int quantum)
{
    // Create a queue for ready processes
    struct queue *readyQueue = createQueue(100);

    int *timeline = (int *)malloc(1000 * sizeof(int)); // For Gantt chart
    int timeIndex = 0;

    int current_time = 0;
    int completed = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        proc[i].rt = proc[i].bt;
        proc[i].inQueue = false;
    }

    // Add first process(es) that arrive at time 0
    for (int i = 0; i < n; i++)
    {
        if (proc[i].at == 0)
        {
            enqueue(readyQueue, i);
            proc[i].inQueue = true;
        }
    }

    // Main scheduling loop
    while (completed < n)
    {
        int current_proc = -1;

        // If ready queue is empty, find next process to arrive
        if (isEmpty(readyQueue))
        {
            int next_arrival = __INT_MAX__;
            int next_proc = -1;

            for (int i = 0; i < n; i++)
            {
                if (proc[i].rt > 0 && proc[i].at < next_arrival && !proc[i].inQueue && proc[i].at > current_time)
                {
                    next_arrival = proc[i].at;
                    next_proc = i;
                }
            }

            if (next_proc != -1)
            {
                // Jump to the arrival time of the next process
                for (int i = current_time; i < next_arrival; i++)
                {
                    timeline[timeIndex++] = -1; // Idle time
                }
                current_time = next_arrival;

                // Add newly arrived process to ready queue
                enqueue(readyQueue, next_proc);
                proc[next_proc].inQueue = true;
            }
            else
            {
                // No more processes to execute
                break;
            }
        }

        // Get process from front of ready queue
        current_proc = dequeue(readyQueue);
        proc[current_proc].inQueue = false;

        if (current_proc == -1)
            continue;

        // Execute process for quantum time or until completion
        int exec_time = (proc[current_proc].rt < quantum) ? proc[current_proc].rt : quantum;

        // Update remaining time
        proc[current_proc].rt -= exec_time;

        // Update timeline/Gantt chart
        for (int i = 0; i < exec_time; i++)
        {
            timeline[timeIndex++] = proc[current_proc].pid;
        }

        // Advance current time
        current_time += exec_time;

        // Check for new arrivals during this time slice
        for (int i = 0; i < n; i++)
        {
            if (proc[i].rt > 0 && proc[i].at <= current_time && !proc[i].inQueue && i != current_proc)
            {
                enqueue(readyQueue, i);
                proc[i].inQueue = true;
            }
        }

        // If process is completed
        if (proc[current_proc].rt == 0)
        {
            completed++;
            proc[current_proc].ct = current_time;
            proc[current_proc].tat = proc[current_proc].ct - proc[current_proc].at;
            proc[current_proc].wt = proc[current_proc].tat - proc[current_proc].bt;
        }
        // If process still has remaining time, put it back in the queue
        else if (proc[current_proc].rt > 0)
        {
            enqueue(readyQueue, current_proc);
            proc[current_proc].inQueue = true;
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < timeIndex; i++)
    {
        if (timeline[i] == -1)
            printf(" Idle |");
        else
            printf(" P%d |", timeline[i]);
    }
    printf("\n");

    free(timeline);
    free(readyQueue->array);
    free(readyQueue);
}

void display(pr *proc, int n)
{
    float avg_wt = 0, avg_tat = 0;

    // Sort by PID for display
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].pid > proc[j + 1].pid)
            {
                pr temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].at, proc[i].bt,
               proc[i].ct, proc[i].tat, proc[i].wt);

        avg_wt += proc[i].wt;
        avg_tat += proc[i].tat;
    }

    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
}

int main()
{
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    pr *proc = (pr *)malloc(n * sizeof(pr));

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].pid = i + 1;
    }

    // Sort processes by arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].at > proc[j + 1].at || (proc[j].at == proc[j + 1].at && proc[j].pid > proc[j + 1].pid))
            {
                pr temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    roundRobin(proc, n, quantum);
    display(proc, n);

    free(proc);
    return 0;
}