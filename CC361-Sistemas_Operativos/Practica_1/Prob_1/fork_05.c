#include <stdio.h>
#include <stdlib.h>

int main() {
  
  if (fork()>0) {
    int status;
    int pid = wait(&status);
    printf("estatus del proceso(%d):%d\n", pid, status);

  }
  else {
    sleep(4);
    printf("error al procesar archivo grande(%d)\n",getpid());
    exit(10);
  }
  
  return 0;
}
