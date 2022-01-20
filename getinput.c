#include "headers.h"

int getinput(char** input)
{
    
    size_t length = 0;

    int check = getline(input,&length,stdin);
    if(check == EOF)
    {
        return 1;
    }
    
    if(check < 0)
    {
        printf("Error while reading input\n");
        return 1;
    }
    if(strcmp(*input,"exit\n") == 0)
    {
        return 1;
    }
    (*input)[check - 1] = '\0';
    return 0;
}