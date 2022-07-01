#include <stdio.h>
#include <unistd.h>

int main(int argc, char *args[]){

    /* la tubería que creó el otro proceso */
    int fildes[2];

    /* Se crea tubería sin nombre */
    if (pipe(fildes) < 0){
        perror("Error al crear la tubería \n");
        return(1);
    }

    /* Se crea proceso hijo */
    if (fork() == 0){
        int dato_entra = 100;
        write(fildes[1], &dato_entra, sizeof(int));
    }else {  /* proceso padre */
        int dato_sale;
        read(fildes[0], &dato_sale, sizeof(int));
        printf("Dato recibido por tubería: %d\n", dato_sale);
    }
    /* cerrar descriptores */
    close(fildes[0]);
    close(fildes[1]);
    return 0;
}