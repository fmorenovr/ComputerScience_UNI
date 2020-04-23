/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Simple Linked List Functions              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "SLL.h"

// ------------------------------------------------//

// str string r read c clean bff buffer

int strrcbff(char *str, int n)
{
  int i, c;
  c=getchar();
  if (c == EOF)
  {
    str[0] = '\0';
    return 0; // end of file, termina
  }
  else if (c == '\n')  i = 0; // si es salto de linea, en cero
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

void Create_sllist(Sllist *l)
{
  *l=NULL;
}

Sllist Create_sllist_sgte()
{
  Sllist l;
  l=(Sllist)malloc(sizeof(sllist));
  return l;
}

void Destroy_sllist(Sllist *l)
{
  Sllist aux;
  while(*l!=NULL)
  {
    aux=*l;
    *l=(*l)->sgte;
    free(aux);
  }
}

void Create_sllistf(Sllistf *o)
{
  *o=NULL;
}

Sllistf Create_sllistf_sgte()
{
  Sllistf o;
  o=(Sllistf)malloc(sizeof(sllistf));
  return o;
}

void Destroy_sllistf(Sllistf *o)
{
  Sllistf aux;
  while(*o!=NULL)
  {
    aux=*o;
    *o=(*o)->sgte;
    free(aux);
  }
}

int isSllist_empty(Sllist l)
{
  return (l==NULL);
}

int isNumber(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0);
}

void Generate_sllist_left(Sllist *l,int n)
{
  Destroy_sllist(l);
  printf("List de %i elementos\n",n);
  int i=0,j;
  char in[1],cad;
  for(i=0;i<n;i++)
  {
    strrcbff(in,2);
    if(!isNumber(in))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      j=atoi(in);
      cad=(char)(j+48);
      Sllist_insert_init(l,cad);
    }
  }
}

void Generate_sllist_right(Sllist *l,int n)
{
  Destroy_sllist(l);
  printf("List de %i elementos\n",n);
  int i=0,j;
  char in[1],cad;
  for(i=0;i<n;i++)
  {
    strrcbff(in,2);
    if(!isNumber(in))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      j=atoi(in);
      cad=(char)(j+48);
      Sllist_insert_last(l,cad);
    }
  }
}

/* OTRA FORMA usando strrcbff

int isNumber(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

void Generate_sllist_left(Sllist *l,int n)
{
  printf("List de %i elementos\n",n);
  int i=0;
  char in[n+1],cad;
  strrcbff(in,n+1);
  for(i=0;i<n;i++)
  {
    if(!isNumber(in[i]))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      if(in[i]=='-')
      {
        cad='-';
      }
      else
      {
        cad=in[i];
      }
      Sllist_insert_init(l,cad);
    }
  }
}

void Generate_sllist_right(Sllist *l,int n)
{
  printf("List de %i elementos\n",n);
  int i=0;
  char in[n+1],cad;
  strrcbff(in,n+1);
  for(i=0;i<n;i++)
  {
    if(!isNumber(in[i]))
    {
      printf("Error de ingreso\n");
      break;
    }
    else
    {
      if(in[i]=='-')
      {
        cad='-';
      }
      else
      {
        cad=in[i];
      }
      Sllist_insert_last(l,cad);
    }
  }
}

*/

void Sllist_insert_init(Sllist *l,char dato)
{
  if(*l==NULL)
  {
    *l=Create_sllist_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Sllist aux;
    aux=Create_sllist_sgte();
    aux->sgte=*l;
    aux->elem=dato;
    *l=aux;
  }
}

void Sllist_insert_last(Sllist *l,char dato)
{
  if(*l==NULL)
  {
    *l=Create_sllist_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Sllist aux,aux1;
    aux=*l;
    while(aux->sgte!=NULL)
      aux=aux->sgte;
    aux1=Create_sllist_sgte();
    aux1->elem=dato;
    aux1->sgte=NULL;
    aux->sgte=aux1;
  }
}

void Sllist_insert_before_val(Sllist *l,char dato,char val)
{
  int band;
  Sllist q,t;
  q=*l;
  band=1;
  if(q==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    band=0;
  }
  else
  {
    while(q->elem!=val && band==1)
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
      Sllist r;
      r=Create_sllist_sgte();
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
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

void Sllist_insert_after_val(Sllist *l,char dato,char val)
{
  int band;
  Sllist q;
  q=*l;
  band=1;
  if(q==NULL)
  {
    band=0;
    printf("List vacia\nNo hay elementos\n");
  }
  else
  {
    while(q->elem!=val && band==1)
    {
      if(q->sgte!=NULL) q=q->sgte;
      else  band=0;
    }
    if(band==1)
    {
      Sllist t=Create_sllist_sgte();
      t->elem=dato;
      t->sgte=q->sgte;
      q->sgte=t;
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

char Sllist_delete_init(Sllist *l)
{
  char dato=' ';
  Sllist aux;
  aux = *l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else{
    dato=aux->elem;
    *l=aux->sgte;
    printf("El elemento eliminado es: %c\n",dato);
  }
  free(aux);
  return dato;
}

char Sllist_delete_last(Sllist *l)
{
  char dato=' ';
  Sllist aux,aux1;
  aux=*l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if(aux->sgte==NULL)
  {
    dato=aux->elem;
    *l=aux->sgte;
    printf("El elemento eliminado es: %c\n",dato);
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
  }
  free(aux);
  return dato;
}

char Sllist_delete_val(Sllist *l,char val)
{
  int band;
  char dato=' ';
  Sllist aux,aux1;
  aux=*l;
  band=1;
  if(aux==NULL)
  {
    printf("List vacia\n no hay elementos\n");
    dato=' ';
  }
  else if(aux->elem!=val && aux->sgte==NULL)
  {
    printf("No se encontro elemento\n");
  }
  else if(aux->elem==val)
  {
    dato=aux->elem;
    *l=aux->sgte;
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else
  {
    while(aux->elem!=val && band==1)
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
      free(aux);
    }
  }
  return dato;
}

char Sllist_delete_before_val(Sllist *l,char val)
{
  char dato=' ';
  int band=1;
  Sllist aux,aux1,aux2;
  aux=*l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  } //vacio CORRECTO

  else if(aux->elem==val)
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  else if(aux->elem!=val && aux->sgte==NULL)
  {
    printf("Elemento unico!\n");
    printf("No encontrado\n");
    dato=' ';
  } // primero elemento CORRECTO

  else if(aux->sgte->elem==val)
  {
    dato = aux->elem;
    *l=aux->sgte;
    printf("Elemento eliminado es %c\n",dato);
    free(aux);
  }
  else if(aux->sgte->sgte==NULL && aux->sgte->elem!=val)
  {
    printf("No se encontro elemento!\n");
    dato=' ';
  } // 2 elementos

  else // de 3 a mas CORRECTO
  {
    aux1=aux; // primero
    aux2=aux->sgte; // segundo
    aux=aux->sgte->sgte; // tercero
    while(aux->elem!=val && band==1)
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
      free(aux2);
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

char Sllist_delete_after_val(Sllist *l,char val)
{
  char dato=' ';
  int band=1;
  Sllist aux,aux1,aux2;
  aux=*l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if(aux->elem==val && aux->sgte==NULL)
  {
    printf("Solo tiene un elemento\n");
  }
  else if(aux->elem!=val && aux->sgte==NULL)
  {
    printf("No encontro el elemento\n");
  }
  else
  {
    while(aux->elem!=val && band==1)
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
        free(aux1);
      }
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

void Sllist_delete_elem_rep(Sllist *l)
{
  Sllist p,q,aux,temp;
  p=q=aux=*l;
  if(aux==NULL)  printf("List vacia!!\n");
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

void Search_elem_sllist(Sllist l,char val)
{
  Sllist aux;
  aux=l;
  while(aux!=NULL && (aux->elem!=val))
    aux=aux->sgte;
  if(aux==NULL) printf("Elemento NO encontrado\n");
  else  printf("Elemento Encontrado\n");
}

void Sllist_elem_frecuency(Sllist l,Sllistf *o)
{
  Sllist p;
  Sllistf temp,prev;
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
      temp=Create_sllistf_sgte();
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


int Num_elem_sllist(Sllist l)
{
  int numelem=0;
  while(l!=NULL)
  {
    l=l->sgte;
    numelem++;
  }
  return numelem;
}

void Order_sllist(Sllist *l)
{
  char temp;
  if(*l == NULL)  printf("List vacia !!\n");
  else if((*l)->sgte==NULL) printf("Solo tiene 1 elemento !!\n");
  else
  {
    Sllist actual=*l;
    Sllist nxt=actual->sgte;
    
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
}

void Invert_sllist(Sllist *l)
{
  Sllist *aux;
  aux=l; // aux apunta a lo que l apunta *aux es *l que es el contenido de la list original
        // es decir que aux se le da la direccion de memoria de l, que es la direccion de memoria
        // de la list original
  Sllist temp,prev;
  if((*aux)==NULL)  printf("List vacia\n");
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

void Invert_n_elem_last(Sllist *l,int n)
{
  Invert_sllist(l);
  Invert_n_elem_init(l,n);
  Invert_sllist(l);
}

void Invert_n_elem_init(Sllist *l,int n)
{
  int m=Num_elem_sllist(*l);
  if(n==m)  Invert_sllist(l);
  else if(m<n) printf("La list no tiene tantos elementos\n");
  else // m>n
  {
    if(n==0) printf("No se cambia nada\n");
    else if(n==1 && n<m)
    {
      printf("En en vano invertir solo el primer nodo\n");
    }
    else if(n==2)
    {
      Sllist *aux,prev,temp;
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
      Sllist *aux,temp,prev,liga;
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

void Sllist_print(Sllist l)
{
  Sllist aux;
  aux = l;
  while (aux != NULL)
  {
    printf("(%c)-->", aux->elem);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("NULL\n");
}

void Sllistf_print(Sllistf o)
{
  printf("*****\n  Number\tOccurence\n*****\n");
  while (o != NULL)
  {
    printf("    %c\t\t%d\n", o->elem, o->times);
    o=o->sgte;
  }
}

void Menu_invert(Sllist *l)
{
  char opcion[2];
  int opcion1,elem;

  for(;;)
  {
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Menu Invertir list:");
    printf("\n 1. Invertir list");
    printf("\n 2. Invertir n primeros elementos del inicio");
    printf("\n 3. Invertir n primeros elementos del final");
    printf("\n 4. Exit");
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,4);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         printf("Se invertira la list: \n");
         Invert_sllist(l);
         opcion1=1;
         break;
      case 2:
         printf("Se invertira por el inicio: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_init(l,elem);
         opcion1=2;
         break;
      case 3:
         printf("Se invertira por el final: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_last(l,elem);
         opcion1=3;
         break;
      case 4:
      default :
         break;
    }
    if(opcion1==4||(opcion1!=1&&opcion1!=2&&opcion1!=3))  break;
  }
}

void Menu_generate(Sllist *l)
{
  char opcion[2];
  int opcion1,elem;

  for(;;)
  {
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Menu Generar list:");
    printf("\n 1. Generar por derecha");
    printf("\n 2. Generar por izquierda");
    printf("\n 3. Exit");
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,4);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         printf("Se generara por derecha: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generate_sllist_right(l,elem);
         opcion1=1;
         break;
      case 2:
         printf("Se generara por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generate_sllist_left(l,elem);
         opcion1=2;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_insert(Sllist *l)
{
  char opcion[2],item[2],val[2];
  int opcion1,dato;

  for(;;)
  {
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Menu Insertar:");
    printf("\n 1. Insertar por el final");
    printf("\n 2. Insertar por el inicio");
    printf("\n 3. Insertar antes de un elemento X");
    printf("\n 4. Insertar despues de un elemento X");
    printf("\n 5. Exit");
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,4);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a insertar por el final: \n");
         strrcbff(item,3);
         Sllist_insert_last(l,item[0]);
         opcion1=1;
         break;
      case 2:
         printf("Ingrese elemento a insertar por el inicio: \n");
         strrcbff(item,3);
         Sllist_insert_init(l,item[0]);
         opcion1=2;
         break;
      case 3:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(item,3);
         printf("del elemento X : \n");
         strrcbff(val,3);
         Sllist_insert_before_val(l,item[0],val[0]);
         opcion1=3;
         break;
      case 4:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(item,3);
         printf("del elemento X : \n");
         strrcbff(val,3);
         Sllist_insert_after_val(l,item[0],val[0]);
         opcion1=4;
         break;
      case 5:
      default :
         break;
    }
    if(opcion1==5||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4))  break;
  }
}

void Menu_delete(Sllist *l)
{
  char opcion[2],item,info,cad[2];
  int opcion1;

  for(;;)
  {
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Menu Eliminar:");
    printf("\n 1. Eliminar por el final");
    printf("\n 2. Eliminar por el inicio");
    printf("\n 3. Eliminar un elemento X");
    printf("\n 4. Eliminar antes de un elemento X");
    printf("\n 5. Eliminar despues de un elemento X");
    printf("\n 6. Eliminar elementos repetidos ");
    printf("\n 7. Exit");
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,4);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         item=Sllist_delete_last(l);
         opcion1=1;
         break;
      case 2:
         item=Sllist_delete_init(l);
         opcion1=2;
         break;
      case 3:
         printf("Eliminar el elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         Sllist_delete_val(l,info);
         opcion1=3;
         break;
      case 4:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         item=Sllist_delete_before_val(l,info);
         opcion1=4;
         break;
      case 5:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         item=Sllist_delete_after_val(l,info);
         opcion1=5;
         break;
      case 6:
         printf("Se eliminaran los elementos repetidos \n");
         Sllist_delete_elem_rep(l);
         opcion1=6;
         break;
      case 7:
      default :
         break;
    }
    if(opcion1==7||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4&&opcion1!=5&&opcion1!=6))  break;
  }
}

void Menu_SLLmain()
{
  
  char opcion[2],info,cad[2];
  int opcion1,m=0;
  Sllist list;
  Sllistf listf;
  Create_sllist(&list);
  Create_sllistf(&listf);
  for(;;)
  {
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n\n Menu Principal:");
    printf("\n 1. Menu Generar");
    printf("\n 2. Menu Insertar");
    printf("\n 3. Menu Eliminar");
    printf("\n 4. Menu Invertir");
    printf("\n 5. Buscar Elemento");
    printf("\n 6. Numero de elementos de la lista");
    printf("\n 7. Numero de elementos-frecuencia de la lista");
    printf("\n 8. Imprimir list");
    printf("\n 9. Destruir list");
    printf("\n10. Ordenar list");
    printf("\n11. Exit");
    printf("\n---------------------------------------------");
    printf("\n---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(opcion,4);
    opcion1=atoi(opcion);
    switch (opcion1)
    {
      case 1:
         Menu_generate(&list);
         break;
      case 2:
         Menu_insert(&list);
         break;
      case 3:
         Menu_delete(&list);
         break;
      case 4:
         Menu_invert(&list);
         break;
      case 5:
         printf("Elemento \"X\" a buscar : \n");
         strrcbff(cad,3);
         info=cad[0];
         Search_elem_sllist(list,info);
         break;
      case 6:
         m=Num_elem_sllist(list);
         printf("\nEl numero de elementos de la lista es: %i\n",m);
         break;
      case 7:
         listf=NULL;
         Sllist_elem_frecuency(list,&listf);
         Sllistf_print(listf);
         break;
      case 8:
         Sllist_print(list);
         break;
      case 9:
         printf("La list se destruira!!\n");
         Destroy_sllist(&list);
         break;
      case 10:
        Order_sllist(&list);
        break;
      case 11:
      default :
         exit(0);
    }
  }
}
