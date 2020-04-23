#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct no no_hash;
struct no
{
  int data; 
  int state; /* 0 para VACIO, 1 para REMOVIDO e 2 para OCUPADO */
};
// Calcula la función de distribución
int funcion(int k, int m, int i)
{ 
  return ((k+i)%m);
}

// Crea la tabla hash 
no_hash *Crea_Hash(int m)
{
  no_hash *temp;
  int i; 
  if((temp = (no_hash*)malloc(m*sizeof(no_hash))) != NULL)
  {
    for(i = 0; i < m; i++)
      temp[i].state = 0;
    return temp;
  }
  else
    exit(0);
}

// Inserta un elemento k en la tabla T de tamañ m
void Inserta_Hash(no_hash *T, int m, int k)
{
  int j, i = 0;
  do
  {
    j = funcion(k, m, i);
    if(T[j].state == 0 || T[j].state == 1)
    {
      T[j].data = k;
      T[j].state = 2;
      printf("\nElemento insertado con éxito!\n");
      printf("%d\t",k);
      return;
    }
    else
      i++;
  }while(i < m);
  printf("\nTabla llena!");
}

int Busca_Hash(no_hash *T, int m, int k, int i)
{
  int j;
  if(i < m)
  {
  j = funcion(k, m, i);
  if(T[j].state == 0)
    return -1;
  else
    if(T[j].state == 1)
      return Busca_Hash(T, m, k, i+1);
    else
      if(T[j].data == k)
        return j;
      else
        return Busca_Hash(T, m, k, i+1);
  }
  return -1;
}

int Remove_Hash(no_hash *T, int m, int k)
{
  int i;
  i = Busca_Hash(T, m, k, 0);
  if(i == -1)
    return -1;
  else
  {
    T[i].state = 1;
    return 1;
  }
}
void main() 
{
  int m, i, k; 
  int resp;
  no_hash *T; 
  printf("\nEntre con el tamaño de la tabla: ");
  scanf("%d",&m);
  T = Crea_Hash(m);
  srand(time(NULL));
  while(1) 
  {
    printf("\n1.-Insertar \n2.-Buscar \n3.-Remover \n4.-Imprimir\n5.- Salir (s)\n");
    scanf("%d",&resp);
    printf("\n");
    //getch(); 
    switch(resp)
    { 
      case 1:
        printf("\nIngrese el número a ser insertado en la tabla: ");
        for(i=0;i<m;i++){
        k=rand()%8;
        Inserta_Hash(T, m, k);}
        break;

      case 2: 
        printf("\nIngrese el número a ser buscado en la tabla: ");
        scanf("%d",&k);
        i = Busca_Hash(T, m, k, 0);
        if(i == -1) 
          printf("\nNumero no encontrado!");
        else 
          printf("\nNumero encontrado!");
        break;

      case 3:
        printf("\nIngrese el número a ser eliminado de la tabla: ");
        scanf("%d",&k);
        i = Remove_Hash(T, m, k); 
        if(i == -1)
          printf("\nNumero no encontrado!");
        else
          printf("\nNumero eliminado con éxito!");
        break;

      case 4:
        printf("\n\nLa tabla Hash es:\n");
        for(i=0;i<m;i++){
          printf("%i\t%d",i,T[i].data);
        }
        break;

      case 5: 
        exit(0);
        break; 
    }
  }
}
