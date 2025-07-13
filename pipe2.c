#include <stdio.h>
#include <unistd.h>
int main()
{
    int pipeds[2];
    int returnstatus;
    char writeimage[2][20] = {"HI", "HELLO"};
    char readimage[20];
    returnstatus = pipe(pipeds);
    int pid;
    if (returnstatus == -1)
    {
        printf("Unable to create pipe\n");
        return 1;
    }
    pid = fork(); // child process
    if (pid == 0)
    {
        read(pipeds[0], readimage, sizeof(readimage));
        printf("Child process reading from pipe msg1 %s\n", readimage);
        read(pipeds[0], readimage, sizeof(readimage));
        printf("Child Process reading from pipe msg2 %s\n", readimage);
    }
    else
    {
        printf("Parent Process Writing to pipe msg1 %s \n", writeimage[0]);
        write(pipeds[1], writeimage[0], sizeof(writeimage[0]));
        printf("Parent Process Writing to pipe msg2 %s \n", writeimage[1]);
        write(pipeds[1], writeimage[1], sizeof(writeimage[1]));
    }
    return 0;
}