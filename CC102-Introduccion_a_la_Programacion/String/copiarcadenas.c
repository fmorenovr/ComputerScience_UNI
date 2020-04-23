#include <stdio.h>
#include <string.h>
#include<math.h>
#define N 100
int main(){
	int i; char copia[N],copia2[N],fuente[N],fuente2[N];
	gets(fuente);
	gets(fuente2);
	for(i=0;fuente[i]!='\0';i++) copia[i]=fuente[i];
	puts("la copia por repiticion es: ");puts(copia);

	strcpy(copia2,fuente2);
	puts("la copia por funcion string.h es: ");puts(copia2);
	return 0;
}


