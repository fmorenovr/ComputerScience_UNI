#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

#define nthreads 4         /* # numero de hilos */

int
main(){

  double x[SIZE],y[SIZE];
  double piSum=0.;
  int i,chunk,tid;
  double start,end,dif;
  
  srand(time(NULL));
  omp_set_num_threads(nthreads);
  chunk = SIZE/nthreads;
  #pragma omp parallel shared(x,y,chunk) private(start,dif,end,tid,i)
  {
    start = omp_get_wtime();
    tid = omp_get_thread_num();
    if (tid == 0)
    {
      printf("openMP se inicializa con %d threads.\n",nthreads);
      printf("Inicializando arrays...\n");
    }
    #pragma omp for ordered schedule (static, chunk)
      for(i=0;i<SIZE;i++){
        x[i] = (double)rand()/RAND_MAX;
        y[i] = (double)rand()/RAND_MAX;
      }
    #pragma omp for ordered schedule (static, chunk) reduction(+:piSum)
      for(i=0;i<SIZE;i++){
        if((x[i]*x[i]+y[i]*y[i])<=1){
          piSum+=1.;
        }
      }
    #pragma omp reduction(max:dif)
      end = omp_get_wtime();
      dif = end-start;
      if(tid==0){
        printf("El proceso paralelizado en openMP demoro %.8fs de tiempo.\n",dif);
      }
  }
  double piAprox = piSum/SIZE*4;

  printf("El montecarlo para PI es: %.6f\n\n",piAprox);
  return 0;
}
