/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 1.1
 * Programul de mai jos primeste diferite argumente
 * pe linia de comanda si bazat pe acestea programul
 * genereaza parole sigure si le afiseaza prin STDOUT.
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- numar argumente incorect
 * -- argumente incorecte
 * -- valori incorecte pentru argumentele date (nu sunt numerice, valoarea nu se conformeaza constrangerilor etc.)
 * --
 */
#include <stdio.h>  // Standard input and output library for basic I/O functions
#include <stdlib.h> // Standard library for memory allocation, process control, conversions, etc.
#include <string.h> // String handling functions
#include <getopt.h> // For parsing command-line options
#include <time.h>   // Time functions for seeding the random number generator

// Definition of long options for command-line arguments
static struct option long_options[] = {
        {"length", required_argument, 0, 'l'},       // Option for specifying password length
        {"characters", required_argument, 0, 'c'},   // Option for specifying character types
        {"extra", required_argument, 0, 'e'},       // Option for including extra characters
        {"help", no_argument, 0, 'h'},              // Option for displaying help
        {0, 0, 0, 0}                                 // End of options marker
};

// Function to display help information
void print_help() {
    printf("Usage: app1 [options]\n");
    printf("Options:\n");
    printf("  -l, --length <length>    Specify password length (max 128). If not used it defaults to 12\n");
    printf("  -c, --characters [types] Specify character types (l, u, d, s) combined, e.g., 'ld' for lowercase and digits. Default is all types.\n");
    printf("  -e, --extra [chars]      Include extra custom characters.\n");
    printf("  -h, --help               Display this help and exit.\n");
}

// Function for generating the password
void generate_password(int length, char* character_set) {
    srand(time(NULL)); // Initialize the random number generator with current time as seed
    for (int i = 0; i < length; i++) {
        printf("%c", character_set[rand() % strlen(character_set)]); // Print a random character from the set
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int c;
    int length = 12; // Default password length
    char character_set[512] = ""; // Initialize the character set to empty

    // Display help if no arguments are provided
    if (argc == 1) {
        print_help();
        return 0;
    }

    // Parse command-line options
    while (1) {
        int option_index = 0;
        c = getopt_long(argc, argv, "l:c:e:h", long_options, &option_index);

        if (c == -1) { // No more options
            break;
        }

        switch (c) {
            case 'l': // Length option
                if (optarg == NULL || optarg[0] == '-') {
                    printf("Warning: No length value provided. Using default length: %d\n", length);
                } else {
                    int temp_length = atoi(optarg); // Convert length argument to integer
                    if (temp_length <= 0 || temp_length > 128) {
                        printf("Error: Length must be a value between 1 and 128.\n");
                        return EXIT_FAILURE;
                    }
                    length = temp_length;
                }
                break;
            case 'c': // Character types option
                for (size_t i = 0; i < strlen(optarg); i++) {
                    switch (optarg[i]) {
                        case 'l':
                            strcat(character_set, "abcdefghijklmnopqrstuvwxyz"); // Add lowercase letters
                            break;
                        case 'u':
                            strcat(character_set, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // Add uppercase letters
                            break;
                        case 'd':
                            strcat(character_set, "0123456789"); // Add digits
                            break;
                        case 's':
                            strcat(character_set, "!@#$%^&*()"); // Add special characters
                            break;
                        default:
                            printf("Error: Invalid character type '%c'.\n", optarg[i]);
                            return EXIT_FAILURE;
                    }
                }
                break;
            case 'e': // Extra characters option
                strcat(character_set, optarg); // Add extra characters to the set
                break;
            case 'h': // Help option
                print_help();
                return 0;
            case '?': // Error in options
            default:
                printf("Error: Unknown option or option requires an argument: '%s'\n", argv[optind - 1]);
                print_help();
                return EXIT_FAILURE;
        }
    }

    // Check for unexpected positional arguments
    if (optind < argc) {
        printf("Error: Unexpected positional argument: '%s'\n", argv[optind]);
        print_help();
        return EXIT_FAILURE;
    }

    // Use all characters if no specific types are specified
    if (strlen(character_set) == 0) {
        strcpy(character_set, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()");
    }

    // Generate and print the password
    generate_password(length, character_set);

    return 0;
}

/*> Exemple de compilare si rulare a programului

 gcc -o app1 app1.c


./app1
Usage: app1 [options]
Options:
  -l, --length <length>    Specify password length (max 128). If not used it defaults to 12
  -c, --characters [types] Specify character types (l, u, d, s) combined, e.g., 'ld' for lowercase and digits. Default is all types.
  -e, --extra [chars]      Include extra custom characters.
  -h, --help               Display this help and exit.


./app1 --length 16
WOdC&x$0Wa^vNN56


 ./app1 --length 10 --characters l
nambihkwgg


 ./app1 --length 8 --characters ld
0xl024lr


 ./app1 --length 14 --extra "@#"
@@@#@@###@@##@


 ./app1 --length 0
Error: Length must be a value between 1 and 128.


 ./app1 --length 129
Error: Length must be a value between 1 and 128.


 ./app1 --characters z
Error: Invalid character type 'z'.


 ./app1 --length 12 unexpected_arg
Error: Unexpected positional argument: 'unexpected_arg'


 ./app1 --unknown
./app1: unrecognized option '--unknown'


 ./app1 --length
./app1: option '--length' requires an argument


*/