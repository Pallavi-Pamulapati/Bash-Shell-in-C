#include "headers.h"

int getpwd()
{
    int error = 0;
    char* Path = (char*)malloc(10000*sizeof(char));
    if(getcwd(Path,10000) == NULL)
    {
        perror("Error while Getting the current directory name");
        error = -1;
    }
    else 
    printf("%s\n",Path);
    free(Path);
    return error;
}