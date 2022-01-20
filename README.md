# How to run the shell
- cd into the directory in which shell is present
- run make command
- run ./a.out
- enter `exit` or `Ctrl + D` to exit from the shell

# Features Implemented.
- Shell prompt is similar to the bash shell 
- `echo` is implemented for single commands with out involving environmental variables
- basic functionalities of `cd` are implemented along with ".","..","-","~",
- `pwd` - displays the path from root directory
- `ls` command with flags `-a,-l,-al,-la` and it can print details of multiple files or directories given as input
- `pinfo` command that displays the info of the process whose process id is given as input
- `repeat` executes the command given as argument the specified number of times.
- `fg` - brings the given background job corresponding to job number to foreground and changes state to running.
- `bg` - changes the state of stopped bacground job to running in background.
- `jobs` command that displays currently running background processes and flags `-r`, `-s` are also implemented
- `sig` command that takes a job number of a running job and sends signal to corresponding to signal number to that process.
- `replay` executes the given command in the given interval of time for a certain period.
- `I/O Redriection` and `Command Pipelines` are implemented.
- `CTRL - Z`, `CTRL - C` and `CTRL - D` signals are handeled.
- Other Systems commands can be executed as background and foreground based on whether "&" given as the input or not respectively

# Assumptions Made

- Name of the background process can't be more than 1000 bytes.
- Name of the directory can't be more than 10000 bytes.
- Absolute path of a directory can't be more than 10000 bytes.
- And maximum no.of arguments can't be more than 10000.
- name of Commands seperated by "|" pipe can't be more than 1000 bytes.
- Name of command given in replay can't be more than 10000 bytes.
- Redirection cannot be performed on multiple files.

# Overview of files

- headers.h
    - contains the protypes of the functions used, headers required and the structs defined
- pwd.c
    - contains getpwd() function that prints the working directory
- ls.c
    - contains lsl() funtion that prints all the information about files and directories. if -a flag is given it also prints the hidden files
    - contains ls() function that counts the no.of -l and -a flags given and stores path of the directory or file given
    - contains LS() funtion that the prints directory and file names in the given directory
    - contains Permissions() function that prints all the permissions of a file or directory
- cd.c
    - contains cd() function that changes the directory according to the arguments provided
- echo.c
    - contains echo() function that prints the string given as argument without extra spaces and tabs.
- execvp.c
    - forks the running process and a child process in foreground if "&" is not given as input that is,the parent process resumes only after the child terminates.
    - if the "&" is not given as input then it runs the child process in background that is, the parent process continues to run simultaneously with the child.
- getinput.c 
    - reads the input and terminates the shell if there is an error in reading the input or if `exit` command is given. In this `Ctrl + D` is handeled.
- repeat.c
    - contains repeat command that repeats the command given as argument multiple times as specified.
- hash.c 
    - contains the functions like insert_sp() that iserts a node(that contains name and process id of a background process) into hash table using seperate chaining, find_sp() that returns the name of the background process whose pid is given as input, gethash() that returns the key for hashing, create_hash_sp() that creates the hash table, Makenode() function that creates the node to insert in the hash table.
- pinfo.c
    - contains pinfo() function that prints the process info (pid, status, virtual memory, executable path) of the given process id as argument.
- prompt.c
    - contains the prompt function that prints `<username@system_name:current_directory>`.
- SignalHandle.c
    - contains handle function that prints whether the background process exited normally or abnormally.
    - contains Handle funtions of `Ctrl+C` and `Ctrl+Z`.
- IORedirection.c
    - Contains redirection() function that is used to implement redirect functionality in the commands.
- jobs_subparts.c
    - Contains function jobs_fg() that implements the `fg` command i.e, brings background job corresponding to given job number to background.
    - contains function jobs_bg() that implements the `bg` command i.e, changes the state of stopped bacground job to running in background.
    - contains function jobs_sig() that implements the `sig` command that takes a job number of a running job and sends signal to corresponding to signal number to that process.
- jobs.c
    - contains jobs() funtion that counts the no.of `-r` and `-s` and prints the jobs using Printlist() funtion.
- linkedlist.c
    - Contains functions that deals with liked list
        - CreateNode() - creates a node to insert in the linked list
        - FindNode() - searches for a node with given pid and returns the corresponding process name.
        - FindPID() - searches for a node with given job number and returns the orresponding process ID.
        - InsertNode() - Inserts a node in the linked list in alphabetically sorted order with respect to process name.
        - DeleteNode() - Deletes a node with given pid from the list
        - PrintList() - Prints the nodes in the list and also prints the status of the process (Stopped / Running)
- pipes.c
    - Contains piped() function that implements pipe functionality in the commands. It tokenizes the given input considering "|" as a delimiter. Then each command runs sequentially such that output of one command becomes input for the following command if any. And this is done by forking.
- replay.c
    - Contains replay_command() function in which the replay command is implemented using sleep() function.