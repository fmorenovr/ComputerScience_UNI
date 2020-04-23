#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("segmento codigo : %p\n", (void *) main);
  printf("segmento heap : %p\n", (void *) malloc(1));
  int x = 3;
  printf("segmento stack : %p\n", (void *) &x);
    
  return x;
}

