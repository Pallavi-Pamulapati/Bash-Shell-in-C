#include "headers.h"

int prompt(char* dir_name)
{
    char* path = (char*)malloc(10000*sizeof(char));
    char* username = (char*)malloc(1000*sizeof(char));
    int check = getlogin_r(username,1000);
    if(check != 0)
    {
        printf("Error while getting the username\n");
        return 1;
    }
    
    char* hostname = (char*)malloc(1000*sizeof(char));
    check = gethostname(hostname,1000);
    if(check != 0)
    {
        printf("Error while getting the hostname\n");
        return 1;
    }
    printf("<%s@%s:",username,hostname);
    getcwd(path,10000);
    // printf("\x1b[32m<%s@%s\x1b[0m:\x1b[34m> \x1b[0m", username, hostname);
    int N = strlen(dir_name),M = strlen(path);
    if(N > M)
    {
        printf("%s",path);
    }
    else 
    {
        char* Some_part = (char*)malloc((N+1)*sizeof(char));
        strncpy(Some_part,path,N);
        Some_part[N] = '\0';
        if(N == M && strcmp(Some_part,dir_name) == 0)
            printf("~");
        else if(strcmp(Some_part,dir_name) == 0 && path[N] == '/')
        {
            printf("~");
            for(int i = N;i < M;i++)
            printf("%c",path[i]);
        }
        else 
        printf("%s",path);
    }
    printf(">");
    free(username);
    free(hostname);
    free(path);

    return 0;
}