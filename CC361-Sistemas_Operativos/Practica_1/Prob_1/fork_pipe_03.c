#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
  int fd_pah[2];
  int fd_hap[2];

  pipe(fd_pah);
  pipe(fd_hap);
  
  char saludos[] = "Saludos desde la Universidad Nacional de Ingeriería";
  char gracias[] = "Gracias";
  char buffer[10];
  
  if (fork()>0) {
    close(fd_pah[0]);
    close(fd_hap[1]);
    write(fd_pah[1], saludos, strlen(saludos)+1);
    printf("\n[X] ENVIADO AL HIJO\n");
    read(fd_hap[0], buffer, 100);
    printf("\n[X] RECIBIDO DEL HIJO\n%s\n", buffer);
  }
  else {
    close(fd_pah[1]);
    close(fd_hap[0]);
    read(fd_pah[0], buffer, 100);
    printf("\n[X] RECIBIDO DEL PADRE\n%s\n", buffer);
    write(fd_hap[1], gracias, strlen(gracias)+1);
    printf("\n[X] ENVIADO AL PADRE\n");

  }
  sleep(100);

  return 0;
}
