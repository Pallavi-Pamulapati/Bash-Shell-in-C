#include "headers.h"

void handle(int A)
{
    int status;
    pid_t PID = waitpid(-1, &status, WNOHANG);

    if (PID > 0)
    {
        char *ptr = (char *)malloc(sizeof(char *) * 1000);
        ptr = FindNode(PID);
        if (WIFEXITED(status))
        {
            printf("%s with pid %d exited normally\n", ptr, PID);
        }
        else
        {
            printf("%s with pid %d exited abnormally\n", ptr, PID);
        }
        DeleteNode(PID);
    }
    return;
}

void CtrlZ_Handler(int A)
{
    printf("\n");
    fflush(stdout);

    return;
}

void CtrlC_Handler(int A)
{
    if (retu != -1)
        kill(retu, SIGINT);
    printf("\n");
    fflush(stdout);

    return;
}