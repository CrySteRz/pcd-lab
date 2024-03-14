/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execle` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execle
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    char *env[] = {NULL}; // Nu foloseste variabile extra de environment
    execle("/bin/ls", "ls", "-l", NULL, env);
    perror("execle");
    return 1; // execle nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execle.c -o execle

./execle
total 56
-rw-rw-r-- 1 ubuntu ubuntu   403 Mar 14 22:30 execl.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 Mar 14 22:37 execle
-rw-rw-r-- 1 ubuntu ubuntu   577 Mar 14 22:37 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 Mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   934 Mar 14 22:33 execlp.c
-rw-rw-r-- 1 ubuntu ubuntu   435 Mar 14 22:32 execv.c
-rw-rw-r-- 1 ubuntu ubuntu   516 Mar 14 22:31 execve.c
-rw-rw-r-- 1 ubuntu ubuntu   481 Mar 14 22:30 execvp.c

 */