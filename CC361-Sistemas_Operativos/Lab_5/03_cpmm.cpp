#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

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

  if(ftruncate(fd_out, info.st_size) < 0){
    perror("Error fijando tamaño del archivo de salida");
    return -1;
  }

  void *addr_out = mmap(0, info.st_size, PROT_WRITE, MAP_SHARED, fd_out, 0);
  if(addr_out == MAP_FAILED){
    perror("Error mapeando archivo de salida");
    return -1;
  }

  memcpy(addr_out, addr_in, info.st_size);
  return 0;
}

