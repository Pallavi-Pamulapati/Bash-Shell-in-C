#include "headers.h"

void jobs(char* inpu)
{
    int rcount = 0,scount = 0; 
    char* delimit = " \t\n";
    char* token = strtok(NULL, delimit);
    while(token != NULL)
    {
        if(strcmp(token, "-r") == 0)
            rcount++;
        else if(strcmp(token,"-s") == 0)
            scount++;
        else 
        {
            printf("Invaild Flag %s\n", token);
            return;
        }

        token = strtok(NULL,delimit);
    }

    if((rcount == 0 && scount == 0) || (rcount != 0 && scount != 0))
        PrintList(0);
    else if(scount == 0 && rcount != 0)
        PrintList(1);
    else if(scount != 0 && rcount == 0)
        PrintList(2);

    return;
}