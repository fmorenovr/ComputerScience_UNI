#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("proceso padre pid:%d\n", getpid());
  
  if (fork()>0) {
    printf("proceso padre pid:");
    fork();
  }
  else {
    printf("proceso hijo pid:");
  }
  printf("%d\n", getpid());


  sleep(100);
  
  return 0;
}
