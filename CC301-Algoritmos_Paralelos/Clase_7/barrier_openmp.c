#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
 
int main (int argc, char *argv[]) {
  int th_id, nthreads,procs,pid;
  int pid1 = getpid();
  printf("Hello World from process %d\n", pid1);
  #pragma omp parallel \
      private(th_id) 
  {
    pid = getpid();
    th_id = omp_get_thread_num();
    printf("Hello World from thread %d\n", th_id);
    printf("Hello World from process %d\n", pid);
    #pragma omp barrier
    if ( th_id == 0 ) {
      nthreads = omp_get_num_threads();
      printf("There are %d threads\n",nthreads);
    }
  }
  procs=omp_get_num_procs();
  printf("There are %d procs\n",procs);
  return 0;
}
