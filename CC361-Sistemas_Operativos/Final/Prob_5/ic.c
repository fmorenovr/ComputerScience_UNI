#include <stdio.h>
#include <stdlib.h>

int main() {
  int contador;

  FILE * f_in = fopen("contador.txt","r");
  fscanf(f_in, "%d", &contador);

  contador++;

  FILE * f_out = fopen(".contador.txt","w");
  fprintf(f_out, "%d", contador);
  fclose(f_out);

  rename(".contador.txt", "contador.txt");

  fclose(f_in);
  printf("contador: %d\n", contador);
}
