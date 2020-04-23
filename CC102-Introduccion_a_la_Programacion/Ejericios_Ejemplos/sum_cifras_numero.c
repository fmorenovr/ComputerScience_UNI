#include<stdio.h>
#include<stdlib.h>
int suma(int n){
    int m,p;
    if(n>0&&n<10)
      return n;
    while(n>=10)
    {
    m=n%10;
    n=n-m;
    n=n/10;
    }
    p=n+m;
    if(n==0)
    return 0;
    else 
    return p;
}
int main(){
    int n;
    printf("ingrese el numero: ");
    scanf("%d",&n);
    if(n<0)
    printf("el numero no puede ser negativo!\n");
    else
    printf("la suma de cifras del nemero %d es %d\n",n,suma(n));
    system("pause");
    return 0;
}
