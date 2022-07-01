#include <stdio.h>

void cambio(int *, int *);

int main (void){
    int x, y;
    x = 3;
    y = 2;
    printf("x = %d, y = %d\n",x, y);
    cambio (&x, &y);
    printf("x = %d, y = %d\n",x, y);
}

void cambio(int *a, int *b) {
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}