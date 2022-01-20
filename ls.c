#include "headers.h"

void Permissions(struct stat* STAT)
{
    char* Ptr = NULL;
    if (S_ISDIR(STAT->st_mode))
        printf("d");
    else
        printf("-");

    if (STAT->st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (STAT->st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (STAT->st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    if (STAT->st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (STAT->st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");

    if (STAT->st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (STAT->st_mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if (STAT->st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (STAT->st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    char scam[100];
    time_t ti = STAT->st_mtime;
    struct tm* tmp;
    tmp = localtime(&ti);
    strftime(scam,sizeof(scam), "%b %d %H:%M", tmp);
    printf(" %4ld %s  %s %5ld  %s ",STAT->st_nlink,getpwuid(STAT->st_uid)->pw_name,getgrgid(STAT->st_gid)->gr_name,STAT->st_size, scam);

    return;
}

void lsl(char* dir_file,int count_a, int number)
{
    struct dirent *Directory_Ptr;
    DIR *Directory;
    Directory = opendir(dir_file);
    if(Directory != NULL)
    {
        if(number > 1)
        printf("%s:\n",dir_file);
        char totalpath[10000];
        long long int toatl = 0;
        while ((Directory_Ptr = readdir(Directory)) != NULL)
        {
            strcpy(totalpath,dir_file);
            strcat(totalpath,"/");
            strcat(totalpath,Directory_Ptr->d_name);
            struct stat STAT = {0};
            if(!stat(totalpath,&STAT))
            {
                if(count_a != 0)
                toatl += STAT.st_blocks;
                else 
                {
                    if(Directory_Ptr->d_name[0] != '.')
                    {
                        toatl += STAT.st_blocks;
                    }
                }
            }
        }
        printf("total %lld\n",toatl/2);
        rewinddir(Directory);

        while((Directory_Ptr = readdir(Directory)) != NULL)
        {
            strcpy(totalpath,dir_file);
            strcat(totalpath,"/");
            strcat(totalpath,Directory_Ptr->d_name);
            struct stat STAT = {0};
            if(!stat(totalpath,&STAT))
            {
                if(count_a != 0)
                {
                    Permissions(&STAT);
                    printf("%s\n",Directory_Ptr->d_name);
                }
                else 
                {
                    if(Directory_Ptr->d_name[0] != '.')
                    {
                        Permissions(&STAT);
                        printf("%s\n",Directory_Ptr->d_name);
                    }
                }
            }
        }
    }
    else
    {
        struct stat STAT = {0};
        if(stat(dir_file,&STAT) == 0)
        {
            Permissions(&STAT);
            printf("%s\n",dir_file);
        }
        else 
        perror("Invalid file or directory");
    }
    return ;
}

void LS(char* dir_file,int count_a,int number)
{
    struct dirent *Directory_Ptr;
    DIR *Directory;
    Directory = opendir(dir_file);

    if(Directory != NULL)
    {
        if(number > 1)
        printf("%s:\n",dir_file);
        while((Directory_Ptr = readdir(Directory)) != NULL)
        {
            if(count_a == 0)
            {
                if(Directory_Ptr->d_name[0] != '.')
                printf("%s\n",Directory_Ptr->d_name);
            }
            else 
            printf("%s\n",Directory_Ptr->d_name);
        }
        closedir(Directory);
    }
    else 
    {
        struct stat STAT = {0};
        if(stat(dir_file,&STAT) == 0)
        {
            printf("%s\n",dir_file);
        }
        else 
        perror("Invalid file or directory");
    }
}

void ls(char* path, char* ROOT)
{
    char *present = (char *)malloc(10000 * sizeof(char));
    getcwd(present, 10000);

    char **store = (char **)malloc(10000 * sizeof(char *));
    char *delimt = " \t";
    char *token = strtok(NULL, delimt);
    int count_l = 0, count_a = 0, j = 0;

    while (token != NULL)
    {
        if (strcmp(token, "-l") == 0)
            count_l++;
        else if (strcmp(token, "-a") == 0)
            count_a++;
        else if(strcmp(token,"-al")== 0 || strcmp(token,"-la") == 0)
        {
            count_l++;
            count_a++;
        }
        else
        {
            store[j] = token;
            j++;
        }
        token = strtok(NULL, delimt);
    }

    if(count_l)
    {
        if (j == 0)
            lsl(present, count_a, j);
        for(int i = 0;i < j;i++)
        {
            if (strcmp(store[i], ".") == 0)
                lsl(present, count_a, j);
            else if (strcmp(store[i], "~") == 0)
                lsl(ROOT, count_a, j);
            else 
            lsl(store[i],count_a,j);

            if(j > 1 && i != j-1)
            printf("\n");
        }   
    }
    else 
    {
        if(j == 0)
            LS(present,count_a,j);
        for(int i = 0;i < j;i++)
        {
            if(strcmp(store[i],".") == 0)
                LS(present,count_a,j);
            else if(strcmp(store[i],"~") == 0)
                LS(ROOT,count_a,j);
            else 
                LS(store[i],count_a,j);
            
            if(j > 1 && i != j-1)
            printf("\n");
        }
    }
    return;
}