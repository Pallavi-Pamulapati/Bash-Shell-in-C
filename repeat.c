#include "headers.h"

void repeat(char* Prev_dir,char* ROOT,const char* input)
{
    char Store[100][1000];
    int j = 0;
    char* delimt = " \t";
    int t = 0;
    char* token = strtok(NULL,delimt);
    t = atoi(token);
    token = strtok(NULL,delimt);
    while(token != NULL)
    {
        strcpy(Store[j],token);
        j++;
        token = strtok(NULL,delimt);
    }
    char* copy = (char*)malloc(10000*sizeof(char));
    char* copy1 = (char*)malloc(10000*sizeof(char));

    strcpy(copy,"");
    for(int i = 0;i < j;i++)
    {
        strcat(copy,Store[i]);
        strcat(copy," ");
    }
    char* final;
    for(int i = 0;i < t;i++)
    {
        strcpy(copy1,copy);
        final = strtok(copy1,delimt);

        while(final != NULL)
        {
            if(!strcmp(final,"cd"))
                cd(Prev_dir,ROOT);
            else if(!strcmp(final,"ls"))
                ls(final,ROOT);
            else if(!strcmp(final,"echo"))
                echo(final);
            else if(!strcmp(final,"pwd"))
                getpwd();
            else if(!strcmp(final,"jobs"))
                jobs(final);
            else if(!strcmp(final, "pinfo"))
                pinfo(final,ROOT);
            else if(!strcmp(final,"replay"))
                replay_command(final,ROOT,Prev_dir);
            else if(!strcmp(final,"fg"))
                jobs_fg(final);
            else if(!strcmp(final,"bg"))
                jobs_bg(final);
            else if(!strcmp(final,"sig"))
                jobs_sig(final);
            else 
            EXECVP(final,1);
            final = strtok(NULL,delimt);
        }
    }
    

    return ;
}