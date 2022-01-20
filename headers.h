#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers.h"
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <assert.h>
#include <fcntl.h>

typedef struct node{
    int pid;
    char* p_name;
    int job_no;
    struct node* next; 
}node;

typedef node* Node;

extern Node Header;
extern int job;

int retu;

// function prototypes of LinkedList
Node CreateNode(int pid, char* name, int job_id);
char* FindNode(int pid);
void InsertNode(int pid, char* name, int job_id);
void DeleteNode(int pid);
void PrintList(int flag);

int prompt(char* dir_name);
int getinput(char** input);
void cd( char *path,char* Prev_dir);
int getpwd();
void echo(char* input);
void ls(char* input,char* Root);
void repeat(char* input,char* Prev_dir,const char* ROOT);
void EXECVP(char* input,int number);
void pinfo(char* input,char* ROOT);
void handle(int A);
void jobs(char* input);
char* Redirection(char* command);
int piped(char* command, char* direc);
void CtrlC_Handler(int A);
int replay_command(char* input,char* direc,char* prev_dir);
void CtrlZ_Handler(int A);
void jobs_fg(char* input);
int FindPID(int job_no);
void jobs_sig(char* input);
void jobs_bg(char *input);


#endif