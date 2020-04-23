#include<stdio.h>
#include<string.h>
#define N 100
void copiar(char*c,int m,int n);
void borrar(char*c,int m,int n);
int main(){
char c[N];
int m,n,op;
printf("ingrese la cadena: "); gets(c);

do{ printf("0) salir\n 1) funcion copiar\n 2) funcion borrar\n");
    printf("ingrese su opcion:"); scanf("%d",&op);
  
   switch(op){
    case 1:    printf("ingrese el inicio: "); scanf("%d",&m);
               printf("ingrese longitud de la subcadena: "); scanf("%d",&n);
               copiar(c,m,n); printf("\n"); break;
   case 2:     printf("ingrese el inicio: "); scanf("%d",&m);
               printf("ingrese longitud de la subcadena: "); scanf("%d",&n);
               borrar(c,m,n); printf("\n");  break;
}

}while(op!=0);


printf("\n");
return 0;
}

void copiar(char*c,int m,int n){
char*p;
int i=0;
p=&c[m-1];
while(i<n){
printf("%c",*p);
p++;
i++;

}
}

void borrar(char*c,int m,int n){
char*p;
int i=0;
p=&c[m-1];
while(i<n){
printf("%c",*p);
p--;
i++;

}

}

