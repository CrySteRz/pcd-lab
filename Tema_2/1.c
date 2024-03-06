/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 2.1
 * Programul de mai jos primeste diferite ca argument numarul
 * de procese pe care trebuie sa le creeze plecand de la procesul 0
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- numar argumente incorect
 * -- argumente incorecte
 * -- valori incorecte pentru argumentele date (nu sunt numerice, valoarea nu se conformeaza constrangerilor etc.)
 * --
 */
#include <stdio.h>   // Standard I/O library for functions like printf and fprintf.
#include <stdlib.h>  // Standard library for functions like exit and atoi.
#include <unistd.h>  // POSIX operating system API, for functions like fork, getpid, and getppid.
#include <sys/wait.h> // Wait functions for process synchronization (wait).
#include <string.h>  // String handling functions, such as strcmp.

// Function to create a specified number of child processes.
void createproc(int n) {
    for (int i = 1; i <= n; ++i) {
        pid_t pid = fork(); // Create a new process.
        if (pid == -1) {
            perror("fork"); // If fork fails, output the error and exit.
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This block is executed by the child process.
            printf("Proces[%d] PID %d PPID %d\n", i, getpid(), getppid()); // Print child's PID and PPID.
            exit(EXIT_SUCCESS); // Child process exits successfully.
        } else {
            // Parent process waits for the child to finish.
            wait(NULL);
        }
    }
}

// Main function: entry point of the program.
int main(int argc, char *argv[]) {
    // Check for the correct number of command line arguments and the '-p' or '--processes' flag.
    if (argc != 3 || (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "--processes") != 0)) {
        fprintf(stderr, "Error! Usage: %s -p <num>\n", argv[0]); // If incorrect usage, print the correct format.
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[2]); // Convert the number of processes from string to integer.
    if (n <= 0) {
        fprintf(stderr, "Invalid number of processes: %s\n", argv[2]); // Validate the input is a positive integer.
        exit(EXIT_FAILURE);
    }

    // Print the PID and PPID of the current (parent) process, which is 'Proces[A]'.
    printf("Proces[A] PID %d PPID %d\n", getpid(), getppid());

    // Fork to create the 'Proces[B]' child process.
    pid_t pid_b = fork();
    if (pid_b == -1) {
        perror("fork"); // If fork fails, output the error and exit.
        exit(EXIT_FAILURE);
    } else if (pid_b == 0) {
        // This block is executed by the child process 'Proces[B]'.
        printf("Proces[B] PID %d PPID %d\n", getpid(), getppid());

        // Fork again to create the 'Proces[0]' child process.
        pid_t pid_d = fork();
        if (pid_d == -1) {
            perror("fork"); // If fork fails, output the error and exit.
            exit(EXIT_FAILURE);
        } else if (pid_d == 0) {
            // This block is executed by the child process 'Proces[0]'.
            printf("Proces[0] PID %d PPID %d\n", getpid(), getppid());
            // Call the function to create the remaining child processes.
            createproc(n);
            exit(EXIT_SUCCESS); // 'Proces[0]' child process exits successfully.
        } else {
            // Parent 'Proces[B]' waits for 'Proces[0]' to finish.
            wait(NULL);
        }
        exit(EXIT_SUCCESS); // 'Proces[B]' child process exits successfully.
    } else {
        // The original parent process waits for 'Proces[B]' to finish.
        wait(NULL);
    }

    // End of the main function.
    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului

 gcc -o 1 1.c

 ./1
Error! Usage: ./1 -p <num>

 ./1 -x 5
Error! Usage: ./1 -p <num>

 ./1 -p abc
Invalid number of processes: abc

 ./1 -p -1
Invalid number of processes: -1

 ./1 -p 3
Proces[A] PID 10167 PPID 3985
Proces[B] PID 10168 PPID 10167
Proces[0] PID 10169 PPID 10168
Proces[1] PID 10170 PPID 10169
Proces[2] PID 10171 PPID 10169
Proces[3] PID 10172 PPID 10169


 ./1 --processes 2
Proces[A] PID 10177 PPID 3985
Proces[B] PID 10178 PPID 10177
Proces[0] PID 10179 PPID 10178
Proces[1] PID 10180 PPID 10179
Proces[2] PID 10181 PPID 10179


 */