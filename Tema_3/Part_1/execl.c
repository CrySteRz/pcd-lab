/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execl` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execl
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl");
    return 1; // execl nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execl.c -o execl

./execl
total 72
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:38 execl
-rw-rw-r-- 1 ubuntu ubuntu   933 mar 14 22:38 execl.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:37 execle
-rw-rw-r-- 1 ubuntu ubuntu  1018 mar 14 22:38 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   934 mar 14 22:33 execlp.c
-rw-rw-r-- 1 ubuntu ubuntu   435 mar 14 22:32 execv.c
-rw-rw-r-- 1 ubuntu ubuntu   516 mar 14 22:31 execve.c
-rw-rw-r-- 1 ubuntu ubuntu   481 mar 14 22:30 execvp.c

 */
