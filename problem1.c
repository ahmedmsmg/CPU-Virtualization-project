/// Ahmed Ghoneim...

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argument_count, char *argument_vector[]) {
    // If there are no arguments (apart from the program name), exit
    if (argument_count <= 1) {
        printf("No command provided.\n");
        exit(0);
    }

    // Command will point to the first argument, parameters array will hold all arguments including the command
    char *command = argument_vector[1];
    char *parameters[argument_count + 1]; // Extra space for NULL terminator

    // Copy argument_vector contents to parameters, starting with command
    for(int index = 1; index < argument_count; index++)
        parameters[index-1] = argument_vector[index];

    // End the parameters array with NULL as required by execvp
    parameters[argument_count-1] = NULL;

    // Fork a new process
    int newProcess = fork();

    if (newProcess == 0) {
        // Child process
        execvp(command, parameters); // Execute the command
    } else if (newProcess > 0) {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("++++\n");
    } else {
        // Fork failed
        printf("Fork failed.\n");
        exit(1);
    }

    return 0;
}
