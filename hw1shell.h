#ifndef HW1SHELL_H
#define HW1SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64
#define MAX_BG_COMMANDS 4

// Structure to store background commands
struct BackgroundCommand {
    pid_t pid; // Adds an ID to the procces automaticly TODO manually
    char command[MAX_INPUT_SIZE];
};
 
 // Function to wait and reap child processes:
void wait_and_reap(struct BackgroundCommand bgCommands[], int *bgCommandCount) ;

// Function to execute external commands
pid_t executeExternalCommand(char* args[], int isBackground, int* bgCommandCount, struct BackgroundCommand bgCommands[]);

// Function to handle internal commands
void handleInternalCommand(char* args[], struct BackgroundCommand bgCommands[], int* bgCommandCount, int argCount);

#endif