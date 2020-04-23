#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
  printf("Descriptor de archivo de entrada %d\n", STDIN_FILENO);
  printf("Descriptor de archivo de salida %d\n", STDOUT_FILENO);
  printf("Descriptor de archivo de error %d\n", STDERR_FILENO);


  write(STDOUT_FILENO, "Hola", strlen("Hola")+1);
  printf("\n");
  return 0;
}

