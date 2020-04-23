#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

double f( double );
double f( double a )
{
  return (4.0 / (1.0 + a*a));
}

int main(int argc, char *argv[])
{
  int num_th, th_id;
  int rank, size;
  int i,n;
  double pi_25 = 3.141592653589793238462643;
  double piomp, pi , h, sumpi, x;
  double startwtime, endwtime;
  double time, timeMax;

  int  namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];

  num_th = omp_get_max_threads();
  omp_set_num_threads(num_th);
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Get_processor_name(processor_name,&namelen);

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0)
  {
    if( argc == 2 ) {
      sscanf( argv[1], "%d", &n );
    } 
    else {      
      printf("\nIngrese numero de intervalos: \n");
      fflush(stdout);
      scanf("%d",&n);
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (n == 0){
    if (rank==0)
      printf("\nNo puede haber division entre 0.\n\n");
  }else{
    startwtime = MPI_Wtime();
    h = 1.0 / (double)n;
    #pragma omp parallel private(th_id,sumpi,x,i,startwtime, endwtime) shared(num_th,n,piomp,h)
    {
      th_id=omp_get_thread_num();
      if (th_id == 0 && rank ==0){
        printf("\nCalculando PI en OpenMP+MPI usando %d intervalos.\n\n",n);
      }
      piomp = 0.0;
      sumpi=0.0;
      #pragma omp barrier
      fprintf(stderr,"Proceso: %d thread: %d, en %s\n",rank,th_id, processor_name);
      #pragma omp barrier
      #pragma omp for reduction(+:piomp)
        for(i = rank + 1; i <= n; i += size) {
          x = h * ((double)i - 0.5);
          sumpi = f(x);
          piomp = piomp + sumpi*h;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&piomp, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  endwtime = MPI_Wtime();
  time = endwtime-startwtime;
  MPI_Reduce(&time,&timeMax,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
  if (rank == 0){
    printf("\npi aprox es: %.16f\nError es: %.16f\n",pi, fabs(pi - pi_25));
    printf("El calculo fue en %lfs en %d procesos con %d hilos por proceso\n\n",timeMax,size,num_th);
  }
  MPI_Finalize();
  return 0;
}
