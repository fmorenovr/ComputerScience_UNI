#include <stdio.h>
#include <stdlib.h>

int main() {
  
  if (fork()>0) {
    wait();
  }
  else {
    sleep(10);
    printf("terminamos de procesar archivo grande\n");
  }
  
  return 0;
}
