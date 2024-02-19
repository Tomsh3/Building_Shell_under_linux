# Building_Shell_under_linux
In this project we had guidelines for building a shell under Linux, 
focusing on fundamental principles and the general idea of creating a functional command-line interface. 
Here are the key points:

* The shell operates in an infinite loop, displaying a prompt and accepting user commands.
* Internal commands like exit, cd, and jobs are implemented within the shell, while external commands are executed using exec system calls.
* Error handling is emphasized, with specific messages for invalid commands, system call failures, and background command limits.
* Background commands are supported, with a maximum of 4 running simultaneously alongside a possible foreground command.
* Child processes are managed using fork, exec, and waitpid system calls to handle background and foreground commands effectively.
* The shell reaps finished background commands to prevent zombie processes and displays relevant messages.
* Special functionalities include changing the working directory with the cd command, listing background processes with jobs, and supporting background and foreground commands.


By following these principles and guidelines, you can create a robust shell program that efficiently executes user commands, handles background processes, and provides a user-friendly command-line interface in a Linux environment.
This is a nice projects that demonstrates one of the basic principles of operating systems.