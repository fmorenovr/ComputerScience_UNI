#include <stdio.h>
#include <string.h>
 
int main()
{
    char palabra[20];
    int i, j;
    int palindromo = 1;
    printf("Escribe una cadena: ");
    fflush(stdout);
    gets(palabra);
    j=strlen(palabra)-1;
    for(i=0; i<strlen(palabra)/2; i++, j--) {//strlen longitud de la cadena
        printf("Comprobando %c==%c\n", palabra[i], palabra[j]);
        if (palabra[i]!=palabra[j]) {
            palindromo = 0;
            break;
        }
    }
    if (palindromo)
        printf("\nEs un palíndrimo.\n");
    else
        printf("\nNo es un palíndrimo.\n");
 
    return (0);
}

