#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct Ficha
{
  unsigned char tipo;
  //Cada ficha es una matriz de 2x4 
  //la cual se codifica en 8 bits de 1 byte
  char x;
  //La posición de la esquina inferior izquierda de la ficha
}Ficha;

#define ANCHO 10
#define ALTO 20

//---------------------------------------

Ficha genera_ficha()
{
  struct Ficha ficha;
  char aleatorio=rand()%7; //Son 7 tipos de ficha

  switch(aleatorio)
    {
    case 0:
      ficha.tipo=15; //Barra horizontal: 0000 1111;
      break;
    case 1:
      ficha.tipo=142;//L invertida: 1000 1110
      break;
    case 2:
      ficha.tipo=46;//L: 0010 1110
      break;
    case 3:
      ficha.tipo=204;//Cuadrado: 1100 1100
      break;
    case 4:
      ficha.tipo=108;//S: 0110 1100 
      break;
    case 5:
      ficha.tipo=78;//T: 0100 1110
      break;
    case 6:
      ficha.tipo=198; //S invertida: 1100 0110
      break;
    }
  if(aleatorio==0) //Esta ficha es más grande
    ficha.x=rand()%7;
  else
    ficha.x=rand()%8;

  return ficha;
}
  
//-----------------------------------

void limpia_matriz(char M[ALTO][ANCHO])
{
  int i,j;

  for(i=0;i<ALTO;i++)
    for(j=0;j<ANCHO;j++)
      M[i][j]=0;
}

void imprime_matriz(char M[ALTO][ANCHO],FILE *fp)
{
  static int n=0;
  n++;
  int i,j;
  fprintf(fp,"%2d------------------\n",n);
    for(i=ALTO-1;i>=0;i--)
      {
      for(j=0;j<ANCHO;j++)
        {
          if(M[i][j]==1)
            fprintf(fp,"*");//Imprime "*" si esta lleno el espacio
          else
            fprintf(fp," ");//Imprime " " si esta vacio el espacio
        }
      fprintf(fp,"\n");//Imprime un salto de linea al final de cada fila
      }
    fprintf(fp,"---------------------\n");
}

char actualiza_matriz(char M[ALTO][ANCHO],Ficha ficha)
{
  int i,j;
  //Es necesario recuperar la información de la forma de la ficha
  //Para eso se utiliza una division y un modulo
  //Si se quiere el bit "n" (contado de izquierda a derecha)
  //Se necesita dividir a "ficha.tipo" por pow(2,8-n) y a ese resultado
  //hallar su modulo por 2

  char forma[2][4];
  
  for(i=0;i<2;i++)
    for(j=0;j<4;j++)
      forma[i][j]=(ficha.tipo/(int)(pow(2,8-(i*4+j+1))))%2;

  //Asi se crea una matriz de 2x4 con la información de la forma de la ficha
  //La fila 0 indica la fila superior
  //Ahora hay que hallar la información de los lugares que estan por debajo
  //de cada "columna" de la ficha
  char altura[4];
  for(i=0;i<4;i++)
    altura[i]=-1; //Si la columna esta vacia, debe de tener altura -1

  //Almacena la altura de cada columna por debajo de la ficha
  
  for(j=0;j<=4;j++)
    for(i=0;i<ALTO;i++)
      if(M[i][j+ficha.x]==1)
        altura[j]=i;

  
  //Si en una columna la ficha esta vacia, no importara cual sea
  //la altura de la columna debajo de esa columna vacia de la ficha

  for(j=0;j<4;j++)
    {
      if(forma[1][j]==0) //Si la ficha no "tiene piso" en una columna
        {
          altura[j] -= 1;
          if(forma[0][j]==0) //Si esa columna esta vacia
            altura[j]=-1; //Se pone -1 porque esa columna no va a obstaculizar
        }    
    }
  //Ahora toca calcular a que altura se ubicara la ficha
  //Se necesita hallar el mayor valor de las alturas

  i= (altura[0]>altura[1]) ? altura[0] : altura[1];
  j= (altura[2]>altura[3]) ? altura[2] : altura[3];

  char alt_mayor= (i>j) ? i : j;

  //Esta es la mayor altura, pero no la posición vertical de la ficha
  //Esta se halla aumentanto el valor de alt_mayor

  alt_mayor++;

  //Ahora solo hay que actualizar la matriz

  for(i=1;i>=0;i--)
    {
      if(alt_mayor+1-i==ALTO)
        return 1;
      for(j=0;j<4;j++)
        if(forma[i][j]!=0)
          {
              M[alt_mayor+1-i][j+ficha.x]=forma[i][j];
          }
    }
  return 0;
}
//---------------------------------
void main()
{
  char M[ALTO][ANCHO], salir=0;

  FILE *fp;

    fp=fopen("tetris.txt","w");
  if (fp==NULL)
    {
      printf("Error al crear el archivo de salida\n");
      return;
    }

  limpia_matriz(M);
  srand(time(0));
  Ficha ficha;
  while(1)
    {
      ficha=genera_ficha();

      salir=actualiza_matriz(M,ficha);

      imprime_matriz(M,fp);

      if(salir)
        break;
    }
  fprintf(fp,"Juego finalizado\n");
  fclose(fp);
}
