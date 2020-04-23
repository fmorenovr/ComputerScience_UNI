#include <stdio.h>
#include <string.h>
 
union Data
{
  int i;
  float f;
  char  str[20];
};
 
typedef union Data Data;
int main( )
{
  Data data;        

  printf( "Memory size occupied by data : %lu\n", sizeof(data));
  data.i = 10;
  data.f = 220.5;
  strcpy( data.str, "C Programming");

  printf( "data.i : %i\n", data.i);
  printf( "data.f : %f\n", data.f);
  printf( "data.str : %s\n", data.str);
  //  el resultado se trunca porque accedemos al la vez la direccion de memoria de union
  // si queremos imprimir 1 a 1, debemos hacerlo 1 por 1
  
  /*
  data.i = 10;
   printf( "data.i : %d\n", data.i);
   
   data.f = 220.5;
   printf( "data.f : %f\n", data.f);
   
   strcpy( data.str, "C Programming");
   printf( "data.str : %s\n", data.str);
   */
  return 0;
}

/*

La definicion de "union" es similar a la de "estructura", La diferencia entre las dos es que en una estructura, los miembros ocupan diferentes areas de la memoria, pero en una union, los miembros ocupan la misma area de memoria. Entonces como ejemplo:

*/
