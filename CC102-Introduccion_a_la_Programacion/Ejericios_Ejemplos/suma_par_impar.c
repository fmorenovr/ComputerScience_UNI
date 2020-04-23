#include<stdio.h>
int main() {
  float suma=0;
   int num,i,sumaimpar=0;
   printf("Ingrese numero=\n");
   scanf("%d",&num);
   i=1;
   suma=num;
   do{
      if(i%2==1)
         if(i>1){
            suma=suma-num; //si el termino es impar,resta
            sumaimpar+=num; //almcena la suma de operandos que se restan
            }
      else 
            suma=suma+num;  //si el termino es par, suma
      printf("Ingrese numero= ");
      scanf("%d",&num);
      if(num>0)
         i++;
      } while (num!=0);
     printf("Suma de todos los términos=%f\n",suma);
     printf("\nTotal de operandos=%d",i);
     printf("\n La suma de terminos impares= %d\n",sumaimpar);
     
     return 0;
        }
      
