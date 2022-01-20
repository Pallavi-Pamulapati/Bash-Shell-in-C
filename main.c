#include "headers.h"

int job;

int main(void)
{
    int check = 0;
    char *direc = (char *)malloc(10000 * sizeof(char));
    getcwd(direc, 10000);
    char *copy = (char *)malloc(10000 * sizeof(char));
    strcpy(copy, direc);
    char **store = (char **)malloc(10000 * sizeof(char *));
    char *prev_dir = (char *)malloc(10000 * sizeof(char *));
    strcpy(prev_dir, direc);
    int imp;
    check = prompt(direc);
    char *input = NULL;
    char *semicolon;
    char *copy_semi = (char *)malloc(10000 * sizeof(char));
    char *space;
    char *path;
    char *delimit = " \t";
    int k = 0;
    job = 0;
    signal(SIGCHLD, handle);
    signal(SIGINT,CtrlC_Handler);
    signal(SIGTSTP,CtrlZ_Handler);
    Header = CreateNode(-100000, "empty", 0);
    retu = -1;
    while (check == 0)
    {
        check = getinput(&input);

        if (check == 1)
            break;

        int j = 0;
        store[j] = strtok(input, ";");
        while (store[j] != NULL)
        {
            j++;
            store[j] = strtok(NULL, ";");
        }
        for (int i = 0; i < j; i++)
        {
            int file1 = dup(1), redirect2 = dup(0);
            int count = 0;
            if (store[i] != NULL)
            {
                store[i] = Redirection(store[i]);
                if (store[i] == NULL)
                    continue;
            }
            int procced = 1;
            if (piped(store[i], direc) != 0)
                procced = 0;
            if (procced)
            {
                space = strtok(store[i], delimit);
                while (space != NULL)
                {
                    if (count == 0)
                    {
                        if (strcmp(space, "cd") == 0)
                        {
                            cd(prev_dir, direc);
                        }
                        else if (strcmp(space, "pwd") == 0)
                        {
                            getpwd();
                        }
                        else if (strcmp(space, "echo") == 0)
                        {
                            echo(store[i]);
                            // break;
                        }
                        else if (strcmp(space, "ls") == 0)
                        {
                            ls(store[i], direc);
                        }
                        else if (strcmp(space, "repeat") == 0)
                        {
                            repeat(prev_dir, direc, store[i]);
                            // break;
                        }
                        else if (strcmp(space, "pinfo") == 0)
                            pinfo(store[i], direc);
                        else if (strcmp(space, "exit") == 0)
                            check = 1;
                        else if (strcmp(space, "jobs") == 0)
                            jobs(space);
                        else if(strcmp(space,"replay") == 0)
                            check = replay_command(space,direc,prev_dir);
                        else if(strcmp(space, "fg") == 0)
                            jobs_fg(space);
                        else if(strcmp(space,"bg") == 0)
                            jobs_bg(space);
                        else if(strcmp(space, "sig") == 0)
                            jobs_sig(space);
                        else
                        {
                            //EXECVP(store[i],0);
                            EXECVP(space, 0);
                            break;
                        }
                    }
                    if (check == 1)
                        break;
                    space = strtok(NULL, delimit);
                    count++;
                }
            }
            dup2(file1, STDOUT_FILENO);
            close(file1);
            dup2(redirect2, STDIN_FILENO);
            close(redirect2);
        }
        free(input);
        if (check == 0)
            check = prompt(direc);
    }

    free(copy);
    return 0;
}