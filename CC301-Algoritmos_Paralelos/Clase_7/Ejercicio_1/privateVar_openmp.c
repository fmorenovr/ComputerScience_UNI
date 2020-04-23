#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main (int argc, char *argv[]) {
  int i,j;
  i=1;
  j=2;
  int* ptr_i=&i,* ptr_j=&j,th_id;
  printf("\nAntes de entrar a los hilos\nLos valores de i,j son: %d,%d\n",i,j);
  printf("\n\nEntrando a los hilos\n\n");
  omp_set_num_threads(4); // 4 subproecsos de hilo
  #pragma omp parallel private(i,j)
  {
    assert(*ptr_i==1&&*ptr_j==2);
    th_id = omp_get_thread_num();
    i+=1*th_id+5;
    j+=2*th_id+2;
    #pragma omp barrier
    printf("Los valores de i,j del hilo %d son: %d,%d\n",th_id,i,j);
  }
  assert(i==1&&j==2);
  printf("\n\nRegresando al hilo master\n\n");
  printf("Los valores no se modificaron!!\nLos valores de i,j son: %d,%d\n\n",i,j);
  return 0;
}
