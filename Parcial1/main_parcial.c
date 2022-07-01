#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <string.h>
//float time_diff(struct timespec *start, struct timespec *end){
//    return (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
//}
float time_sum(struct timeval *time){
    return(time->tv_sec) + 1e-6*(time->tv_usec);
}
int main(int argc, char* argv[]) {
    struct timeval start;
    struct timeval end;
    int size = argc - 1;
    char* parameters[size];
    int index;
    for (index = 1; index <= size; index++){
        parameters[index-1] = argv[index];
    }
    pid_t pid = fork();
    if(pid < 0){
        printf("Falló fork()");
        return 1;
    }else if(pid == 0){
        /* Tamaño en bytes que tendrá el área de memoria compartida */
        const int SIZE = 4096;
        /* nombre del área de memoria compartida */
        const char *name = "TIME";
        /* descriptor de archivo del área de memoria compartida */
        int fd;
        /* puntero al área de memoria compartida */
        void *ptr;
        /* se crea el área de memoria compartida */
        fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        if (fd == -1) {
            perror("Error en shm_open");
            return(-1);
        }
        /* se establece el tamaño del área de memoria compartida */
        ftruncate(fd, SIZE);
        /* se mapea el área de memoria compartida */
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (ptr == MAP_FAILED) {
            perror("Error MAP_FAILED");
            return (-1);
        }
    
        /* Shared memory */
        ///////////////////////////////////
        gettimeofday(&start, NULL);
        float time_start = time_sum(&start);
        printf("Tiemo inicio: %0.8f sec\n",time_start);
        
        size_t n = sizeof(time_start);
        //printf("%zd\n",n);
        //memcpy(ptr, ,n);
        ////////////

        execvp(argv[1], parameters);
    }else{
        wait(NULL);
        printf("Hijo termina\n");
        // tiempo final
        /* tamaño en bytes del área de memoria compartida */
        const int SIZE = 4096;

        /* nombre del área de memoria compartida */
        const char *name = "TIME";

        /* descriptor de archivo del área de memoria compartida */
        int fd;

        /* puntero al área de memoria compartida */
        char *ptr;

        /* se abre el área de memoria compartida */
        fd = shm_open(name, O_RDONLY, 0666);
        if (fd == -1) {
            perror("Error en shm_open");
            return -1;
        }
        /* se mapea el área de memoria compartida */
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

        if (ptr == MAP_FAILED) {
            perror("Error MAP_FAILED");
            return -1;
        }

        /* se leen los bytes que están en el área de
        memoria compartida */
        //////////////////////////////
        printf("%f\n", ptr);
        ////////////////////////////
        
        /* este proceso se desengancha del área de memoria compartida */
        shm_unlink(name);
        
    }     
    return 0;
}