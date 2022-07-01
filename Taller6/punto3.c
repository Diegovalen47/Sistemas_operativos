#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *args[]) {

    const char mypipe[] = "/tmp/mypipe";

    int fd = open(mypipe, O_RDONLY);

    int dato_sale;

    read(fd, &dato_sale, sizeof(int));
    printf("Dato que sale de tuberia: %d\n", dato_sale);

    close(fd);
    return 0;
}