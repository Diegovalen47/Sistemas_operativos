#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>

/*
AUTORES:
- Santiago Castro Tabares
- Diego Valentin Osorio Marin
*/

int main(int argc, char* argv[]) {

    /* Descriptores de archivos escritura y 
    lectura de la tuberia */
    int fildes[2];
    
    /* Estructuras timeval para capturar los tiempos
    en segundos y microsegundos */
    struct timeval start;
    struct timeval end;
    
    /* Cantidad de parametros */
    int size = argc - 1;
    /* Lista con parametros */
    char* parameters[size];
    int index;
    /* Captura de todos los parametros
    que se pasan por consola */
    for (index = 1; index <= size; index++){
        parameters[index-1] = argv[index];
    }

    /* Creación de la tuberia */
    int tuberia_sin_nombre = pipe(fildes);

    if (tuberia_sin_nombre < 0) {
        perror("Error al crear la tuberia");
        return(1);
    }

    /* Creacion del proceso hijo */
    pid_t pid = fork();
    /* Control del fork */
    if(pid < 0){
        printf("Fallo fork()");
        return 1;
    /* Seccion de codigo del proceso hijo */
    }else if(pid == 0){
        /* Capturamos tiempo inicial */
        gettimeofday(&start, NULL);
        /* Guardamos tiempo incial con microsegundos */
        double time_start = (double)(start.tv_sec+ (1e-6)*start.tv_usec);
        /* Se escribe este tiempo en la tuberia */
        write(fildes[1], &time_start, sizeof(double));
        /* Mostramos marca de tiempo inicial */
        printf("Tiempo inicio: %lf sec\n",time_start);
        /* El hijo es el encargado de ejecutar el
        comando y sus diferentes parametros por medio
        de un execvp */
        execvp(argv[1], parameters);
    /* Seccion de codigo poroceso padre */
    }else{
        /* Se espera a que el hijo termine */
        wait(NULL);
        /* Cuado hijo termina se captura el tiempo final */
        gettimeofday(&end, NULL);

        double time_start_sale;
        /* leemos el tiempo inicial que fue escrito en la tuberia
        por el proceso hijo, y lo guardamos en time_start_sale */
        read(fildes[0], &time_start_sale, sizeof(double));
        /* Guardamos tiempo final con microsegundos */
        double time_end = (double)(end.tv_sec+ (1e-6)*end.tv_usec);
        /* Mostramos marca de tiempo final */
        printf("Tiempo final: %lf sec\n",time_end);
        /* Calculamos la diferencia de tiempo */
        double diferencia_tiempo = time_end - time_start_sale;
        /* Mostramos por pantalla el tiempo transcurrido para
        ejecutar el comando pasado como parametro*/
        printf("Tiempo transcurrido: %lf sec\n",diferencia_tiempo);
    }
    /* Cerramos descriptores de la tuberia */
    close(fildes[0]);
    close(fildes[1]);
    return 0;
}