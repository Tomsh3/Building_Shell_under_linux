#include "hw1shell.h"

// Function to wait and reap child processes:
void wait_and_reap(struct BackgroundCommand bgCommands[], int *bgCommandCount) {
            for (int i = 0; i<=*bgCommandCount; i++)
            {
                pid_t pidBuffer = 0;
                while (pidBuffer <= 0) // Wait for the current process to end
                    pidBuffer = waitpid(bgCommands[i].pid, NULL, WNOHANG);
                if (pidBuffer != -1 && pidBuffer != 0) // Process ended - reap it
                {
                    printf("hw1shell: pid %d finished\n", bgCommands[i].pid);
                    for (int j = i; j < *bgCommandCount - 1; j++) {
                        bgCommands[j] = bgCommands[j + 1];
                    }
                    (*bgCommandCount)--;
                }
            }
       // }
    
}

// Function to execute external commands
pid_t executeExternalCommand(char* args[], int isBackground, int* bgCommandCount, struct BackgroundCommand bgCommands[]) {
    pid_t pid; // TODO

    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) { // Ececute new proccesz if failed returns "-1"z else "0"
            fprintf(stderr, "hw1shell: invalid command\n");
            exit(EXIT_FAILURE); // TODO change all EXIT with CONTINUE and change the error massage content - section 11 from the assigment sheet
        }
    }
    else if (pid < 0) {
        fprintf(stderr, "hw1shell: fork failed, errno is %d\n", errno);
    }
    else {
        // Parent process
        if (!isBackground) {
            // Wait for foreground process
            waitpid(pid, NULL, 0);
        }
        else {
            // Display background command information
            printf("hw1shell: pid %d started\n", pid); // TODO check if we need to execute the procces or only show it visually
        }
    }
    return pid;
}

// Function to handle internal commands
void handleInternalCommand(char* args[], struct BackgroundCommand bgCommands[], int* bgCommandCount, int argCount) {
    if (strcmp(args[0], "exit") == 0) {
        // Terminate and exit
        if (*bgCommandCount != 0) {
        wait_and_reap(bgCommands, bgCommandCount);
        }
        exit(EXIT_SUCCESS);
    }
    
    else if (strcmp(args[0], "cd") == 0) {
        // Change directory
        if (args[1] == NULL) { // Empty directory input
            fprintf(stderr, "hw1shell: cd: missing argument\n");
        }
        else { 
            if (chdir(args[1]) != 0) { // chdir actually change the path and return '0' if succes, '-1' otherwise
                fprintf(stderr, "hw1shell: invalid command\n");
            }
        }
    }
    else if (strcmp(args[0], "jobs") == 0) {
        // Display background commands
        for (int i = 0; i < *bgCommandCount; i++) {
            printf("%d\t%s\n", bgCommands[i].pid, bgCommands[i].command);
        }
    }
    else {
        // Execute external command
        int isBackground = 0;
        pid_t pidAssist;
        if (args[argCount - 1] != NULL && strcmp(args[argCount - 1], "&") == 0) { // Check if the user requested background command
            isBackground = 1;
            args[argCount - 1] = NULL; // Remove the "&" from arguments
        }

        if (*bgCommandCount >= MAX_BG_COMMANDS && isBackground) {
            fprintf(stderr, "hw1shell: too many background commands running\n");
        }
        else {
            // Execute command
            pidAssist = executeExternalCommand(args, isBackground, bgCommandCount, bgCommands);

            // Store background command information
            if (isBackground && pidAssist>0) {
                bgCommands[*bgCommandCount].pid = pidAssist;
                strcpy(bgCommands[*bgCommandCount].command, args[0]);
                (*bgCommandCount)++;
            }
        }
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char* args[MAX_ARG_SIZE];
    int argCount;
    struct BackgroundCommand bgCommands[MAX_BG_COMMANDS];
    int bgCommandCount = 0;

    while (1) {
        printf("hw1shell$ ");
        fflush(stdout); // Clear input buffer 

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "hw1shell: fgets failed, errno is %d\n", errno);
            exit(EXIT_FAILURE);
        }

        // Tokenize input   test to the input word
        argCount = 0;
        args[argCount] = strtok(input, " \t\n"); // Breaks input wherever " ", tab or new line is written
        while (args[argCount] != NULL) { // Continue breaking the line until the end of it
            argCount++;
            args[argCount] = strtok(NULL, " \t\n");
        }

        // No command provided
        if (argCount == 0) {
            continue;
        }

        // Handle internal and external commands
        handleInternalCommand(args, bgCommands, &bgCommandCount, argCount);
        pid_t pidBuffer;
        for (int i = 0; i <= 4; i++)
        {
            pidBuffer = waitpid(bgCommands[i].pid, NULL, WNOHANG);
            if (pidBuffer != -1 && pidBuffer != 0)
            {
                printf("hw1shell: pid %d finished\n", bgCommands[i].pid);
                for (int j = i; j < bgCommandCount - 1; j++) {
                    bgCommands[j] = bgCommands[j + 1];
                }
                bgCommandCount--;
                i--;
            }
        }
    }

    return 0;
}
