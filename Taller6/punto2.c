#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *args[]) {

    const char mypipe[] = "/tmp/mypipe";

    if (mkfifo(mypipe, 0666) < 0) {
        perror("Error al crear la tuberia\n");
        return(1);
    }

    int fd = open(mypipe, O_WRONLY);

    int dato_entra = 200;

    write(fd, &dato_entra, sizeof(int));

    close(fd);
    return 0;
}