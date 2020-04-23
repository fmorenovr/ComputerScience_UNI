/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Double Linked List Functions              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

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

void Create_dllist(Dllist *l,Dllist *q)
{
  (*l)=NULL; // apuntador al principio
  (*q)=NULL; // apuntador al final
}

Dllist Create_dllist_sgte()
{
  Dllist aux=(Dllist)malloc(sizeof(dllist)); // reserva memoria para un nodito 
  return aux;
}

void Destroy_dllist(Dllist *l,Dllist *q)
{
  Dllist aux;
  if((*l) !=NULL)
  {
    if((*l)->prev==NULL) // apuntador nodo inicial
    {
      while(*l!=NULL)
      {
        aux=*l;
        *l=(*l)->sgte;
        free(aux);
      }
    }
    else if((*l)->sgte==NULL) // apuntador nodo final
    {
      while(*l!=NULL)
      {
        aux=*l;
        *l=(*l)->prev;
        free(aux);
      }
    }
  }
  *q=*l;
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

int isDllist_empty(Dllist l,Dllist q)
{
  return (l==NULL && q==NULL);
}

int isNumber(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0);
}

void Generate_dllist_left(Dllist *l,Dllist *q,int n)
{
  Destroy_dllist(l,q); // ya sea que ingrese por final o derecha 
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
      Dllist_insert_init(l,q,cad);
    }
  }
}

void Generate_dllist_right(Dllist *l,Dllist *q,int n)
{
  Destroy_dllist(l,q);
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
      Dllist_insert_last(l,q,cad);
    }
  }
}
/*
// OTRA FORMA usando strrcbff

int isNumber(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

void Generate_dllist_left(Dllist *l,Dllist *q,int n)
{
  Destroy_dllist(l,q);
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
      Dllist_insert_init(l,q,cad);
    }
  }
}

void Generate_dllist_right(Dllist *l,Dllist *q,int n)
{
  Destroy_dllist(l,q);
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
      Dllist_insert_last(l,q,cad);
    }
  }
}

*/

void Dllist_insert_init(Dllist *l,Dllist *q,char dato)
{
  if(*l==NULL && *q ==NULL)
  {
    *l=Create_dllist_sgte();
    (*l)->sgte=NULL;
    (*l)->prev=NULL;
    (*l)->elem=dato;
    (*q)=(*l);
  }
  else
  {
    Dllist aux;
    aux=Create_dllist_sgte();
    aux->sgte=*l;
    (*l)->prev=aux;
    aux->prev=NULL;
    aux->elem=dato;
    *l=aux;
  }
}

void Dllist_insert_last(Dllist *l,Dllist *q,char dato)
{
  // *l es el apuntador al inicio y *q es el apuntador al final
  if(*l==NULL && *q ==NULL)
  {
    *q=Create_dllist_sgte();
    (*q)->sgte=NULL;
    (*q)->prev=NULL;
    (*q)->elem=dato;
    (*l)=(*q);
  }
  else
  {
    Dllist aux;
    aux=Create_dllist_sgte();
    aux->prev=*q;
    (*q)->sgte=aux;
    aux->sgte=NULL;
    aux->elem=dato;
    *q=aux;
  }
}

void Dllist_insert_before_val_init(Dllist *l,Dllist *p,char dato,char val)
{
  int band;
  Dllist q;
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
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Dllist r;
      r=Create_dllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->sgte=*p;
        r->prev=NULL;
        (*p)->prev=r;
        (*l)=r;
      }
      else if(*l==q) // el primer nodo
      {
        r->sgte=(*l);
        r->prev=(*l)->prev;
        (*l)->prev=r;
        (*l)=r;
      }
      else
      {
        r->sgte=q;
        r->prev=q->prev;
        q->prev->sgte=r;
        q->prev=r;
      }
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

void Dllist_insert_after_val_init(Dllist *l,Dllist *p,char dato,char val)
{
  int band;
  Dllist q;
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
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Dllist r;
      r=Create_dllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->prev=*l;
        r->sgte=NULL;
        (*l)->sgte=r;
        (*p)=r;
      }
      else if(q==(*p))
      {
        r->prev=(*p);
        r->sgte=(*p)->sgte;
        (*p)->sgte=r;
        (*p)=r;
      }
      else
      {
        r->prev=q;
        r->sgte=q->sgte;
        q->sgte->prev=r;
        q->sgte=r;
      }
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

void Dllist_insert_before_val_last(Dllist *l,Dllist *p,char dato,char val)
{
  int band;
  Dllist q;
  q=*p;
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
      if(q->prev!=NULL)
      {
        q=q->prev;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Dllist r;
      r=Create_dllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->prev=*l;
        r->sgte=NULL;
        (*l)->sgte=r;
        (*p)=r;
      }
      else if(*p==q) // el primer nodo desde el final
      {
        r->prev=(*p);
        r->sgte=(*p)->sgte;
        (*p)->sgte=r;
        (*p)=r;
      }
      else
      {
        r->prev=q;
        r->sgte=q->sgte;
        q->sgte->prev=r;
        q->sgte=r;
      }
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

void Dllist_insert_after_val_last(Dllist *l,Dllist *p,char dato,char val)
{
  int band;
  Dllist q;
  q=*p;
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
      if(q->prev!=NULL)
      {
        q=q->prev;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      Dllist r;
      r=Create_dllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->sgte=*p;
        r->prev=NULL;
        (*p)->prev=r;
        (*l)=r;
      }
      else if(q==(*l))
      {
        r->sgte=(*l);
        r->prev=(*l)->prev;
        (*l)->prev=r;
        (*l)=r;
      }
      else
      {
        r->sgte=q;
        r->prev=q->prev;
        q->prev->sgte=r;
        q->prev=r;
      }
      printf("\nSe inserto correctamente\n");
    }
    else  printf("\nNo se encontro el elemento %c\n",val);
  }
}

char Dllist_delete_init(Dllist *l,Dllist *q)
{
  char dato;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if((*l)==(*q)&&(*l)!=NULL)
  {
    dato=(*l)->elem;
    (*l)=NULL;
    (*q)=NULL;
    printf("El elemento eliminado es: %c\n",dato);
  }
  else{
    dato=(*l)->elem;
    (*l)=(*l)->sgte;
    (*l)->prev=NULL;
    printf("El elemento eliminado es: %c\n",dato);
  }
  return dato;
}

char Dllist_delete_last(Dllist *l,Dllist *q)
{
  char dato;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if((*l)==(*q)&&(*l)!=NULL)
  {
    dato=(*q)->elem;
    (*l)=NULL;
    (*q)=NULL;
    printf("El elemento eliminado es: %c\n",dato);
  }
  else{
    dato=(*q)->elem;
    (*q)=(*q)->prev;
    (*q)->sgte=NULL;
    printf("El elemento eliminado es: %c\n",dato);
  }
  return dato;
}

char Dllist_delete_val(Dllist *l,Dllist *q,char val)
{
  int band;
  char dato;
  band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia no hay elementos\n");
    dato=' ';
  }
  else if((*q)==(*l) && (*l)->elem==val)
  {
    dato=(*q)->elem;
    (*l)=(*q)=NULL;
    printf("El elemento eliminado es: %c\n",dato);
  }
  else if((*q)==(*l) && (*l)->elem!=val)
  {
    printf("Elemento no encontrado\n");
    dato=' ';
  }
  else if((*l)->elem==val && (*l)!=(*q))
  {
    dato=(*l)->elem;
    *l=(*l)->sgte;
    (*l)->prev=NULL;
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else if((*q)->elem==val && (*l)!=(*q))
  {
    dato=(*q)->elem;
    *q=(*q)->prev;
    (*q)->sgte=NULL;
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else
  {
    Dllist aux;
    aux=(*l);
    while(aux->elem!=val && band==1)
    {
      if(aux->sgte!=(*q))
      {
        aux=aux->sgte;
      }
      else  band=0;
    }
    if(band==0) printf("No se encontro Elemento\n");
    else
    {
      dato=aux->elem;
      aux->prev->sgte=aux->sgte;
      aux->sgte->prev=aux->sgte;
      free(aux);
      printf("Se elimino correctamente\n");
      printf("El elemento eliminado es: %c\n",dato);
    }
  }
  return dato;
}

void Dllist_delete_elem_rep(Dllist *r,Dllist *s)
{
  Dllist p,q,aux,temp;
  p=q=aux=(*r);
  if((*r)==NULL && (*s==NULL))  printf("List vacia!!\n");
  else if((*r)==(*s) && (*r)!=NULL) printf("Solo tiene un elemento!! \n");
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
          if(q->sgte!=NULL)  q->sgte->prev=aux;
          else (*s)=aux;
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

char Dllist_delete_before_val_init(Dllist *l,Dllist *q,char val)
{
  char dato=' ';
  int band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  } //vacio CORRECTO

  else if((*l)->elem==val) // primer elemento
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }

  else if((*l)->sgte->elem==val)
  {
    dato = (*l)->elem;
    *l=(*l)->sgte;
    (*l)->prev=NULL;
    printf("Elemento eliminado es %c\n",dato);
  }
  else if((*l)->sgte==(*q) &&(*q)->elem!=val && (*l)->elem!=val)
  {
    printf("No se encontro Elemento\n");
  }
  else // de 3 a mas CORRECTO
  {
    Dllist aux;
    aux=*l;
    aux=aux->sgte->sgte; // tercero
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
      dato=aux->prev->elem;
      aux->prev->prev->sgte=aux;
      aux->prev=aux->prev->prev;
      printf("Se elimino correctamente\n");
      printf("El elemento eliminado es: %c\n",dato);
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

char Dllist_delete_before_val_last(Dllist *l,Dllist *q,char val)
{
  char dato;
  int band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  } //vacio CORRECTO

  else if((*q)->elem==val) // primer elemento
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }

  else if((*q)->prev->elem==val)
  {
    dato = (*q)->elem;
    *q=(*q)->prev;
    (*q)->sgte=NULL;
    printf("Elemento eliminado es %c\n",dato);
  }
  else if((*q)->prev==(*l) &&(*q)->elem!=val && (*l)->elem!=val)
  {
    printf("No se encontro Elemento\n");
  }
  else // de 3 a mas CORRECTO
  {
    Dllist aux;
    aux=*q;
    aux=aux->prev->prev; // tercero
    while(aux->elem!=val && band==1)
    {
      if(aux->prev!=NULL)
      {
        aux=aux->prev;
      }
      else  band=0;
    }
    if(band==1)
    {
      dato=aux->sgte->elem;
      aux->sgte->sgte->prev=aux;
      aux->sgte=aux->sgte->sgte;
      printf("Se elimino correctamente\n");
      printf("El elemento eliminado es: %c\n",dato);
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

char Dllist_delete_after_val_init(Dllist *l,Dllist *q,char val)
{
  char dato;
  int band=1;
  Dllist aux;
  aux=*l;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if((*l)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*l)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  else if((*l)->elem==val && (*l)->sgte==(*q))
  {
    dato = (*q)->elem;
    (*l)->sgte=NULL;
    (*q)=(*l);
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
        dato=aux->sgte->elem;
        aux->sgte->sgte->prev=aux;
        aux->sgte=aux->sgte->sgte;
        printf("Se elimino correctamente\n");
        printf("El elemento eliminado es: %c\n",dato);
      }
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

char Dllist_delete_after_val_last(Dllist *l,Dllist *q,char val)
{
  char dato;
  int band=1;
  Dllist aux;
  aux=*q;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
    dato=' ';
  }
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
    dato=' ';
  }
  else if((*q)->elem==val && (*q)->prev==(*l))
  {
    dato = (*l)->elem;
    (*q)->prev=NULL;
    (*l)=(*q);
  }
  else
  {
    while(aux->elem!=val && band==1)
    {
      if(aux->prev!=NULL)
      {
        aux=aux->prev;
      }
      else  band=0;
    }
    if(band==1)
    {
      if(aux->prev==NULL)
      {
        printf("No hay elementos por eliminar!!\n");
      }
      else
      {
        dato=aux->prev->elem;
        aux->prev->prev->sgte=aux;
        aux->prev=aux->prev->prev;
        printf("Se elimino correctamente\n");
        printf("El elemento eliminado es: %c\n",dato);
      }
    }
    else  printf("No se encontro Elemento\n");
  }
  return dato;
}

void Search_elem_dllist(Dllist l,Dllist q,char val)
{
  Dllist aux;
  aux=l;
  while(aux!=NULL && (aux->elem!=val))
    aux=aux->sgte;
  if(aux==NULL) printf("Elemento NO encontrado\n");
  else  printf("Elemento Encontrado\n");
}

void Dllist_elem_frecuency(Dllist l,Dllist q,Sllistf *o)
{
  Dllist p;
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

int Num_elem_dllist(Dllist l)
{
  if(l==NULL) printf("Lista vacia\n");
  else
  {
    int numelem=0;
    while(l!=NULL)
    {
      l=l->sgte;
      numelem++;
    }
    return numelem;
  }
}

void Order_dllist(Dllist l,Dllist q)
{
  char temp;
  if(l == NULL && (q) == (l))  printf("List vacia !!\n");
  else if((l)->sgte==NULL && (q)->prev==NULL && (q) == (l)) printf("Solo tiene 1 elemento !!\n");
  else
  {
    Dllist actual=l;
    Dllist nxt=actual->sgte;
    
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

void Invert_dllist(Dllist *l,Dllist *q)
{
  Dllist temp,pre;
  if((*l)==NULL && (*q)==NULL)  printf("List vacia\n");
  else if((*l)->sgte==NULL && (*l)==(*q)) printf("Invertir un solo nodo es en vano\n");
  else if((*q)->sgte==NULL && (*l)->prev==NULL && (*l)->sgte==(*q))
  {
    temp=(*l);
    (*q)->sgte=temp;
    (*q)->prev=NULL;
    temp->prev=(*q);
    temp->sgte=NULL;
    (*l)=(*q);
    (*q)=temp;
  }
  else
  {
    Dllist *aux;
    aux=l;
    pre=(*aux);
    temp=(*aux)->sgte;
    (*aux) = (*aux)->sgte->sgte;
    pre->sgte = NULL;
    while ((*aux)->sgte !=NULL)
    {
      temp->sgte = pre;
      pre->prev=temp;
      if(pre->sgte==NULL) (*q)=pre;
      pre = temp;
      temp = (*aux);
      (*aux) = (*aux)->sgte;
    }
    temp->sgte = pre;
    pre->prev=temp;
    temp->prev=(*aux);
    (*aux)->sgte = temp;
    (*aux)->prev=NULL;
  }
}

void Invert_n_elem_init(Dllist *l,Dllist*q,int n)
{
  int m=Num_elem_dllist(*l);
  if(n==m)  Invert_dllist(l,q);
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
      Dllist *aux,pre,temp;
      aux=l; // aux apunta a lo que apunta l
      pre=(*aux);
      temp=(*aux)->sgte;
      (*aux)=(*aux)->sgte->sgte;
      temp->sgte=pre;
      temp->prev=NULL;
      pre->prev=temp;
      pre->sgte=(*aux);
      (*aux)->prev=pre;
      (*aux)=temp;
    }
    else if(n>=3)
    {
      int i;
      Dllist *aux,temp,pre,liga;
      aux=l;
      pre=(*aux);
      temp=(*aux)->sgte;
      (*aux) = (*aux)->sgte->sgte;
      liga=pre;
      temp->sgte=liga;
      liga->prev=temp;
      i=2;
      while (i<n)
      {
        pre=temp;
        temp = (*aux);
        (*aux) = (*aux)->sgte;
        temp->sgte=pre;
        pre->prev=temp;
        i++;
      }
      liga->sgte = (*aux);
      (*aux)->prev=liga;
      temp->prev=NULL;
      (*aux)=temp;
    }
  }
}

void Invert_n_elem_last(Dllist *l,Dllist*q,int n)
{
  int m=Num_elem_dllist(*l);
  if(n==m)  Invert_dllist(l,q);
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
      Dllist *aux,pre,temp;
      aux=q; // aux apunta a lo que apunta l
      pre=(*aux);
      temp=(*aux)->prev;
      (*aux)=(*aux)->prev->prev;
      temp->prev=pre;
      temp->sgte=NULL;
      pre->sgte=temp;
      pre->prev=(*aux);
      (*aux)->sgte=pre;
      (*aux)=temp;
    }
    else if(n>=3)
    {
      int i;
      Dllist *aux,temp,pre,liga;
      aux=q;
      pre=(*aux);
      temp=(*aux)->prev;
      (*aux) = (*aux)->prev->prev;
      liga=pre;
      temp->prev=liga;
      liga->sgte=temp;
      i=2;
      while (i<n)
      {
        pre=temp;
        temp = (*aux);
        (*aux) = (*aux)->prev;
        temp->prev=pre;
        pre->sgte=temp;
        i++;
      }
      liga->prev = (*aux);
      (*aux)->sgte=liga;
      temp->sgte=NULL;
      (*aux)=temp;
    }
  }
}

void Dllist_print_init(Dllist l)
{
  if(l==NULL) printf("NULL\n");
  else
  {
    Dllist aux;
    aux = l;
    printf("NULL<--");
    while (aux != NULL)
    {
      printf("(%c)", aux->elem);
      aux = aux->sgte;
      if(aux!=NULL) printf("<-->");
    }
    if (aux == NULL) printf("-->NULL\n");
  }
}

void Dllist_print_last(Dllist l)
{
  if(l==NULL) printf("NULL\n");
  else
  {
    Dllist aux;
    aux = l;
    printf("NULL<--");
    while (aux != NULL)
    {
      printf("(%c)", aux->elem);
      aux = aux->prev;
      if(aux!=NULL) printf("<-->");
    }
    if (aux == NULL) printf("-->NULL\n");
  }
}

void Sllistf_print(Sllistf o)
{
  if(o==NULL) printf("Lista vacia\n");
  else
  {
    printf("*****\n  Number\tOccurence\n*****\n");
    while (o != NULL)
    {
      printf("    %c\t\t%d\n", o->elem, o->times);
      o=o->sgte;
    }
  }
}

void Menu_invert(Dllist *l,Dllist *q)
{
  char opcion;
  int opcion1,elem;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Invertir list:");
    printf("\n 1. Invertir list");
    printf("\n 2. Invertir n primeros elementos desde inicio");
    printf("\n 3. Invertir n primeros elementos desde final");
    printf("\n 4. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Se invertira la list: \n");
         Invert_dllist(l,q);
         opcion1=1;
         break;
      case 2:
         printf("Se invertira por el inicio: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_init(l,q,elem);
         opcion1=2;
         break;
      case 3:
         printf("Se invertira por el final: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_last(l,q,elem);
         opcion1=3;
         break;
      case 4:
      default :
         break;
    }
    if(opcion1==4||(opcion1!=1&&opcion1!=2&&opcion1!=3))  break;
  }
}

void Menu_generate(Dllist *l,Dllist *q)
{
  char opcion;
  int opcion1,elem;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Generar list:");
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
         Generate_dllist_right(l,q,elem);
         opcion1=1;
         break;
      case 2:
         printf("Se generara por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generate_dllist_left(l,q,elem);
         opcion1=2;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_insert(Dllist *l,Dllist *q)
{
  char opcion,item,val;
  int opcion1,dato;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Insertar:");
    printf("\n 1. Insertar por el inicio");
    printf("\n 2. Insertar por el final");
    printf("\n 3. Insertar antes de un elemento X desde el inicio");
    printf("\n 4. Insertar despues de un elemento X desde el inicio");
    printf("\n 5. Insertar antes de un elemento X desde el final");
    printf("\n 6. Insertar despues de un elemento X desde el final");
    printf("\n 7. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         printf("Ingrese elemento a insertar por el inicio : \n");
         strrcbff(&item,3);
         Dllist_insert_init(l,q,item);
         opcion1=1;
         break;
      case 2:
         printf("Ingrese elemento a insertar por el final: \n");
         strrcbff(&item,3);
         Dllist_insert_last(l,q,item);
         opcion1=2;
         break;
      case 3:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         Dllist_insert_before_val_init(l,q,item,val);
         opcion1=3;
         break;
      case 4:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         Dllist_insert_after_val_init(l,q,item,val);
         opcion1=4;
         break;
      case 5:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         Dllist_insert_before_val_last(l,q,item,val);
         opcion1=3;
         break;
      case 6:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         Dllist_insert_after_val_last(l,q,item,val);
         opcion1=4;
         break;
      case 7:
      default :
         break;
    }
    if(opcion1==5||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4))  break;
  }
}

void Menu_delete(Dllist *l,Dllist *q)
{
  char opcion,item,val;
  int opcion1;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Eliminar:");
    printf("\n 1. Eliminar por el inicio");
    printf("\n 2. Eliminar por el final");
    printf("\n 3. Eliminar un elemento X ");
    printf("\n 4. Eliminar antes de un elemento X desde el inicio");
    printf("\n 5. Eliminar despues de un elemento X desde el inicio");
    printf("\n 6. Eliminar antes de un elemento X desde el final");
    printf("\n 7. Eliminar despues de un elemento X desde el final");
    printf("\n 8. Eliminar elementos repetidos ");
    printf("\n 9. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         item=Dllist_delete_init(l,q);
         opcion1=1;
         break;
      case 2:
         item=Dllist_delete_last(l,q);
         opcion1=2;
         break;
      case 3:
         printf("Eliminar el elemento \"X\" : \n");
         strrcbff(&val,2);
         Dllist_delete_val(l,q,val);
         opcion1=3;
         break;
      case 4:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=Dllist_delete_before_val_init(l,q,val);
         opcion1=4;
         break;
      case 5:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=Dllist_delete_after_val_init(l,q,val);
         opcion1=5;
         break;
      case 6:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=Dllist_delete_before_val_last(l,q,val);
         opcion1=4;
         break;
      case 7:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=Dllist_delete_after_val_last(l,q,val);
         opcion1=5;
         break;
      case 8:
         printf("Se eliminaran los elementos repetidos \n");
         Dllist_delete_elem_rep(l,q);
         opcion1=6;
         break;
      case 9:
      default :
         break;
    }
    if(opcion1==7||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4&&opcion1!=5&&opcion1!=6))  break;
  }
}

void Menu_print(Dllist l,Dllist q)
{
  char opcion;
  int opcion1,elem;

  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n Menu Imprimir list:");
    printf("\n 1. Imprimir desde el inicio");
    printf("\n 2. Imprimir desde el final");
    printf("\n 3. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         Dllist_print_init(l);
         opcion1=1;
         break;
      case 2:
         Dllist_print_last(q);
         opcion1=2;
         break;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_DLLmain()
{
  char opcion,info;
  int opcion1,m=0;
  Dllist init,last;
  Sllistf listf;
  Create_dllist(&init,&last);
  Create_sllistf(&listf);
  for(;;)
  {
    printf("---------------------------------------------");
    printf("\n\n Menu Principal:");
    printf("\n 1. Menu Generar");
    printf("\n 2. Menu Insertar");
    printf("\n 3. Menu Eliminar");
    printf("\n 4. Menu Invertir");
    printf("\n 5. Menu Imprimir");
    printf("\n 6. Buscar Elemento");
    printf("\n 7. Numero de elementos de la lista");
    printf("\n 8. Numero de elementos-frecuencia de la lista");
    printf("\n 9. Destruir list");
    printf("\n10. Ordenar list");
    printf("\n11. Exit");
    printf("---------------------------------------------");
    printf("\n Ingresa opcion : \n");
    strrcbff(&opcion,4);
    opcion1=atoi(&opcion);
    switch (opcion1)
    {
      case 1:
         Menu_generate(&init,&last);
         break;
      case 2:
         Menu_insert(&init,&last);
         break;
      case 3:
         Menu_delete(&init,&last);
         break;
      case 4:
         Menu_invert(&init,&last);
         break;
      case 5:
         Menu_print(init,last);
         break;
      case 6:
         printf("Elemento \"X\" a buscar : \n");
         strrcbff(&info,2);
         Search_elem_dllist(init,last,info);
         break;
      case 7:
         m=Num_elem_dllist(init);
         printf("\nEl numero de elementos de la lista es: %i\n",m);
         break;
      case 8:
         listf=NULL;
         Dllist_elem_frecuency(init,last,&listf);
         Sllistf_print(listf);
         break;
      case 9:
         printf("La list se destruira!!\n");
         Destroy_dllist(&init,&last);
         break;
      case 10:
        Order_dllist(init,last);
        break;
      case 11:
      default :
         exit(0);
    }
  }
}
