#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void redirect_io(char **args) {
    int in = -1, out = -1;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            in = open(args[i + 1], O_RDONLY);
            dup2(in, STDIN_FILENO);
            args[i] = NULL;  // Truncate command
        } else if (strcmp(args[i], ">") == 0) {
            out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(out, STDOUT_FILENO);
            args[i] = NULL;  // Truncate command
        }
    }
}

void execute(char **args) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        redirect_io(args);
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        wait(NULL);
    }
}

int main() {
    // Sample command with arguments to test the shell
    char *args[] = {"ls", "-l", ">", "output.txt", NULL};

    // Call the execute function with the test command
    execute(args);

    return 0;
}
