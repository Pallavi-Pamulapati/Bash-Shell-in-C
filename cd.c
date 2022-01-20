#include "headers.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cd(char* Prev_dir,char* root)
{
    int k = 0;
    char* direc = (char*)malloc(10000*sizeof(char));
    getcwd(direc,10000);
    int check;
    char* path;
    char* Path;
    char* delimit = " \t";
    char* copy = (char*)malloc(10000*sizeof(char));
    char* space = strtok(NULL, delimit);
    int flag = 0;
 
    if(space == NULL)
    {
        strcpy(copy,root);
        k = 1;
    }
    else
    {
        path = space;
        if(strcmp(path,"~") == 0 || space == NULL)
            path = root;
        else if(path[0] == '~' && path[1] == '/')
        {
            strcpy(copy,root);
            strcat(copy,&path[1]);
            k = 1;
        }
        else if(strcmp(path,"-") == 0)
        {
            flag = 1;   
        }   
        space = strtok(NULL, delimit);
    }
    if(space == NULL)
    {
        if(k == 0)
        Path = path;
        else 
        Path = copy;
    }
    else 
    {
        printf("To many arguments for cd command\n");
            return;
    }
    
    if(flag == 0)
    check = chdir(Path);
    else 
    {
        printf("%s\n",Prev_dir);
        check = chdir(Prev_dir);
    }
    if(check != 0)
    {
        perror("Error while Changing directory");
    }
    else 
    {
        if(strcmp(Path,direc) != 0)
        strcpy(Prev_dir,direc);
    }

    free(direc);
    free(copy);
    return;
}