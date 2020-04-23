#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int fibonnaci(int x, int iteracion)
{
  printf("stack %d fib(%d) %p\n", (int)pthread_self(), x, &x);
  if(x == 0 || x == 1)
    return 1;
  else
    return fibonnaci(x-1, ++iteracion);
}

void * fib_thread(){
  fibonnaci(5,1);
      
  return;
}

int main()
{
  pthread_t tid_01;
      
  //printf("stack %d main() %p\n", (int)pthread_self(), &tid_01);
  
  fibonnaci(5,1);
  
  pthread_create(&tid_01, NULL, fib_thread, NULL);
  
  pthread_join(tid_01, NULL);
  
  return 0;
}

