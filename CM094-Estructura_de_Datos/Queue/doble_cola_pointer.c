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
void Cola_push_right(int dato); // inserto derecha
void Cola_push_left(int dato); // inserto izquierda
int Cola_pop_right(); // extraigo por la derecha
int Cola_pop_left(); // extraigo por la izquierda
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

void Cola_push_right(int dato)
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

void Cola_push_left(int dato)
{

  if(esCola_vacia())
  {
    frente=(Cola)malloc(sizeof(cola));
    frente->sgte=NULL;
    frente->info=dato;
    final = frente;
  }
  else
  {
    Cola aux;
    aux = (Cola)malloc(sizeof(cola));
    aux->sgte=frente;
    aux->info=dato;
    frente=aux;
  }
  numelem++;
}

int Cola_pop_left()
{
  Cola aux;
  int dato;
  aux=frente;
  dato=frente->info;
  if(aux->sgte!=NULL)
  {
    aux=aux->sgte;
    free(frente);
    frente=aux;
  }
  else
  {
    frente=NULL;
    final=NULL;
  }
  numelem--;
  return dato;
}

int Cola_pop_right()
{
  Cola aux;
  int dato;
  aux=frente;
  dato=final->info;
  if(frente!=final)
  {
    while (aux->sgte != final)
    {
      aux = aux->sgte;
    }
    aux->sgte=NULL;
    final=aux;
  }
  else
  {
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
  char opcion,item;
  int opcion1,dato;

  for(;;)
  {
    printf("\n Menu Principal:");
    printf("\n 1. Encolar por derecha");
    printf("\n 2. Encolar por izquierda");
    printf("\n 3. Desencolar por izquierda");
    printf("\n 4. Desencolar por derecha");
    printf("\n 5. Mostrar Cola");
    printf("\n 6. Numero de elementos de la cola");
    printf("\n 7. Destruir Cola");
    printf("\n 8. Exit");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a encolar : \n");
         strrcbff(&item,4);
         dato=atoi(&item);
         Cola_push_right(dato);
         break;
      case 2:
         printf("Ingrese elemento a encolar : \n");
         strrcbff(&item,2);
         dato=atoi(&item);
         Cola_push_left(dato);
         break;
      case 3:
          if(esCola_vacia())
            printf("Cola Vacia!!\n");
          else
          {
            dato=Cola_pop_left();
            printf("\nEl elemento desencolado es: %i\n",dato);
          }
          break;
      case 4:
          if(esCola_vacia())
            printf("Cola Vacia!!\n");
          else
          {
            dato=Cola_pop_right();
            printf("\nEl elemento desencolado es: %i\n",dato);
          }
          break;
      case 5:
          printf("Los elementos son: \n");
          Cola_print();
          break;
      case 6:
          Num_elem_cola();
          break;
      case 7:
          printf("La cola se destruira! \n");
          Destruir_cola();
          break;
      case 8:
      default :
          exit(0);
    }
  }
  return 0;
}
