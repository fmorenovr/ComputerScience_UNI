/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include<stdlib.h>

#define SIZE 10
#define n 5 // numero de particiones

int pila[SIZE]; // pila que contiene a las 2 subpilas va de 0 a SIZE-1
int base[n],tope[n];

// Creo n subilas en una pila
void Crear_n_subpilas() // n es el numero de subpilas
{
  int i;
  if(SIZE%n==0)
  {
    for(i=0;i<n;i++)
    {
      base[i]=i*SIZE/n; // esto me indica desde donde comienza cada pila
                       // es decir desde 0 hasta 7,8 hasta 15,16 ... 32
                       // si SIZE = 40 y n =5
      tope[i]=base[i]-1; // indica vacio -1, 7, 15 ...31
    }
    printf("\nSe crearon %i subpilas ",n);
  }
  else
  {
    printf("\nNo se puede fragmentar la pila !! no es multiplo\n");
  }
} 

//Funciones de insertacion
void push_subpila_i(int i,int data)
{
  if(i==(n-1))
  {
    if(tope[i]<SIZE-1)
    {
      tope[i]++;
      pila[tope[i]] = data;
    }
    else printf("Subpila %i llena! Overflow\n",i+1);
  }
  else if(tope[i]<base[i+1]-1) // evalua si tope 1 aun no choca con tope2 -1
  {
    tope[i]++;
    pila[tope[i]] = data;
  }
  else
  {
    printf ("Subpila %i llena! Overflow Local\n",i+1);
  }
}

int valido_i(int i)
{
  i=i-1;
  return ((0<=i) && (i<n));
}

// Funciones de extraccion
void pop_subpila_i(int i)
{
  int dato;
  if (tope[i] >= base[i])
  {
    dato = pila[tope[i]];
    tope[i]--;
    printf ("%d valor extraido de la subpila %i\n", dato,i+1);
  }
  else
  {
    printf ("Subpila %i vacia! Underflow ! \n",i+1);
  }
}

int esSubpila_llena_i(int i)
{
  if(i==n-1)  return (tope[i]==SIZE-1);
  else  return (tope[i]==base[i+1]-1);
}

int esSubpila_vacia_i(int i)
{
  return (tope[i]<base[i]);
}

//Funciones para Print Subpila 1 y Subpila 2
void print_subpila_i(int i)
{
  int j;
  for (j = base[i]; j <= tope[i]; j++)
  {
    printf ("%d ", pila[j]);
  }
  printf ("\n");
}

void print_toda_subpila()
{
  int i,j;
  for (i=0;i<n;i++)
  {
    printf ("|");
    for (j = base[i]; j <= tope[i]; j++)
    {
      printf ("%d ", pila[j]);
    }
  }
  printf("|");
}

// Overflow Local

int Overflow_local_right(int i)
{
  int j,k,over=1;
  if(esSubpila_llena_i(i)&&(i<n-1))
  {
    for(j=i;j<n;j++) // si ninguno cumple se va hasta n
    {
      if(!esSubpila_llena_i(j))
        break;
    }
    if(j!=n)
    {
      for(k=tope[j];k>=base[i+1];k--)
      {
        pila[k+1]=pila[k];
      }
      for(k=i+1;k<=j;k++)
      {
        base[k]=base[k]+1;
        tope[k]=tope[k]+1;
      }
    }
  }
  else
  {
    over=0;
    printf("\nAun no ocurre Overflow\n");
  }
  return over;
}

int Overflow_local_left(int i)
{
  int j,k,over=1;
  if(esSubpila_llena_i(i)&&(i>0))
  {
    for(j=i;j>=0;j--) // si ninguno cumple se va hasta -1
    {
      if(!esSubpila_llena_i(j))
        break;
    }
    if(j!=-1)
    {
      for(k=base[j+1];k<=tope[i];k++)
      {
        pila[k-1]=pila[k];
      }
      for(k=j+1;k<=i;k++)
      {
        base[k]=base[k]-1;
        tope[k]=tope[k]-1;
      }
    }
  }
  else
  {
    over=0;
    printf("\nAun no ocurre Overflow\n");
  }
  return over;
}

int main()
{
  int opcion,dato,i,valido;
  Crear_n_subpilas(n);
  for(;;) {
      printf("\nMenu Principal");
      printf("\n1.Ingresar datos a una subpila \n2.Mostrar una subpila  \n3.Extraer datos a una subpila \n4.Realizar Overflow derecha \n5.Realizar Overflow izquierda \n6.Mostrar todas las subpilas \n7.Salir \n");
      printf("\nIngrese Opcion: \n");
      scanf("%d",&opcion);
      printf("\n");
      switch (opcion) {
      case 1:
         printf("\ningresa el numero de subpila: \n");
         scanf("%d",&i);
         valido=valido_i(i);
         if(valido)
         {
           printf("\ningresa el dato a agregar: \n");
           scanf("%d",&dato);
           push_subpila_i(i-1,dato);
         }
         else printf("\nNumero de Subpila Erroneo\n");
         break;
      case 2:
         printf("\ningresa el numero de subpila: \n");
         scanf("%d",&i);
         valido=valido_i(i);
         if(valido)
         {
           print_subpila_i(i-1);
         }
         else printf("\nNumero de Subpila Erroneo\n");
         break;
      case 3:
         printf("\ningresa el numero de subpila: \n");
         scanf("%d",&i);
         valido=valido_i(i);
         if(valido)
         {
           pop_subpila_i(i-1);
         }
         else printf("\nNumero de Subpila Erroneo\n");
         break;
      case 4:
         printf("\ningresa el numero de subpila: \n");
         scanf("%d",&i);
         valido=valido_i(i);
         if(valido)
         {
           Overflow_local_right(i-1);
         }
         else printf("\nNumero de Subpila Erroneo\n");
         break;
      case 5:
         printf("\ningresa el numero de subpila: \n");
         scanf("%d",&i);
         valido=valido_i(i);
         if(valido)
         {
           Overflow_local_left(i-1);
         }
         else printf("\nNumero de Subpila Erroneo\n");
         break;
      case 6:
         print_toda_subpila();
         break;
      case 7:
      default:
         exit(0);
      }
   }
  return 0;
}
