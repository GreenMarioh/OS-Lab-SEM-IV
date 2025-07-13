#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void forkxample()
{
    int p;
    p = fork();
    if (p < 0)
    {
        perror("fork fail");
        exit(1);
    }
    else if (p == 0)
        printf("Hello from Child\n");
    else
        printf("Hello from Parent\n");
}
int main()
{
    forkxample();
    return 0;
}