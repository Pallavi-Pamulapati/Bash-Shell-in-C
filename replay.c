#include "headers.h"

int replay_command(char *input, char *direc, char *prev_dir)
{
    char *delimit = " \t";
    char *token = strtok(NULL, delimit);

    if (strcmp(token, "-command") != 0)
    {
        printf("Invalid Command\n");
        return 0;
    }

    char *command = (char *)malloc(10000 * sizeof(char));
    strcpy(command, "");

    token = strtok(NULL, delimit);

    while (strcmp(token, "-interval") != 0 && token != NULL)
    {
        strcat(command, token);

        token = strtok(NULL, delimit);
        if (strcmp(token, "-interval") != 0)
            strcat(command, " ");
    }

    if (strcmp(token, "-interval") != 0)
    {
        printf("Invalid Command");
        return 0;
    }

    token = strtok(NULL, delimit);

    int interval = atoi(token);

    token = strtok(NULL, delimit);

    if (strcmp(token, "-period") != 0)
    {
        printf("please provide valid arguments for replay command\n");
        return 0;
    }

    token = strtok(NULL, delimit);

    int period = atoi(token);

    char *copy = (char *)malloc(10000 * sizeof(char));
    strcpy(copy, "");
    char *space;
    int check = 0;

    if (interval == 0)
    {
        printf("Please Give a proper interval\n");
        return 0;
    }

    for (int i = 0; i < period / interval; i++)
    {
        sleep(interval);
        strcpy(copy, command);
        int count = 0;
        space = strtok(copy, delimit);
        check = 0;
        while (space != NULL && check == 0)
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
                    echo(copy);
                    // break;
                }
                else if (strcmp(space, "ls") == 0)
                {
                    ls(copy, direc);
                }
                else if (strcmp(space, "repeat") == 0)
                {
                    repeat(prev_dir, direc, copy);
                    // break;
                }
                else if (strcmp(space, "pinfo") == 0)
                    pinfo(copy, direc);
                else if (strcmp(space, "exit") == 0)
                    check = 1;
                else if (strcmp(space, "jobs") == 0)
                    jobs(space);
                else
                {
                    EXECVP(space, 0);
                    break;
                }
            }
            if (check == 1)
                break;
            space = strtok(NULL, delimit);
            count++;
        }
        if (check == 1)
            break;
    }
    sleep(period % interval);

    if (check == 1)
        return 1;

    free(command);
    free(copy);
}