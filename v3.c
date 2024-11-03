#include <stdio.h>       // For printf()
#include <stdlib.h>      // For exit(), EXIT_FAILURE
#include <string.h>      // For strcmp()
#include <unistd.h>      // For fork(), execvp(), pid_t
#include <sys/types.h>   // For pid_t
#include <sys/wait.h>    // For waitpid()

void execute(char **args) {
    int background = 0;

    // Check if the command should run in the background
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;
            args[i] = NULL;  // Remove '&' from arguments
            break;
        }
    }

    pid_t pid = fork();
    if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
    } else { // Parent process
        if (!background) {
            waitpid(pid, NULL, 0);  // Wait for the child if not background
        } else {
            printf("[Background] PID: %d\n", pid);  // Background process info
        }
    }
}

int main() {
    // Sample usage: this code will need to be expanded to handle user input
    char *args[] = {"sleep", "10", "&", NULL}; // Test command running in background
    execute(args);

    return 0;
}
