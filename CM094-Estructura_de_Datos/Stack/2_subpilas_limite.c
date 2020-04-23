/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include<stdlib.h>

#define SIZE 5
 
int pila[SIZE]; // pila que contiene a las 2 subpilas va de 0 a SIZE-1
int tope1 = -1; // vacio por la izquierda
int tope2 = SIZE; // vacio por la derecha
 
//Funciones de insertacion
void push_subpila1 (int data,int num)
{
  if (tope1 < num - 1) // evalua si tope 1 aun no choca con tope2 -1
  {
    tope1++;
    pila[tope1] = data;
  }
  else
  {
    printf ("Subpila 1 llena ! No se puede agregar\n");
  }
}
void push_subpila2 (int data)
{
  if (tope1 < tope2 - 1)
  {
    tope2--;
    pila[tope2] = data; 
  }
  else
  {
    printf ("Subpila 2 llena ! No se puede agregar\n");
  }
}
 
// Funciones de extraccion
void pop_subpila1()
{
  int dato;
  if (tope1 > -1)
  {
    dato = pila[tope1];
    tope1--;
    printf ("%d valor extraido de la subpila 1\n", dato);
  }
  else
  {
    printf ("Subpila 1 vacia! No se puede extraer\n");
  }
}
void pop_subpila2()
{
  int dato;
  if (tope2 < SIZE)
  {
    dato = pila[tope2];
    tope2++;
    printf ("%d valor extraido de la subpila 2\n", dato);
  }
  else
  {
    printf ("Subpila 2 vacia! No se puede extraer\n");
  }
}

//Funciones para Print Subpila 1 y Subpila 2
void print_subpila1()
{
  int i;
  for (i = tope1; i >= 0; --i)
  {
    printf ("%d ", pila[i]);
  }
  printf ("\n");
}
void print_subpila2()
{
  int i;
  for (i = tope2; i < SIZE; ++i)
  {
    printf ("%d ", pila[i]);
  }
  printf ("\n");
}

int main()
{
  int elem1,elem2,opcion,dato;
  printf("\nIngrese numero de elementos de la subpila 1: \n");
  scanf("%i",&elem1);
  elem2=SIZE-elem1;
  printf("\nEntonces el numero de elementos de la subpila 2 es %i: \n",elem2);
  for(;;) {
      printf("\nMenu Principal");
      printf("\n1.Ingresar datos a la subpila 1 \n2.Ingresar datos a la subpila 2 \n3.Extraer datos a la subpila 1 \n4.Extraer datos a la subpila 2\n5.Imprimir subpilas 1 y 2 \n6.Salir \n");
      printf("\nIngrese Opcion: \n");
      scanf("%d",&opcion);
      switch (opcion) {
      case 1:
         printf("\ningresa el dato a agregar: \n");
         scanf("%d",&dato);
         push_subpila1(dato,elem1);
         break;
      case 2:
         printf("\ningresa el dato a agregar: \n");
         scanf("%d",&dato);
         push_subpila2(dato);
         break;
      case 3:
         pop_subpila1();
         break;
      case 4:
         pop_subpila2();
         break;
      case 5:
         print_subpila1();
         print_subpila2();
         break;
      case 6:
      default:
         exit(0);
      }
   }

}
