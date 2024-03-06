/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 2.3
 * Programul de mai jos primeste diferite cauta in folder-ul
 * /proc toate informatiile despre procese de care are nevoie
 * si apoi le afiseaza.
 */
#include <stdio.h> // Standard I/O library for functions like printf and fprintf.
#include <dirent.h> // Include the directory entry structure library to work with directory and file system operations
#include <stdlib.h> // Standard library for functions like exit and atoi.
#include <string.h> // String handling functions, such as strcmp.

// Function to print process information for a given PID
void printProcessInfo(const char* pid) {
    // Declare buffers for file path and line reading
    char path[40], line[100], *p;
    // Declare a file pointer to open and read files
    FILE* statusf;

    // Construct the path to the 'status' file for a given PID
    snprintf(path, 40, "/proc/%s/status", pid);
    // Open the 'status' file in read mode
    statusf = fopen(path, "r");
    // If the file couldn't be opened, exit the function
    if (!statusf)
        return;

    // Print the PID
    printf("PID: %s ", pid);

    // Read the file line by line
    while (fgets(line, 100, statusf)) {
        // Print lines containing process name, parent PID, user ID, and group ID
        if (strncmp(line, "Name:", 5) == 0 ||
            strncmp(line, "PPid:", 5) == 0 ||
            strncmp(line, "Uid:", 4) == 0 ||
            strncmp(line, "Gid:", 4) == 0) {
            printf("%s ", line);
        }
    }

    // Close the file
    fclose(statusf);
}

int main() {
    // Open the /proc directory
    DIR* proc = opendir("/proc");
    // Declare a directory entry pointer
    struct dirent* ent;

    // If opening the directory failed, print an error and exit
    if (proc == NULL) {
        perror("opendir(/proc)");
        return 1;
    }

    // Iterate over all entries in the /proc directory
    while ((ent = readdir(proc)) != NULL) {
        // If the entry is a directory and its name is a number (PID), print its info
        if (ent->d_type == DT_DIR && strtol(ent->d_name, NULL, 10) > 0) {
            printProcessInfo(ent->d_name);
        }
    }

    // Close the /proc directory
    closedir(proc);
    // Return success
    return 0;
}
/*> Exemple de compilare si rulare a programului

 gcc -o 3 3.c

./3
PID: 1 Name:    systemd
 PPid:  0
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 2 Name:   kthreadd
 PPid:  0
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 3 Name:   rcu_gp
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 4 Name:   rcu_par_gp
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 5 Name:   slub_flushwq
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 6 Name:   netns
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 11 Name:  mm_percpu_wq
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0
 PID: 12 Name:  rcu_tasks_kthread
 PPid:  2
 Uid:   0       0       0       0
 Gid:   0       0       0       0

 */