/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.3
 * Programul de mai jos implementeaza un shell simplu care primeste un username si o parola,
 * si executa comenzi shell, sau mai multe despartite de un delimiter, in cazul acesta ";".
 */
#include <stdio.h>   // Standard I/O library for functions like printf and fprintf.
#include <stdlib.h>  // Standard library for functions like exit and atoi.
#include <string.h>  // String handling functions, such as strcmp.
#include <sys/wait.h> // Wait functions for process synchronization (wait).
#include <unistd.h>  // POSIX operating system API, for functions like fork, getpid, and getppid.
#include <stdbool.h> // Boolean type and values
#include <ctype.h>    // Character type functions, such as isspace


// Function to execute a single command in a child process.
int execute_command(const char *command) {
    // Create a new process.
    pid_t pid = fork();

    if (pid == -1) {
        // If fork fails, output an error message and exit.
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // In the parent process, wait for the child to complete.
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to complete.
        // Check and print the exit status of the child process.
        if(WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else if(WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        }
        // Return the status of the child process.
        return status;
    } else {
        // In the child process, execute the command using exec.
        execlp("sh", "sh", "-c", command, (char *)NULL);
        // If exec fails, output an error message and exit.
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
}

// Function to execute multiple commands separated by semicolons.
void adapted_system(const char *commands) {
    // Duplicate the commands string, as strtok modifies the original.
    char *commands_copy = strdup(commands);
    // Split the commands string into individual commands.
    char *command = strtok(commands_copy, ";");

    while (command) {
        // Skip any leading whitespace before the command.
        while(isspace(*command)) command++;
        // Execute the individual command.
        execute_command(command);
        // Move to the next command in the string.
        command = strtok(NULL, ";");
    }

    // Free the duplicated string after use.
    free(commands_copy);
}

// Function to validate user login credentials.
bool login(const char *username, const char *password) {
    // Implementation is assumed to be the same as the one provided by the user.
}

// Function that provides the main shell interface for command input and execution.
void shell() {
    // Variables to store the username and password.
    char username[256];
    char password[256];

    // Prompt and read the username.
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input.
    username[strcspn(username, "\n")] = 0;

    // Prompt and read the password.
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input.
    password[strcspn(password, "\n")] = 0;

    // Attempt to login with the provided credentials.
    if (login(username, password)) {
        // Inform the user of a successful login.
        printf("Login successful!\n");
        // Buffer to hold the command input by the user.
        char command[256];
        while(1) {
            // Display the command prompt.
            printf("$ ");
            // Read a command from the user. If input fails, break out of the loop.
            if(fgets(command, sizeof(command), stdin) == NULL) break;
            // Skip if the command is empty.
            if(command[0] == '\n') continue;
            // Remove newline character from input.
            command[strcspn(command, "\n")] = 0;
            // Exit the shell if the user enters 'exit'.
            if(strcmp(command, "exit") == 0) break;
            // Pass the command(s) to the adapted system function for execution.
            adapted_system(command);
        }
    } else {
        // Inform the user if login failed.
        printf("Login failed. Access denied.\n");
    }
}

// Main function: entry point of the program.
int main() {
    // Start the shell function, which handles the main logic.
    shell();
    // Return 0 to indicate successful execution to the operating system.
    return 0;
}
/*
 * gcc second_shell.c -o second_shell
 * ./second_shell
Username: ubuntu
Password: 1234
Login successful!
$ echo "hello";ls;ps;echo "done"
hello
Child exited with status 0
second_shell  second_shell.c
Child exited with status 0
    PID TTY          TIME CMD
   3603 pts/0    00:00:00 bash
   5703 pts/0    00:00:00 second_shell
   5715 pts/0    00:00:00 sh
   5716 pts/0    00:00:00 ps
Child exited with status 0
done
Child exited with status 0

 */