#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers.h"
 
void echo(char* input)
{
    char* delimt = " \t";
    char * token = strtok(NULL,delimt);
    while(token != NULL)
    {
        printf("%s ",token);
        token = strtok(NULL,delimt);
    }
    printf("\n");

    return;
}