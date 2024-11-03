#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define DELIMITERS " \t\r\n\a"

void shell_prompt() {
    printf("PUCITshell:- ");
}

char **parse_input(char *input) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, DELIMITERS);
    while (token != NULL) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

void execute(char **args) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
    } else { // Parent process
        wait(NULL);
    }
}

int main() {
    char *input;
    char **args;
    size_t bufsize = 0;

    while (1) {
        shell_prompt();
        if (getline(&input, &bufsize, stdin) == -1) { // EOF or error
            printf("\n");
            break;
        }

        args = parse_input(input);
        if (args[0] != NULL) {
            execute(args);
        }

        free(args);
    }

    free(input);
    return 0;
}
