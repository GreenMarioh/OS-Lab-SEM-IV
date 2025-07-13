#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process
{
    int pid;
    int at;
    int bt;
    int wt;
    int ct;
    int tat;
};
typedef struct process pr;

void sjf(pr *pr, int n, int *executionOrder)
{
    int current = 0, completedCount = 0;
    bool completed[n];
    for (int i = 0; i < n; i++)
        completed[i] = false;

    while (completedCount < n)
    {
        int minIndex = -1;
        int minBurst = __INT_MAX__;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && pr[i].at <= current)
            {
                if (pr[i].bt < minBurst || (pr[i].bt == minBurst && pr[i].at < pr[minIndex].at))
                {
                    minBurst = pr[i].bt;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) // No process is available, move time forward
        {
            current++;
        }
        else
        {
            pr[minIndex].ct = current + pr[minIndex].bt;
            pr[minIndex].tat = pr[minIndex].ct - pr[minIndex].at;
            pr[minIndex].wt = pr[minIndex].tat - pr[minIndex].bt;
            completed[minIndex] = true;
            executionOrder[completedCount] = minIndex;
            current = pr[minIndex].ct;
            completedCount++;
        }
    }
}

void display(pr *pr, int n, int *executionOrder)
{
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        int index = executionOrder[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               pr[index].pid, pr[index].at, pr[index].bt,
               pr[index].ct, pr[index].tat, pr[index].wt);
    }
}

void sort(pr *prr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (prr[j].at > prr[j + 1].at || (prr[j].at == prr[j + 1].at && prr[j].pid > prr[j + 1].pid))
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
    printf("Enter the number of process\n");
    scanf("%d", &n);
    pr *prr = (pr *)malloc(n * sizeof(pr));
    int *executionOrder = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &prr[i].at, &prr[i].bt);
        prr[i].pid = i + 1;
    }

    sort(prr, n);
    sjf(prr, n, executionOrder);
    display(prr, n, executionOrder);

    free(prr);
    free(executionOrder);
}
