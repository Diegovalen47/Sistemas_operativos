#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int *p = (int *) malloc(sizeof(int));
	int n1 = 999;
	p = &n1;	
	free(p);
	memcpy(p, &n1, sizeof(int));
	return 0;
}
