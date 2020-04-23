#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 160               /* number of rows in matrix A */
#define NCA 160               /* number of columns in matrix A */
#define NCB 90               /* number of columns in matrix B */

#define nthreads 4           /* # numero de hilos */

int
main (int argc, char *argv[]) 
{
  int	tid,                   /* thread ID */
      chunk,                 /* # de operaciones x hilo */
      i,j,k;
  double	a[NRA][NCA],           /* matrix A */
          b[NCA][NCB],           /* matrix B */
          c[NRA][NCB];           /* matrix C */

  omp_set_num_threads(nthreads);
  chunk = NRA/nthreads;                    /* # de veces chunk size */

  srand(time(0));
  double start,dif,end;
  printf("\n\n");
  /*** Region paralela para todas las variables ***/
  #pragma omp parallel shared(a,b,c,chunk) private(start,dif,end,tid,i,j,k)
  {
    start  = omp_get_wtime();
    tid = omp_get_thread_num();
    if (tid == 0)
    {
      printf("openMP se inicializa con %d threads.\n",nthreads);
      printf("Inicializando arrays...\n");
    }
    /*** Initialize matrices ***/
    #pragma omp for ordered schedule (static, chunk) 
      for (i=0; i<NRA; i++)
        for (j=0; j<NCA; j++)
          a[i][j]= rand()%3+1;
    #pragma omp for ordered schedule (static, chunk)
      for (i=0; i<NCA; i++)
        for (j=0; j<NCB; j++)
          b[i][j]= rand()%3+1;
    #pragma omp for ordered schedule (static, chunk)
      for (i=0; i<NRA; i++)
        for (j=0; j<NCB; j++)
          c[i][j]= 0;  
    /*** multiplicacion compartiendo iteraciones en el loop de sallida ***/
    printf("Thread %d empieza a multiplicar...\n",tid);
    #pragma omp for ordered schedule (static, chunk)
      for (i=0; i<NRA; i++)    
      {
        printf("Thread=%d hace la fila=%d\n",tid,i);
        for(j=0; j<NCB; j++)
          for (k=0; k<NCA; k++)
            c[i][j] += a[i][k] * b[k][j];
      }
    #pragma omp reduction(max:dif)
      end = omp_get_wtime();
      dif = end-start;
      if(tid==0){
        printf("El proceso paralelizado en openMP demoro %.8fs de tiempo.\n",dif);
      }
  }   /*** Fin de region paralela ***/
//  double end = omp_get_wtime();
//  double dif = end - start;
  
/*
  printf("\n\n");
  printf("Matrix A %dx%d:\n",NRA,NCA);
  for (i=0; i<NRA; i++)
  {
    printf("\n"); 
    for (j=0; j<NCA; j++) 
      printf("%6.2f ", a[i][j]);
  }
  printf("\n\n");
  printf("Matrix B %dx%d:\n",NCA,NCB);
  for (i=0; i<NCA; i++)
  {
    printf("\n"); 
    for (j=0; j<NCB; j++) 
      printf("%6.2f ", b[i][j]);
  }
  printf("\n\n");
  printf("Matrix C=AB %dx%d:\n",NRA,NCB);
  for (i=0; i<NRA; i++)
  {
    printf("\n"); 
    for (j=0; j<NCB; j++) 
      printf("%6.2f ", c[i][j]);
  }*/
  printf("\n\n");
  return 0;
}
