/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 2.2
 * Programul de mai jos primeste diferite ca argument numarul
 * de procese pe care trebuie sa le creeze plecand de la procesul 0,
 * si numarul de subprocese pe care le creeze plecand de la procesele create anterior
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

// Function to create a specified number of child processes, each with a specified number of subchildren.
void createproc(int n, int s) {
    // Loop to create n child processes
    for (int i = 1; i <= n; ++i) {
        // Fork a new process
        pid_t pid = fork();
        // If fork fails, print an error and exit
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This block is executed by the child process.
            printf("Process[%d] PID %d PPID %d\n", i, getpid(), getppid());

            // Subchildren creation loop
            pid_t lastSubPid;
            for (int j = 1; j <= s; ++j) {
                lastSubPid = fork();
                if (lastSubPid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (lastSubPid == 0) {
                    // This block is executed by the subchild process.
                    printf("Process[%d.%d] PID %d PPID %d\n", i, j, getpid(), getppid());
                    // No further subprocesses are created if this is the last one
                    if (j == s) exit(EXIT_SUCCESS);
                } else {
                    // The parent (child of the original process) waits for its children to finish
                    wait(NULL);
                    // Then it exits successfully
                    exit(EXIT_SUCCESS);
                }
            }
            // After all subchildren have been created, the child process exits.
            exit(EXIT_SUCCESS);
        } else {
            // The original parent process waits for all its children to finish
            wait(NULL);
        }
    }
}

// Main function: entry point of the program
int main(int argc, char *argv[]) {
    // Initialize process and subprocess counters
    int n = 0, s = 0;

    // Parse command line arguments for --processes and --subprocesses flags
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--processes") == 0) {
            n = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--subprocesses") == 0) {
            s = atoi(argv[i + 1]);
        }
    }

    // If n or s is not specified or is zero, print error message and exit
    if (n <= 0 || s <= 0) {
        fprintf(stderr, "Error! Usage: %s --processes <num> --subprocesses <num>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Print the parent process ID (Process A)
    printf("Process[A] PID %d PPID %d\n", getpid(), getppid());

    // Fork to create Process B
    pid_t pid_b = fork();
    if (pid_b == -1) {
        // If fork fails, print an error and exit
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_b == 0) {
        // Print Process B's PID and PPID
        printf("Process[B] PID %d PPID %d\n", getpid(), getppid());

        // Fork to create Process D
        pid_t pid_d = fork();
        if (pid_d == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid_d == 0) {
            // Print Process D's PID and PPID
            printf("Process[0] PID %d PPID %d\n", getpid(), getppid());
            // Process D creates the specified number of child processes with subchildren
            createproc(n, s);
            // Then exits successfully
            exit(EXIT_SUCCESS);
        } else {
            // Process B waits for Process D to finish
            wait(NULL);
        }

        // Process B then exits successfully
        exit(EXIT_SUCCESS);
    } else {
        // The original parent process waits for Process B to finish
        wait(NULL);
    }

    // The program exits successfully
    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului

 gcc -o 2 2.c

./2
Error! Usage: ./2 --processes <num> --subprocesses <num>

 ./2 --processes 2
Error! Usage: ./2 --processes <num> --subprocesses <num>

 ./2 --processes 2 --subprocesses 2
Process[A] PID 9200 PPID 7665
Process[B] PID 9201 PPID 9200
Process[0] PID 9202 PPID 9201
Process[1] PID 9203 PPID 9202
Process[1.1] PID 9204 PPID 9203
Process[1.2] PID 9205 PPID 9204
Process[2] PID 9206 PPID 9202
Process[2.1] PID 9207 PPID 9206
Process[2.2] PID 9208 PPID 9207

 ./2 --processes abc --subprocesses -1
Error! Usage: ./2 --processes <num> --subprocesses <num>

./2 --procs 10 --subproc 2
Error! Usage: ./2 --processes <num> --subprocesses <num>

./2 --processes 3 --subprocesses 2
Process[A] PID 9215 PPID 7665
Process[B] PID 9216 PPID 9215
Process[0] PID 9217 PPID 9216
Process[1] PID 9218 PPID 9217
Process[1.1] PID 9219 PPID 9218
Process[1.2] PID 9220 PPID 9219
Process[2] PID 9221 PPID 9217
Process[2.1] PID 9222 PPID 9221
Process[2.2] PID 9223 PPID 9222
Process[3] PID 9224 PPID 9217
Process[3.1] PID 9225 PPID 9224
Process[3.2] PID 9226 PPID 9225


 ./2 --processes 2 --subprocesses 0
Error! Usage: ./2 --processes <num> --subprocesses <num>


 ./2 --processes 1 --subprocesses 1
Process[A] PID 9237 PPID 7665
Process[B] PID 9238 PPID 9237
Process[0] PID 9239 PPID 9238
Process[1] PID 9240 PPID 9239
Process[1.1] PID 9241 PPID 9240
 */