#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define BSIZE 1024

int main(int argc, char *argv[]){
  if(argc != 3){
    cerr << "Usar: " << argv[0] << " archivoingreso archivosalida" << endl;
    return -1;
  }
 
  int fd_in = open(argv[1], O_RDONLY);
  if(fd_in < 0){
    perror(argv[1]);
    return -1;
  }

  struct stat info;
  if(fstat(fd_in, &info) < 0){
    perror("Error status de archivo de ingreso");
    return -1;
  }

  void *addr_in = mmap(0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);
  if(addr_in == MAP_FAILED){
    perror("Error mapeando archivo de ingreso");
    return -1;
  }

  int fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(fd_out < 0){
    perror(argv[2]);
    return -1;
  }

  ssize_t bytes;
  char buffer[BSIZE];
  while((bytes = read(fd_in, buffer, BSIZE)) > 0){
    write(fd_out, buffer, bytes);
  }

  close(fd_in);
  close(fd_out);

  return 0;
}

