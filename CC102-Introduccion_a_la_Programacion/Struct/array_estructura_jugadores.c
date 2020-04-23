/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define jug 3

typedef struct Jugador{
	char nombre[40],telf[10],sexo[10];
	int edad;
	float altura;
} Jugador;

Jugador jugadores[jug];

// string read comprobamos y clean buffer
int strrcbff(char *str, int n) // funcion que borra el flujo de entrada
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

// string delete spaces blank
int strdsb(char *strng)
{
  char*tmp;
  while((tmp=strchr(strng,32))!=NULL)
    sprintf(tmp,"%s",tmp+1);
  return 1;
}

void Ingresar_jugador()
{
  int i;
  char edad[3],altura[4];
  for(i=0;i<jug;i++){
    printf("\n");
		printf("ingrese nombre del jugador: %i \n",i+1);
		strrcbff(jugadores[i].nombre,40);
    printf("\n");
		printf("ingrese sexo:\n");
		strrcbff(jugadores[i].sexo,10);
		if(!(strcmp(jugadores[i].sexo,"masculino")==0||strcmp(jugadores[i].sexo,"Masculino")==0||strcmp(jugadores[i].sexo,"femenino")==0||strcmp(jugadores[i].sexo,"femenino")==0))
		{
		  printf("\nSexo incorrecto! \n");
		  break;
		}
    printf("\n");
		printf("ingrese telefono:\n");
		strrcbff(jugadores[i].telf,10);
    if(atoi(jugadores[i].telf))
		{
		  printf("\nNumero incorrecto! \n");
		  break;
		}
    printf("\n");
		printf("ingrese edad:\n");
		strrcbff(edad,3);
		jugadores[i].edad=atoi(edad);
		if(jugadores[i].edad)
		{
		  if(jugadores[i].edad>91)
		  {
		    printf("Es algo anciano ... %d",jugadores[i].edad);
		  }
		  else if(jugadores[i].edad<=0)
		  {
		    printf("\nError de edad !!!\n");
		    break;
		  }
		}
		else
		{
		  printf("\n Error de edad !!!\n");
		  break;
		}
    printf("\n");
		printf("ingrese altura(en m):\n");
		strrcbff(altura,4);
		jugadores[i].altura=atof(altura);
		if(jugadores[i].altura)
		{
		  if(jugadores[i].altura>2.15)
		  {
		    printf("\nEs muy raro que mida mas de %f\n",jugadores[i].altura);
		  }
		  else if(50<jugadores[i].altura)
		  {
		    printf("\nEsta registrando ninos ?? \n");
		  }
		  else if(jugadores[i].altura<=0)
		  {
		    printf("\n Error de altura! \n");
		    break;
		  }
		}
		else
		{
		  printf("\n Error de altura !!!\n");
		  break;
		}
		printf("\n");
	}
}

// gets() reserva la cadena en un puntero string
// al imprimir se imprime como %s porque gets lo transforma a string

void Encontrar_jugador(char nom[40])
{
  int i;
  for(i=0;i<jug;i++)
  {
    if(!strcmp(jugadores[i].nombre,nom))
    {
      printf("\nNombre\t\tSexo\t\tTelefono\t\tEdad\t\tAltura del jugador %i:\n",i+1);
      printf("\n%s\t\t%s\t%s\t\t%i\t\t%.2f\n",jugadores[i].nombre,jugadores[i].sexo,jugadores[i].telf,jugadores[i].edad,jugadores[i].altura);
      break;
    }
	}
}

void mostrar_jugadores()
{
  int i;
  for(i=0;i<jug;i++)
  {
    printf("\nNombre\t\tSexo\t\tTelefono\t\tEdad\t\tAltura del jugador %i:\n",i+1);
    printf("\n%s\t\t%s\t%s\t\t%i\t\t%.2f\n",jugadores[i].nombre,jugadores[i].sexo,jugadores[i].telf,jugadores[i].edad,jugadores[i].altura);
	}
}

int main(){
  int opcion;
  char nomb[40],aux[3];
	
  for(;;) {
      printf("\nMenu Principal");
      printf("\n1.Ingresar Datos de jugadores \n2.Buscar Datos de jugador \n3.Mostrar todos los jugadores \n4.Salir \n");
      printf("\nIngrese Opcion: \n");
      strrcbff(aux,3);
      opcion=atoi(aux);
      switch (opcion) {
      case 1:
         Ingresar_jugador();
         break;
      case 2:
         printf("\ningresa el nombre a buscar: \n");
         strrcbff(nomb,40);
         printf("Datos del Jugador \n");
         Encontrar_jugador(nomb);
         break;
      case 3:
         mostrar_jugadores();
         break;
      case 4:
      default:
         exit(0);
      }
   }
	return 0;
}
