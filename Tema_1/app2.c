/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 1.2
 * Programul de mai jos acceptă diferite operații matematice și valori pe linia de comandă și, bazat pe acestea,
 * afișează rezultatul operației respective. Operațiile acceptate sunt adunare, scădere, înmulțire și divizie.
 * Am tratat următoarele situații limită care pot apărea în contextul programului:
 * -- număr argumente incorect
 * -- argumente incorecte
 * -- valori incorecte pentru argumentele date (nu sunt numerice, valoarea nu se conformează constrângerilor etc.)
 * -- împărțire la zero
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

// Funcția care afișează modul de utilizare al programului
void print_help(char *program_name) {
    printf("Utilizare: %s [--adunare | --scadere | --inmultire | --divizie] --val1 <valoare1> --val2 <valoare2> [--help]\n", program_name);
    printf("Operatii disponibile: adunare, scadere, inmultire, divizie\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *op = NULL; // Opțiunea (operația matematică)
    double val1 = 0; // Prima valoare
    double val2 = 0; // A doua valoare
    int help_flag = 0; // Indicator pentru ajutor
    int op_count = 0; // Numărul de operații specificate

    // Definirea opțiunilor acceptate și a argumentelor lor
    static struct option long_options[] = {
            {"adunare", no_argument, 0, 'a'},
            {"scadere", no_argument, 0, 's'},
            {"inmultire", no_argument, 0, 'i'},
            {"divizie", no_argument, 0, 'd'},
            {"val1", required_argument, 0, '1'},
            {"val2", required_argument, 0, '2'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    // Dacă nu sunt furnizate argumente, afișează modul de utilizare și se termină programul
    if (argc == 1) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    // Parcurge argumentele furnizate
    while ((opt = getopt_long_only(argc, argv, "asid1:2:h", long_options, NULL)) != -1) {
        switch (opt) {
            // Verifică opțiunea pentru adunare
            case 'a':
                op_count++;
                op = "adunare";
                break;
                // Verifică opțiunea pentru scădere
            case 's':
                op_count++;
                op = "scadere";
                break;
                // Verifică opțiunea pentru înmulțire
            case 'i':
                op_count++;
                op = "inmultire";
                break;
                // Verifică opțiunea pentru divizie
            case 'd':
                op_count++;
                op = "divizie";
                break;
                // Pentru prima valoare
            case '1':
                // Verifică și validează valoarea
                if (sscanf(optarg, "%lf", &val1) != 1 || val1 < 0) {
                    printf("Eroare: Valoarea pentru val1 trebuie sa fie un numar real pozitiv.\n");
                    return EXIT_FAILURE;
                }
                break;
                // Pentru a doua valoare
            case '2':
                // Verifică și validează valoarea
                if (sscanf(optarg, "%lf", &val2) != 1 || val2 < 0) {
                    printf("Eroare: Valoarea pentru val2 trebuie sa fie un numar real pozitiv.\n");
                    return EXIT_FAILURE;
                }
                break;
                // Opțiunea pentru afișarea ajutorului
            case 'h':
                help_flag = 1;
                break;
                // Pentru orice altă opțiune necunoscută
            case '?':
                printf("Optiune necunoscuta: %c\n", optopt);
                return EXIT_FAILURE;
                // În caz de eroare neașteptată
            default:
                abort();
        }
    }

    // Dacă s-a cerut ajutorul, afișează modul de utilizare și se termină programul
    if (help_flag) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    // Dacă nu s-a specificat nicio operație sau s-au specificat mai multe operații, afișează o eroare și se termină programul
    if (op_count != 1) {
        printf("Eroare: Specificati o singura operatie folosind optiunile --adunare, --scadere, --inmultire sau --divizie\n");
        return EXIT_FAILURE;
    }

    // Verifică dacă valorile pentru operațiile de divizie sunt nenule pentru a evita împărțirea la zero
    if (val1 == 0 || val2 == 0) {
        if (strcmp(op, "divizie") == 0) {
            printf("Eroare: Pentru operatia de divizie, ambele valori trebuie sa fie nenule.\n");
            return EXIT_FAILURE;
        }
    }

    // Verifică dacă valoarea a doua este zero pentru operația de divizie
    if (val2 == 0 && strcmp(op, "divizie") == 0) {
        printf("Eroare: Impartirea la zero!\n");
        return EXIT_FAILURE;
    }

    // Efectuează operația specificată și afișează rezultatul
    if (strcmp(op, "adunare") == 0) {
        printf("Rezultat adunare: %.2f\n", val1 + val2);
    } else if (strcmp(op, "scadere") == 0) {
        printf("Rezultat scadere: %.2f\n", val1 - val2);
    } else if (strcmp(op, "inmultire") == 0) {
        printf("Rezultat inmultire: %.2f\n", val1 * val2);
    } else if (strcmp(op, "divizie") == 0) {
        printf("Rezultat divizie: %.2f\n", val1 / val2);
    }

    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului


 gcc -o app2 app2.c


 ./app2
Utilizare: ./app2 [--adunare | --scadere | --inmultire | --divizie] --val1 <valoare1> --val2 <valoare2> [--help]
Operatii disponibile: adunare, scadere, inmultire, divizie


 ./app2 --adunare --val1 5 --val2 3 --scadere
Eroare: Specificati o singura operatie folosind optiunile --adunare, --scadere, --inmultire sau --divizie


 ./app2 --divizie --val1 10 --val2 0
Eroare: Pentru operatia de divizie, ambele valori trebuie sa fie nenule.


./app2 --adunare --val1 5 --val2 3
Rezultat adunare: 8.00


 ./app2 --inmultire --val1 5 --val2 3
Rezultat inmultire: 15.00


./app2 --divizie --val1 10 --val2 2
Rezultat divizie: 5.00
*/