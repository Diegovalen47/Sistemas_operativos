#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[])
{

   long *p = (long *) malloc(5*sizeof(long));
   long *valor_inicial_puntero = p;
   long n = 100;
   //int acum_reset_pointer = 0;

   for (int i =0; i < 5; i++) {
      
      memcpy(p, &n, sizeof(long));
      if (i != 4){
         p += 1;
         //acum_reset_pointer +=1;
         n += 100;
      }
   }

   p = valor_inicial_puntero;
   //acum_reset_pointer = 0;

   for (int i =0; i < 5; i++) {
      
      printf("%p  ", p);
      printf("heap[%d", i);
      printf("] ");
      printf("%li\n", *p);
      if (i != 4){
         p += 1;
         //acum_reset_pointer +=1;
      }
   }

   printf("Valor inicial puntero %p\n", valor_inicial_puntero);

   p = valor_inicial_puntero;

   free(p);

   printf("Bye\n");

   return 0;
}