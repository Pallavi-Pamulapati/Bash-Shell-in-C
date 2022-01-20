#include "headers.h"

void jobs_sig(char *input)
{
    char *delimit = " \t";
    char *token = strtok(NULL, delimit);

    if (token == NULL)
    {
        printf("Less No.of Arguments for sig\n");
        return;
    }

    int job_no = atoi(token);

    if (job_no <= 0 || job_no > job)
    {
        printf("Invalid Job Number\n");
        return;
    }

    token = strtok(NULL, delimit);

    if (token == NULL)
    {
        printf("Less No.of Arguments\n");
        return;
    }

    int signal_number = atoi(token);
    int pid = FindPID(job_no);

    int check = kill(pid, signal_number);

    if (check < 0)
    {
        printf("Kill is not successful\n");
        return;
    }

    return;
}

void jobs_fg(char *input)
{
    char *delimit = " \t";
    char *token = strtok(NULL, delimit);

    if (token == NULL)
    {
        printf("Less No.of Arguments for fg command\n");
        return;
    }

    int job_no = atoi(token);

    token = strtok(NULL, delimit);

    if (token != NULL)
    {
        printf("Too many arguments\n");
        return;
    }

    if (job_no <= 0 || job_no > job)
    {
        printf("Invalid Job Number\n");
        return;
    }

    int pid = FindPID(job_no);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    int status;

    tcsetpgrp(0, pid);
    tcsetpgrp(1, pid);

    int check = kill(pid, SIGCONT);

    if (check < 0)
    {
        printf("KILL is unsuccessful\n");
        return;
    }

    // printf("%d\n", pid);

    waitpid(pid, &status, WUNTRACED);

    if (WIFSTOPPED(status))
        kill(pid, SIGSTOP);

    tcsetpgrp(0, getpid());
    tcsetpgrp(1, getpid());

    if (!WIFSTOPPED(status))
        DeleteNode(pid);

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return;
}

void jobs_bg(char *input)
{
    char *delimit = " \t";
    char *token = strtok(NULL, delimit);

    if (token == NULL)
    {
        printf("Less No.of Arguments for fg command\n");
        return;
    }

    int job_no = atoi(token);

    token = strtok(NULL, delimit);

    if (token != NULL)
    {
        printf("Too many arguments\n");
        return;
    }

    if (job_no <= 0 || job_no > job)
    {
        printf("Invalid Job Number\n");
        return;
    }

    int pid = FindPID(job_no);

    int check = kill(pid, SIGCONT);

    if (check < 0)
        perror("Kill Unseccessful");

    return;
}