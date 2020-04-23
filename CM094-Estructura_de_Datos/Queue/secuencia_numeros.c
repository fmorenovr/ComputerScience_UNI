/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

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
  int item,i,j=0,k=0,l=0,m=0;
  int grup1[SIZE],grup2[SIZE],grup3[SIZE],grup4[SIZE];
  for(i=0;i<SIZE;i++)
  {
    scanf("%i",&item);
    Cola_push(item);
  }
  printf("\nSeparamos los grupos: \n");
  Cola_print();
  printf("\n");
  for(i=0;i<SIZE;i++)
  {
    item=Cola_pop();
    if(0<=item && item<=10)
    {
      grup1[j]=item;
      j++;
    }
    else if(10<item && item<=19)
    {
      grup2[k]=item;
      k++;
    }
    else if(19<item && item<=29)
    {
      grup3[l]=item;
      l++;
    }
    else if(29<item)
    {
      grup4[m]=item;
      m++;
    }
  }
  j=j-1;
  k=k-1;
  l=l-1;
  m=m-1;
  
  printf("\nGrupo 1: 0< y <=10 \n");
  if(j!=-1)  for(j;j>=0;j--)  printf("%i ",grup1[j]);
  else  printf("Vacio\n");

  printf("\nGrupo 2: 10< y <=19\n");
  if(k!=-1)  for(k;k>=0;k--)  printf("%i ",grup2[k]);
  else  printf("Vacio\n");
  
  printf("\nGrupo 3: 19< y <=29\n");  
  if(l!=-1)  for(l;l>=0;l--)  printf("%i ",grup3[l]);
  else  printf("Vacio\n");
  
  printf("\nGrupo 4: 29< \n");
  if(m!=-1)  for(m;m>=0;m--)  printf("%i ",grup4[m]);
  else  printf("Vacio\n");
  printf("\n");
  return 0;
}
