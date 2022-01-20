#include "headers.h"

Node Header;

Node CreateNode(int pid, char* name, int job_id)
{
    Node ptr = (Node)malloc(sizeof(node));
    ptr->p_name = (char*)malloc(1000*sizeof(char));
    ptr->p_name[0] =  '\0';   
    strcpy(ptr->p_name,name);
    ptr->pid = pid;
    ptr->job_no = job_id;
    ptr->next = NULL;

    return ptr;
}

char* FindNode(int pid)
{
    Node temp = Header;
    
    while(temp != NULL)
    {
        if(temp->pid == pid)
            return temp->p_name;
        
        temp = temp->next;
    }

    return NULL;
}

int FindPID(int job_no)
{
    Node temp = Header;

    while(temp != NULL)
    {
        if(temp->job_no == job_no)
            return temp->pid;
        
        temp = temp->next;
    }

    return 0;
}

void InsertNode(int pid, char* name, int job_id)
{
    Node head = Header;
    Node ptr = CreateNode(pid,name,job_id);

    while(head->next != NULL && (strcmp(name, head->next->p_name) >= 0))
        head = head->next;
    
    ptr->next = head->next;
    head->next = ptr;

    return;
}

void DeleteNode(int pid)
{
    Node prev = Header;
    Node del = prev->next;
    while(prev != NULL)
    {
        del = prev->next;
        if(prev->next != NULL && prev->next->pid == pid)
        {
            prev->next = prev->next->next;
            free(del->p_name);
            free(del);
        }

        prev = prev->next;
    }
    return;
}
// 0 = all, 1 = running, 2 = sleeping
void PrintList(int flag)
{
    Node head = Header;
    char* delimit = " \t\n";

    while(head->next != NULL)
    {
        char path[1000] = "";
        char path_p[10] = "";
        sprintf(path_p,"%d",head->next->pid);
        strcpy(path,"/proc/");
        strcat(path,path_p);
        strcat(path,"/stat");
        FILE* FID  = fopen(path,"r");
        if(FID == NULL)
        {
            perror("Error while open file to know status");
            return;
        }
        int count = 0;
        char line[10000];
        fgets(line,10000,FID);
        char status[2] = "";
        char* part = strtok(line,delimit);
        count ++;

        while(part != NULL)
        {
            part = strtok(NULL,delimit);
            if(count == 2)
            {
                strcpy(status,part);
                break;
            }
            count++;
        }

        if(flag == 0)
        {
            printf("[%d] ",head->next->job_no);
            if(strcmp(status, "S") == 0 || (strcmp(status,"R") == 0) || (strcmp(status, "D") == 0))
                printf("Running ");
            else
                printf("Stopped ");

            printf("%s [%d]\n",head->next->p_name, head->next->pid);
        }
        else if(flag == 1 && (strcmp(status,"R") == 0 || (strcmp(status,"S") == 0) || (strcmp(status, "D") == 0)))
            printf("[%d] Running %s [%d]\n", head->next->job_no, head->next->p_name, head->next->pid);
        else if(flag == 2 && !((strcmp(status,"R") == 0 || (strcmp(status,"S") == 0) || (strcmp(status, "D") == 0))))
            printf("[%d] Stopped %s [%d]\n", head->next->job_no, head->next->p_name, head->next->pid);
        head = head->next;
    }


    return;
}