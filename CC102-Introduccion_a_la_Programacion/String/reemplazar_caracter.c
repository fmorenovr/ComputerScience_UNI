#include <stdio.h>
#include <string.h>
#include<math.h>
#define N 100
int reemplaza(char a[]){
int i,contador=0; 
	for(i=0;a[i]!='\0';i++){
		if(a[i]==' ') {printf("%c",'_');contador++;}
		else printf("%c",a[i]);
	}
return contador;
}
int main(){
	char tex[N]; int n;
	puts("ingrese texto"); gets(tex);
	n=reemplaza(tex);
	puts("\n");
	printf("se remplazador %d espacios\n",n);
	return 0;
}

