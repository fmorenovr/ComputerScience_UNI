#include<stdio.h>
int main(){
    int n;
    printf("ingrese el numero de la fila con  mayor *");
    scanf("%i",&n);
    int i,j;
    for(i=1;i<=n;i++){
        for(j=1;j<=(n-i);j++){
            printf(" ");
        }
        for(j=1;j<=(2*i-1);j++){
            printf("*");
        }
        printf("\n");
    }
    for(i=n-1;i>0;i--){
        for(j=0;j<(n-i);j++){
            printf(" ");
        }
        for(j=0;j<(2*i-1);j++){
            printf("*");
        }
        printf("\n");
    }
  
}
