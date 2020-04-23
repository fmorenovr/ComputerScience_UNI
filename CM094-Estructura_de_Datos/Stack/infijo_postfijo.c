/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define size 50 // longuitud de cadena
#define max 30 //  longuitud total de la pila
#define cif 4 // numeros de maximo 4 cifras

typedef struct Pila {
   char s[max]; // Pila con tamanio "max"
   int tope;   // Indice del ultimo elementos agregado
} Pila;

Pila pila = { {}, -1};
char infijo[size],postfijo[size];
// cadena es la que se ingresa y aux es la que devuelve

int indice; // longuitud de elementos real de infijo
// Operaciones Auxiliares

int esPila_llena()
{
  return (pila.tope >= max-1); // true // false
}

int esPila_vacia()
{
  // Comparamos con -1 porque los arrays comienzan
  // desde el indice "0"
  return (pila.tope == -1); // verdadero es vacia
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

int isOperator(char c) 
{ 
  if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='(' || c==')'||c=='[' || c==']'||c=='{' || c=='}') return 1;
  return 0;
}

int esNumero(char c)
{
  return ('0'<=c && c<='9');
}

int esLetra(char c)
{
  return (('a'<=c && c<='z') || ('A'<=c && c<='Z'));
}

int leer_Cadena()
{
  int j;
  for(j=0;j<size;j++){
    scanf("%c",&infijo[j]);
    if(infijo[j]=='\n') break; // no toma el salto de linea 
  }
  return j;
}

int Operar(int a,int b,char c)
{
  if(c=='+'){  return (a+b);}
  else if(c=='-'){  return (a-b);}
  else if(c=='*'){  return (a*b);}
  else if(c=='/'){  return (a/b);}
  else if(c=='^'){  return (pow(a,b));}
}

int verificar_Cadena(int num)
{
  int j=0,correcto=1;
  while(j<num)
  {
    if(infijo[0]=='*' || infijo[0]=='/' || infijo[0]=='^')
    {
      correcto=0;
      break;
    }
    if(esNumero(infijo[j]) ||esLetra(infijo[j])|| isOperator(infijo[j]))
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
          if(isOperator(infijo[j+1]) || esNumero(infijo[j+1]))
            correcto = 1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(esLetra(infijo[j]))
        {
          if(isOperator(infijo[j+1])|| esLetra(infijo[j+1]))
            correcto = 1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='^' || infijo[j]=='-' || infijo[j]=='+' || infijo[j]=='/' || infijo[j]=='*')
        {
          if(esNumero(infijo[j+1])||esLetra(infijo[j+1])||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'){ correcto=1;}
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='(')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'||esNumero(infijo[j+1])||esLetra(infijo[j+1])){
            correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]==')')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')
          correcto=1;
          else{ correcto=0;break;}
        } // correcto correcto
      
        if(infijo[j]=='[')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'||esLetra(infijo[j+1])||esNumero(infijo[j+1])){
            correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]==']')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')
            correcto=1;
          else{ correcto=0;break;}
        }
      
        if(infijo[j]=='{')
        {
          if(infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='('||infijo[j+1]=='['||infijo[j+1]=='{'||esLetra(infijo[j+1])||esNumero(infijo[j+1])){
            correcto=1;}
          else{ correcto=0;break;}
        } //correcto correcto
      
        if(infijo[j]=='}')
        {
          if(infijo[j+1]=='^'||infijo[j+1]=='-'||infijo[j+1]=='+'||infijo[j+1]=='/'||infijo[j+1]=='*'||infijo[j+1]==')'||infijo[j+1]==']'||infijo[j+1]=='}')
            correcto=1;
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

int cadena_Balanceada()
{
  int i=0,balanceada=1,verificado;
  char parentesis;
  indice = leer_Cadena();
  verificado=verificar_Cadena(indice);
  if(verificado){
    while(balanceada==1 && i<indice)
    {
      if(infijo[i]=='(')  Pila_push(infijo[i]);
      if(infijo[i]=='[')  Pila_push(infijo[i]);
      if(infijo[i]=='{')  Pila_push(infijo[i]);
      if(infijo[i]=='}')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='{')  parentesis=Pila_pop();
          else  Pila_push(infijo[i]);
        }
        else  balanceada=0;
      }
      if(infijo[i]==']')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='[')  parentesis=Pila_pop();
          else  Pila_push(infijo[i]);
        }
        else  balanceada=0;
      }
      if(infijo[i]==')')
      {
        if(!esPila_vacia())
        {
          if(pila.s[pila.tope]=='(')  parentesis=Pila_pop();
          else  Pila_push(infijo[i]);
        }
        else  balanceada=0;
      }
      i++;
    }
    if(balanceada==1 && esPila_vacia())  return 1; // cadena balanceada
    else return 0; // cadena no balanceada
  }
  else  return 0; // no es correcta la cadena
}

int Prioridad_operador(char a,char b)
{
  int x,y;
  if(a=='+'){  x=1;}
  if(a=='-'){  x=1;}
  if(a=='*'){  x=2;}
  if(a=='/'){  x=2;}
  if(a=='^'){  x=3;}
  if(b=='+'){  y=1;}
  if(b=='-'){  y=1;}
  if(b=='*'){  y=2;}
  if(b=='/'){  y=2;}
  if(b=='^'){  y=3;}
  return x-y;
}

int RPN() // reverse polish notation
{
  int i=0,balanceo,contador;
  char operador;
  int prioridad=0;
  
  balanceo = cadena_Balanceada();

  if(balanceo)
  {
    printf("\nCadena Correcta, empieza el algoritmo rpn: \n");
    while(i<indice)
    {
      if(infijo[i]=='*' || infijo[i]=='+' || infijo[i]=='-' || infijo[i]=='/' || infijo[i]=='^')
      {
        if(esNumero(infijo[i+1])||esLetra(infijo[i+1]))  postfijo[i+contador]=' ';

        if(esPila_vacia()){  Pila_push(infijo[i]);}
        else
        {
          if(pila.s[pila.tope]=='('||pila.s[pila.tope]=='['||pila.s[pila.tope]=='{')  Pila_push(infijo[i]);
          else if(pila.s[pila.tope]=='+'||pila.s[pila.tope]=='-'||pila.s[pila.tope]=='*'||pila.s[pila.tope]=='/'||pila.s[pila.tope]=='^')
          {
          // DESDE AQUI
            prioridad=Prioridad_operador(infijo[i],pila.s[pila.tope]);
            while((!esPila_vacia()) && (prioridad<=0) && (pila.s[pila.tope]!='('&&pila.s[pila.tope]!='{'&&pila.s[pila.tope]!='['))
            {
              postfijo[i+contador]=Pila_pop();
              if(pila.s[pila.tope]!='('&&pila.s[pila.tope]!='{'&&pila.s[pila.tope]!='[')
              {
                contador++;
                prioridad=Prioridad_operador(infijo[i],pila.s[pila.tope]);
              }
              else  prioridad=3;
            }
           // HASTA AQUI
            Pila_push(infijo[i]);
          }
        }
      }
      else if(infijo[i]=='(')
      {
        Pila_push(infijo[i]);
        postfijo[i+contador]='(';
      }
      else if(infijo[i]=='[')
      {
        Pila_push(infijo[i]);
        postfijo[i+contador]='[';
      }
      else if(infijo[i]=='{')
      {
        Pila_push(infijo[i]);
        postfijo[i+contador]='{';
      }
      else if(esNumero(infijo[i])||esLetra(infijo[i]))  postfijo[i+contador]=infijo[i];
      else if(infijo[i]==')') // entra un ')'
      {// lo mismo
        prioridad=0;
        while((!esPila_vacia()) && (prioridad<=0) && (pila.s[pila.tope]!='('))
        {
          postfijo[i+contador]=Pila_pop();
          if(pila.s[pila.tope]!='(')  contador++;
          else
          {
            contador++;
            prioridad=3;
          }
        }// aca
        postfijo[i+contador]=infijo[i]; 
        if(pila.s[pila.tope]=='(')  operador=Pila_pop();
      }
      else if(infijo[i]==']') // entra un ')'
      {// lo mismo
        prioridad=0;
        while((!esPila_vacia()) && (prioridad<=0) && (pila.s[pila.tope]!='['))
        {
          postfijo[i+contador]=Pila_pop();
          if(pila.s[pila.tope]!='[')  contador++;
          else
          {
            contador++;
            prioridad=3;
          }
        }// aca
        postfijo[i+contador]=infijo[i]; 
        if(pila.s[pila.tope]=='[')  operador=Pila_pop();
      }
      else // entra un '}'
      {// lo mismo
        prioridad=0;
        while((!esPila_vacia()) && (prioridad<=0) && (pila.s[pila.tope]!='{'))
        {
          postfijo[i+contador]=Pila_pop();
          if(pila.s[pila.tope]!='{')  contador++;
          else
          {
            contador++;
            prioridad=3;
          }
        }// aca
        postfijo[i+contador]=infijo[i]; 
        if(pila.s[pila.tope]=='{')  operador=Pila_pop();
      }
      i++;
    } // sale con i = indice y un valor determinado de contador
    while(!esPila_vacia())
    {
      postfijo[i+contador]=Pila_pop();
      i++;
    }
    return i+contador;
  }
  else
  {
    printf("\nError de Ingreso !!!\n");
    printf("Solo ingrese numeros y operadores \n");
    printf("O la cadena no esta balanceada. \n");
    printf("En tal caso ingrese mismo pares de parentesis '(' ')'\n");
    return 0;
  }
}

int Calculo_RPN(int len){
  int i=0,j=0,cont=0,cifra=0,numero=0,numero1=0,numero2=0,numero3=0,cifras[cif];
  double potencia=0;
  char caracter,cifras1[cif];
  while(i<len)
  {
    j=0;
    if(postfijo[i]=='('||postfijo[i]=='['||postfijo[i]=='{'||esLetra(postfijo[i])||postfijo[i]==' '||esNumero(postfijo[i]))
      Pila_push(postfijo[i]);
    // Correcto
    else if(postfijo[i]=='+'||postfijo[i]=='-'||postfijo[i]=='*'||postfijo[i]=='/'||postfijo[i]=='^')
    {
      if(pila.s[pila.tope]==' ') caracter=Pila_pop();
      while(!esPila_vacia() && cont<2 && pila.s[pila.tope]!='(' && pila.s[pila.tope]!='[' && pila.s[pila.tope]!='{')
      {
        while(esNumero(pila.s[pila.tope]))
        {
          caracter=Pila_pop();
          numero1=(int)(caracter-48);
          potencia=pow((double)10,(double)cifra);
          numero2=numero2+numero1*(int)potencia;
          cifra++;        
        }
        cont++;
        if(pila.s[pila.tope]==' '&&cont<2)
        {
          cifra=0;
          caracter=Pila_pop();
          numero3=numero2;
        }
        if(pila.s[pila.tope]=='+')
        {
          caracter=Pila_pop();
        }
        if(pila.s[pila.tope]=='-')
        {
          caracter=Pila_pop();
          numero2=numero2*(-1);
        }
      }
      numero=Operar(numero3,numero2,postfijo[i]);
      numero3=numero;
      cont=0;cifra=0;
      if(numero<0)
      {
        numero=abs(numero);
        Pila_push('-');
        j++;
      }
      while(numero>0)
      {
        numero1=numero%10;
        cifras[j]=numero1;
        j++;
        numero=numero/10;
      }
      while(j>0)
      {
        j--;
        caracter=(char)(cifras[j]+48);
        Pila_push(caracter);
      }
      Pila_push(' ');
    }
    else if(postfijo[i]==')'||postfijo[i]==']'||postfijo[i]=='}')
    {
      if(pila.s[pila.tope]==' ')  caracter=Pila_pop();
      while(!esPila_vacia() && pila.s[pila.tope]!='(' && pila.s[pila.tope]!='[' && pila.s[pila.tope]!='{')
      {
        cifras1[j]=Pila_pop();
        j++;
      }
      if(pila.s[pila.tope]=='('||pila.s[pila.tope]=='['||pila.s[pila.tope]=='{')
      {
        caracter=Pila_pop();
        Pila_push(' ');
      }
      while(j>0)
      {
        j--;
        cifras1[j]=Pila_pop();
        Pila_push(cifras1[j]);
      }
    } // correcto
    i++;
  }
  if(pila.s[pila.tope]==' ')  caracter=Pila_pop();
  cifra=0;
  while(!esPila_vacia()&&esNumero(pila.s[pila.tope]))
  {
    caracter=Pila_pop();
    numero1=(int)(caracter-48);
    potencia=pow((double)10,(double)cifra);
    numero2=numero2+numero1*(int)potencia;    cifra++;
  }
  
  if(pila.s[pila.tope]=='-')
  {
    caracter=Pila_pop();
    numero2=numero2*(-1);
  }
  if(pila.s[pila.tope]==' ')  caracter=Pila_pop();
  
  return numero2;
}

int main()
{
  int len,resultado;
  printf("\nIngrese la cadena de operaciones: \n");
  len=RPN();
//  resultado=Calculo_RPN(len);
  printf("La forma rpn es: \n");
  int m;
  for(m=0;m<len;m++)
  {
    printf("%c",postfijo[m]);
  }
  printf("\n");
  printf("\n");
  for(m=0;m<size;m++)
  {
    printf("%c",pila.s[m]);
  }
  printf("\n");
  printf("\n");
  printf("Longuitud del infijo es: %i\n",indice);
  printf("Longuitud del postfijo es: %i\n",len);
//  printf("El resultado es: %i ",resultado);
  printf("\n");
  printf("\n");
}

