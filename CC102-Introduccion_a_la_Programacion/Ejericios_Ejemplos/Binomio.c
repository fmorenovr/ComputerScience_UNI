#include<stdio.h>
//tiene limite de n=14 creo para imprimir numeros mas alto hay q modificar el argumento del factorial
#define  N 200

void imprimir(int vector[],int n){
     int i;
     for(i=0;i<n;i++)
        printf("%3d   ",vector[i]);//%3d significa q me reservara 3 espacios para escribir el numero
        printf("\n");
     
}

int factorial(int n){
     if(n==0||n==1) return 1;
     if(n>1) return n*factorial(n-1);}//factorial

int combinatorio(int m, int n){
     return factorial(m)/(factorial(n)*factorial(m-n));}//combinatorio

int main(){
    int n,v[N]={0},i,j,k,aux;
    printf("ingrese n :");
    scanf("%d",&n);
    for(i=0,aux=n;i<=n;i++,aux--){//el aux es para no afectar al n q lo usaremos
        for(j=0;j<=i;j++) v[j]=combinatorio(i,j);//uso binomio de newton
        for(k=aux;k>=0;k--) printf("   ");//imprimo los espacios de la izquierda del triangulo
        imprimir(v,i+1);
    }
    return 0;
}
