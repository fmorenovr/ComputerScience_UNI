/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>

struct pila{ // creo una estructura tipo Pila
   char info;   // valor contenido en la pila
   struct pila *tope;
};

typedef struct pila pila; // creamos una variable pila 
                          // del tipo struct pila
typedef struct pila *Pila; // creo una variable Pila
                           // que es una variable q almacena la 
                           //direccion de memoria de una variable 
                           //tipo struct Pila
int numelem=0;
int strrcbff(char *str, int n) // funcion que borra el flujo de entrada
{
  int i, c;
  c=getchar();
  if (c == EOF)
  {
    str[0] = '\0';
    return 0; // end of file, termina
  }
  if (c == '\n')  i = 0; // si es salto de linea, en cero
  else
  {
    str[0] = c;
    i = 1; // sino es un caracter cualquiera
  }
  // inicializamos i 
  for(; i < n-1 && (c=getchar())!=EOF && c!='\n'; i++)  str[i] = c;
  str[i] = '\0';
  if (c != '\n' && c != EOF)
    while ((c = getchar()) != '\n' && c != EOF);
  return 1;
}

void Crear_pila(Pila *p); // correcto
Pila Crear_pila_elem(); // correcto
void Destruir_Pila(Pila *p); // correcto
int esPila_vacia(Pila p); // correcto 
void Pila_push(Pila *p,char dato); // correcto
char Pila_pop(Pila *p); // correcto
void Pila_print(Pila p); // correcto
void Num_elem_pila();

void Crear_pila(Pila *p)
{
  *p=NULL;
} // correcto

Pila Crear_pila_elem(){
  Pila q;
  q=(Pila)malloc(sizeof(pila));
  return q;
} // correcto

void Destruir_pila(Pila *p)
{
  Pila aux;
  while(*p!=NULL)
  {
    aux=*p;
    *p=(*p)->tope;
    free(aux);
  }
  numelem=0;
}

int esPila_vacia(Pila p)
{
  return (p==NULL); // si la pila apunta a null
} // correcto

// Operaciones Basicas
void Pila_push(Pila *p,char dato)
{
  if(*p==NULL)
  {
    *p=Crear_pila_elem();
    (*p)->tope=NULL;
    (*p)->info=dato;
  }
  else
  {
    Pila aux;
    aux=Crear_pila_elem();
    aux->tope=*p;
    aux->info=dato;
    *p=aux;
  }
  numelem++;
} // correcto

char Pila_pop(Pila *p)
{
  char dato;
  Pila aux;
  aux=*p;
  dato = aux->info;
  aux=aux->tope;
  free(*p);
  *p=aux;
  numelem--;
  return dato;
}

void Pila_print(Pila p)
{
  Pila aux;
  aux=p;
  while (aux != NULL)
  {
    printf("%c-->", aux->info);
    aux = aux->tope;
  }
  if(aux==NULL) printf("NULL\n");
} // correcto

void Num_elem_pila()
{
  printf("\nEl numero de elementos de la pila es: %i\n",numelem);
}

int main()
{
   char item, item1,opcion;
   int opcion1;
   Pila s;
   Crear_pila(&s);
   printf("\n\tImplementacion de una Pila");
  for(;;) {
      printf("\nMenu Principal");
      printf("\n1.Push \n2.Pop \n3.Show \n4.Destruir Pila \n5.Numero de elementos \n6.Exit");
      printf("\nIngrese Opcion: \n");
      strrcbff(&opcion,3);
      opcion1=atoi(&opcion);
      switch (opcion1) {
     case 1:
        printf("\ningresa el valor a agregar: \n");
        scanf("%c", &item);
        Pila_push(&s,item);
        printf("\n");
        break;
     case 2:
        if (esPila_vacia(s))
          printf("\nLa Pila esta Vacia, no se puede extraer elementos \n");
        else {
           item1=Pila_pop(&s);
           printf("\nEl elemento quitado es: %c\n", item1);
        }
        break;
     case 3:
       Pila_print(s);
       printf("\n");
       break;
     case 4:
       printf("La pila se destruira !\n");
       Destruir_pila(&s);
       printf("\n");
       break;
     case 5:
       Num_elem_pila();
       break;
     case 6:
     default:
        exit(0);
     }
  }
  return 0;
}
