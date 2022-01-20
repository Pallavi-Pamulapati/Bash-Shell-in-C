#include "headers.h"

int piped(char *command, char *direc)
{
    if (strstr(command, " | ") == NULL)
        return 0;
    int original1 = dup(1), original2 = dup(0);

    char *copy = (char *)malloc(1000 * sizeof(char));
    strcpy(copy, "");
    strcpy(copy, command);
    char store[100][1000] = {0};
    char *delimit = " \n\t";
    char *token = strtok(copy, "|");
    int j = 0, input = 0;
    while (token != NULL)
    {
        strcpy(store[j], token);
        j++;

        token = strtok(NULL, "|");
    }

    int fileDescriptors[2] = {0};
    char *space;
    space=(char*)malloc(sizeof(char)*1024);
    int count = 0;
    for (int p = 0; p < j; p++)
    {
        count = 0;
        char *send = (char *)malloc(1000 * sizeof(char));
        if (pipe(fileDescriptors) < 0)
        {
            perror("Could not create pipe.");
            exit(1);
        }
        int return_value = fork();
        if (return_value == 0)
        {
            int k = 0;
            char *tokens[100] = {0};
            for (int i = 0; i < 100; i++)
                tokens[i] = (char *)malloc(1000 * sizeof(char));
            space = strtok(store[p], delimit);

            while (space != NULL)
            {
                strcpy(tokens[k], space);
                k++;
                space = strtok(NULL, delimit);
            }

            if (input != 0)
            {
                dup2(input, 0);
                close(input);
            }
            if (fileDescriptors[1] != 1 && p != j - 1)
            {
                dup2(fileDescriptors[1], 1);
                close(fileDescriptors[1]);
            }

            strcpy(send, "");
            for (int i = 0; i < k; i++)
            {
                strcat(send, tokens[i]);
                if (i != k - 1)
                    strcat(send, " ");
            }
            tokens[k]=NULL;
            char *tok = strtok(send, delimit);
            if (strcmp(tok, "pinfo") == 0)
                pinfo(send, direc);
            else if (strcmp(tok, "jobs") == 0)
                jobs(send);
            else
                execvp(tokens[0], tokens);
            exit(0);
        }
        else
        {
            int stats;
            waitpid(return_value, &stats, 0);
        }
        input = fileDescriptors[0];
        close(fileDescriptors[1]);
    }
    
    return 1;
}