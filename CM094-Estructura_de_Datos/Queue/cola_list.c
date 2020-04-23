#include<stdio.h>
#include<stdlib.h>

struct cola
{
  char info;
  struct cola *sgte;
};
typedef struct cola cola; // cola es una 
                          // variable tipo struct cola
typedef struct cola *Cola;// Cola es una variable que contiene la direccion
                          //de memoria de una variable tipo struct cola

int numelem=0;
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
void Crear_cola(Cola *q); // correcto
Cola Crear_cola_elem(); // correcto
void Destruir_cola(Cola *q); // correcto
int esCola_vacia(Cola q); // correcto
void Cola_push(Cola *q,char dato); // correcto
char Cola_pop(Cola *q);
void Cola_print(Cola q);
void Num_elem_cola(); // correcto

void Crear_cola(Cola *q)
{
    *q=NULL;
}
Cola Crear_cola_elem()
{
  Cola q;
  q=(Cola)malloc(sizeof(cola));
  return q;
}
void Destruir_cola(Cola *q)
{
  Cola aux;
  while(*q!=NULL)
  {
    aux=*q;
    *q=(*q)->sgte;
    free(aux);
  }
  numelem=0;
}

int esCola_vacia(Cola q)
{
  return (q==NULL);
}

void Cola_push(Cola *q,char dato)
{
  if(*q==NULL)
  {
    *q=Crear_cola_elem();
    (*q)->sgte=NULL;
    (*q)->info=dato;
  }
  else
  {
    Cola aux,aux1;
    aux=*q;
    while(aux->sgte!=NULL)
      aux=aux->sgte;
    aux1=Crear_cola_elem();
    aux1->info=dato;
    aux1->sgte=NULL;
    aux->sgte=aux1; // lo agrega porque setamos trabajando con el mismisimo q
  }
  numelem++;
}

char Cola_pop(Cola *q)
{
  char dato;
//  Cola aux;
//  aux=*q;
  dato = (*q)->info;
  *q=(*q)->sgte;
//  free(aux);
  numelem--;
  return dato;
}

void Cola_print(Cola q)
{
  Cola aux;
  aux = q;
  while (aux != NULL)
  {
    printf("%c-->", aux->info);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("NULL\n");
}

void Num_elem_cola()
{
  printf("\nEl numero de elementos de la cola es: %i",numelem);
}

int main()
{
  char opcion[2],item;
  int opcion1;
  Cola q;
  Crear_cola(&q);

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
         Cola_push(&q,item);
         break;
      case 2:
          if(esCola_vacia(q))
            printf("Cola Vacia!!\n");
          else
          {
            item=Cola_pop(&q);
            printf("\nEl elemento desencolado es: %c\n",item);
          }
          break;
      case 3:
          printf("Los elementos son: \n");
          Cola_print(q);
          break;
      case 4:
          Num_elem_cola();
          break;
      case 5:
          printf("La cola se destruira! \n");
          Destruir_cola(&q);
          break;
      case 6:
      default :
          exit(0);
    }
  }
  return 0;
}
