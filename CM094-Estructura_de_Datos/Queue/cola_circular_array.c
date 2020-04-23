/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

typedef struct Colacir{
int c_q[SIZE];
int frente;
int final; // ambos van dede 0 hasta SIZE-1
} Colacir;

Colacir colacir={ {},-1,-1};

/*
void Inicia_cola()
{
  cola.frente=-1;
  cola.final=-1;
}
*/

// Operaciones Auxiliares
int esColacir_llena()
{
  return ((colacir.final==SIZE-1&&colacir.frente==0)||colacir.final+1==colacir.frente);
}

int esColacir_vacia()
{
  return (colacir.frente==-1&&colacir.final==-1); // ambos vuelven a -1 si es vacia;
}

// Operaciones Basicas
void Colacir_push(int dato)
{
  if(colacir.final==SIZE-1) // si llega salta hasta cero y comienza la vuelta
  {
    colacir.final=0;
  }
  else
  {
    colacir.final++;
    if(colacir.final==0)  colacir.frente=0; // identifica para el primer elemento
  }
  colacir.c_q[colacir.final]=dato;
}

int Colacir_pop()
{
  int dato;
  dato=colacir.c_q[colacir.frente];
  if(colacir.frente==colacir.final) // cuando se encuentran vuelven a vacio
  {
    colacir.frente=-1;
    colacir.final=-1;
  }
  if(colacir.frente==SIZE-1)  colacir.frente=0;
  else{ colacir.frente++;}
  return dato;
}

void Colacir_print() // verificar
{
  int i;
  if(esColacir_vacia()) printf("No hay elementos por mostrar \n");
  else
  {
    printf("Los elementos son: \n");
    if(colacir.frente<colacir.final)
    {
      for(i=colacir.frente;i<=colacir.final;i++)
      {
        printf("%i\t%d \n",i,colacir.c_q[i]);
      }
    }
    else if(colacir.frente>colacir.final)
    {
      for(i=colacir.frente;i<SIZE;i++)
      {
        printf("%i\t%d \n",i,colacir.c_q[i]);
      }
      for(i=0;i<=colacir.final;i++)
      {
        printf("%i\t%d \n",i,colacir.c_q[i]);
      }
    }
  }
}

int main()
{
  int opcion,item,item1;
  
  printf("\n\tImplementacion de una Cola Circular");
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
       if (esColacir_llena())
          printf("\nLa Cola Esta llena, no se puede encolar elementos \n");
       else{
          Colacir_push(item);
       }
       break;
     case 2:
       if (esColacir_vacia())
         printf("\nLa Cola esta Vacia, no se puede desencolar elementos \n");
       else {
          item1=Colacir_pop();
          printf("\nEl elemento quitado es: %d\n", item1);
       }
       break;
     case 3:
       Colacir_print();
       break;
     case 4:
     default:
       exit(0);
    }
  }
  return 0;
}
