#include<stdio.h>
void calcula(int x,int y);

int main(){
int x,y,mcd,mcm;
int *p,*q;
p=&mcd;
q=&mcm;
printf("ingrese los valores a cacular: ");
printf("primer valor: "); scanf("%d",&x);
printf("segundo valor: "); scanf("%d",&y);
cacula(x,y);
printf("el mcd es %d",*p);
printf("el mcm es %d",*q);
return 0;
}
void calcula(int x,int y){
int i,j,mcd,mcm,a,b;
i=x;
j=y;

while(a!=0){
a=x%y;
x=y;
y=a;
}
mcd=x;

mcm=(i*j)/mcd;
printf("el mcd y mcm de los numeros es %d %d respectivamente \n ",mcd,mcm);

}

