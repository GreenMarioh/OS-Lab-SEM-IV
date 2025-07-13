#include <stdio.h>
#include <stdlib.h>

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
void fcfs(pr *pr, int n)
{
	int current=0;
	for (int i=0;i<n;i++)
	{
		if(current<pr[i].at)
		{
			current= pr[i].at;
		}
		pr[i].ct=current+pr[i].bt;
		pr[i].tat=pr[i].ct - pr[i].at;
		pr[i].wt=pr[i].tat - pr[i].bt;
		current=pr[i].ct;
	}
}
void display(pr *pr, int n) {
	printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
	for (int i = 0; i < n; i++) {
		printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
			   pr[i].pid,pr[i].at, pr[i].bt,
			   pr[i].ct, pr[i].tat,pr[i].wt);
	}
}
void sort(pr *prr, int n)
{
	for(int i=0;i<n;i++)
	{
		for( int j=0;j<n-i-1;j++)
		{
			if(prr[j].at>prr[j+1].at || (prr[j].at==prr[j+1].at&&prr[j].pid>prr[j+1].pid))
			{
				pr temp= prr[j];
				prr[j]=prr[j+1];
				prr[j+1]= temp;
			}
		}
	}
}

int main()
{
	int n;
	printf("Enter the number of process\n");
	scanf("%d",&n);
	pr *prr=(pr*)malloc(n*sizeof(pr));
	for(int i=0;i<n;i++)
	{
		printf("Enter the arrival time and burst time for process %d :",i+1);
		scanf("%d %d",&prr[i].at,&prr[i].bt);
		prr[i].pid=i+1;
	}
	sort(prr,n);
	fcfs(prr,n);
	display(prr,n);
	free(prr);
}


