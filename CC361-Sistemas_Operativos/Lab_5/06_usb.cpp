#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#define BSIZE 256

int main(int argc, char *argv[]){
 
  int fd_in = open("/dev/input/mouse1", O_RDONLY);
  if(fd_in < 0){
    perror("/dev/input/mouse1");
    return -1;
  }

  ssize_t bytes;
  char buffer[BSIZE];
  while((bytes = read(fd_in, buffer, BSIZE)) > 0){
    int i = 0;
    for(; i<bytes;i++)
    {
      printf("%o\n", buffer[i]);
    }
  }

  return 0;
}
