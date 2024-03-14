/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execv` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execv
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    execv(args[0], args);
    perror("execv");
    return 1; // execv nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execv.c -o execv

./execv
total 120
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:38 execl
-rw-rw-r-- 1 ubuntu ubuntu   986 mar 14 22:38 execl.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:37 execle
-rw-rw-r-- 1 ubuntu ubuntu  1018 mar 14 22:38 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   934 mar 14 22:33 execlp.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:43 execv
-rw-rw-r-- 1 ubuntu ubuntu   520 mar 14 22:43 execv.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:41 execve
-rw-rw-r-- 1 ubuntu ubuntu  1206 mar 14 22:43 execve.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 mar 14 22:40 execvp
-rw-rw-r-- 1 ubuntu ubuntu  1118 mar 14 22:40 execvp.c

 */
