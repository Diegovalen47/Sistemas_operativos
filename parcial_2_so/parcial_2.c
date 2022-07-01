#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

/*
AUTORES:
- Santiago Castro Tabares
- Diego Valentin Osorio Marin
*/

int log_base_2(long number) {
   return (int) (log(number) / log(2));
}

int main(int argc, char* argv[]) {

   printf("\n");

   // Estructuras timeval para capturar los tiempos
   // en segundos y microsegundos
   struct timeval start;
   struct timeval end;

   // Definimos constantes obtenidas del enunciano
   const int TAMANO_PAGINA = 4096; // Bytes
   const int ESPACIO_DIR_VIR = 32; // bits

   /*

   Esquema TLB

   || dir_1 | pag_1 | despl_1 | cant_pop_1 || dir_2 | pag_2 | deslp_2 | cant_pop_2 || ..... || dir_n | pag_n | despl_n | cant_pop_n || <== Heap
   ||  8 B  |  8 B  |   8 B   |     8 B    ||  8 B  |  8 B  |   8 B   |     8 B    || ..... ||  8 B  |  8 B  |   8 B   |     8 B    ||
   |        |       |         |            |        |       |         |             |       |        |       |         |            |
   p       +1      +2        +3           +4       +5      +6        +7            +8     +4*(n-4)  +4*(n-3) +4*(n-2) +4*(n-1)    +4*n

   */

   // Tamano definido para el TLB
   int CANT_DIREC_TLB = 5;
   int DIR_PAG_DESP_LRU = 4;
   int LONGITUD_TLB = CANT_DIREC_TLB * DIR_PAG_DESP_LRU * sizeof(long);

   // N = 12 ==> 2^12 = 4096
   int N = log_base_2(TAMANO_PAGINA);
   // M = 32 ==> 2^32 = 4294967296
   int M = ESPACIO_DIR_VIR;
   // P = 20 ==> 32 -12 = 20
   // cantidad de bits para indice de pagina
   // tomando los P bits mas significativos
   int P = M - N;
   // D = N = 12
   // cantidad de bits para desplazamiento
   // tomando los D bits menos significativos
   int D = N;

   // Teniendo en cuenta que solo tenemos 32 bits para direccionamiento
   // virtual (estos bits son en sistema binario) esto sería:
   // 2^32 = 4 294 967 296
   // por lo que la direccion que se ingrese al sistema tendra que ser:
   // direccion ingresada en decimal < 4 294 967 296
   // y este numero para representarlo necesita 10 bits (10 posiciones)
   // por ello la variable input tiene tamano [10]
   char input[10];
   long dir_decimal;
   long aux_dir_decimal;
   bool igual_a_s = false;

   // Asignación del espacio en el heap y puntero
   long *TLB_pointer = (long *) malloc(LONGITUD_TLB);
   long *VALOR_INICIAL_PUNTERO = TLB_pointer;
   long *save_pointer = VALOR_INICIAL_PUNTERO;

   // Variables necesarias para la traducción
   int count_displacement; // 11
   int count_page; // 19
   int displacement[D];
   int page[P];
   int count;
   long dec_displacement;
   long dec_page;
   long LRU_INICIAL = 1;
   long min;
   long *min_pointer;

   int cont = 0;

   // Variable señal para TLB HIT o TLB MISS
   bool esta_en_tlb;

   do {

      printf("Ingrese direccion virtual: ");
      scanf("%s",input);

      if (strcmp(input, "s") == 0) {

         igual_a_s = true;

      }
      else {

         dir_decimal = atol(input);

         // ACÁ TOMAR TIEMPO INICIAL
         gettimeofday(&start, NULL);
         // Guardamos tiempo incial con microsegundos
         double time_start = (double)(start.tv_sec+ (1e-6)*start.tv_usec);

         // BUSQUEDA EN EL TLB

         TLB_pointer = VALOR_INICIAL_PUNTERO;

         esta_en_tlb = false;

         for (int i = 0; i < CANT_DIREC_TLB; i++) {

            if (*TLB_pointer == dir_decimal) {

               esta_en_tlb = true;

               TLB_pointer += 1;
               dec_page = *TLB_pointer;

               TLB_pointer += 1;
               dec_displacement = *TLB_pointer;

               TLB_pointer += 1;
               *TLB_pointer += 1;

               // ACÁ TOMAR TIEMPO final
               gettimeofday(&end, NULL);
               // Guardamos tiempo final con microsegundos
               double time_end = (double)(end.tv_sec+ (1e-6)*end.tv_usec);

               // Calculamos la diferencia de tiempo
               double diferencia_tiempo = time_end - time_start;

               printf("Numero de pagina: %li", dec_page);
               printf("\n");
               printf("Despazamiento: %li", dec_displacement);
               printf("\n");
               printf("Tiempo de traduccion: %lf", diferencia_tiempo);
               printf("\n");
               printf("TLB: Hit");
               printf("\n");
               printf("\n");

               break;

            }

            if (i != (CANT_DIREC_TLB - 1)) {

               TLB_pointer += 4;

            }

         }

         if (!esta_en_tlb) {

            // TRADUCCION : Acá se inicia el proceso de traducción
            count_displacement = D - 1; // 11
            count_page = P - 1; // 19
            displacement[D];
            page[P];
            count = 0;
            dec_displacement = 0;
            dec_page = 0;
            aux_dir_decimal = dir_decimal;

            while (count < ESPACIO_DIR_VIR) {

               int result = aux_dir_decimal % 2;

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

               aux_dir_decimal = aux_dir_decimal / 2;
               count++;

            }
            // TRADUCCION : Acá se termina el proceso de traducción

            // ACÁ TOMAR TIEMPO final
            gettimeofday(&end, NULL);
            // Guardamos tiempo final con microsegundos
            double time_end = (double)(end.tv_sec+ (1e-6)*end.tv_usec);

            // Calculamos la diferencia de tiempo
            double diferencia_tiempo = time_end - time_start;

            printf("Numero de pagina: %li", dec_page);
            printf("\n");
            printf("Despazamiento: %li", dec_displacement);
            printf("\n");
            printf("Tiempo de traduccion: %lf", diferencia_tiempo);
            printf("\n");
            printf("TLB: Miss");
            printf("\n");
            printf("\n");

            // Caso cuando el TLB no está lleno
            if (cont < CANT_DIREC_TLB) {

               cont++;

               // Guardar traduccion en el TLB
               memcpy(save_pointer, &dir_decimal, sizeof(long));
               save_pointer += 1;

               memcpy(save_pointer, &dec_page, sizeof(long));
               save_pointer += 1;

               memcpy(save_pointer, &dec_displacement, sizeof(long));
               save_pointer += 1;

               memcpy(save_pointer, &LRU_INICIAL, sizeof(long));
               save_pointer += 1;

            }
            else { // Caso cuando el TLB está lleno

               // Politica de reemplazo (LRU : Least Recently Used)

               TLB_pointer = VALOR_INICIAL_PUNTERO;
               TLB_pointer = TLB_pointer + 3;

               min_pointer = TLB_pointer + 3;
               min = *min_pointer;

               for (int i = 0; i < CANT_DIREC_TLB; i++) {

                  if (*TLB_pointer < min) {

                     min = *TLB_pointer;
                     min_pointer = TLB_pointer;

                  }

                  if (i != (CANT_DIREC_TLB - 1)) {

                     TLB_pointer += 4;

                  }

               }

               min_pointer -= 3;

               // Reemplazar traduccion en el TLB
               memcpy(min_pointer, &dir_decimal, sizeof(long));
               min_pointer += 1;

               memcpy(min_pointer, &dec_page, sizeof(long));
               min_pointer += 1;

               memcpy(min_pointer, &dec_displacement, sizeof(long));
               min_pointer += 1;

               memcpy(min_pointer, &LRU_INICIAL, sizeof(long));

            }

         }

      }

   } while(!igual_a_s);

   printf("Good bye!\n");
   printf("\n");

   // Restauramos el valor inicial del puntero
   TLB_pointer = VALOR_INICIAL_PUNTERO;
   // Para luego liberar el espacio con free
   free(TLB_pointer);

   return 0;
}