#include "headers.h"

char* Redirection(char* command)
{
    char* copy = (char*)malloc(10000*sizeof(char));
    strcpy(copy, command);
    char* modified = (char*)malloc(10000*sizeof(char));
    char store[100][1000] = {0};
    int j = 0,fd = 0;
    int icount = 0, ocount = 0, acount = 0;
    if(strstr(copy, "<") || strstr(copy,">") || strstr(copy,">>"))
    {
        char* delimit = " \t\n";
        char* token = strtok(copy,delimit);

        while(token != NULL)
        {
            strcpy(store[j],token);
            j++;

            if(strcmp(token,"<") == 0)
                icount++;
            else if(strcmp(token, ">") == 0)
                ocount++;
            else if(strcmp(token,"<<") == 0)
                acount++;
            token = strtok(NULL,delimit);
        }
        if(icount >= 2 || acount >= 2 || ocount >= 2 || (acount + ocount) >= 2)
        {
            printf("Multiple Operations\n");
            return NULL;
        }
        for(int i = 0;i < j;i++)
        {
            if(strcmp(store[i], "<") == 0)
                store[i][0] = '\0';
            else if(strcmp(store[i],">") == 0)
            {
                if(i+1 >= j)
                {
                    printf("No file given to redirect\n");
                    return NULL;
                }
                else
                {
                    store[i][0] = '\0';
                    fd = open(store[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0)
                    {
                        perror("Failed to open file.");
                        return NULL;
                    }
                    if (dup2(fd, STDOUT_FILENO) < 0)
                    {
                        perror("Unable to duplicate file descriptor.");
                        return NULL;
                    }
                    store[i+1][0] = '\0';
                }
            }
            else if(strcmp(store[i], ">>") == 0)
            {
                if(i+1 >= j)
                {
                    printf("No file given to redirect\n");
                    return NULL;
                }
                else
                {
                    store[i][0] = '\0';
                    fd = open(store[i+1], O_APPEND | O_WRONLY | O_CREAT, 0644);
                    if (fd < 0)
                    {
                        perror("Failed to open file.");
                        return NULL;
                    }
                    if (dup2(fd, STDOUT_FILENO) < 0)
                    {
                        perror("Unable to duplicate file descriptor.");
                        return NULL;
                    }
                    store[i+1][0] = '\0';
                }
            }
        }
        strcpy(modified,"");
        for(int i = 0; i < j;i++)
        {
            strcat(modified, store[i]);
            strcat(modified, " ");
        }

        return modified;
    }
    return copy;
}