#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct process
{
    int pid;
    int at;
    int bt; 
    int rt; 
    int wt;
    int ct;
    int tat;
    bool started; 
};
typedef struct process pr;

void srtf(pr *pr, int n)
{
    int current = 0;
    int completed = 0;
    int prevRunning = -1;

    // Array to track the timeline of process execution
    int *timeline = (int *)malloc(1000 * sizeof(int)); // Assuming max time is 1000
    int timeIndex = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        pr[i].rt = pr[i].bt;
        pr[i].started = false;
    }

    // Execute until all processes complete
    while (completed < n)
    {
        int shortest = -1;
        int minRemaining = __INT_MAX__;

        // Find process with shortest remaining time among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (pr[i].rt > 0 && pr[i].at <= current)
            {
                if (pr[i].rt < minRemaining)
                {
                    minRemaining = pr[i].rt;
                    shortest = i;
                }
                // If tie in remaining time, choose the one that arrived earlier
                else if (pr[i].rt == minRemaining && pr[i].at < pr[shortest].at)
                {
                    shortest = i;
                }
            }
        }

        // If no process is available, advance time
        if (shortest == -1)
        {
            current++;
            timeline[timeIndex++] = -1; // Idle time
        }
        else
        {
            // Record if process started for the first time
            if (!pr[shortest].started)
            {
                pr[shortest].started = true;
            }

            // Context switch tracking (for visualization)
            if (prevRunning != shortest && prevRunning != -1)
            {
                // A context switch happened
            }

            // Execute the process for one time unit
            pr[shortest].rt--;
            timeline[timeIndex++] = pr[shortest].pid;
            current++;
            prevRunning = shortest;

            // If process completes
            if (pr[shortest].rt == 0)
            {
                completed++;
                pr[shortest].ct = current;
                pr[shortest].tat = pr[shortest].ct - pr[shortest].at;
                pr[shortest].wt = pr[shortest].tat - pr[shortest].bt;
            }
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
}

void display(pr *pr, int n)
{
    float avg_wt = 0, avg_tat = 0;

    // Sort by PID for display
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pr[j].pid > pr[j + 1].pid)
            {
                struct process temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;
            }
        }
    }

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               pr[i].pid, pr[i].at, pr[i].bt,
               pr[i].ct, pr[i].tat, pr[i].wt);

        avg_wt += pr[i].wt;
        avg_tat += pr[i].tat;
    }

    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
}

void sort(pr *prr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (prr[j].at > prr[j + 1].at || (prr[j].at == prr[j + 1].at && prr[j].bt > prr[j + 1].bt))
            {
                pr temp = prr[j];
                prr[j] = prr[j + 1];
                prr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    pr *prr = (pr *)malloc(n * sizeof(pr));

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &prr[i].at, &prr[i].bt);
        prr[i].pid = i + 1;
    }

    sort(prr, n);
    srtf(prr, n);
    display(prr, n);

    free(prr);
    return 0;
}