/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.2
 * Programul de mai jos implementeaza un shell simplu care primeste un username si o parola,
 * si executa comenzi shell.
 */
#include <stdio.h>   // Standard I/O library for functions like printf and fprintf.
#include <stdlib.h>  // Standard library for functions like exit and atoi.
#include <string.h>  // String handling functions, such as strcmp.
#include <sys/wait.h> // Wait functions for process synchronization (wait).
#include <unistd.h>  // POSIX operating system API, for functions like fork, getpid, and getppid.
#include <stdbool.h> // Boolean type and values

// Custom implementation of the system function to execute shell commands
int custom_system(const char *command) {
    // Fork the current process
    pid_t pid = fork();

    if (pid == -1) { // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to complete
        return WEXITSTATUS(status); // Return the exit status of the child process
    } else { // Child process
        // Execute the command in the shell
        execlp("sh", "sh", "-c", command, (char *)NULL);
        // If execlp returns, it means it failed
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
}

// Function to validate user login
bool login(const char *username, const char *password) {
    // Open file containing credentials
    FILE *file = fopen("/tmp/credentials.txt", "r");
    char line[256];
    char cred[256];

    if (file == NULL) { // If file can't be opened
        perror("Unable to open the file");
        return false;
    }

    // Format the input credentials
    sprintf(cred, "%s:%s", username, password);

    // Check each line in the file for matching credentials
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        // If credentials match
        if (strcmp(line, cred) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Function to handle the shell interface and commands
void shell() {
    char username[256];
    char password[256];

    // Prompt for username
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    // Prompt for password
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    // If login is successful
    if (login(username, password)) {
        printf("Login successful!\n");
        char command[256];
        while(1) {
            // Prompt for command
            printf("$ ");
            if(fgets(command, sizeof(command), stdin) == NULL) break;
            if(command[0] == '\n') continue; // Ignore empty commands
            command[strcspn(command, "\n")] = 0;
            if(strcmp(command, "exit") == 0) break; // Exit on command 'exit'
            // Execute the command
            custom_system(command);
        }
    } else {
        // If login fails
        printf("Login failed. Access denied.\n");
    }
}

int main() {
    shell(); // Start the shell
    return 0;
}

/*> Exemple de compilare si rulare a programului
 * gcc shell.c -o shell
 * ./shell
 * Username: user
 * Password: pass
 * Login successful!
 * $ ls
 * shell  shell.c
 */
