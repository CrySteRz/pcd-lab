/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 1.4
 * Programul de mai jos este o unealta de diagnosticare a retelei.
 * Acesta accepta diferite argumente de la linia de comanda si executa
 * actiuni precum testarea conectivitatii la internet,
 * executarea de ping-uri catre un host specificat sau efectuarea de traceroute.
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- numar argumente incorect
 * -- argumente incorecte
 * -- valori incorecte pentru argumentele date
 * --
 */
#include <stdio.h>    // Biblioteca standard pentru intrare și ieșire pentru funcțiile de bază I/O
#include <stdlib.h>   // Biblioteca standard pentru alocare de memorie, controlul proceselor, conversii, etc.
#include <string.h>   // Funcții pentru manipularea șirurilor de caractere
#include <argp.h>     // Biblioteca pentru analiza argumentelor de linie de comandă

// Structura pentru a stoca argumentele specificate de utilizator
struct arguments {
    char *host;
    int ping;
    int traceroute;
    int check_internet;
};

// Opțiunile acceptate de programul nostru
static struct argp_option options[] = {
        {"ping", 'p', 0, 0, "Ping către gazda dată"},
        {"traceroute", 't', 0, 0, "Traceroute către gazda dată"},
        {"check-internet", 'c', 0, 0, "Verificare conectivitate internet"},
        {"help", 'h', 0, 0, "Afișează acest mesaj de ajutor"},
        {0}
};

// Funcție pentru analiza opțiunilor specificate de utilizator
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'p':
            if (arguments->traceroute || arguments->check_internet) {
                argp_error(state, "Poate fi specificată o singură opțiune la un moment dat.");
                return ARGP_ERR_UNKNOWN;
            }
            arguments->ping = 1;
            break;
        case 't':
            if (arguments->ping || arguments->check_internet) {
                argp_error(state, "Poate fi specificată o singură opțiune la un moment dat.");
                return ARGP_ERR_UNKNOWN;
            }
            arguments->traceroute = 1;
            break;
        case 'c':
            if (arguments->ping || arguments->traceroute) {
                argp_error(state, "Poate fi specificată o singură opțiune la un moment dat.");
                return ARGP_ERR_UNKNOWN;
            }
            arguments->check_internet = 1;
            break;
        case 'h':
            argp_state_help(state, stdout, ARGP_HELP_STD_HELP);
            exit(0);
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {
                argp_usage(state);
            }
            arguments->host = arg;
            break;
        case ARGP_KEY_END:
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// Structura argp care conține informațiile despre opțiunile și funcția de analiză
static struct argp argp = {options, parse_opt, "", "Ping și traceroute către o GAZDĂ"};

int main(int argc, char *argv[]) {
    struct arguments arguments;

    // Inițializarea argumentelor cu valori implicite
    arguments.host = NULL;
    arguments.ping = 0;
    arguments.traceroute = 0;
    arguments.check_internet = 0;

    // Analiza argumentelor și opțiunilor specificate de utilizator
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Verificarea conectivității la internet, dacă este specificat
    if (arguments.check_internet) {
        printf("Verificare conectivitate la internet...\n");
        if (system("wget -q --spider http://google.com") == 0) {
            printf("Conexiune la internet disponibilă.\n");
        } else {
            printf("Conexiune la internet indisponibilă.\n");
        }
    }

    // Efectuarea unui ping către gazdă, dacă este specificat
    if (arguments.ping) {
        if (arguments.host != NULL) {
            printf("Ping către %s\n", arguments.host);
            char command[100];
            sprintf(command, "ping -c 5 %s", arguments.host);
            system(command);
        } else {
            printf("Specificați o gazdă pentru ping!\n");
        }
    }

    // Efectuarea unui traceroute către gazdă, dacă este specificat
    if (arguments.traceroute) {
        if (arguments.host != NULL) {
            printf("Traceroute către %s\n", arguments.host);
            char command[100];
            sprintf(command, "traceroute %s", arguments.host);
            system(command);
        } else {
            printf("Specificați o gazdă pentru traceroute!\n");
        }
    }

    return 0;
}

/*> Exemple de compilare si rulare a programului
 *

  gcc -o app3 app3.c -L/usr/include/argp.h

  ./app3
--NO OUTPUT--

./app3 --ping=example.com
./app3: option '--ping' doesn't allow an argument
Try `app3 --help' or `app3 --usage' for more information.


./app3 --unknown-option
./app3: unrecognized option '--unknown-option'
Try `app3 --help' or `app3 --usage' for more information.

./app3 -p
Specificați o gazdă pentru ping!


./app3 -p -t
app3: Poate fi specificată o singură opțiune la un moment dat.
Try `app3 --help' or `app3 --usage' for more information.


./app3 -c


./app3 -p google.com
Ping către google.com
PING google.com


 ./app3 -t example.com
Traceroute către example.com

*/