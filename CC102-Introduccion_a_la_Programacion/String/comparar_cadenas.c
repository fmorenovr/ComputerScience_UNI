#include <stdio.h>
#include <string.h>
#include<math.h>
#define N 100
int main(){
	char a[N],b[N]; int i,aux;
	puts("ingrese la cadena A: "); gets(a);
	puts("\n");
	puts("ingrese la cadena B"); gets(b);
	for(i=0;a[i]!='\0' || b[i]!='\0';i++){
		if(a[i]==b[i]) break;
		else{   if(a[i]>b[i]){ puts("la cadena A es mayor a B\n");return 0; }
			else {puts("la cadena B es mayor a A\n"); return 0;}
		}
	}
        puts("son iguales");
	/*
	aux=strcmp(a,b);
	switch(aux){
		case 1: puts("la cadena A es mayor a B\n"); break;
		case 0: puts("las cadenas son igules\n"); break;
		default: puts("la cadena B es mayor a A\n"); break;
	}*/
	return 0;
}
