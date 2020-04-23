#include <stdio.h>
#include <stdlib.h>

int main() {
  
  if (fork()>0) {
    if (fork()==0) {
      if(fork()>0){
        fork();
      }
    }
  }
  else {
    if(fork()>0){
      fork();
    }
  }
  sleep(100);
  
  return 0;
}
