/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

typedef struct Coladoble{
int c_q[SIZE];
int frente_right; // right porque se inserta desde derecha y saca desde left
int final_right; // ambos van dede 0 hasta SIZE-1
int frente_left; // left porque se inserta desde left y saca desde right
int final_left; // ambos van dede SIZE-1 hasta 0
} Coladoble;

Coladoble coladob={ {},-1,-1,SIZE,SIZE};

int esColadob_llena()
{
  return ((coladob.final_right==SIZE-1 && coladob.frente_right==0)||(coladob.final_left==0 && coladob.frente_left==SIZE-1));
} // correcto

int esColadob_vacia()
{
  return ((coladob.frente_right>coladob.final_right)||(coladob.frente_left<coladob.final_left)||(coladob.frente_left==SIZE && coladob.final_left==SIZE)||(coladob.frente_right==-1 && coladob.final_right==-1));
} // correcto

void Coladob_push_right(int dato) // inserto por la derecha
{
  if(coladob.final_right==SIZE-1)
    printf("No se puede insertar por la derecha\n");
  else
  {
    coladob.final_right++;
    coladob.c_q[coladob.final_right]=dato;
    if(coladob.final_right==0)  coladob.frente_right=0; // aumenta porque tiene que empezar desde 0
    coladob.frente_left=coladob.final_right;
    coladob.final_left=coladob.frente_right;
  }
} // correcto

void Coladob_push_left(int dato) // inserto por la izquierda
{
  if(coladob.final_left==0)
   printf("No se puede insertar por la izquierda\n");
  else
  {
    coladob.final_left--;
    coladob.c_q[coladob.final_left]=dato;
    if(coladob.final_left==SIZE-1)  coladob.frente_left=SIZE-1; // aumenta porque tiene que empezar desde 0
    coladob.frente_right=coladob.final_left;
    coladob.final_right=coladob.frente_left;
  }
} // correcto

int Coladob_pop_right() // quito por la izquierda
{
  int dato;
  dato=coladob.c_q[coladob.frente_right];
  coladob.frente_right++;
  if(esColadob_vacia())
  {
    coladob.frente_right=-1;
    coladob.final_right=-1;
  }
  coladob.frente_left=coladob.final_right;
  coladob.final_left=coladob.frente_right;
  return dato;
}

int Coladob_pop_left() //quito por la derecha
{
  int dato;
  dato=coladob.c_q[coladob.frente_left];
  coladob.frente_left--;
  if(esColadob_vacia())
  {
    coladob.frente_left=SIZE;
    coladob.final_left=SIZE;
  }
  coladob.frente_right=coladob.final_left;
  coladob.final_right=coladob.frente_left;
  return dato;
}

void Coladob_print_right()
{
  int i;
  if(esColadob_vacia())  printf("No hay elementos por mostrar \n");
  else
  {
    printf("Los elementos son de izquierda a derecha son: \n");
    for(i=coladob.frente_right;i<=coladob.final_right;i++)
    {
      printf("%i\t%d \n",i,coladob.c_q[i]);
    }
  }
}

void Coladob_print_left()
{
  int i;
  if(esColadob_vacia())  printf("No hay elementos por mostrar \n");
  else
  {
    printf("Los elementos son de derecha a izquierda son: \n");
    for(i=coladob.frente_left;i>=coladob.final_left;i--)
    {
      printf("%i\t%d \n",i,coladob.c_q[i]);
    }
  }
}

int main()
{
  int opcion,item,item1;
  
  printf("\n\tImplementacion de una Cola Doble");
  while (1)
  {
    printf("\nMenu Principal:\n");
    printf("1.Encolar por derecha\n");
    printf("2.Encolar por izquierda\n");
    printf("3.Desencolar por derecha\n");
    printf("4.Desencolar por izquierda\n");
    printf("5.Show Cola de derecha a izquierda \n");
    printf("6.Show Cola de izquierda a derecha \n");
    printf("7.Exit \n");
    printf("Ingresa tu opcion :\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
     case 1:
       printf("\ningresa el valor a encolar por derecha: \n");
       scanf("%d", &item);
       if (esColadob_llena())
          printf("\nLa Cola Esta llena, no se puede encolar elementos \n");
       else{
          Coladob_push_right(item);
       }
       break;
     case 2:
       printf("\ningresa el valor a encolar por izquierda: \n");
       scanf("%d", &item);
       if (esColadob_llena())
          printf("\nLa Cola Esta llena, no se puede encolar elementos \n");
       else{
          Coladob_push_left(item);
       }
       break;
     case 3:
       if (esColadob_vacia())
         printf("\nLa Cola esta Vacia, no se puede desencolar elementos \n");
       else {
          item1=Coladob_pop_left();
          printf("\nEl elemento quitado por derecha es: %d\n", item1);
       }
       break;
     case 4:
       if (esColadob_vacia())
         printf("\nLa Cola esta Vacia, no se puede desencolar elementos \n");
       else {
          item1=Coladob_pop_right();
          printf("\nEl elemento quitado por izquierda es: %d\n", item1);
       }
       break;
     case 5:
       Coladob_print_left();
       break;
     case 6:
       Coladob_print_right();
       break;
     case 7:
     default:
       exit(0);
    }
  }
  return 0;
}
