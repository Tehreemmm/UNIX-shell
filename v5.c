#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "expected argument to \"cd\"\n");
        } else {
            chdir(args[1]);
        }
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else {
        printf("Available commands:\n cd [dir], exit, jobs, kill [pid], help\n");
    }
}

int main() {
    // Example usage of execute_builtin
    char *args[] = {"cd", "/tmp", NULL};  // Example command
    execute_builtin(args);

    return 0;
}
