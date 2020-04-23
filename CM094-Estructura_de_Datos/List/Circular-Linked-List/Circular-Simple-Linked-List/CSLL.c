/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Circular Simple Linked List Functions     ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "CSLL.h"

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

void Create_csllist(Csllist *l)
{
  (*l)=Create_csllist_sgte();
  (*l)->sgte=NULL;
  (*l)->elem='~';
}

Csllist Create_csllist_sgte()
{
  Csllist l;
  l=(Csllist)malloc(sizeof(csllist));
  return l;
}

void Destroy_csllist(Csllist *cabeza,Csllist *l)
{
  Csllist aux;
  while(*l!=(*cabeza)&&*l!=NULL)
  {
    aux=*l;
    *l=(*l)->sgte;
    free(aux);
  }
  (*cabeza)->sgte=NULL;
}

int isCsllist_empty(Csllist l)
{
  return (l->sgte==NULL);
}

void Create_csllistf(Csllistf *o)
{
  *o=NULL;
}

Csllistf Create_csllistf_sgte()
{
  Csllistf o;
  o=(Csllistf)malloc(sizeof(csllistf));
  return o;
}

void Destroy_csllistf(Csllistf *o)
{
  Csllistf aux;
  while(*o!=NULL)
  {
    aux=*o;
    *o=(*o)->sgte;
    free(aux);
  }
}

int isNumber(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0);
}

void Generate_csllist_left(Csllist *q,Csllist *l,int n)
{
  Destroy_csllist(q,l);
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
      Csllist_insert_init(q,l,cad);
    }
  }
}

void Generate_csllist_right(Csllist *q,Csllist *l,int n)
{
  Destroy_csllist(q,l);
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
      Csllist_insert_last(q,l,cad);
    }
  }
}

/* OTRA FORMA usando strrcbff

int isNumber(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

void Generate_csllist_left(Csllist *q,Csllist *l,int n)
{
  Destroy_csllist(q,l);
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
      Csllist_insert_init(q,l,cad);
    }
  }
}

void Generate_csllist_right(Csllist *q,Csllist *l,int n)
{
  
  Destroy_csllist(q,l);
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
      Csllist_insert_last(q,l,cad);
    }
  }
}

*/

void Csllist_insert_init(Csllist *cabeza,Csllist *l,char dato)
{
  if(*l==NULL)
  {
    *l=Create_csllist_sgte();
    (*cabeza)->sgte=*l;
    (*l)->sgte=(*cabeza);
    (*l)->elem=dato;
  }
  else
  {
    Csllist aux;
    aux=Create_csllist_sgte();
    aux->sgte=*l;
    aux->elem=dato;
    *l=aux;
    (*cabeza)->sgte=(*l);
  }
}

void Csllist_insert_last(Csllist *cabeza,Csllist *l,char dato)
{
  if((*l)==NULL)
  {
    *l=Create_csllist_sgte();
    (*cabeza)->sgte=(*l);
    (*l)->sgte=(*cabeza);
    (*l)->elem=dato;
  }
  else
  {
    Csllist aux,aux1;
    aux=*l;
    while(aux->sgte!=(*cabeza))
      aux=aux->sgte;
    aux1=Create_csllist_sgte();
    aux1->elem=dato;
    aux1->sgte=(*cabeza);
    aux->sgte=aux1;
  }
}

void Csllist_insert_before_val(Csllist *cabeza,Csllist *l,char dato,char val)
{
  int band;
  Csllist q,t;
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
      if(q->sgte!=(*cabeza))
      {
        t=q;
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Csllist r;
      r=Create_csllist_sgte();
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

void Csllist_insert_after_val(Csllist *cabeza,Csllist *l,char dato,char val)
{
  int band;
  Csllist q;
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
      if(q->sgte!=(*cabeza)) q=q->sgte;
      else  band=0;
    }
    if(band==1)
    {
      Csllist t=Create_csllist_sgte();
      t->elem=dato;
      t->sgte=q->sgte;
      q->sgte=t;
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

char Csllist_delete_init(Csllist *cabeza,Csllist *l)
{
  char dato=' ';
  Csllist aux;
  aux = *l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  }
  else{
    dato=aux->elem;
    if(aux->sgte==(*cabeza))  *l=NULL;
    else  *l=aux->sgte;
    (*cabeza)->sgte=(*l);
    printf("El elemento eliminado es: %c\n",dato);
  }
  free(aux);
  return dato;
}

char Csllist_delete_last(Csllist *cabeza,Csllist *l)
{
  char dato=' ';
  Csllist aux,aux1;
  aux=*l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  }
  else if(aux->sgte==(*cabeza))
  {
    dato=aux->elem;
    *l=NULL;
    (*cabeza)->sgte=(*l);
    printf("El elemento eliminado es: %c\n",dato);
  }
  else
  {
    while(aux->sgte!=(*cabeza))
    {
      aux1=aux;
      aux=aux->sgte;
    }
    dato=aux->elem;
    aux1->sgte=(*cabeza);
    printf("El elemento eliminado es: %c\n",dato);
  }
  free(aux);
  return dato;
}

char Csllist_delete_val(Csllist *cabeza,Csllist *l,char val)
{
  int band;
  char dato=' ';
  Csllist aux,aux1;
  aux=*l;
  band=1;
  if(aux==NULL)
  {
    printf("List vacia\n no hay elementos\n");
    dato=' ';
  }
  else if(aux->elem!=val && aux->sgte==(*cabeza))
  {
    printf("No se encontro elemento\n");
  }
  else if(aux->elem==val && aux->sgte==(*cabeza))
  {
    dato=aux->elem;
    (*l)=NULL;
    (*cabeza)->sgte=(*l);
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else if(aux->elem==val && aux->sgte->sgte!=(*cabeza))
  {
    dato=aux->elem;
    (*l)=aux->sgte;
    (*cabeza)->sgte=(*l);
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else
  {
    while(aux->elem!=val && band==1)
    {
      if(aux->sgte!=(*cabeza))
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
    printf("El elemento eliminado es: %c\n",dato);
      free(aux);
    }
  }
  return dato;
}

char Csllist_delete_before_val(Csllist *cabeza,Csllist *l,char val)
{
  char dato=' ';
  int band=1;
  Csllist aux,aux1,aux2;
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
  else if(aux->elem!=val && aux->sgte==(*cabeza))
  {
    printf("Elemento unico!\n");
    printf("No encontrado\n");
    dato=' ';
  } // primero elemento CORRECTO

  else if(aux->sgte->elem==val)
  {
    dato = aux->elem;
    *l=aux->sgte;
    (*cabeza)->sgte=(*l);
    printf("Se elimino correctamente\n");
    printf("Elemento eliminado es %c\n",dato);
    free(aux);
  }
  else if(aux->sgte->sgte==(*cabeza) && aux->sgte->elem!=val)
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
      if(aux->sgte!=(*cabeza))
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

char Csllist_delete_after_val(Csllist *cabeza,Csllist *l,char val)
{
  char dato=' ';
  int band=1;
  Csllist aux,aux1,aux2;
  aux=*l;
  if(aux==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  }
  else if(aux->elem==val && aux->sgte==(*cabeza))
  {
    printf("Solo tiene un elemento\n");
  }
  else if(aux->elem!=val && aux->sgte==(*cabeza))
  {
    printf("No encontro el elemento\n");
  }
  else
  {
    while(aux->elem!=val && band==1)
    {
      if(aux->sgte!=(*cabeza))
      {
        aux=aux->sgte;
      }
      else  band=0;
    }
    if(band==1)
    {
      if(aux->sgte==(*cabeza))
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

void Csllist_delete_elem_rep(Csllist *cabeza,Csllist *l)
{
  Csllist p,q,aux,temp;
  p=q=aux=*l;
  if(aux==NULL)  printf("List vacia!!\n");
  else if(aux->sgte==(*cabeza)) printf("Solo tiene un elemento!! \n");
  else
  {
    q=q->sgte;
    while(p!=(*cabeza))
    {
      aux=p;
      while(q!=(*cabeza))
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
      if(p->sgte==(*cabeza))
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

void Search_elem_csllist(Csllist cabeza,Csllist l,char val)
{
  Csllist aux;
  aux=l;
  while(aux!=cabeza && (aux->elem!=val))
    aux=aux->sgte;
  if(aux==cabeza) printf("Elemento NO encontrado\n");
  else  printf("Elemento Encontrado\n");
}

void Csllist_elem_frecuency(Csllist cabeza,Csllist l,Csllistf *o)
{
  Csllist p;
  Csllistf temp,prev;
  p=l;
  if(p!=NULL)
  {
    while(p!=cabeza)
    {
      temp=(*o);
      while(temp!=NULL && temp->elem != p->elem)
      {
        prev=temp;
        temp=temp->sgte;
      }
      if(temp==NULL)
      {
        temp=Create_csllistf_sgte();
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
}

int Num_elem_csllist(Csllist cabeza,Csllist l)
{
  int numelem=0;
  while(l!=cabeza)
  {
    l=l->sgte;
    numelem++;
  }
  return numelem;
}

void Order_csllist(Csllist *cabeza,Csllist *l)
{
  char temp;
  if(*l == NULL)  printf("List vacia !!\n");
  else if((*l)->sgte==(*cabeza)) printf("Solo tiene 1 elemento !!\n");
  else
  {
    Csllist actual=*l;
    Csllist nxt=actual->sgte;
    
    while(actual->sgte!=(*cabeza))
    {
      while(nxt!=(*cabeza))
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

void Invert_csllist(Csllist *cabeza,Csllist *l)
{
  Csllist *aux;
  aux=l; // aux apunta a lo que l apunta *aux es *l que es el contenido de la list original
        // es decir que aux se le da la direccion de memoria de l, que es la direccion de memoria
        // de la list original
  Csllist temp,prev;
  if((*aux)==NULL)  printf("List vacia\n");
  else if((*aux)->sgte==(*cabeza)) printf("Invertir un solo nodo es en vano\n");
  else if((*aux)->sgte->sgte==(*cabeza))
  {
    (*aux)->sgte->sgte=(*aux);
    (*aux)=(*aux)->sgte;
    (*aux)->sgte->sgte=(*cabeza);
    (*cabeza)->sgte=(*aux);
  }
  else
  {
    prev=(*aux);
    temp=(*aux)->sgte;
    (*aux) = (*aux)->sgte->sgte;
    prev->sgte = (*cabeza);
    while ((*aux)->sgte != (*cabeza))
    {
      temp->sgte = prev;
      prev = temp;
      temp = (*aux);
      (*aux) = (*aux)->sgte;
    }
    temp->sgte = prev;
    (*aux)->sgte = temp;
    (*cabeza)->sgte=(*aux);
  }
  // *aux = *l ya fueron invertidos ya que sus contenidos que es el mismo
  // porque apuntan a la misma direccion de memoria
}

void Invert_n_elem_last(Csllist *cabeza,Csllist *l,int n)
{
  Invert_csllist(cabeza,l);
  Invert_n_elem_init(cabeza,l,n);
  Invert_csllist(cabeza,l);
}

void Invert_n_elem_init(Csllist *cabeza,Csllist *l,int n)
{
  int m=Num_elem_csllist(*cabeza,*l);
  if(n==m)  Invert_csllist(cabeza,l);
  else if(m<n) printf("La list no tiene tantos elementos\n");
  else // m>n
  {
    if(n==0) printf("No se cambia nada\n");
    else if(n==1)
    {
      printf("En en vano invertir solo el primer nodo\n");
    }
    else if(n==2)
    {
      Csllist *aux,prev,temp;
      aux=l; // aux apunta a lo que apunta l
      prev=(*aux);
      temp=(*aux)->sgte;
      (*aux)=(*aux)->sgte->sgte;
      temp->sgte=prev;
      prev->sgte=(*aux);
      (*aux)=temp;
      (*cabeza)->sgte=(*aux);
    }
    else if(n>=3)
    {
      int i;
      Csllist *aux,temp,prev,liga;
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
      (*cabeza)->sgte=(*aux);
      //  *aux = *l ya fueron invertidos ya que sus contenidos que es el mismo
      // porque apuntan a la misma direccion de memoria
    }
  }
}

void Csllist_print(Csllist l,Csllist q)
{
  Csllist aux;
  aux = q;
  printf("T.nil-->");
  if(aux!=NULL)
  {
    while (aux->sgte != l)
    {
      printf("(%c)-->", aux->elem);
      aux = aux->sgte;
    }
    printf("(%c)\n", aux->elem);
  }
  else  printf("\n");
  //------------------------------//
  aux = q;
  printf("^       ");
  if(aux!=NULL)
  {
    while (aux->sgte != l)
    {
      printf("      ");
      aux = aux->sgte;
    }
    printf("  |\n");
  }
  else  printf("|\n");
  //------------------------------//
  aux = q;
  printf("|---<--");
  if(aux!=NULL)
  {
    while (aux->sgte != l)
    {
      printf("--<---");
      aux = aux->sgte;
    }
    printf("---v\n");
  }
  else  printf("-v\n");
}

void Csllistf_print(Csllistf o)
{
  printf("*****\n  Number\tOccurence\n*****\n");
  while (o != NULL)
  {
    printf("    %c\t\t%d\n", o->elem, o->times);
    o=o->sgte;
  }
}

void Menu_invert(Csllist *cabeza,Csllist *l)
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
         Invert_csllist(cabeza,l);
         Csllist_print(*cabeza,*l);
         opcion1=1;
         break;
      case 2:
         printf("Se invertira por el inicio: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_init(cabeza,l,elem);
         Csllist_print(*cabeza,*l);
         opcion1=2;
         break;
      case 3:
         printf("Se invertira por el final: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_last(cabeza,l,elem);
         Csllist_print(*cabeza,*l);
         opcion1=3;
         break;
      case 4:
      default :
         break;
    }
    if(opcion1==4||(opcion1!=1&&opcion1!=2&&opcion1!=3))  break;
  }
}

void Menu_generate(Csllist *cabeza,Csllist *l)
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
         Generate_csllist_right(cabeza,l,elem);
         Csllist_print(*cabeza,*l);
         opcion1=1;
         break;
      case 2:
         printf("Se generara por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generate_csllist_left(cabeza,l,elem);
         Csllist_print(*cabeza,*l);
         opcion1=2;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_insert(Csllist *cabeza,Csllist *l)
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
         Csllist_insert_last(cabeza,l,item[0]);
         Csllist_print(*cabeza,*l);
         opcion1=1;
         break;
      case 2:
         printf("Ingrese elemento a insertar por el inicio: \n");
         strrcbff(item,3);
         Csllist_insert_init(cabeza,l,item[0]);
         Csllist_print(*cabeza,*l);
         opcion1=2;
         break;
      case 3:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(item,3);
         printf("del elemento X : \n");
         strrcbff(val,3);
         Csllist_insert_before_val(cabeza,l,item[0],val[0]);
         Csllist_print(*cabeza,*l);
         opcion1=3;
         break;
      case 4:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(item,3);
         printf("del elemento X : \n");
         strrcbff(val,3);
         Csllist_insert_after_val(cabeza,l,item[0],val[0]);
         Csllist_print(*cabeza,*l);
         opcion1=4;
         break;
      case 5:
      default :
         break;
    }
    if(opcion1==5||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4))  break;
  }
}

void Menu_delete(Csllist *cabeza,Csllist *l)
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
         item=Csllist_delete_last(cabeza,l);
         Csllist_print(*cabeza,*l);
         opcion1=1;
         break;
      case 2:
         item=Csllist_delete_init(cabeza,l);
         Csllist_print(*cabeza,*l);
         opcion1=2;
         break;
      case 3:
         printf("Eliminar el elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         Csllist_delete_val(cabeza,l,info);
         Csllist_print(*cabeza,*l);
         opcion1=3;
         break;
      case 4:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         item=Csllist_delete_before_val(cabeza,l,info);
         Csllist_print(*cabeza,*l);
         opcion1=4;
         break;
      case 5:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(cad,3);
         info=cad[0];
         item=Csllist_delete_after_val(cabeza,l,info);
         Csllist_print(*cabeza,*l);
         opcion1=5;
         break;
      case 6:
         printf("Se eliminaran los elementos repetidos \n");
         Csllist_delete_elem_rep(cabeza,l);
         Csllist_print(*cabeza,*l);
         opcion1=6;
         break;
      case 7:
      default :
         break;
    }
    if(opcion1==7||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4&&opcion1!=5&&opcion1!=6))  break;
  }
}

void Menu_CSLLmain()
{
  
  char opcion[2],info,cad[2];
  int opcion1,m=0;
  Csllist list;
  Csllistf listf;
  Create_csllist(&list);
  Create_csllistf(&listf);
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
         Menu_generate(&list,&(list->sgte));
         break;
      case 2:
         Menu_insert(&list,&(list->sgte));
         break;
      case 3:
         Menu_delete(&list,&(list->sgte));
         break;
      case 4:
         Menu_invert(&list,&(list->sgte));
         break;
      case 5:
         printf("Elemento \"X\" a buscar : \n");
         strrcbff(cad,3);
         info=cad[0];
         Search_elem_csllist(list,list->sgte,info);
         break;
      case 6:
         m=Num_elem_csllist(list,list->sgte);
         printf("\nEl numero de elementos de la lista es: %i\n",m);
         break;
      case 7:
         listf=NULL;
         Csllist_elem_frecuency(list,list->sgte,&listf);
         Csllistf_print(listf);
         break;
      case 8:
         Csllist_print(list,list->sgte);
         break;
      case 9:
         printf("La list se destruira!!\n");
         Destroy_csllist(&list,&(list->sgte));
         break;
      case 10:
        Order_csllist(&list,&(list->sgte));
        break;
      case 11:
      default :
         exit(0);
    }
  }
}
