#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
  int fd_ph[2];
  int fd_hp[2];
  pipe(fd_ph);
  pipe(fd_hp);
  char mensaje[100];
  char buffer[10];

  if (fork()>0) {
    do {
    if(gets(mensaje)) {
      write(fd_ph[1], mensaje, strlen(mensaje)+1);
      read(fd_hp[0], buffer, 100);
      printf("P:%s\n", buffer);
    }
    } while(1);
    printf("\n");
  }
  else {
    printf("H:");
    do {
      read(fd_ph[0], buffer, 100);
      write(fd_hp[1], "nn", strlen("nn")+1);
    } while(1);
  }

  return 0;
}
