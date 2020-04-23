#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
  int fd[2];

  pipe(fd);
  
  char saludos[] = "Saludos desde la Universidad Nacional de Ingeriería";
  char buffer[10];
  
  if (fork()>0) {
    close(fd[0]);
    write(fd[1], saludos, strlen(saludos)+1);

  }
  else {
    close(fd[1]);
    read(fd[0], buffer, 100);
    printf("%s\n", buffer);

  }
  sleep(100);

  return 0;
}
