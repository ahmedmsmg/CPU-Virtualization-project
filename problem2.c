/// Ahmed Ghoneim...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argCount, char *argList[]) {
    // Initialize child processes
    int firstChildProcess, secondChildProcess;
    // Save command1 and command2
    char *command1 = argList[1], *command2 = argList[3];
    // Create pipe
    int pipeFileDescriptors[2];
    if (pipe(pipeFileDescriptors) == -1)
        return 0;
    // Start first child
    firstChildProcess = fork();
    if (firstChildProcess == 0) {
        close(pipeFileDescriptors[0]);
        dup2(pipeFileDescriptors[1], STDOUT_FILENO);
        execlp(command1, command1, (char *)NULL);
    }
    // Start second child
    secondChildProcess = fork();
    if (secondChildProcess == 0) {
        close(pipeFileDescriptors[1]);
        dup2(pipeFileDescriptors[0], STDIN_FILENO);
        execlp(command2, command2, (char *)NULL);
    } 

    // Close the pipe
    close(pipeFileDescriptors[0]);
    close(pipeFileDescriptors[1]);

    // Parent process should wait for both child processes to finish
    waitpid(firstChildProcess, NULL, 0);
    waitpid(secondChildProcess, NULL, 0);

    printf("++++\n");

    return 0;
}
