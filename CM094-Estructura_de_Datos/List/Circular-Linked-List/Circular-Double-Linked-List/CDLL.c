/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###       Circular Double Linked List Functions      ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "CDLL.h"

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

void Create_cdllist(CDllist *l)
{
  (*l)=Create_cdllist_sgte();
  (*l)->sgte=NULL;
  (*l)->prev=NULL;
  (*l)->elem='~';
}

CDllist Create_cdllist_sgte()
{
  CDllist aux=(CDllist)malloc(sizeof(cdllist));
  return aux;
}

void Destroy_cdllist(CDllist *cabeza,CDllist *l,CDllist *q)
{
  CDllist aux;
  if((*l) !=(*cabeza)&&*l!=NULL)
  {
    if((*l)->prev==(*cabeza)) // apuntador nodo inicial
    {
      while(*l!=(*cabeza))
      {
        aux=*l;
        *l=(*l)->sgte;
        free(aux);
      }
    }
    else if((*l)->sgte==(*cabeza)) // apuntador nodo final
    {
      while(*l!=(*cabeza))
      {
        aux=*l;
        *l=(*l)->prev;
        free(aux);
      }
    }
  }
  *q=*l=NULL;
  (*cabeza)->sgte=NULL;
  (*cabeza)->prev=NULL;
}

int isCDllist_empty(CDllist l)
{
  return (l->sgte==NULL && l->prev==NULL);
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

int isNumber(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0);
}

void Generate_cdllist_left(CDllist *cabeza,CDllist *l,CDllist *q,int n)
{
  Destroy_cdllist(cabeza,l,q); // ya sea que ingrese por final o derecha 
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
      CDllist_insert_init(cabeza,l,q,cad);
    }
  }
}

void Generate_cdllist_right(CDllist *cabeza,CDllist *l,CDllist *q,int n)
{
  Destroy_cdllist(cabeza,l,q);
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
      CDllist_insert_last(cabeza,l,q,cad);
    }
  }
}
/*
// OTRA FORMA usando strrcbff

int isNumber(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

void Generate_cdllist_left(CDllist *cabeza,CDllist *l,CDllist *q,int n)
{
  Destroy_cdllist(cabeza,l,q);
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
      CDllist_insert_init(cabeza,l,q,cad);
    }
  }
}

void Generate_cdllist_right(CDllist *cabeza,CDllist *l,CDllist *q,int n)
{
  Destroy_cdllist(cabeza,l,q);
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
      CDllist_insert_last(cabeza,l,q,cad);
    }
  }
}

*/

void CDllist_insert_init(CDllist *cabeza,CDllist *l,CDllist *q,char dato)
{
  if(*l==NULL && *q ==NULL)
  {
    *l=Create_cdllist_sgte();
    (*cabeza)->sgte=*l;
    (*l)->prev=(*cabeza);
    (*l)->elem=dato;
    (*l)->sgte=(*cabeza);
    (*l)->elem=dato;
    (*q)=(*l);
    (*cabeza)->prev=*q;
  }
  else
  {
    CDllist aux;
    aux=Create_cdllist_sgte();
    aux->sgte=*l;
    (*l)->prev=aux;
    aux->prev=(*cabeza);
    aux->elem=dato;
    (*cabeza)->sgte=aux;
    *l=aux;
  }
}

void CDllist_insert_last(CDllist *cabeza,CDllist *l,CDllist *q,char dato)
{
  // *l es el apuntador al inicio y *q es el apuntador al final
  if(*l==NULL && *q ==NULL)
  {
    *q=Create_cdllist_sgte();
    (*cabeza)->sgte=*q;
    (*q)->prev=(*cabeza);
    (*q)->elem=dato;
    (*q)->sgte=(*cabeza);
    (*q)->elem=dato;
    (*l)=(*q);
    (*cabeza)->prev=*q;
  }
  else
  {
    CDllist aux;
    aux=Create_cdllist_sgte();
    aux->prev=*q;
    (*q)->sgte=aux;
    aux->sgte=(*cabeza);
    aux->elem=dato;
    (*cabeza)->prev=aux;
    *q=aux;
  }
}

void CDllist_insert_before_val_init(CDllist *cabeza,CDllist *l,CDllist *p,char dato,char val)
{
  int band;
  CDllist q;
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
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      CDllist r;
      r=Create_cdllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->sgte=*p;
        r->prev=(*cabeza);
        (*cabeza)->sgte=r;
        (*p)->prev=r;
        (*l)=r;
      }
      else if(*l==q) // primer nodo
      {
        r->sgte=*l;
        r->prev=(*cabeza);
        (*l)->prev=r;
        (*l)=r;
        (*cabeza)->sgte=(*l);
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

void CDllist_insert_after_val_init(CDllist *cabeza,CDllist *l,CDllist *p,char dato,char val)
{
  int band;
  CDllist q;
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
        q=q->sgte;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      CDllist r;
      r=Create_cdllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->prev=*l;
        r->sgte=(*cabeza);
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

void CDllist_insert_before_val_last(CDllist *cabeza,CDllist *l,CDllist *p,char dato,char val)
{
  int band;
  CDllist q;
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
      if(q->prev!=(*cabeza))
      {
        q=q->prev;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      CDllist r;
      r=Create_cdllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->prev=*l;
        r->sgte=(*cabeza);
        (*l)->sgte=r;
        (*cabeza)->sgte=(*l);
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

void CDllist_insert_after_val_last(CDllist *cabeza,CDllist *l,CDllist *p,char dato,char val)
{
  int band;
  CDllist q;
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
      if(q->prev!=(*cabeza))
      {
        q=q->prev;
      }
      else  band=0; //significa que llego al final y no encontro info
    }
    if(band==1)
    {
      CDllist r;
      r=Create_cdllist_sgte();
      r->elem=dato;
      if(*l==q && *p==q) // un nodo
      {
        r->sgte=*p;
        r->prev=(*cabeza);
        (*p)->prev=r;
        (*l)=r;
        (*cabeza)->sgte=(*l);
      }
      else if(q==(*l))
      {
        r->sgte=(*l);
        r->prev=(*l)->prev;
        (*l)->prev=r;
        (*l)=r;
        (*cabeza)->sgte=(*l);
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

void CDllist_delete_elem_rep(CDllist *cabeza,CDllist *r,CDllist *s)
{
  CDllist p,q,aux,temp;
  p=q=aux=(*r);
  if((*r)==NULL && (*s==NULL))  printf("List vacia!!\n");
  else if((*r)==(*s) && (*r)!=NULL) printf("Solo tiene un elemento!! \n");
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
          if(q->sgte!=(*cabeza))  q->sgte->prev=aux;
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

void Order_cdllist(CDllist cabeza,CDllist l,CDllist q)
{
  char temp;
  if(l == NULL && (q) == (l))  printf("List vacia !!\n");
  else if((l)->sgte==cabeza && (q)->prev==cabeza && (q) == (l)) printf("Solo tiene 1 elemento !!\n");
  else
  {
    CDllist actual=l;
    CDllist nxt=actual->sgte;
    
    while(actual->sgte!=cabeza)
    {
      while(nxt!=cabeza)
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

void CDllist_print_init(CDllist r,CDllist l)
{
  CDllist aux;
  aux = l;
  printf("^---->---");
  if(aux!=NULL)
  {
    while (aux->sgte != r)
    {
      printf("--->---");
      aux = aux->sgte;
    }
    printf("--|\n");
  }
  else  printf("-|\n");
  //------------------------------//
  aux = l;
  printf("|        ");
  if(aux!=NULL)
  {
    while (aux->sgte != r)
    {
      printf("       ");
      aux = aux->sgte;
    }
    printf("  v\n");
  }
  else  printf(" v\n");
  //------------------------------//
  aux = l;
  printf("T.nil<-->");
  if(aux!=NULL)
  {
    while (aux->sgte != r)
    {
      printf("(%c)<-->", aux->elem);
      aux = aux->sgte;
    }
    printf("(%c)\n", aux->elem);
  }
  else  printf("\n");
  //------------------------------//
  aux = l;
  printf("^        ");
  if(aux!=NULL)
  {
    while (aux->sgte != r)
    {
      printf("       ");
      aux = aux->sgte;
    }
    printf("  |\n");
  }
  else  printf(" |\n");
  //------------------------------//
  aux = l;
  printf("|----<---");
  if(aux!=NULL)
  {
    while (aux->sgte != r)
    {
      printf("---<---");
      aux = aux->sgte;
    }
    printf("--v\n");
  }
  else  printf("-v\n");
}

void CDllist_print_last(CDllist r,CDllist l)
{
  CDllist aux;
  aux = l;
  printf("^---->---");
  if(aux!=NULL)
  {
    while (aux->prev != r)
    {
      printf("--->---");
      aux = aux->prev;
    }
    printf("--|\n");
  }
  else  printf("-|\n");
  //------------------------------//
  aux = l;
  printf("|        ");
  if(aux!=NULL)
  {
    while (aux->prev != r)
    {
      printf("       ");
      aux = aux->prev;
    }
    printf("  v\n");
  }
  else  printf(" v\n");
  //------------------------------//
  aux = l;
  printf("T.nil<-->");
  if(aux!=NULL)
  {
    while (aux->prev != r)
    {
      printf("(%c)<-->", aux->elem);
      aux = aux->prev;
    }
    printf("(%c)\n", aux->elem);
  }
  else  printf("\n");
  //------------------------------//
  aux = l;
  printf("^        ");
  if(aux!=NULL)
  {
    while (aux->prev != r)
    {
      printf("       ");
      aux = aux->prev;
    }
    printf("  |\n");
  }
  else  printf(" |\n");
  //------------------------------//
  aux = l;
  printf("|----<---");
  if(aux!=NULL)
  {
    while (aux->prev != r)
    {
      printf("---<---");
      aux = aux->prev;
    }
    printf("--v\n");
  }
  else  printf("-v\n");
}

void CDllist_elem_frecuency(CDllist cabeza,CDllist l,Sllistf *o)
{
  CDllist p;
  Sllistf temp,prev;
  p=l;
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

int Num_elem_cdllist(CDllist cabeza,CDllist l)
{
  if(l==NULL) printf("Lista vacia\n");
  else
  {
    int numelem=0;
    while(l!=cabeza)
    {
      l=l->sgte;
      numelem++;
    }
    return numelem;
  }
}

void Search_elem_cdllist(CDllist cabeza,CDllist l,char val)
{
  CDllist aux;
  aux=l;
  while(aux!=cabeza && (aux->elem!=val))
    aux=aux->sgte;
  if(aux==cabeza) printf("Elemento NO encontrado\n");
  else  printf("Elemento Encontrado\n");
}

void Invert_cdllist(CDllist *cabeza,CDllist *l,CDllist *q)
{
  CDllist temp,pre;
  if((*l)==NULL && (*q)==NULL)  printf("List vacia\n");
  else if((*l)->sgte==(*cabeza) && (*l)==(*q)) printf("Invertir un solo nodo es en vano\n");
  else if((*q)->sgte==(*cabeza) && (*l)->prev==(*cabeza) && (*l)->sgte==(*q))
  {
    temp=(*l);
    (*q)->sgte=temp;
    (*q)->prev=(*cabeza);
    temp->prev=(*q);
    temp->sgte=(*cabeza);
    (*l)=(*q);
    (*q)=temp;
  }
  else
  {
    CDllist *aux;
    aux=l;
    pre=(*aux);
    temp=(*aux)->sgte;
    (*aux) = (*aux)->sgte->sgte;
    pre->sgte = (*cabeza);
    while ((*aux)->sgte !=(*cabeza))
    {
      temp->sgte = pre;
      pre->prev=temp;
      if(pre->sgte==(*cabeza)) (*q)=pre;
      pre = temp;
      temp = (*aux);
      (*aux) = (*aux)->sgte;
    }
    temp->sgte = pre;
    pre->prev=temp;
    temp->prev=(*aux);
    (*aux)->sgte = temp;
    (*aux)->prev=(*cabeza);
  }
}

void Invert_n_elem_last(CDllist *cabeza,CDllist *l,CDllist*q,int n)
{
  int m=Num_elem_cdllist(*cabeza,*l);
  if(n==m)  Invert_cdllist(cabeza,l,q);
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
      CDllist *aux,pre,temp;
      aux=q; // aux apunta a lo que apunta l
      pre=(*aux);
      temp=(*aux)->prev;
      (*aux)=(*aux)->prev->prev;
      temp->prev=pre;
      temp->sgte=(*cabeza);
      pre->sgte=temp;
      pre->prev=(*aux);
      (*aux)->sgte=pre;
      (*aux)=temp;
    }
    else if(n>=3)
    {
      int i;
      CDllist *aux,temp,pre,liga;
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
      temp->sgte=(*cabeza);
      (*aux)=temp;
    }
  }
}

void Invert_n_elem_init(CDllist *cabeza,CDllist *l,CDllist*q,int n)
{
  int m=Num_elem_cdllist(*cabeza,*l);
  if(n==m)  Invert_cdllist(cabeza,l,q);
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
      CDllist *aux,pre,temp;
      aux=l; // aux apunta a lo que apunta l
      pre=(*aux);
      temp=(*aux)->sgte;
      (*aux)=(*aux)->sgte->sgte;
      temp->sgte=pre;
      temp->prev=(*cabeza);
      pre->prev=temp;
      pre->sgte=(*aux);
      (*aux)->prev=pre;
      (*aux)=temp;
    }
    else if(n>=3)
    {
      int i;
      CDllist *aux,temp,pre,liga;
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
      temp->prev=(*cabeza);
      (*aux)=temp;
    }
  }
}

char CDllist_delete_init(CDllist *cabeza,CDllist *l,CDllist *q)
{
  char dato=' ';
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
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
    (*l)->prev=(*cabeza);
    (*cabeza)->sgte=(*l);
    printf("El elemento eliminado es: %c\n",dato);
  }
  return dato;
}

char CDllist_delete_last(CDllist *cabeza,CDllist *l,CDllist *q)
{
  char dato=' ';
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
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
    (*q)->sgte=(*cabeza);
    (*cabeza)->prev=(*q);
    printf("El elemento eliminado es: %c\n",dato);
  }
  return dato;
}

char CDllist_delete_val(CDllist *cabeza,CDllist *l,CDllist *q,char val)
{
  int band;
  char dato=' ';
  band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia no hay elementos\n");
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
  }
  else if((*l)->elem==val && (*l)!=(*q))
  {
    dato=(*l)->elem;
    *l=(*l)->sgte;
    (*l)->prev=(*cabeza);
    (*cabeza)->sgte=(*l);
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else if((*q)->elem==val && (*l)!=(*q))
  {
    dato=(*q)->elem;
    *q=(*q)->prev;
    (*q)->sgte=(*cabeza);
    (*cabeza)->prev=(*q);
    printf("Se elimino correctamente\n");
    printf("El elemento eliminado es: %c\n",dato);
  }
  else
  {
    CDllist aux;
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

char CDllist_delete_before_val_init(CDllist *cabeza,CDllist *l,CDllist *q,char val)
{
  char dato=' ';
  int band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  } //vacio CORRECTO

  else if((*l)->elem==val) // primer elemento
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }

  else if((*l)->sgte->elem==val)
  {
    dato = (*l)->elem;
    *l=(*l)->sgte;
    (*l)->prev=(*cabeza);
    (*cabeza)->sgte=*l;
    printf("Elemento eliminado es %c\n",dato);
  }
  else if((*l)->sgte==(*q) &&(*q)->elem!=val && (*l)->elem!=val)
  {
    printf("No se encontro Elemento\n");
  }
  else // de 3 a mas CORRECTO
  {
    CDllist aux;
    aux=*l;
    aux=aux->sgte->sgte; // tercero
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

char CDllist_delete_before_val_last(CDllist *cabeza,CDllist *l,CDllist *q,char val)
{
  char dato=' ';
  int band=1;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  } //vacio CORRECTO

  else if((*q)->elem==val) // primer elemento
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No se encontro elemento\n");
  }

  else if((*q)->prev->elem==val)
  {
    dato = (*q)->elem;
    *q=(*q)->prev;
    (*q)->sgte=(*cabeza);
    (*cabeza)->prev=*q;
    printf("Elemento eliminado es %c\n",dato);
  }
  else if((*q)->prev==(*l) &&(*q)->elem!=val && (*l)->elem!=val)
  {
    printf("No se encontro Elemento\n");
  }
  else // de 3 a mas CORRECTO
  {
    CDllist aux;
    aux=*q;
    aux=aux->prev->prev; // tercero
    while(aux->elem!=val && band==1)
    {
      if(aux->prev!=(*cabeza))
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

char CDllist_delete_after_val_init(CDllist *cabeza,CDllist *l,CDllist *q,char val)
{
  char dato=' ';
  int band=1;
  CDllist aux;
  aux=*l;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  }
  else if((*l)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*l)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  else if((*l)->elem==val && (*l)->sgte==(*q))
  {
    dato = (*q)->elem;
    (*l)->sgte=(*cabeza);
    (*cabeza)->prev=*l;
    (*q)=(*l);
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

char CDllist_delete_after_val_last(CDllist *cabeza,CDllist *l,CDllist *q,char val)
{
  char dato=' ';
  int band=1;
  CDllist aux;
  aux=*q;
  if((*l)==NULL && (*q)==NULL)
  {
    printf("List vacia\nNo hay elementos\n");
  }
  else if((*q)->elem==val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  
  else if((*q)->elem!=val && (*q)==(*l))
  {
    printf("No hay elementos por eliminar\n");
  }
  else if((*q)->elem==val && (*q)->prev==(*l))
  {
    dato = (*l)->elem;
    (*q)->prev=(*cabeza);
    (*cabeza)->sgte=(*q);
    (*l)=(*q);
  }
  else
  {
    while(aux->elem!=val && band==1)
    {
      if(aux->prev!=(*cabeza))
      {
        aux=aux->prev;
      }
      else  band=0;
    }
    if(band==1)
    {
      if(aux->prev==(*cabeza))
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

void Menu_invert(CDllist *cabeza,CDllist *l,CDllist *q)
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
         Invert_cdllist(cabeza,l,q);
         opcion1=1;
         break;
      case 2:
         printf("Se invertira por el inicio: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_init(cabeza,l,q,elem);
         opcion1=2;
         break;
      case 3:
         printf("Se invertira por el final: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Invert_n_elem_last(cabeza,l,q,elem);
         opcion1=3;
         break;
      case 4:
      default :
         break;
    }
    if(opcion1==4||(opcion1!=1&&opcion1!=2&&opcion1!=3))  break;
  }
}

void Menu_generate(CDllist *cabeza,CDllist *l,CDllist *q)
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
         Generate_cdllist_right(cabeza,l,q,elem);
         opcion1=1;
         break;
      case 2:
         printf("Se generara por izquierda: \n");
         printf("Ingrese Numero de elementos:\n");
         scanf("%i",&elem);
         Generate_cdllist_left(cabeza,l,q,elem);
         opcion1=2;
         break;
      case 3:
      default :
         break;
    }
    if(opcion1==3||(opcion1!=1&&opcion1!=2))  break;
  }
}

void Menu_insert(CDllist *cabeza,CDllist *l,CDllist *q)
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
         CDllist_insert_init(cabeza,l,q,item);
         opcion1=1;
         break;
      case 2:
         printf("Ingrese elemento a insertar por el final: \n");
         strrcbff(&item,3);
         CDllist_insert_last(cabeza,l,q,item);
         opcion1=2;
         break;
      case 3:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         CDllist_insert_before_val_init(cabeza,l,q,item,val);
         opcion1=3;
         break;
      case 4:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         CDllist_insert_after_val_init(cabeza,l,q,item,val);
         opcion1=4;
         break;
      case 5:
         printf("Ingrese elemento a insertar antes : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         CDllist_insert_before_val_last(cabeza,l,q,item,val);
         opcion1=3;
         break;
      case 6:
         printf("Ingrese elemento a insertar despues : \n");
         strrcbff(&item,3);
         printf("del elemento X : \n");
         strrcbff(&val,3);
         CDllist_insert_after_val_last(cabeza,l,q,item,val);
         opcion1=4;
         break;
      case 7:
      default :
         break;
    }
    if(opcion1==5||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4))  break;
  }
}

void Menu_print(CDllist cabeza,CDllist l,CDllist q)
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
         CDllist_print_init(cabeza,l);
         opcion1=1;
         break;
      case 2:
         CDllist_print_last(cabeza,q);
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

void Menu_delete(CDllist *cabeza,CDllist *l,CDllist *q)
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
         item=CDllist_delete_init(cabeza,l,q);
         opcion1=1;
         break;
      case 2:
         item=CDllist_delete_last(cabeza,l,q);
         opcion1=2;
         break;
      case 3:
         printf("Eliminar el elemento \"X\" : \n");
         strrcbff(&val,2);
         CDllist_delete_val(cabeza,l,q,val);
         opcion1=3;
         break;
      case 4:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=CDllist_delete_before_val_init(cabeza,l,q,val);
         opcion1=4;
         break;
      case 5:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=CDllist_delete_after_val_init(cabeza,l,q,val);
         opcion1=5;
         break;
      case 6:
         printf("Eliminar antes del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=CDllist_delete_before_val_last(cabeza,l,q,val);
         opcion1=4;
         break;
      case 7:
         printf("Eliminar despues del elemento \"X\" : \n");
         strrcbff(&val,2);
         item=CDllist_delete_after_val_last(cabeza,l,q,val);
         opcion1=5;
         break;
      case 8:
         printf("Se eliminaran los elementos repetidos \n");
         CDllist_delete_elem_rep(cabeza,l,q);
         opcion1=6;
         break;
      case 9:
      default :
         break;
    }
    if(opcion1==7||(opcion1!=1&&opcion1!=2&&opcion1!=3&&opcion1!=4&&opcion1!=5&&opcion1!=6))  break;
  }
}

void Menu_CDLLmain()
{
  char opcion,info;
  int opcion1,m=0;
  CDllist ring;
  Sllistf listf;
  Create_cdllist(&ring);
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
         Menu_generate(&ring,&(ring->sgte),&(ring->prev));
         break;
      case 2:
         Menu_insert(&ring,&(ring->sgte),&(ring->prev));
         break;
      case 3:
         Menu_delete(&ring,&(ring->sgte),&(ring->prev));
         break;
      case 4:
         Menu_invert(&ring,&(ring->sgte),&(ring->prev));
         break;
      case 5:
         Menu_print(ring,ring->sgte,ring->prev);
         break;
      case 6:
         printf("Elemento \"X\" a buscar : \n");
         strrcbff(&info,2);
         Search_elem_cdllist(ring,ring->sgte,info);
         break;
      case 7:
         m=Num_elem_cdllist(ring,ring->sgte);
         printf("\nEl numero de elementos de la lista es: %i\n",m);
         break;
      case 8:
         listf=NULL;
         CDllist_elem_frecuency(ring,ring->sgte,&listf);
         Sllistf_print(listf);
         break;
      case 9:
         printf("La list se destruira!!\n");
         Destroy_cdllist(&ring,&(ring->sgte),&(ring->prev));
         break;
      case 10:
        Order_cdllist(ring,ring->sgte,ring->prev);
        break;
      case 11:
      default :
         exit(0);
    }
  }
}
