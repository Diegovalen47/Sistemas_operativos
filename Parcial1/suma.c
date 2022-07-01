#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    int parametro_1;
    int parametro_2;

    sscanf(argv[1], "%d", &parametro_1);
    sscanf(argv[2], "%d", &parametro_2);


    int sum = parametro_1 + parametro_2;

    printf("Mira la suma es = %d\n", sum);
    return 0;
}