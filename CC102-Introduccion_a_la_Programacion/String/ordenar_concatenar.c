#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
void ordena(char [],int);
char cont(char [],char [],int,int);
int main(){
	char s[N+1],t[N+1];
	int n,m,i;
	char *p;
	printf("Ingrese cadenas:\n");
	printf("Cadena 1:"); gets(s);
	printf("Cadena 2:"); gets(t);
	n=strlen(s);
	m=strlen(t);	
	ordena(s,n);
	ordena(t,m);
	cont(s,t,n,m);
return 0;
}

void ordena(char cad[],int n){ //ordena las cadenas ingresadas
	int i,j;
	char aux;
	for(i=0;i<=n;i++)
		for(j=0;j+1<=n;j++){
			if(cad[j]>cad[j+1]){
				aux=cad[j+1];
				cad[j+1]=cad[j];
				cad[j]=aux;
			}
		}	
}

char cont(char a[],char b[],int x,int y){ //concatena las cadenas ingresadas
	int i,j,p;
	char f[x+y+1];
	p=x+y+1;
	for(i=0;i<=x;i++)
		f[i]=a[i];
	for(j=i;j<=p;j++)
		f[j]=b[j-i];
	printf("Cadena concatenada:");
	for(i=0;i<=p;i++)	
	printf("%c",f[i]);
	printf("\n");
	printf("Cadena Ordenada:");
	ordena(f,p);
	for(i=0;i<=p;i++)	
	printf("%c",f[i]);
	printf("\n");
}
