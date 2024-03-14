/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execlp` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execlp
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    execlp("ls", "ls", "-l", NULL); // `ls` va fi căutat în PATH ca sa poata rula
    perror("execlp");
    return 1; // execlp nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execlp.c -o execlp

 ./execlp
total 40
-rw-rw-r-- 1 ubuntu ubuntu   403 mar 14 22:30 execl.c
-rw-rw-r-- 1 ubuntu ubuntu   486 mar 14 22:31 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   533 mar 14 22:32 execlp.c
-rw-rw-r-- 1 ubuntu ubuntu   435 mar 14 22:32 execv.c
-rw-rw-r-- 1 ubuntu ubuntu   516 mar 14 22:31 execve.c
-rw-rw-r-- 1 ubuntu ubuntu   481 mar 14 22:30 execvp.c

 */


