/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execvp` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execvp
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    char *args[] = {"ls", "-l", NULL}; // `ls` va fi căutat în PATH ca sa poata rula
    execvp(args[0], args);
    perror("execvp");
    return 1; // execvp nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execvp.c -o execvp

./execvp
total 88
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:38 execl
-rw-rw-r-- 1 ubuntu ubuntu   986 mar 14 22:38 execl.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:37 execle
-rw-rw-r-- 1 ubuntu ubuntu  1018 mar 14 22:38 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   934 mar 14 22:33 execlp.c
-rw-rw-r-- 1 ubuntu ubuntu   435 mar 14 22:32 execv.c
-rw-rw-r-- 1 ubuntu ubuntu   516 mar 14 22:31 execve.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:40 execvp
-rw-rw-r-- 1 ubuntu ubuntu   571 mar 14 22:40 execvp.c

 */