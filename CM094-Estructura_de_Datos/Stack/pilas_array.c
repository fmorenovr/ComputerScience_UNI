/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>

#define max 10 //  longuitud total de la pila

typedef struct Pila {
   int s[max]; // Pila con tamanio "max"
   int tope;   // Indice del ultimo elementos agregado
} Pila;

Pila pila = { {}, -1};

/*
void Inicia_pila()
{
  pila.tope=-1;
}
*/

// Operaciones Auxiliares

int esPila_llena()
{
  return (pila.tope >= max-1);
}

int esPila_vacia()
{
  // Comparamos con -1 porque los arrays comienzan
  // desde el indice "0"
  return (pila.tope == -1);
}

// Operaciones Basicas

void Pila_push(int dato)
{
    pila.tope++;
    pila.s[pila.tope]=dato;
}

int Pila_pop()
{
  int dato;
  dato=pila.s[pila.tope];
  pila.tope--;
  return dato;
}

// si el array es de tipo char cambiar la funcion Pila_pop, y la definicion en la estructura Pila y Pila_push

void Pila_print()
{
  int i;
  if(esPila_vacia())  printf("No hay elementos por mostrar \n");
  else
  {
    for(i=0;i<=pila.tope;i++)
    {
      printf("%i\t%d \n",i,pila.s[i]);
    }
  }
}


int main()
{
   int item, item1, opcion;

   printf("\n\tImplementacion de una Pila");
  for(;;) {
      printf("\nMenu Principal");
      printf("\nTope: %i, max: %i",pila.tope+1,max);
      printf("\n1.Push \n2.Pop \n3.Show \n4.Exit");
      printf("\nIngrese Opcion: \n");
      scanf("%d", &opcion);
      switch (opcion) {
     case 1:
        printf("\ningresa el valor a agregar: \n");
        scanf("%d", &item);
        if (esPila_llena())
           printf("\nLa Pila Esta llena, no se puede insertar elementos \n");
        else{
           Pila_push(item);
        }
        break;
     case 2:
        if (esPila_vacia())
          printf("\nLa Pila esta Vacia, no se puede extraer elementos \n");
        else {
           item1=Pila_pop();
           printf("\nEl elemento quitado es: %d\n", item1);
        }
        break;
     case 3:
       Pila_print();
       break;
     case 4:
     default:
        exit(0);
     }
  }
  return 0;
}
