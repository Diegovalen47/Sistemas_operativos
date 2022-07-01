#include <stdio.h>
int f(int x){
	x = x + 1;
	return 0;
}

int main (int argc, char *argv[]){
	int n;
	int a = 0;
	int b = 0;
	int *pn = &n;
	printf("argv[0] = %s\n",argv[0]);
	printf("argv[1] = %s\n",argv[1]);
	a = a + 1;
	printf("Esto es una linea\n");
	printf("Ingrese un entero: ");
	scanf("%d", &n);
	printf("Valor leido = %d\n", n);
	printf("Valor leido (des)referenciado = %d\n", *pn);
	a = a + 1;
	b = f(a);
	printf("a = %d\n",a);
	a = a + 3;
	printf("a = %d\n",a);
	return 0;
}
