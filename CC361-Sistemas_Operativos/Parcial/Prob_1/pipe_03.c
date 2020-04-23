#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void promedio(char * cadena);

int main() {
  int fd_ph[2];
  int fd_hp[2];
  pipe(fd_ph);
  pipe(fd_hp);
  char mensaje[100] = "1 2 3 4";
  char buffer[10];

  if (fork()>0) {
    write(fd_ph[1], mensaje, strlen(mensaje)+1);
    read(fd_hp[0], buffer, 100);
    printf("P:%s\n", buffer);
    printf("\n");
  }
  else {
    printf("H:");
    read(fd_ph[0], buffer, 100);
    promedio(buffer);
    write(fd_hp[1], buffer, strlen(buffer)+1);
  }

  return 0;
}

void promedio(char * cadena) {
    int suma = 0;
    int contador = 0;
    float promedio;
    char *token;
   
    /* get the first token */
    token = strtok(cadena, " ");
   
    /* walk through other tokens */
    while( token != NULL ) 
    {
       suma += atoi(token); 
       contador++;
       token = strtok(NULL, " ");
    }
    promedio = (float)suma/contador;
    sprintf(cadena, "%.2f", promedio); 
}
