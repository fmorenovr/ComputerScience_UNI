/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

typedef struct Cola{
int q[SIZE];
int frente,final; // ambos van dede 0 hasta SIZE-1
} Cola;

Cola cola={ {},-1,-1};

/*
void Inicia_cola()
{
  cola.frente=-1;
  cola.final=-1;
}
*/

// Operaciones Auxiliares
int esCola_llena()
{
  return (cola.final==SIZE-1);
}

int esCola_vacia()
{
  return (cola.frente>cola.final || (cola.frente==-1 && cola.final==-1));
}

// Operaciones Basicas
void Cola_push(int dato)
{
  cola.final++;
  cola.q[cola.final]=dato;
  if(cola.final==0)  cola.frente=0; // aumenta porque tiene que empezar desde 0
}

int Cola_pop()
{
  int dato;
  dato=cola.q[cola.frente];
  cola.frente++;
  if(esCola_vacia())
  {
    cola.frente=-1;
    cola.final=-1;
  }
  return dato;
}

void Cola_print()
{
  int i;
  if(esCola_vacia())  printf("No hay elementos por mostrar \n");
  else
  {
    printf("Los elementos son: \n");
    for(i=cola.frente;i<=cola.final;i++)
    {
      printf("%i\t%d \n",i,cola.q[i]);
    }
  }
}

int main()
{
  int opcion,item,item1;
  
  printf("\n\tImplementacion de una Cola");
  while (1)
  {
    printf("\nMenu Principal:\n");
    printf("1.Encolar \n");
    printf("2.Desencolar \n");
    printf("3.Show Cola \n");
    printf("4.Exit \n");
    printf("Ingresa tu opcion :\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
     case 1:
       printf("\ningresa el valor a encolar: \n");
       scanf("%d", &item);
       if (esCola_llena())
          printf("\nLa Cola Esta llena, no se puede encolar elementos \n");
       else{
          Cola_push(item);
       }
       break;
     case 2:
       if (esCola_vacia())
         printf("\nLa Cola esta Vacia, no se puede desencolar elementos \n");
       else {
          item1=Cola_pop();
          printf("\nEl elemento quitado es: %d\n", item1);
       }
       break;
     case 3:
       Cola_print();
       break;
     case 4:
     default:
       exit(0);
    }
  }
  return 0;
}
