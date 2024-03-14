/**
 * Blidaru Ionut Marian
 * IA3 2023, subgrupa 3
 * Tema 3.1
 * Programul de mai jos foloseste functia `execve` pentru a rula comanda `ls -l`.
 */
#include <unistd.h> // libraria asta e necesara pentru execve
#include <stdio.h> // libraria asta e necesara pentru perror

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[] = {NULL}; // Nu foloseste variabile extra de environment
    execve(args[0], args, env);
    perror("execve");
    return 1; // execve nu returnează dacă reușește
}

/*> Exemple de compilare si rulare a programului
 gcc execve.c -o execve

./execve
total 104
-rwxrwxr-x 1 ubuntu ubuntu 16008 Mar 14 22:38 execl
-rw-rw-r-- 1 ubuntu ubuntu   986 Mar 14 22:38 execl.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 Mar 14 22:37 execle
-rw-rw-r-- 1 ubuntu ubuntu  1018 Mar 14 22:38 execle.c
-rwxrwxr-x 1 ubuntu ubuntu 16008 Mar 14 22:33 execlp
-rw-rw-r-- 1 ubuntu ubuntu   934 Mar 14 22:33 execlp.c
-rw-rw-r-- 1 ubuntu ubuntu   435 Mar 14 22:32 execv.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 Mar 14 22:41 execve
-rw-rw-r-- 1 ubuntu ubuntu   606 Mar 14 22:41 execve.c
-rwxrwxr-x 1 ubuntu ubuntu 16056 Mar 14 22:40 execvp
-rw-rw-r-- 1 ubuntu ubuntu  1118 Mar 14 22:40 execvp.c

 */