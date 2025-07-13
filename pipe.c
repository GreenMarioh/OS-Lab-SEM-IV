#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define pipe(fds) _pipe(fds, 512, O_BINARY)
#else

#endif
int main()
{
    int pipefds[2];
    int returnstatus;
    char writemessage[2][20] = {"Hi", "Hello"};
    char readmessage[20];
    returnstatus = pipe(pipefds);
    if (returnstatus == -1)
    {
        printf("Unable to create pipe\n");
        return 1;
    }
    printf("Writing to pipe-msg-1 is %s \n", writemessage[0]);
    write(pipefds[1], writemessage[0], sizeof(writemessage[0]));
    read(pipefds[0], readmessage, sizeof(readmessage));
    printf("Reading from pipe-msg-1 is %s \n", readmessage);
    printf("_____________msg-2_________\n");
    write(pipefds[1], writemessage[1], sizeof(writemessage[1]));
    read(pipefds[0], readmessage, sizeof(readmessage));
    printf("reading _____ msg-2___ %s\n", readmessage);
    return 0;
}