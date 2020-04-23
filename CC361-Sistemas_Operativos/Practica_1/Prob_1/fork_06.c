#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  
  if (fork()>0) {
    wait();
  }
  else {
    execlp("/bin/ls", "ls", "-l", NULL);
  }
  
  return 0;
}
