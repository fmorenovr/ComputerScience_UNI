/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>

struct lista{ // creo una estructura tipo Lista
   char elem; // elemento de la lista
   struct lista *sgte;
};

typedef struct lista lista;
typedef struct lista *Lista;

struct ocurr{
  char elem;
  int times;
  struct ocurr *sgte;
};

typedef struct ocurr ocurr;
typedef struct ocurr *Ocurr;

int numelem=0;

// 1 Funcion para leer dato limpiando buffer de entrada
int strrcbff(char *str,int n);

// 7 Funciones de Ayuda a la lista
void Crear_lista(Lista *l);
Lista Crear_lista_sgte();
void Destruir_lista(Lista *l);
int esLista_vacia(Lista l);
void Crear_lista_ocurr(Ocurr *o);
Ocurr Crear_lista_ocurr_sgte();
void Destruir_lista_ocurr(Ocurr *o);

// 3 Funciones para generar listas
void Generar_lista_left(Lista *l,int n);
void Generar_lista_right(Lista *l,int n);
void Menu_generar(Lista *l);

// 5 Funciones Insertar elementos de la lista
void Lista_insert_left(Lista *l,char dato);
void Lista_insert_right(Lista *l,char dato);
void Lista_insert_antes_info(Lista *l,char dato,char info);
void Lista_insert_despues_info(Lista *l,char dato,char info);
void Menu_insert(Lista *l);

// 7 Funciones Extraer elementos de la lista
char Lista_delet_left(Lista *l);
char Lista_delet_right(Lista *l);
char Lista_delet_info(Lista *l,char info);
char Lista_delet_antes_info(Lista *l,char info);
char Lista_delet_despues_info(Lista *l,char info);
void Lista_delet_elem_rep(Lista *l);
void Menu_delet(Lista *l);

// 5 Funciones de buscar y numerar los elementos de la lista
void Buscar_elem_lista(Lista l,char info);
void Ocurr_elem_lista(Lista l,Ocurr *o);
int Num_elem_lista();
void Ordenar_lista(Lista *l);                     // Selection Sort en orden ascendente
int esNumero(char i[]);

// 4 Funciones para invertir elementos
void Invertir_lista(Lista *l);
void Invertir_n_elem_left(Lista *l,int n);
void Invertir_n_elem_right(Lista *l,int n);
void Menu_invertir(Lista *l);

// 2 Funcion Imprimir elementos de la lista
void Lista_print(Lista l);
void Lista_ocurr_print(Ocurr o);

// ------------------------------------------------//

int strrcbff(char *str, int n)
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

void Crear_lista(Lista *l)
{
  *l=NULL;
}

Lista Crear_lista_sgte()
{
  Lista l;
  l=(Lista)malloc(sizeof(lista));
  return l;
}

void Destruir_lista(Lista *l)
{
  Lista aux;
  while(*l!=NULL)
  {
    aux=*l;
    *l=(*l)->sgte;
    free(aux);
  }
  numelem=0;
}

void Crear_lista_ocurr(Ocurr *o)
{
  *o=NULL;
}

Ocurr Crear_lista_ocurr_sgte()
{
  Ocurr o;
  o=(Ocurr)malloc(sizeof(ocurr));
  return o;
}

void Destruir_lista_ocurr(Ocurr *o)
{
  Ocurr aux;
  while(*o!=NULL)
  {
    aux=*o;
    *o=(*o)->sgte;
    free(aux);
  }
}

int esLista_vacia(Lista l)
{
  return (l==NULL);
}

int esNumero(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0);
}

void Generar_lista_left(Lista *l,int n)
{
  Destruir_lista(l);
  printf("Lista de %i elementos\n",n);
  int i=0,j;
  char in[1],cad;
  for(i=0;i<n;i++)
  {
    strrcbff(in,2);
    if(!esNumero(in))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      j=atoi(in);
      cad=(char)(j+48);
      Lista_insert_left(l,cad);
    }
  }
}

void Generar_lista_right(Lista *l,int n)
{
  Destruir_lista(l);
  printf("Lista de %i elementos\n",n);
  int i=0,j;
  char in[1],cad;
  for(i=0;i<n;i++)
  {
    strrcbff(in,2);
    if(!esNumero(in))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      j=atoi(in);
      cad=(char)(j+48);
      Lista_insert_right(l,cad);
    }
  }
}

void Lista_insert_left(Lista *l,char dato)
{
  if(*l==NULL)
  {
    *l=Crear_lista_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Lista aux;
    aux=Crear_lista_sgte();
    aux->sgte=*l;
    aux->elem=dato;
    *l=aux;
  }
  numelem++;
}

void Lista_insert_right(Lista *l,char dato)
{
  if(*l==NULL)
  {
    *l=Crear_lista_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Lista aux,aux1;
    aux=*l;
    while(aux->sgte!=NULL)
      aux=aux->sgte;
    aux1=Crear_lista_sgte();
    aux1->elem=dato;
    aux1->sgte=NULL;
    aux->sgte=aux1;
  }
  numelem++;
}

void Lista_insert_antes_info(Lista *l,char dato,char info)
{
  int band;
  Lista q,t;
  q=*l;
  band=1;
  if(q==NULL)
  {
    printf("Lista vacia\nNo hay elementos\n");
    band=0;
  }
  else
  {
    while(q->elem!=info && band==1)
    {
      if(q->sgte!=NULL)
      {
        t=q;
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Lista r;
      r=Crear_lista_sgte();
      r->elem=dato;
      if(*l==q) // un nodo
      {
        r->sgte=*l;
        *l=r;
      }
      else
      {
        t->sgte=r;
        r->sgte=q;
      }
      numelem++;
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",info);
  }
}

void Lista_insert_despues_info(Lista *l,char dato,char info)
{
  int band;
  Lista q;
  q=*l;
  band=1;
  if(q==NULL)
  {
    band=0;
    printf("Lista vacia\nNo hay elementos\n");
  }
  else
  {
    while(q->elem!=info && band==1)
    {
      if(q->sgte!=NULL) q=q->sgte;
      else  band=0;
    }
    if(band=1)
    {
      Lista t=Crear_lista_sgte();
      t->elem=dato;
      t->sgte=q->sgte;
      q->sgte=t;
      numelem++;
      printf("\nSe inserto correctamente\n");
      numelem++;
    }
    else  printf("\nNo se encontro el elemento %c\n",info);
  }
}

char Lista_delet_left(Lista *l)
{
  char dato;
  Lista aux;
  aux = *l;
  if(aux==NULL)
  {
    printf("Lista vacia\nNo hay elementos\n");
    dato=' ';
  }
  else{
    dato=aux->elem;
    *l=aux->sgte;
    printf("El elemento eliminado es: %c\n",dato);
    numelem--;
  }
  free(aux);
  return dato;
}

char Lista_delet_right(Lista *l)
{
  char dato;
  Lista aux,aux1;
  aux=*l;
  if(aux==NULL)
  {
    printf("Lista vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if(aux->sgte==NULL)
  {
    dato=aux->elem;
    *l=aux->sgte;
    printf("El elemento eliminado es: %c\n",dato);
    numelem--;
  }
  else
  {
    while(aux->sgte!=NULL)
    {
      aux1=aux;
      aux=aux->sgte;
    }
    dato=aux->elem;
    aux1->sgte=NULL;
    printf("El elemento eliminado es: %c\n",dato);
    numelem--;
  }
  free(aux);
  return dato;
}

char Lista_delet_info(Lista *l,char info)
{
  int band;
  char dato;
  Lista aux,aux1;
  aux=*l;
  band=1;
  if(aux==NULL)
  {
    printf("Lista vacia\n no hay elementos\n");
    dato=' ';
  }
  else if(aux->elem==info)
  {
    dato=aux->elem;
    *l=aux->sgte;
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
    numelem--;
  }
  else
  {
    while(aux->elem!=info && band==1)
    {
      if(aux->sgte!=NULL)
      {
        aux1=aux;
        aux=aux->sgte;
      }
      else  band=0;
    }
    if(band==0) printf("No se encontro Elemento\n");
    else
    {
      dato=aux->elem;
      aux1->sgte=aux->sgte;
      printf("Se elimino correctamente\n");
      numelem--;
    }
  }
  free(aux);
  return dato;
}

char Lista_delet_antes_info(Lista *l,char info)
{
  char dato;
  int band=1;
  Lista aux,aux1,aux2;
  aux=*l;
  if(aux==NULL)
  {
    printf("Lista vacia\nNo hay elementos\n");
    dato=' ';
  } //vacio CORRECTO

  else if(aux->elem==info)
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  else if(aux->elem!=info && aux->sgte==NULL)
  {
    printf("Elemento unico!\n");
    printf("No encontrado\n");
    dato=' ';
  } // primero elemento CORRECTO

  else if(aux->sgte->elem==info)
  {
    dato = aux->elem;
    *l=aux->sgte;
    printf("Elemento eliminado es %c\n",dato);
    free(aux);
    numelem--;
  }
  else if(aux->sgte->sgte==NULL && aux->sgte->elem!=info)
  {
    printf("No se encontro elemento!\n");
    dato=' ';
  } // 2 elementos

  else // de 3 a mas CORRECTO
  {
    aux1=aux; // primero
    aux2=aux->sgte; // segundo
    aux=aux->sgte->sgte; // tercero
    while(aux->elem!=info && band==1)
    {
      if(aux->sgte!=NULL)
      {
        aux1=aux1->sgte;
        aux2=aux2->sgte;
        aux=aux->sgte;
      }
      else  band=0;
    }
    if(band==1)
    {
      dato=aux2->elem;
      aux1->sgte=aux;
      printf("Se elimino correctamente\n");
      printf("El elemento eliminado es: %c\n",dato);
      numelem--;
      free(aux2);
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

char Lista_delet_despues_info(Lista *l,char info)
{
  char dato;
  int band=1;
  Lista aux,aux1,aux2;
  aux=*l;
  if(aux==NULL)
  {
    printf("Lista vacia\nNo hay elementos\n");
    dato=' ';
  }
  else
  {
    while(aux->elem!=info && band==1)
    {
      if(aux->sgte!=NULL)
      {
        aux=aux->sgte;
      }
      else  band=0;
    }
    if(band==1)
    {
      if(aux->sgte==NULL)
      {
        printf("No hay elementos por eliminar!!\n");
      }
      else
      {
        aux1=aux->sgte;
        aux2=aux1->sgte;
        dato=aux1->elem;
        aux->sgte=aux2;
        printf("Se elimino correctamente\n");
        printf("El elemento eliminado es: %c\n",dato);
        numelem--;
        free(aux1);
      }
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

void Lista_delet_elem_rep(Lista *l)
{
  Lista p,q,aux,temp;
  p=q=aux=*l;
  if(aux==NULL)  printf("Lista vacia!!\n");
  else if(aux->sgte==NULL) printf("Solo tiene un elemento!! \n");
  else
  {
    q=q->sgte;
    while(p!=NULL)
    {
      aux=p;
      while(q!=NULL)
      {
        if(q->elem == p->elem)
        {
          aux->sgte=q->sgte;
          temp=q;
          q=q->sgte;
          free(temp);
        }
        else
        {
          aux=q;
          q=q->sgte;
        }
      }
      if(p->sgte==NULL)
      {
        printf("Proceso Terminado !!\n");
        break;
      }
      else
      {
        p=p->sgte;
        q=p->sgte;
      }
    }
  }
}

void Buscar_elem_lista(Lista l,char info)
{
  Lista aux;
  aux=l;
  while(aux!=NULL && (aux->elem!=info))
    aux=aux->sgte;
  if(aux==NULL) printf("Elemento NO encontrado\n");
  else  printf("Elemento Encontrado\n");
}

void Ocurr_elem_lista(Lista l,Ocurr *o)
{
  Lista p;
  Ocurr temp,prev;
  p=l;
  while(p!=NULL)
  {
    temp=(*o);
    while(temp!=NULL && temp->elem != p->elem)
    {
      prev=temp;
      temp=temp->sgte;
    }
    if(temp==NULL)
    {
      temp=Crear_lista_ocurr_sgte();
      temp->elem=p->elem;
      temp->times=1;
      temp->sgte=NULL;
      if(*o!=NULL)  prev->sgte=temp;
      else  *o=temp;
    }
    else  temp->times+=1;
    p=p->sgte;
  }
}

void Lista_ocurr_print(Ocurr o)
{
  printf("*****\n  Number\tOccurence\n*****\n");
  while (o != NULL)
  {
    printf("    %c\t\t%d\n", o->elem, o->times);
    o=o->sgte;
  }
}

void Invertir_lista(Lista *l)
{
  Lista *aux;
  aux=l; // aux apunta a lo que l apunta *aux es *l que es el contenido de la lista original
        // es decir que aux se le da la direccion de memoria de l, que es la direccion de memoria
        // de la lista original
  Lista temp,prev;
  if((*aux)==NULL)  printf("Lista vacia\n");
  else if((*aux)->sgte==NULL) printf("Invertir un solo nodo es en vano\n");
  else if((*aux)->sgte->sgte==NULL)
  {
    (*aux)->sgte->sgte=(*aux);
    (*aux)=(*aux)->sgte;
    (*aux)->sgte->sgte=NULL;
  }
  else
  {
    prev=(*aux);
    temp=(*aux)->sgte;
    (*aux) = (*aux)->sgte->sgte;
    prev->sgte = NULL;
    while ((*aux)->sgte != NULL)
    {
      temp->sgte = prev;
      prev = temp;
      temp = (*aux);
      (*aux) = (*aux)->sgte;
    }
    temp->sgte = prev;
    (*aux)->sgte = temp;
  }
  // *aux = *l ya fueron invertidos ya que sus contenidos que es el mismo
  // porque apuntan a la misma direccion de memoria
}

void Invertir_n_elem_right(Lista *l,int n)
{
  Invertir_lista(l);
  Invertir_n_elem_left(l,n);
  Invertir_lista(l);
}

void Invertir_n_elem_left(Lista *l,int n)
{
  int m=Num_elem_lista();
  if(n==m)  Invertir_lista(l);
  else if(m<n) printf("La lista no tiene tantos elementos\n");
  else // m>n
  {
    if(n==0) printf("No se cambia nada\n");
    else if(n==1 && n<m)
    {
      printf("En en vano invertir solo el primer nodo\n");
    }
    else if(n==2)
    {
      Lista *aux,prev,temp;
      aux=l; // aux apunta a lo que apunta l
      prev=(*aux);
      temp=(*aux)->sgte;
      (*aux)=(*aux)->sgte->sgte;
      temp->sgte=prev;
      prev->sgte=(*aux);
      (*aux)=temp;
    }
    else if(n>=3)
    {
      int i;
      Lista *aux,temp,prev,liga;
      aux=l;
      prev=(*aux);
      temp=(*aux)->sgte;
      (*aux) = (*aux)->sgte->sgte;
      liga=prev;
      temp->sgte=liga;
      i=2;
      while (i<n)
      {
        prev=temp;
        temp = (*aux);
        (*aux) = (*aux)->sgte;
        temp->sgte=prev;
        i++;
      }
      liga->sgte = (*aux);
      (*aux)=temp;
      //  *aux = *l ya fueron invertidos ya que sus contenidos que es el mismo
      // porque apuntan a la misma direccion de memoria
    }
  }
}

void Ordenar_lista(Lista *l)
{
  char temp;
  Lista actual=*l;
  Lista nxt=actual->sgte;
  
  while(actual->sgte!=NULL)
  {
    while(nxt!=NULL)
    {
      if(actual->elem > nxt->elem)
      {
        temp=nxt->elem;
        nxt->elem=actual->elem;
        actual->elem=temp;
      }
      nxt=nxt->sgte;
    }
    actual=actual->sgte;
    nxt=actual->sgte;
  }
}

int Num_elem_lista()
{
  return (numelem);
}

void Lista_print(Lista l)
{
  Lista aux;
  aux = l;
  while (aux != NULL)
  {
    printf("%c-->", aux->elem);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("NULL\n");
}

void Menu_invertir(Lista *l)
{
  char opcion;
  int opcion1,elem;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Invertir lista:");
    printf("\n 1. Invertir lista");
    printf("\n 2. Invertir n primeros elementos de izquierda");
    printf("\n 3. Invertir n primeros elementos de derecha");
    printf("\n 4. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Se invertira la lista: \n");
         Invertir_lista(l);
         opcion1=1;
         break;
      case 2:
         printf("Se invertira por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invertir_n_elem_left(l,elem);
         opcion1=2;
         break;
      case 3:
         printf("Se invertira por derecha: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invertir_n_elem_right(l,elem);
         opcion1=3;
         break;
      case 4:
      default :
         break;
    }
    if(opcion1==4||(opcion1!=1&&opcion1!=2&&opcion1!=3))  break;
  }
}

void Menu_generar(Lista *l)
{
  char opcion;
  int opcion1,elem;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Generar lista:");
    printf("\n 1. Generar por derecha");
    printf("\n 2. Generar por izquierda");
    printf("\n 3. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Se generara por derecha: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generar_lista_right(l,elem);
         opcion1=1;
         break;
      case 2:
         printf("Se generara por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generar_lista_left(l,elem);
         opcion1=2;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_insert(Lista *l)
{
  char opcion,item,info;
  int opcion1,dato;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Insertar:");
    printf("\n 1. Insertar por derecha");
    printf("\n 2. Insertar por izquierda");
    printf("\n 3. Insertar antes de un elemento X");
    printf("\n 4. Insertar despues de un elemento X");
    printf("\n 5. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a insertar por derecha: \n");
         strrcbff(&item,3);
         Lista_insert_right(l,item);
         opcion1=1;
         break;
      case 2:
         printf("Ingrese elemento a insertar por izquierda: \n");
         strrcbff(&item,3);
         Lista_insert_left(l,item);
         opcion1=2;
         break;
      case 3:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&info,3);
         Lista_insert_antes_info(l,item,info);
         opcion1=3;
         break;
      case 4:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&info,3);
         Lista_insert_despues_info(l,item,info);
         opcion1=4;
         break;
      case 5:
      default :
         break;
    }
    if(opcion1==5||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4))  break;
  }
}

void Menu_delet(Lista *l)
{
  char opcion,item,info;
  int opcion1;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Eliminar:");
    printf("\n 1. Eliminar por derecha");
    printf("\n 2. Eliminar por izquierda");
    printf("\n 3. Eliminar un elemento X");
    printf("\n 4. Eliminar antes de un elemento X");
    printf("\n 5. Eliminar despues de un elemento X");
    printf("\n 6. Eliminar elementos repetidos ");
    printf("\n 7. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         item=Lista_delet_right(l);
         opcion1=1;
         break;
      case 2:
         item=Lista_delet_left(l);
         opcion1=2;
         break;
      case 3:
         printf("Eliminar el elemento \"X\" : \n");
         strrcbff(&info,2);
         Lista_delet_info(l,info);
         opcion1=3;
         break;
      case 4:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(&info,2);
         item=Lista_delet_antes_info(l,info);
         opcion1=4;
         break;
      case 5:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(&info,2);
         item=Lista_delet_despues_info(l,info);
         opcion1=5;
         break;
      case 6:
         printf("Se eliminaran los elementos repetidos \n");
         Lista_delet_elem_rep(l);
         opcion1=6;
         break;
      case 7:
      default :
         break;
    }
    if(opcion1==7||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4&&opcion1!=5&&opcion1!=6))  break;
  }
}

int main()
{
  char opcion,info;
  int opcion1,m;
  Lista lista;
  Ocurr ocurr;
  Crear_lista(&lista);
  Crear_lista_ocurr(&ocurr);
  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n\n Menu Principal:");
    printf("\n 1. Menu Generar");
    printf("\n 2. Menu Insertar");
    printf("\n 3. Menu Eliminar");
    printf("\n 4. Menu Invertir");
    printf("\n 5. Buscar Elemento");
    printf("\n 6. Numero de elementos de la lista");
    printf("\n 7. Numero de elementos-ocurrencia de la lista");
    printf("\n 8. Imprimir lista");
    printf("\n 9. Destruir lista");
    printf("\n10. Ordenar lista");
    printf("\n11. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         Menu_generar(&lista);
         break;
      case 2:
         Menu_insert(&lista);
         break;
      case 3:
         Menu_delet(&lista);
         break;
      case 4:
         Menu_invertir(&lista);
         break;
      case 5:
         printf("Elemento \"X\" a buscar : \n");
         strrcbff(&info,2);
         Buscar_elem_lista(lista,info);
         break;
      case 6:
         m=Num_elem_lista();
         printf("\nEl numero de elementos de la lista es: %i\n",m);
         break;
      case 7:
         Ocurr_elem_lista(lista,&ocurr);
         Lista_ocurr_print(ocurr);
         break;
      case 8:
         Lista_print(lista);
         break;
      case 9:
         printf("La lista se destruira!!\n");
         Destruir_lista(&lista);
         break;
      case 10:
        Ordenar_lista(&lista);
        break;
      case 11:
      default :
         exit(0);
    }
  }
  return 0;
}
