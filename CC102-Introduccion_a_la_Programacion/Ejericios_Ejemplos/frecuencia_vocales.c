#include <stdio.h>
#include <string.h>
#include<math.h>
#define N 100
int frecuencia(char a[],char x){
	int i,contador=0;
	for(i=0;a[i]!='\0';i++){
		if(a[i]==x) contador++;
	}
	return contador;
}
void asteriscos(int n){
	int i=0;
	for(i=0;i<n;i++) printf("*");
	puts("\n");
}
int main(){
	char v[N]; 
	puts("ingrese texto: "); gets(v);
	printf("a\t%3d\t",frecuencia(v,'a')); asteriscos(frecuencia(v,'a'));
	printf("e\t%3d\t",frecuencia(v,'e')); asteriscos(frecuencia(v,'e'));
	printf("i\t%3d\t",frecuencia(v,'i')); asteriscos(frecuencia(v,'i'));
	printf("o\t%3d\t",frecuencia(v,'o')); asteriscos(frecuencia(v,'o'));
	printf("u\t%3d\t",frecuencia(v,'u')); asteriscos(frecuencia(v,'u'));
	return 0;
}

