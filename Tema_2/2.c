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

// Function to create a specified number of child processes and their subprocesses.
void createproc(int n, int s) {
    for (int i = 1; i <= n; ++i) {
        pid_t pid = fork(); // Create a new process.
        if (pid == -1) {
            perror("fork"); // If fork fails, output the error and exit.
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This block is executed by the child process.
            printf("Proces[%d] PID %d PPID %d\n", i, getpid(), getppid()); // Print child's PID and PPID.

            // For each child process, create the specified number of subprocesses.
            for (int j = 1; j <= s; ++j) {
                pid_t subpid = fork();
                if (subpid == -1) {
                    perror("fork"); // If fork fails, output the error and exit.
                    exit(EXIT_FAILURE);
                } else if (subpid == 0) {
                    // This block is executed by the subprocess.
                    printf("Proces[%d.%d] PID %d PPID %d\n", i, j, getpid(), getppid());
                    exit(EXIT_SUCCESS); // Subprocess exits successfully.
                } else {
                    wait(NULL); // Parent (child process) waits for the subprocess to finish.
                }
            }

            exit(EXIT_SUCCESS); // Child process exits successfully.
        } else {
            wait(NULL); // Original parent process waits for the child to finish.
        }
    }
}

// Main function: entry point of the program.
int main(int argc, char *argv[]) {
    int n = 0, s = 0; // Initialize variables for number of processes and subprocesses.

    // Parse command-line arguments for both number of processes and subprocesses.
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--processes") == 0) {
            n = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--subprocesses") == 0) {
            s = atoi(argv[i + 1]);
        }
    }

    // Validate the input to ensure positive integers for processes and subprocesses.
    if (n <= 0 || s < 0) {
        fprintf(stderr, "Error! Usage: %s --processes <num> --subprocesses <num>\n", argv[0]);
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
            createproc(n, s); // Create the remaining child processes and their subprocesses.
            exit(EXIT_SUCCESS); // 'Proces[0]' child process exits successfully.
        } else {
            wait(NULL); // Parent 'Proces[B]' waits for 'Proces[0]' to finish.
        }
        exit(EXIT_SUCCESS); // 'Proces[B]' child process exits successfully.
    } else {
        wait(NULL); // The original parent process waits for 'Proces[B]' to finish.
    }

    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului

 gcc -o 2 2.c

./2
Error! Usage: ./2 --processes <num> --subprocesses <num>

 ./2 --processes 2
Proces[A] PID 10294 PPID 3985
Proces[B] PID 10295 PPID 10294
Proces[0] PID 10296 PPID 10295
Proces[1] PID 10297 PPID 10296
Proces[2] PID 10298 PPID 10296


 ./2 --processes 2 --subprocesses 2
Proces[A] PID 10283 PPID 3985
Proces[B] PID 10284 PPID 10283
Proces[0] PID 10285 PPID 10284
Proces[1] PID 10286 PPID 10285
Proces[1.1] PID 10287 PPID 10286
Proces[1.2] PID 10288 PPID 10286
Proces[2] PID 10289 PPID 10285
Proces[2.1] PID 10290 PPID 10289
Proces[2.2] PID 10291 PPID 10289


 ./2 --processes abc --subprocesses -1
Error! Usage: ./2 --processes <num> --subprocesses <num>

./2 --procs 10 --subproc 2
Error! Usage: ./2 --processes <num> --subprocesses <num>

./2 --processes 3 --subprocesses 2
Proces[A] PID 10316 PPID 3985
Proces[B] PID 10317 PPID 10316
Proces[0] PID 10318 PPID 10317
Proces[1] PID 10319 PPID 10318
Proces[1.1] PID 10320 PPID 10319
Proces[1.2] PID 10321 PPID 10319
Proces[2] PID 10322 PPID 10318
Proces[2.1] PID 10323 PPID 10322
Proces[2.2] PID 10324 PPID 10322
Proces[3] PID 10325 PPID 10318
Proces[3.1] PID 10326 PPID 10325
Proces[3.2] PID 10327 PPID 10325


 ./2 --processes 2 --subprocesses 0
Proces[A] PID 10336 PPID 3985
Proces[B] PID 10337 PPID 10336
Proces[0] PID 10338 PPID 10337
Proces[1] PID 10339 PPID 10338
Proces[2] PID 10340 PPID 10338


 ./2 --processes 1 --subprocesses 1
Proces[A] PID 10346 PPID 3985
Proces[B] PID 10347 PPID 10346
Proces[0] PID 10348 PPID 10347
Proces[1] PID 10349 PPID 10348
Proces[1.1] PID 10350 PPID 10349
 */