/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "nm_fun.h"

int main()
{
   char opcion,signo;
   int cifras1=0,cifras2=0,nega1=0,nega2=0,opcion1,n=0,n1=0,m1=0,m=0;
   int comparar1=0,comparar2=0,invertir=0,igual=0,igual1=0,suma=0;
   Pila opera1,opera2,resultado;
   Crear_pila(&opera1);
   Crear_pila(&opera2);
   Crear_pila(&resultado);
   
   for(;;){
     printf("\n---------------------------------------------");
     printf("\n\nMenu de operaciones con Numeros grandes:\n");
     printf("1. Ingresar los numeros: \n");
     printf("2. Sumar numeros\n");
     printf("3. Restar numeros\n");
     printf("4. Exit\n");
     printf("\n---------------------------------------------");
     printf("\n\nIngrese opcion:\n");
     strrcbff(&opcion,3);
     opcion1=atoi(&opcion);
     switch (opcion1) {
      case 1:
        nega1=0;
        igual=0;
        nega2=0;
        comparar1=0;
        comparar2=0;
        printf("\nSe ingresara ambos numeros: \n");
        while(comparar1==0)
        {
          Destruir_pila(&opera1);
          printf("\nIngrese el numero de cifras del primer operando\n");
          strrcbff(&opcion,200);
          cifras1=atoi(&opcion);
          n=Generar_pila(&opera1,cifras1);
          signo=Pila_delet_right(&opera1);
          if(esPila_vacia(opera1) && signo=='-')
          {
            printf("\nIngrese cifras aparte del signo\n");
            comparar1=0;
          }
          else if(n<cifras1 || Buscar_elem_pila(opera1,'-'))
          {
            printf("\nCadena incorrecta vuelva a ingresar el numero\n");
            comparar1=0;
          }
          else
          {
            if(signo == '-')  nega1=1;
            Pila_insert_right(&opera1,signo);
            comparar1=1;
          }
        }
        fflush(stdin);
        while(comparar2==0)
        {
          Destruir_pila(&opera2);
          printf("\nIngrese el numero de cifras del segundo operando\n");
          strrcbff(&opcion,5);
          cifras2=atoi(&opcion);
          m=Generar_pila(&opera2,cifras2);
          signo=Pila_delet_right(&opera2);
          if(esPila_vacia(opera2) && signo=='-')
          {
            printf("\nIngrese cifras aparte del signo\n");
            comparar2=0;
          }
          else if(m<cifras2 ||Buscar_elem_pila(opera2,'-'))
          {
            printf("\nCadena incorrecta vuelva a ingresar el numero\n");
            comparar2=0;
          }
          else
          {
            if(signo == '-')  nega2=1;
            Pila_insert_right(&opera2,signo);
            comparar2=1;
          }
        }
        printf("\n");
        fflush(stdin);
        if((comparar1==1&&comparar2==1))
        {
          if((nega1==0 && nega2==0))
          {
            if(m<n)
            {
              Completar_zeros(&opera2,m,n);
              m=n;
              comparar1=0;
            }
            else if(m>n)
            {
              Completar_zeros(&opera1,n,m);
              n=m;
              comparar2=0;
            }
            igual =1;
            invertir=1;
            suma=0;
          }
          else if((nega1==1 && nega2==1))
          {
            signo=Pila_delet_right(&opera1);
            signo=Pila_delet_right(&opera2);
            if(m<n)
            {
              Completar_zeros(&opera2,m,n);
              m=n;
              comparar1=0;
            }
            else if(m>n)
            {
              Completar_zeros(&opera1,n,m);
              n=m;
              comparar2=0;
            }
            Pila_insert_right(&opera1,signo);
            Pila_insert_right(&opera2,signo);
            igual =1;
            invertir=1;
            suma=0;
          }
          else if((nega1==1 && nega2==0))
          {
            signo=Pila_delet_right(&opera1);
            n1=n-1;
            if(m<n1)
            {
              Completar_zeros(&opera2,m,n-1);
              m=n1;
              comparar1=0;
            }
            else if(m>n1)
            {
              Completar_zeros(&opera1,n-1,m);
              n1=m;
              comparar2=0;
            }
            Pila_insert_right(&opera1,signo);
            igual1 =1;
            invertir=1;
            suma=0;
          }
          else if((nega1==0 && nega2==1))
          {
            signo=Pila_delet_right(&opera2);
            m1=m-1;
            if(m1<n)
            {
              Completar_zeros(&opera2,m-1,n);
              m1=n;
              comparar1=0;
            }
            else if(m1>n)
            {
              Completar_zeros(&opera1,n,m-1);
              n=m1;
              comparar2=0;
            }
            Pila_insert_right(&opera2,signo);
            igual1 =1;
            invertir=1;
            suma=0;
          }
        }
        else
        {
          printf("\nHa ingresado uno o los dos operandos de manera erronea !!\n");
        }
        break;
      case 2:
          Destruir_pila(&resultado);
          if(igual==1 && ((nega1==0 && nega2==0) || (nega1==1 && nega2==1))&&suma==0)
          {
            if(nega1==0 && nega2==0)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
            }
            else if(nega1==1 && nega2==1)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              signo=Pila_delet_right(&opera1);
              signo=Pila_delet_right(&opera2);
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera1,signo);
              Pila_insert_left(&opera2,signo);
              Pila_insert_right(&resultado,signo);
            }
            resultado=Invertir_pila(&resultado);
            printf("\n\n");
            Pila_print(opera1);
            printf("+\n");
            Pila_print(opera2);
            printf("La suma es: \n");
            printf("----------------\n");
            Pila_print(resultado);
            //suma=1;
          }
          else if(igual1==1 && ((nega1==1 && nega2==0) || (nega1==0 && nega2==1))&&suma==0)
          {
            if(nega1==1 && nega2==0)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Resta(opera2,opera1);
              if(invertir)
              {
                signo=Pila_delet_right(&opera1);
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera1,signo);              
            }
            else if(nega1==0 && nega2==1)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Resta(opera1,opera2);
              if(invertir)
              {
                signo=Pila_delet_right(&opera2);
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera2,signo);              
            }
            resultado=Invertir_pila(&resultado);
            printf("\n\n");
            Pila_print(opera1);
            printf("+\n");
            Pila_print(opera2);
            printf("La suma es: \n");
            printf("----------------\n");
            Pila_print(resultado);
            //suma=1;
          }
          else
          {
            printf("Falta ingresar uno de los 2 operandos !!\n");
          }
          break;
      case 3:
          Destruir_pila(&resultado);
          if(igual==1 && ((nega1==0 && nega2==0) || (nega1==1 && nega2==1))&&suma==0)
          {
            if(nega1==0 && nega2==0) // resta
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Resta(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
            }
            else if(nega1==1 && nega2==1) // resta
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              signo=Pila_delet_right(&opera1);
              signo=Pila_delet_right(&opera2);
              resultado = Resta(opera2,opera1);
              if(invertir)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera1,signo);
              Pila_insert_left(&opera2,signo);
            }
            resultado=Invertir_pila(&resultado);
            printf("\n\n");
            Pila_print(opera1);
            printf("-\n");
            Pila_print(opera2);
            printf("La resta es: \n");
            printf("----------------\n");
            Pila_print(resultado);
            //suma=1;
          }
          else if(igual1==1 && ((nega1==1 && nega2==0) || (nega1==0 && nega2==1))&&suma==0)
          {
            if(nega1==1 && nega2==0)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                signo=Pila_delet_right(&opera1);
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera1,signo);
              Pila_insert_right(&resultado,signo);            
            }
            else if(nega1==0 && nega2==1)
            {
              if(invertir==0)
              {
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=1;
              }
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                signo=Pila_delet_right(&opera2);
                opera1=Invertir_pila(&opera1);
                opera2=Invertir_pila(&opera2);
                invertir=0;
              }
              Pila_insert_left(&opera2,signo);              
            }
            resultado=Invertir_pila(&resultado);
            printf("\n\n");
            Pila_print(opera1);
            printf("-\n");
            Pila_print(opera2);
            printf("La resta es: \n");
            printf("----------------\n");
            Pila_print(resultado);
            //suma=1;
          }
          else
          {
            printf("Falta ingresar uno de los 2 operandos !!\n");
          }
          break;
      case 4:
      default:
        exit(0);
     }
  }
  return 0;
}
