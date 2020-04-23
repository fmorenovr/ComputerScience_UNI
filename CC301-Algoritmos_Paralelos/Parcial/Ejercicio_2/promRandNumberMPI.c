#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>
#define N 10

void randomAlloc(double *v);
void imprime(double *v);

int
main(int argc, char *argv[]){
	//double vi[N];	
	double vi[N];
	int a,b;
	int n,i;	
	int size, rank;
	double t1,t0; //variables para el tiempo
	double sum=0.0,sumtotal;
	double prodtotal,prod=1.0;
	double prom,promtotal;
	double minTotal,maxTotal;
	
	srand(time(NULL));
		
  randomAlloc(vi);
/*inicializacion de MPI	*/
	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	//se reparte informacion a cada procesador

//  n=N/size;
  
  MPI_Barrier( MPI_COMM_WORLD );
  /*a=n*rank;
  b=n*(rank+1);*/
  t0 = MPI_Wtime();

  // Suma de los numeros
  for(i=rank;i<N;i+=size){
	  sum=sum+vi[i];
  }
  prom = sum/N; // Promedio parcial

  // Producto de los numeros
  for(i=rank;i<N;i+=size){
	  prod=prod*vi[i];
  }
  // maximo local
  // minimo local
  double max = vi[rank];
  double min = vi[rank];
  for(i=rank;i<N;i+=size){
    if (vi[i]> max)
	    max = vi[i];
	  if (vi[i]<min)
	    min = vi[i];
  }

/* // Decomentar para ver los datos en los procesos  
  printf("Promedio parcial del proceso %i es: %f\n",rank,prom);
  printf("Suma parcial del proceso %i es: %f\n",rank,sum);
  printf("Producto parcial del proceso %i es: %f\n",rank,prod);

  printf("El minimo local del proceso %i es:%lf\n",rank,min);
  printf("El maximo local del proceso %i es:%lf\n",rank,max);
*/
  MPI_Barrier(MPI_COMM_WORLD);	

  MPI_Allreduce( &sum, &sumtotal, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );
  MPI_Allreduce( &prod, &prodtotal, 1, MPI_DOUBLE, MPI_PROD, MPI_COMM_WORLD );
  MPI_Allreduce( &prom, &promtotal, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );
  MPI_Allreduce( &max, &maxTotal, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD );
  MPI_Allreduce( &min, &minTotal, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD );
  
  MPI_Barrier(MPI_COMM_WORLD);
  t1 = MPI_Wtime();
   if( rank == 0 ){
    printf("El vector es:\n");
    imprime(vi);
    printf("\nSuma total del vector es: %f\n", sumtotal);
    printf("Promedio total del vector es:%f\n", promtotal);
    printf("Producto total del vector es:%f\n", prodtotal);
    printf("Maximo total del vector es:%f\n", maxTotal);
    printf("Minimo total del vector es:%f\n", minTotal);
    printf("El tiempo es %fs con %d nodos\n", t1-t0, size);
  }
  MPI_Finalize();
  return 0;
}

void randomAlloc(double *v){
	int i;
	for(i=0;i<N;i++){
		v[i]=rand()%10+1;
    }
}

void imprime(double *v){
	int i;
	for(i=0;i<N;i++)
		printf("%f ",v[i]);
}
