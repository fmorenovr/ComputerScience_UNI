/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>

#define size 40 // longuitud de cadena
#define max 20 //  longuitud total de la pila

typedef struct Pila {
   char s[max]; // Pila con tamanio "max"
   int tope;   // Indice del ultimo elementos agregado
} Pila;

Pila pila = { {}, -1};
int balanceada=1;
char cadena[size];
int indice;
// Operaciones Auxiliares

int esPila_llena()
{
  return (pila.tope >= max-1);
}

int esPila_vacia()
{
  // Comparamos con -1 porque los arrays comienzan
  // desde el indice "0"
  return(pila.tope == -1); // verdadero es vacia
}

// Operaciones Basicas

void Pila_push(char dato)
{
  if (esPila_llena()) printf("\nLa Pila Esta llena, no se puede insertar elementos \n");
  else{
    pila.tope++;
    pila.s[pila.tope]=dato;
  }
}

char Pila_pop()
{
  char dato;
  dato=pila.s[pila.tope];
  pila.tope--;
  return dato;
}

// si el array es de tipo char cambiar la funcion Pila_pop, y la definicion en la estructura Pila y Pila_push

void Pila_print()
{
  int i;
  if(esPila_vacia())  printf("No hay elementos por mostrar \n");
  else
  {
    for(i=0;i<=pila.tope;i++)
    {
      printf("%i\t%c \n",i,pila.s[i]);
    }
  }
}

int leer_Cadena()
{
  int j;
  for(j=0;j<size;j++){
    scanf("%c",&cadena[j]);
    if(cadena[j]=='\n') break;
  }
  return j;
}

int isOperator(char c) 
{ 
  return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^'|| c=='('||c==')'||c=='['|| c==']'||c=='{'||c=='}');
}

int esNumero(char c)
{
  return ('0'<=c && c<='9');
}

int esLetra(char c)
{
  return (('a'<=c && c<='z') || ('A'<=c && c<='Z'));
}


int verificar_Cadena(int num,char infijo[size])
{
  int j=0,correcto=1;
  while(j<num)
  {
    if(infijo[0]=='*' || infijo[0]=='/' || infijo[0]=='^')
    {
      correcto=0;
      break;
    }
    if(esNumero(infijo[j])||esLetra(infijo[j])|| isOperator(infijo[j]))
    {
      if(infijo[num-1]=='('||infijo[num-1]=='{'||infijo[num-1]=='[' || infijo[num-1]=='+' || infijo[num-1]=='-' || infijo[num-1]=='*' || infijo[num-1]=='/' || infijo[num-1]=='^')
      {
        correcto=0;
        break;
      } // correcto
      
      if(j<=num-2)
      {
        if(esNumero(infijo[j]))
        {
          if(isOperator(infijo[j+1])||esNumero(infijo[j+1])) correcto = 1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(esLetra(infijo[j]))
        {
          if(isOperator(infijo[j+1])||esLetra(infijo[j+1])) correcto = 1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='^' || infijo[j]=='-' || infijo[j]=='+' || infijo[j]=='/' || infijo[j]=='*')
        {
          if(esNumero(infijo[j+1])||esLetra(infijo[j+1])||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'){ correcto=1;}
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='(')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]==')'||infijo[j+1]=='['||infijo[j+1]=='{'||esNumero(infijo[j+1])||esLetra(infijo[j+1])){    correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]==')')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')   correcto=1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='[')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'||esLetra(infijo[j+1])||esNumero(infijo[j+1])){  correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]==']')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')  correcto=1;
          else{ correcto=0;break;}
        }
      
        if(infijo[j]=='{')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'||esLetra(infijo[j+1])||esNumero(infijo[j+1])){   correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]=='}')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')  correcto=1;
          else{ correcto=0;break;}
        }
      }
      correcto = 1;
    }
    else
    {
      correcto = 0;
      break;
    }
    j++;
  }
  return correcto;
}


int main()
{
  int i=0,verificado;
  char parentesis;
  printf("\nIngrese la cadena de operaciones: \n");

  indice = leer_Cadena();
  verificado=verificar_Cadena(indice,cadena);

  if(verificado){
    while(balanceada==1 && i<indice)
    {
      if(cadena[i]=='(')  Pila_push(cadena[i]);
      if(cadena[i]=='[')  Pila_push(cadena[i]);
      if(cadena[i]=='{')  Pila_push(cadena[i]);
      if(cadena[i]=='}')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='{')  parentesis=Pila_pop();
          else  Pila_push(cadena[i]);
        }
        else  balanceada=0;
      }
      if(cadena[i]==']')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='[') parentesis=Pila_pop();
          else  Pila_push(cadena[i]);
        }
        else  balanceada=0;
      }
      if(cadena[i]==')')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='(')  parentesis=Pila_pop();
          else  Pila_push(cadena[i]);
        }
        else  balanceada=0;
      }
      i++;
    }
    if(balanceada==1 && esPila_vacia())
    {
      printf("\nPila Balanceada\n\n");
    }
    else
    {
      printf("\nPila NO balanceada\n\n");
    }
    for(i=0;i<indice;i++) printf("%c",pila.s[i]);
    printf("\n");
  }
  else
  {
    printf("\nError de Ingreso !!!\n");
    printf("Solo ingrese numeros/letras y operadores \n");
  }
}

// copie el archivo .c en el escritorio o desktop
// abra terminal
// escriba cd EScritorio o cd Desktop (dependiendo de su idioma de sistema espanol o ingles)
// escriba los 2 siguientes comandos:

// gcc tarea_balanceada.c -o cadena
// ./cadena
