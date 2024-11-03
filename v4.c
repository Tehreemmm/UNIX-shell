#define _POSIX_C_SOURCE 200809L  // Ensures POSIX functions like strdup are available

#include <stdio.h>      // For printf()
#include <stdlib.h>     // For malloc(), free()
#include <string.h>     // For strdup(), strlen()

#define MAX_HISTORY 10  // Maximum number of commands in history

// Assume history is an array of char arrays storing the last MAX_HISTORY commands
char *history[MAX_HISTORY];
int history_count = 0;

void add_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        // Duplicate the command and check for NULL
        char *cmd_copy = strdup(command);
        if (cmd_copy != NULL) {
            history[history_count++] = cmd_copy;
        } else {
            fprintf(stderr, "Error: Unable to allocate memory for command.\n");
        }
    } else {
        // Free the oldest command and shift the history
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        // Duplicate the new command
        char *cmd_copy = strdup(command);
        if (cmd_copy != NULL) {
            history[MAX_HISTORY - 1] = cmd_copy;
        } else {
            fprintf(stderr, "Error: Unable to allocate memory for command.\n");
        }
    }
}

void show_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}

int main() {
    // Sample commands to test the history functions
    add_to_history("ls -l");
    add_to_history("pwd");
    add_to_history("echo Hello World");

    printf("Command History:\n");
    show_history();

    // Free allocated memory
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }

    return 0;
}
