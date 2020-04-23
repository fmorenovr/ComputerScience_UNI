/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

struct cola
{
  int info;
  struct cola *sgte;
};

typedef struct cola *Cola;
typedef struct cola cola;

Cola frente=NULL,final=NULL;

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

int esCola_vacia();
void Destruir_cola();
void Cola_push(int dato);
int Cola_pop();
void Cola_print();
void Num_elem_cola(); 
int numelem = 0;

int esCola_vacia()
{
  return (frente==NULL&&final==NULL);
}

void Destruir_cola()
{
  while (frente!= final)
  {
    frente = frente->sgte;
  }
  if(frente==final&&final!=NULL)
  {
    frente=final->sgte;
    final=NULL;
  }
}

void Cola_push(int dato)
{

  if(esCola_vacia())
  {
    final=(Cola)malloc(sizeof(cola));
    final->sgte=NULL;
    final->info=dato;
    frente = final;
  }
  else
  {
    Cola aux;
    aux = (Cola)malloc(sizeof(cola));
    final->sgte=aux;
    aux->info=dato;
    aux->sgte=NULL;
    final=aux;
  }
  numelem++;
}

int Cola_pop()
{
  Cola aux;
  int dato;
  aux=frente;
  if(aux->sgte!=NULL)
  {
    aux=aux->sgte;
    dato=frente->info;
    free(frente);
    frente=aux;
  }
  else
  {
    dato=frente->info;
    frente=NULL;
    final=NULL;
  }
  numelem--;
  return dato;
}

void Cola_print()
{
  Cola aux;
  aux = frente;
  while (aux != final)
  {
    printf("%i-->", aux->info);
    aux = aux->sgte;
  }
  if(aux==final && final!=NULL)
  {
    printf("%i-->", aux->info);
    aux=final->sgte;
  }
  if(aux==NULL)
    printf("NULL");
}

void Num_elem_cola()
{
  printf("\nEl numero de elementos de la cola es: %i",numelem);
}

int main()
{
  char opcion[2],item;
  int opcion1,dato;

  for(;;)
  {
    printf("\n 1. Encolar");
    printf("\n 2. Desencolar");
    printf("\n 3. Mostrar Cola");
    printf("\n 4. Numero de elementos de la cola");
    printf("\n 5. Destruir Cola");
    printf("\n 6. Exit");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,3);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a encolar : \n");
         strrcbff(&item,2);
         dato=atoi(&item);
         Cola_push(dato);
         break;
      case 2:
          if(esCola_vacia())
            printf("Cola Vacia!!\n");
          else
          {
            dato=Cola_pop();
            printf("\nEl elemento desencolado es: %i\n",dato);
          }
          break;
      case 3:
          printf("Los elementos son: \n");
          Cola_print();
          break;
      case 4:
          Num_elem_cola();
          break;
      case 5:
          printf("La cola se destruira! \n");
          Destruir_cola();
          break;
      case 6:
      default :
          exit(0);
    }
  }
  return 0;
}
