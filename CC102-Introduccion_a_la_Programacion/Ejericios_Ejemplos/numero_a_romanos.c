#include<stdio.h>

void p_romano(int valor);

int main()
{
  int valor;
  printf("Ingrese un numero:");
  scanf("%d",&valor);

  if(valor<9000 && valor>0)
    p_romano(valor);
  else
    printf("El numero ingresado no se puede representar");

  printf("\n");

  return 0;
}

void p_romano(int valor)
{
  //El programa va imprimiendo los caracteres que representan al numero
  //por "bloques" que son cuasi-equivalente a una cifra
  //Se pueden agregar mas bucles identicos al inicio para aumentar la cota superior
  //de los valores representados

  //Maximo valor: 8999

  //Este bucle imprime los "bloques" de caracteres relacionados con M y D
  //V'MMM, V'MM, V'M, V', MV', MMM, MM, M, CM
  while(valor>=900)//valor<9000
    {
      if(valor>=5000)
	{printf("V'"); valor-=5000;} //V':5000
      if(valor<1000 && valor>=900)
	{printf("C"); valor+=100;}   //C:100
      if(valor>=1000)
	{printf("M");valor-=1000;}   //M:1000
      if(valor>=3000)
	{printf("V'"); valor-=3000;}
    }

  //Este bucle imprime los "bloques" de caracteres relacionados con C y D
  //DCCC, DCC, DC, D, CD, CCC, CC, C, XC
  while(valor>=90)//valor<900
    {
      if(valor>=500)
	{printf("D"); valor-=500;}
      if(valor<100 && valor>=90)
	{printf("X"); valor+=10;}
      if(valor>=100)
	{printf("C");valor-=100;}
      if(valor>=300)
	{printf("D"); valor-=300;}
    }

  //Este bucle imprime los "bloques" de caracteres relacionados con X y L
  //LXXX, LXX, LX, L, XL, XXX, XX, X, IX
  while(valor>=9)//valor<90
    {
      if(valor>=50)
	{printf("L"); valor-=50;}
      if(valor<10 && valor>=9)
	{printf("I"); valor+=1;}
      if(valor>=10)
	{printf("X");valor-=10;}
      if(valor>=30)
	{printf("L"); valor-=30;}
    }

  //Este bucle imprime los "bloques" de caracteres relacionados con I y V
  //VIII, VII, VI, V, IV, III, II, I
  while(valor>=1)//valor<9
    {
      if(valor>=5)
	{printf("V"); valor-=5;}
      if(valor>=1)
	{printf("I");valor-=1;}
      if(valor>=3)
	{printf("V"); valor-=3;}
    }
}
