#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    /* Se crea nuevo proceso */
    pid = fork();
    if (pid < 0) { /* Error en fork */
        printf("Falló fork()");
        return 1;
    }
    else if (pid == 0) { /* proceso hijo */
        while(1){
            printf("Hola gey");
        }
        execlp("/bin/ls","ls", "-l", NULL);
    }
    else { /* Proceso padre */
            /* Se espera a que proceso hijo termine */
        wait(NULL);
        printf("Hijo termina\n")
    }
}