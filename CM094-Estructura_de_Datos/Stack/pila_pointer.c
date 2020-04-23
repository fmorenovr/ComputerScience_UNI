/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
 
struct pila
{
  int info;
  struct pila *sgte;
};

typedef struct pila *Pila;

Pila tope=NULL;

int strrcbff(char *str,int n)
{
  int i,c;
  c=getchar();
  if(c==EOF)
  {
    str[0]='\0';
    return 0;
  }
  if(c=='\n') i=0;
  else
  {
    str[0]=c;
    i=1;
  }
  for(;i<n-1&&(c=getchar())!=EOF && c!='\n';i++)  str[i]=c;
  str[i]='\0';
  if(c!='\n' && c!=EOF)
    while((c=getchar())!='\n' && c!=EOF);
  return 1;
}

int esPila_vacia();
void Destruir_pila();
void Pila_push(int dato);
int Pila_pop();
void Pila_print();
void Num_elem_pila(); 
int numelem = 0;

int esPila_vacia()
{
  return (tope==NULL);
}

void Destruir_pila()
{
  while(tope!=NULL)
  {
    tope=tope->sgte;
  }
  numelem=0;
}

void Pila_push(int dato)
{
  if(esPila_vacia())
  {
    tope = (struct pila*)malloc(sizeof(struct pila));
    tope->info=dato;
    tope->sgte=NULL;
  }
  else
  {
    Pila aux;
    aux = (struct pila*)malloc(sizeof(struct pila));
    aux->info = dato;
    aux->sgte = tope;
    tope = aux;
  }
  numelem++;
}

int Pila_pop()
{
  int dato;
  Pila aux;
  aux = tope;
  dato=aux->info;
  tope = tope->sgte;
  free(aux);
  numelem--;
  return dato;
}

void Num_elem_pila()
{
  printf("\nEl numero de elementos de la pila es: %i\n",numelem);
}

void Pila_print()
{
  Pila aux;
  aux = tope;
  while (aux != NULL)
  {
    printf("%i-->", aux->info);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("NULL\n");
}

int main()
{
  char opcion[2],item;
  int opcion1,dato;

  for(;;)
  {
    printf("\n 1. Apilar");
    printf("\n 2. Desapilar");
    printf("\n 3. Mostrar Pila");
    printf("\n 4. Numero de elementos de la pila");
    printf("\n 5. Destruir Pila");
    printf("\n 6. Exit");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,3);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a apilar : \n");
         strrcbff(&item,2);
         dato=atoi(&item);
         Pila_push(dato);
         break;
      case 2:
          if(esPila_vacia())
            printf("Pila Vacia!!\n");
          else
          {
            dato=Pila_pop();
            printf("\nEl elemento desapilado es: %i\n",dato);
          }
          break;
      case 3:
          printf("Los elementos son: \n");
          Pila_print();
          break;
      case 4:
          Num_elem_pila();
          break;
      case 5:
          printf("La pila se destruira! \n");
          Destruir_pila();
          break;
      case 6:
      default :
          exit(0);
    }
  }
  return 0;
}
