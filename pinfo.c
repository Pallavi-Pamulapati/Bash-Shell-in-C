#include "headers.h"

void pinfo(char* input,char* ROOT)
{
    pid_t PID;
    char* delimt = " \t\n";
    char * part = strtok(NULL,delimt);
    char path_p[100];

    if(part == NULL)
    {
        PID = getpid();
        sprintf(path_p,"%d",PID);
    }
    int j = 0;
    while(part != NULL)
    {
        if(j > 1)
        {
            printf("Too many arguments for pinfo");
            return;
        }
        PID = atoi(part);
        strcpy(path_p,part);
        part = strtok(NULL,delimt);
        j++;
    }

    char* path = (char*)malloc(1000*sizeof(char));
    strcpy(path,"/proc/");
    strcat(path,path_p);
    strcat(path,"/stat");

    FILE* FID  = fopen(path,"r");
    if(FID == NULL)
    {
        perror("Error while open file");
        return;
    }
    int count = 0;
    char line[10000];
    char* TGID = (char*)malloc(sizeof(char)*100);
    char* PPID = (char*)malloc(sizeof(char)*100);
    fgets(line,10000,FID);
    part = strtok(line,delimt);
    count ++;
    while (part != NULL)
    {
        part = strtok(NULL,delimt);
        if(count == 2)
        {
            printf("pid -- %d\n",PID);
            printf("Process Status -- {%s",part);
        }
        else if(count == 4)
        {
            strcpy(TGID,part);
        }
        else if(count == 7)
        {
            strcpy(PPID,part);
        }
        else if(count == 22)
        {
            if(strcmp(TGID,PPID) == 0)
                printf("+}\n");
            else
            printf("}\n");
            printf("memory -- ");
                printf("%s ",part);
            printf("{Virtual Memory}\n");
        }
        count++;
    }
    strcpy(path,"/proc/");
    strcat(path,path_p);
    strcat(path,"/exe");
    strcpy(line,"");
    int retu = readlink(path,line,10000);
    if(retu == -1)
    {
        printf("Error while accessing /proc/%d/exe\n",PID);
        return;
    }
    line[retu] = '\0';
    int N,M;
    N = strlen(ROOT);
    M = strlen(line);
    if(N > M)
    printf("Executable Path -- %s\n",line);
    else 
    {
        printf("Executable Path -- ");
        char* Some_part = (char*)malloc((N+1)*sizeof(char));
        strncpy(Some_part,line,N);
        Some_part[N] = '\0';
        if(N == M && strcmp(Some_part,ROOT) == 0)
            printf("~");
        else if(strcmp(Some_part,ROOT) == 0 && line[N] == '/')
        {
            printf("~");
            for(int i = N;i < M;i++)
            printf("%c",line[i]);
        }
        else 
        printf("%s",line);
        printf("\n");
    }

    return;
}