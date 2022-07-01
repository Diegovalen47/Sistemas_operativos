#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/*
AUTORES:
- Santiago Castro Tabares
- Diego Valentin Osorio Marin
*/

// Definimos constantes obtenidas del enunciano
const int TAMANO_PAGINA = 4096; // Bytes
const long ESPACIO_DIR_VIR = 32; // bits

// Variables globales n, m, p, d
int N;
int M;
int P;
int D;

int main(int argc, char* argv[]) {

   // N = 12 ==> 2^12 = 4096
   N = log_base_2(TAMANO_PAGINA);
   // M = 32 ==> 2^32 = 4294967296
   M = ESPACIO_DIR_VIR;
   // P = 20 ==> 32 -12 = 20
   // cantidad de bits para indice de pagina
   // tomando los P bits mas significativos
   P = M - N;
   // D = N = 12
   // cantidad de bits para desplazamiento
   // tomando los D bits menos significativos
   D = N;

   // Teniendo en cuenta que solo tenemos 32 bits para direccionamiento
   // virtual (estos bits son en sistema binario) esto sería:
   // 2^32 = 4 294 967 296
   // por lo que la direccion que se ingrese al sistema tendra que ser:
   // direccion ingresada en decimal < 4 294 967 296
   // y este numero para representarlo necesita 10 bits (10 posiciones)
   // por ello la variable input tiene tamano [10]
   char input[10];
   long dir_decimal;
   bool igual_a_s = false;

   do {

      printf("Ingrese direccion virtual: ");
      scanf("%s",input);

      if (strcmp(input, "s") == 0) {

         igual_a_s = true;

      }
      else {

         dir_decimal = atol(input);
         binary(dir_decimal);

      }

   } while(!igual_a_s);

   printf("Good bye!\n");

   return 0;
}

int binary(long dec_num) {

   int count_displacement = D - 1; // 11
   int count_page = P - 1; // 19
   int displacement[D];
   int page[P];
   int count = 0;
   int dec_displacement = 0;
   int dec_page = 0;

   while (count < ESPACIO_DIR_VIR) {

      int result = dec_num % 2;

      if(count_displacement >= 0) {

         displacement[count_displacement] = result;

         if(result != 0){

            dec_displacement += pow(2, count);

         }

         count_displacement--;

      }
      else {

         page[count_page] = result;

         if(result != 0) {

            dec_page += pow(2, ((P - 1) - count_page));

         }

         count_page--;

      }

      dec_num = dec_num / 2;
      count++;

   }

   printf("Numero de página: %d", dec_page);
   printf("\n");
   printf("Despazamiento: %d", dec_displacement);
   printf("\n");
   printf("\n");

   // La siguiente parte es para imprimir 
   // dec_page y dec_displacement en binario (para verificar)

   // COMENTE Y DESCOMENTE CUANDO SEA NECESARIO VERIFICAR

   // count = 0;

   // while (count < ESPACIO_DIR_VIR) {

   //    if(count < D) {

   //       printf("%d", displacement[count]);

   //    }
   //    else {

   //       if(count == D) {

   //          printf("\n");

   //       }

   //       printf("%d", page[count - D]);

   //    }

   //    count++;

   // }

   // printf("\n");

}

int log_base_2(long number) {

   return (int) (log(number) / log(2));

}