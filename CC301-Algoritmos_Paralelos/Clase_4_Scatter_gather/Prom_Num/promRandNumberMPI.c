#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>
#define N 1000

void randomAlloc(double *v);
void imprime(double *v);

int
main(int argc, char *argv[]){
	//double vi[N];	
	double vector[N];
	int a,b;
	int n,i;	
	int size, rank;
	double t1,t0; //variables para el tiempo
	double sum,sumtotal;
	
	srand(time(NULL));
		
  randomAlloc(vector);
/*inicializacion de MPI	*/
	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	//se reparte informacion a cada procesador
  if(size%2!=0 && size!=1){
    if(rank==0)
      printf("Usar numero de procesadores par!!!\nExit program !!\n");
    MPI_Finalize();
    return 0;
  }else
  {
	  n=N/size;
	  double vi[n];
	  MPI_Scatter(&vector,n,MPI_DOUBLE,&vi,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	  MPI_Barrier( MPI_COMM_WORLD );
	  sum=0.0;
	  /*a=n*rank;
	  b=n*(rank+1);*/
	  t0 = MPI_Wtime();
	
	  for(i=0;i<n;i++){
		  sum=sum+vi[i];
	  }
	  sum = sum/n; // Promedio parcial
	  
	  printf("Promedio parcial del proceso %i es: %f\n",i,sum);
		
	  MPI_Allreduce( &sum, &sumtotal, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );
    MPI_Barrier(MPI_COMM_WORLD);
	  t1 = MPI_Wtime();
	   if( rank == 0 ){
      printf("la suma de los promedios parciales es: %f\n", sumtotal);
	    printf("promedio total de todos los procesos es:%f\n", sumtotal/size);	
      printf("El tiempo es %fs con %d nodos\n", t1-t0, size);
	  }
	  MPI_Finalize();
	}
  return 0;
}

void randomAlloc(double *v){
	int i;
	for(i=0;i<N;i++){
		v[i]=rand()%100;
			}
		}

void imprime(double *v){
	int i;
	for(i=0;i<N;i++)
		printf("%f ",v[i]);
			}
