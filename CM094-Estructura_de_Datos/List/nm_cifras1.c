#include <stdio.h>
#include <stdlib.h>

struct lista{ // creo una estructura tipo Lista
   char elem; // elemento de la lista
   struct lista *sgte;
};

typedef struct lista lista;
typedef struct lista *Lista;


int strrcbff(char *str,int n);
void Crear_lista(Lista *l);
int esLista_vacia(Lista l);
void Destruir_lista(Lista *l);
Lista Crear_lista_sgte();

int Generar_lista_left(Lista *l,int n);
void Lista_insert_left(Lista *l,char dato);
void Lista_insert_right(Lista *l,char dato);
char Lista_delet_left(Lista *l);
char Lista_delet_right(Lista *l);

int Buscar_elem_lista(Lista l,char info);
Lista Invertir_lista(Lista *l);
void Lista_print(Lista l);
int esNumero(char i);
void Completar_zeros(Lista *l,int n,int m);
// Operaciones suma resta division multiplicacion

Lista Suma(Lista l,Lista q);
Lista Resta(Lista l,Lista q);

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

void Crear_lista(Lista *l)
{
  *l=NULL;
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
}

int esLista_vacia(Lista l)
{
  return (l==NULL);
}

Lista Crear_lista_sgte()
{
  Lista l;
  l=(Lista)malloc(sizeof(lista));
  return l;
}

Lista Invertir_lista(Lista *l)
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
  return (*aux); // *aux = *l ya fueron invertidos sus contenidos que es el mismo
}

int Buscar_elem_lista(Lista l,char info)
{
  Lista aux;
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
int esNumero(char i)
{
  return (strcmp(i,"9")==0||strcmp(i,"8")==0||strcmp(i,"7")==0||strcmp(i,"6")==0||strcmp(i,"5")==0||strcmp(i,"4")==0||strcmp(i,"3")==0||strcmp(i,"1")==0||strcmp(i,"2")==0||strcmp(i,"0")==0||strcmp(i,"-")==0);
}*/

int esNumero(char i)
{
  return (i=='9'||i=='8'||i=='7'||i=='6'||i=='5'||i=='4'||i=='3'||i=='2'||i=='1'||i=='0'||i=='-');
}

int Generar_lista_left(Lista *l,int n)
{
  printf("Lista de %i elementos\n",n);
  int i=0,k=0;
  char in[n+1],cad;
  fflush(stdin);
  strrcbff(in,n+1);
  printf("%s\n",in);
  for(i=0;i<n;i++)
  {
    if(!esNumero(in[i]))
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
      Lista_insert_left(l,cad);
    }
    k++;
  }
  return k;
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
}

void Lista_print(Lista l)
{
  Lista aux;
  aux = l;
  while (aux != NULL)
  {
    printf("%c", aux->elem);
    aux = aux->sgte;
  }
  if (aux == NULL) printf("\n");
}

void Completar_zeros(Lista *l,int n,int m)
{
  char cad='0';
  int i;
  for(i=0;i<(m-n);i++)
  {
    Lista_insert_right(l,cad);
  }
}

Lista Suma(Lista op_1,Lista op_2)
{
  Lista rpta=NULL;
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
    Lista_insert_right(&rpta,cif);
    
    op_1=op_1->sgte;
    op_2=op_2->sgte;
  }
  if(carry)
  {
    Lista_insert_right(&rpta,'1');
  }
  return rpta;
}

Lista Resta(Lista op_1,Lista op_2)
{
  Lista rpta=NULL;
  char a,b;
  int cambio=0;
  op_1=Invertir_lista(&op_1);
  op_2=Invertir_lista(&op_2);
  Lista aux,aux1;
  aux=op_1;
  aux1=op_2;
  a=aux->elem;
  b=aux1->elem;
  while(a >= b && (aux->sgte!=NULL&&aux1->sgte!=NULL)) // evaluamos quien es mayor xd
  {
    aux=aux->sgte;
    aux1=aux1->sgte;
    a=aux->elem;
    b=aux1->elem;
    if(a < b)  cambio=1;
  }
  
  if(cambio==1) // hacemos cambiaso
  {
    aux = op_1;
    op_1=op_2;
    op_2=aux;
    cambio=1;
  }
  op_1=Invertir_lista(&op_1);
  op_2=Invertir_lista(&op_2);
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
    Lista_insert_right(&rpta,cif);
    
    op_1=op_1->sgte;
    op_2=op_2->sgte;
    if((op_1==NULL)&&(op_2==NULL))  break;
  }
  if(carry==-1)
  {
    Lista_insert_right(&rpta,'-');
  }
  if(cambio)
  {
    aux = op_1;
    op_1=op_2;
    op_2=aux;
    Lista_insert_right(&rpta,'-');
  }
  return rpta;
}

int main()
{
   char opcion,signo;
   int cifras1=0,cifras2=0,nega1=0,nega2=0,opcion1,n=0,n1=0,m1=0,m=0;
   int comparar1=0,comparar2=0,invertir=0,igual=0,igual1=0,suma=0;
   Lista opera1,opera2,resultado;
   Crear_lista(&opera1);
   Crear_lista(&opera2);
   Crear_lista(&resultado);
   
   for(;;){
     printf("\n---------------------------------------------");
     printf("\n\nMenu de operaciones con Numeros grandes:\n");
     printf("1. Ingresar el primer numero\n");
     printf("2. Ingresar el segundo numero\n");
     printf("3. Completar ceros\n");
     printf("4. Sumar numeros\n");
     printf("5. Restar numeros\n");
     printf("6. Exit\n");
     printf("\n---------------------------------------------");
     printf("\n\nIngrese opcion:\n");
     strrcbff(&opcion,3);
     opcion1=atoi(&opcion);
     switch (opcion1) {
      case 1:
        Destruir_lista(&opera1); // cada vez que ingresas un numero debes borrar el anterior
        igual=0;
        nega1=0;
        printf("\nIngrese el numero de cifras del primer operando\n");
        fflush(stdin);
        scanf("%i",&cifras1);
        n=Generar_lista_left(&opera1,cifras1);
        signo=Lista_delet_right(&opera1);
        if(esLista_vacia(opera1) && signo=='-')
          printf("Ingrese cifras aparte del signo");
        else if(n<cifras1 || Buscar_elem_lista(opera1,'-'))
        {
          printf("Cadena incorrecta vuelva a ingresar\n\n");
          comparar1=0;
        }
        else
        {
          if(signo == '-')  nega1=1;
          Lista_insert_right(&opera1,signo);
          comparar1=1;
        }
        break;
      case 2:
        Destruir_lista(&opera2); // cada vez que ingresas un numero debes borrar el anterior
        igual=0;
        nega2=0;
        printf("\nIngrese el numero de cifras del segundo operando\n");
        fflush(stdin);
        scanf("%i",&cifras2);
        m=Generar_lista_left(&opera2,cifras2);
        signo=Lista_delet_right(&opera2);
        if(esLista_vacia(opera2) && signo=='-')
          printf("Ingrese cifras aparte del signo");
        else if(m<cifras2 ||Buscar_elem_lista(opera2,'-'))
        {
          printf("Cadena incorrecta vuelva a ingresar\n\n");
          comparar2=0;
        }
        else
        {
          if(signo == '-')  nega2=1;
          Lista_insert_right(&opera2,signo);
          comparar2=1;
        }
        printf("\n");
        break;
      case 3:
        if((comparar1==1&&comparar2==1)&&(nega1==0 && nega2==0))
        {
          if(m<n)
          {
            Completar_zeros(&opera2,m,n);
            m=n;
            comparar1=0;
          }
          else if(m>n)
          {
            Completar_zeros(&opera1,n,m);
            n=m;
            comparar2=0;
          }
          igual =1;
          invertir=1;
          suma=0;
        }
        else if((comparar1==1&&comparar2==1)&&(nega1==1 && nega2==1))
        {
          signo=Lista_delet_right(&opera1);
          signo=Lista_delet_right(&opera2);
          if(m<n)
          {
            Completar_zeros(&opera2,m,n);
            m=n;
            comparar1=0;
          }
          else if(m>n)
          {
            Completar_zeros(&opera1,n,m);
            n=m;
            comparar2=0;
          }
          Lista_insert_right(&opera1,signo);
          Lista_insert_right(&opera2,signo);
          igual =1;
          invertir=1;
          suma=0;
        }
        else if((comparar1==1&&comparar2==1)&&(nega1==1 && nega2==0))
        {
          signo=Lista_delet_right(&opera1);
          n1=n-1;
          if(m<n1)
          {
            Completar_zeros(&opera2,m,n-1);
            m=n1;
            comparar1=0;
          }
          else if(m>n1)
          {
            Completar_zeros(&opera1,n-1,m);
            n1=m;
            comparar2=0;
          }
          Lista_insert_right(&opera1,signo);
          igual1 =1;
          invertir=1;
          suma=0;
        }
        else if((comparar1==1&&comparar2==1)&&(nega1==0 && nega2==1))
        {
          signo=Lista_delet_right(&opera2);
          m1=m-1;
          if(m1<n)
          {
            Completar_zeros(&opera2,m-1,n);
            m1=n;
            comparar1=0;
          }
          else if(m1>n)
          {
            Completar_zeros(&opera1,n,m-1);
            n=m1;
            comparar2=0;
          }
          Lista_insert_right(&opera2,signo);
          igual1 =1;
          invertir=1;
          suma=0;
        }
        else
        {
          printf("\nSi ha modificado uno debe modificar el otro !!\n");
          printf("O quizas uno de los operandos es incorrecto !!\n\n");
        }
        Lista_print(opera1);
        Lista_print(opera2);
        break;
      case 4:
          Destruir_lista(&resultado);
          if(igual==1 && ((nega1==0 && nega2==0) || (nega1==1 && nega2==1))&&suma==0)
          {
            if(nega1==0 && nega2==0)
            {
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
            }
            else if(nega1==1 && nega2==1)
            {
              signo=Lista_delet_right(&opera1);
              signo=Lista_delet_right(&opera2);
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera1,signo);
              Lista_insert_left(&opera2,signo);
              Lista_insert_right(&resultado,signo);
            }
            resultado=Invertir_lista(&resultado);
            printf("\n\n");
            Lista_print(opera1);
            printf("+\n");
            Lista_print(opera2);
            printf("La suma es: \n");
            printf("----------------\n");
            Lista_print(resultado);
            suma=1;
          }
          else if(igual1==1 && ((nega1==1 && nega2==0) || (nega1==0 && nega2==1))&&suma==0)
          {
            if(nega1==1 && nega2==0)
            {
              resultado = Resta(opera2,opera1);
              if(invertir)
              {
                signo=Lista_delet_right(&opera1);
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera1,signo);              
            }
            else if(nega1==0 && nega2==1)
            {
              resultado = Resta(opera1,opera2);
              if(invertir)
              {
                signo=Lista_delet_right(&opera2);
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera2,signo);              
            }
            resultado=Invertir_lista(&resultado);
            printf("\n\n");
            Lista_print(opera1);
            printf("+\n");
            Lista_print(opera2);
            printf("La suma es: \n");
            printf("----------------\n");
            Lista_print(resultado);
            suma=1;
          }
          else
          {
            printf("Si modifico uno modifique el otro !!\n");
            printf("Falta ingresar uno de los 2 operandos !!\n");
            printf("O quiza esta sumando un positivo con un negativo!!\n");
            printf("En ese caso use la funcion restar ! \n");
          }
          break;
      case 5:
          Destruir_lista(&resultado);
          if(igual==1 && ((nega1==0 && nega2==0) || (nega1==1 && nega2==1))&&suma==0)
          {
            if(nega1==0 && nega2==0) // resta
            {
              resultado = Resta(opera1,opera2);
              if(invertir)
              {
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
            }
            else if(nega1==1 && nega2==1) // resta
            {
              signo=Lista_delet_right(&opera1);
              signo=Lista_delet_right(&opera2);
              resultado = Resta(opera2,opera1);
              if(invertir)
              {
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera1,signo);
              Lista_insert_left(&opera2,signo);
            }
            resultado=Invertir_lista(&resultado);
            printf("\n\n");
            Lista_print(opera1);
            printf("-\n");
            Lista_print(opera2);
            printf("La resta es: \n");
            printf("----------------\n");
            Lista_print(resultado);
            suma=1;
          }
          else if(igual1==1 && ((nega1==1 && nega2==0) || (nega1==0 && nega2==1))&&suma==0)
          {
            if(nega1==1 && nega2==0)
            {
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                signo=Lista_delet_right(&opera1);
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera1,signo);
              Lista_insert_right(&resultado,signo);            
            }
            else if(nega1==0 && nega2==1)
            {
              resultado = Suma(opera1,opera2);
              if(invertir)
              {
                signo=Lista_delet_right(&opera2);
                opera1=Invertir_lista(&opera1);
                opera2=Invertir_lista(&opera2);
                invertir=0;
              }
              Lista_insert_left(&opera2,signo);              
            }
            resultado=Invertir_lista(&resultado);
            printf("\n\n");
            Lista_print(opera1);
            printf("-\n");
            Lista_print(opera2);
            printf("La resta es: \n");
            printf("----------------\n");
            Lista_print(resultado);
            suma=1;
          }
          else
          {
            printf("Si modifico uno modifique el otro !!\n");
            printf("Falta ingresar uno de los 2 operandos !!\n");
            printf("O quiza esta sumando un positivo con un negativo!!\n");
            printf("En ese caso use la funcion restar ! \n");
          }
          break;
      case 6:
      default:
        exit(0);
     }
  }
  return 0;
}
