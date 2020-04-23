#include <stdio.h>
#include <string.h>
#include<math.h>
#define N 100
void s(){
	int i;
	for(i=65;i<=122;i++){
		printf("%d\t%c\n",i,i);
	}
}
void invertir(char a[], char b[]){
	int i,j;
	for(i=strlen(a),j=0;i-1>=0;i--,j++){
		
		b[j]=a[i-1];
	}
	b[j]='\0';
}
void mayuscula(char a[]){
	int i;
	for(i=0;a[i]!='\0';i++)
		if(a[i]>=97 && a[i]<=122) printf("%c",a[i]-('a'-'A'));
		else printf("%c",a[i]);
}
int main(){
	char a[N],copia[N];
	puts("ingrese un texto"); gets(a);
	invertir(a,copia);
	mayuscula(copia);
	
	return 0;
}
