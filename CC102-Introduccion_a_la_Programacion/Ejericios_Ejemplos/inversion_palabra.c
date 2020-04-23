#include <stdio.h>
#include <string.h>
#define N 20

int main()
{
char palabra[N];

printf("Ingrese palabra: ");
scanf("%s",palabra);
printf("La palabra es: %s \n",palabra);

int i=0,lon;
while(palabra[i]!='\0'){
i++;
}

printf("La palabra \" %s \" tienes %i caracteres \n", palabra, i);

lon=strlen(palabra);
printf("Longitud: %i \n",lon);

printf("La palabra al reves es: ");
while(i>=0){
printf("%c",palabra[i]);
i--;
}
printf("\n");

return 0;
}
