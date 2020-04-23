#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SIZE 100000

int
main(int argc, char *argv[]){

  int size,rank;
  double x[SIZE],y[SIZE];
  double piSum=0.;
  int i;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  
  srand(time(NULL));
  double start = MPI_Wtime();
  for(i=rank;i<SIZE;i+=size){
    x[i] = (double)rand()/RAND_MAX;
    y[i] = (double)rand()/RAND_MAX;
  }
  
  for(i=rank;i<SIZE;i+=size){
    if((x[i]*x[i]+y[i]*y[i])<=1){
      piSum+=1.;
    }
  }
  
  double piAprox;
  MPI_Allreduce(&piSum,&piAprox,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
  piAprox = piAprox/SIZE*4;
  
  double end = MPI_Wtime();
  double dif = end - start;
  double time_tot;
  MPI_Allreduce(&dif,&time_tot,1,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD);
  if(rank==0){
    printf("\n\nEl proceso paralelizado en MPI demoro %.8fs de tiempo.\n",time_tot);
    printf("El montecarlo para PI es: %.6f\n\n\n",piAprox);
  }
  MPI_Finalize();
  return 0;
}
