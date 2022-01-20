#include "headers.h"

void EXECVP(char* input,int number)
{
    char* delimt = " \t";
    char** store = (char**)malloc(10000*sizeof(char*)); 
    char* command = (char*)malloc(10000*(sizeof(char)));
    int j = 0;
    store[j] = input;
    j++;
    while(store[j-1] != NULL)
    {
        store[j] = strtok(NULL,delimt);
        j++;
    }
    retu = fork();
    if(retu == 0)
    {
        setpgid(0,0);
        if(strcmp(store[j-2], "&") == 0)
        store[j-2] = NULL;
        int x = execvp(store[0],store);
        if(x == -1)
            printf("Invalid Command\n");
        exit(1);
    }
    else
    {
        strcpy(command,"");
        for(int i = 0;i <= j-2; i++)
        {
            strcat(command, store[i]);
            if(i!= j-2)
            strcat(command, " ");
        }

        if(strcmp(store[j-2],"&") != 0)
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            int status;
            tcsetpgrp(0,retu);
            waitpid(retu,&status,WUNTRACED);
            if(WIFSTOPPED(status))
            {
                job++;
                InsertNode(retu, command, job);
                kill(retu,SIGSTOP);
            }
            retu = -1;
            tcsetpgrp(0,getpid());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
        else
        {
            job++;
            char Process_Name[1000] = {0};
            for(int i = 0;i < j-2; i++)
            {
                strcat(Process_Name,store[i]);
                strcat(Process_Name," ");                    
            }
            InsertNode(retu,Process_Name,job);
            if(number == 0)
                printf("%d\n",retu);
        }
    }
    free(store);
    free(command);
    return;
}