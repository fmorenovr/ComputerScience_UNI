/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "nm_fun.h"


// -----------------------------------------------------------

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

void Crear_pila(Pila *l)
{
  *l=NULL;
}

int esPila_vacia(Pila l)
{
  return (l==NULL);
}

void Destruir_pila(Pila *l)
{
  Pila aux;
  while(*l!=NULL)
  {
    aux=*l;
    *l=(*l)->sgte;
    free(aux);
  }
}

Pila Crear_pila_sgte()
{
  Pila l;
  l=(Pila)malloc(sizeof(pila));
  return l;
}

Pila Invertir_pila(Pila *l)
{
  Pila *aux;
  aux=l;
  Pila temp,prev;
  if((*aux)==NULL)  printf("Pila vacia\n");
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
  return (*aux); // *aux = *l ya fueron invertidos sus contenidos que es el mismo
}

int Buscar_elem_pila(Pila l,char info)
{
  Pila aux;
  aux=l;
  while(aux!=NULL && (aux->elem!=info))
    aux=aux->sgte;
  if(aux==NULL)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*
int esNumero(char i[])
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0||strcmp(i,"-")==0);
}*/

int esNumero(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

int Generar_pila(Pila *l,int n)
{
  printf("Pila de %i elementos\n",n);
  int i=0,k=0;
  char in[n+1],cad;
  strrcbff(in,n+1);
  for(i=0;i<n;i++)
  {
    if(!esNumero(in[i]))
    {
      printf("\nError de ingreso\n");
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
      Pila_insert_left(l,cad);
    }
    k++;
  }
  return k;
}

void Pila_insert_left(Pila *l,char dato)
{
  if(*l==NULL)
  {
    *l=Crear_pila_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Pila aux;
    aux=Crear_pila_sgte();
    aux->sgte=*l;
    aux->elem=dato;
    *l=aux;
  }
}

char Pila_delet_right(Pila *l)
{
  char dato;
  Pila aux,aux1;
  aux=*l;
  if(aux==NULL)
  {
    dato=' ';
  }
  else if(aux->sgte==NULL)
  {
    dato=aux->elem;
    *l=aux->sgte;
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
  }
  free(aux);
  return dato;
}

void Pila_insert_right(Pila *l,char dato)
{
  if(*l==NULL)
  {
    *l=Crear_pila_sgte();
    (*l)->sgte=NULL;
    (*l)->elem=dato;
  }
  else
  {
    Pila aux,aux1;
    aux=*l;
    while(aux->sgte!=NULL)
      aux=aux->sgte;
    aux1=Crear_pila_sgte();
    aux1->elem=dato;
    aux1->sgte=NULL;
    aux->sgte=aux1;
  }
}

void Pila_print(Pila l)
{
  Pila aux;
  aux = l;
  while (aux != NULL)
  {
    printf("%c", aux->elem);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("\n");
}

void Completar_zeros(Pila *l,int n,int m)
{
  char cad='0';
  int i;
  for(i=0;i<(m-n);i++)
  {
    Pila_insert_right(l,cad);
  }
}

Pila Suma(Pila op_1,Pila op_2)
{
  Pila rpta=NULL;
  char cif;
  int ad1,ad2,carry=0,sum=0; // dec es el numero de decenas que llevamos en la suma
  while((op_1!=NULL)&&(op_2!=NULL))
  // while( op_1 && op_2 ) tambien sirve
  {
    ad1=(int)(op_1->elem)-48;
    ad2=(int)(op_2->elem)-48;
    
    sum=ad1+ad2+carry;
    carry = sum>=10; // devuelve el valor 1 verdadero 0 falso 
    if(carry) sum -= 10; 
    
    cif=(char)(sum + 48);
    Pila_insert_right(&rpta,cif);
    
    op_1=op_1->sgte;
    op_2=op_2->sgte;
  }
  if(carry)
  {
    Pila_insert_right(&rpta,'1');
  }
  return rpta;
}

Pila Resta(Pila op_1,Pila op_2)
{
  Pila rpta=NULL;
  char a,b;
  int cambio=0;
  op_1=Invertir_pila(&op_1);
  op_2=Invertir_pila(&op_2);
  Pila aux,aux1;
  aux=op_1;
  aux1=op_2;
  a=aux->elem;
  b=aux1->elem;
  if(a<b) cambio=1;
  else{
    while(a == b && (aux->sgte!=NULL&&aux1->sgte!=NULL)) // evaluamos quien es mayor xd
    {
      aux=aux->sgte;
      aux1=aux1->sgte;
      a=aux->elem;
      b=aux1->elem;
      if(a < b)  cambio=1;
    }
  }
  
  if(cambio==1) // hacemos cambiaso
  {
    aux = op_1;
    op_1=op_2;
    op_2=aux;
    cambio=1;
  }
  op_1=Invertir_pila(&op_1);
  op_2=Invertir_pila(&op_2);
  char cif;
  int ad1,ad2,carry=0,res=0;
  while((op_1!=NULL)&&(op_2!=NULL))
  {
    ad1=(int)(op_1->elem)-48;
    ad2=(int)(op_2->elem)-48;
    res=ad1-ad2+carry;;
    if(res<0)
    {
      if(op_1->sgte!=NULL && op_2->sgte!=NULL)
        res=res+10;
      else if(op_1->sgte==NULL && op_2->sgte==NULL)
        res=res*-1;
     carry=-1;
    }
    else carry =0;
    cif=(char)(res + 48);
    Pila_insert_right(&rpta,cif);
    
    op_1=op_1->sgte;
    op_2=op_2->sgte;
    if((op_1==NULL)&&(op_2==NULL))  break;
  }
  if(carry==-1)
  {
    Pila_insert_right(&rpta,'-');
  }
  if(cambio)
  {
    aux = op_1;
    op_1=op_2;
    op_2=aux;
    Pila_insert_right(&rpta,'-');
  }
  return rpta;
}
