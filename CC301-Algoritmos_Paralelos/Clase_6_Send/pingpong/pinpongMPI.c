#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include<math.h>
#include "mpi.h"
#define N 10
#define T 5 //aqui definimos T que representa el nro de iteraciones 
void aleatorio(double v[N]);
void imprime(double v[N]);
void pedirT(int *t);

int
main(int argc,char*argv[]){
	int rank,size;	
	double t0,t1;
	double vector[N],vector2[N];
	double v2[N];
	double v1[N];
	MPI_Status status;
	srand(time(NULL));	
	aleatorio(vector);//ve mensaje-vector que se tomara de reenvio  
	/*Inicializacion del MPI*/
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank==0 && size!=2){
    printf("Solo usar 2 procesadores\n");
	  exit(0);
	}
	//reparte informacion a cada procesador 
	t0=MPI_Wtime();
	int count=0;	
	int partner_rank=(rank+1)%2;
	while(count<T){	
	  if(rank == count% 2){
		  count++;
		  MPI_Send(&vector, N, MPI_DOUBLE, partner_rank,30, MPI_COMM_WORLD);
		  MPI_Send(&count,1, MPI_INT, partner_rank,20, MPI_COMM_WORLD);
		  printf("Procesador %d envia el  vector siguiente a %d\n",rank,partner_rank);
		  imprime(vector);
		  printf("\n");	
		}
	  else {
		  MPI_Recv(&vector, N, MPI_DOUBLE, partner_rank, 30, MPI_COMM_WORLD,&status);
		  MPI_Recv(&count, 1, MPI_INT, partner_rank,20, MPI_COMM_WORLD,&status);
		  printf("Procesador %d recive el vector siguiente de %d\n",partner_rank,rank);
		  imprime(vector);
		  printf("\n");
    }
	}
	/*t0 = MPI_Wtime()-t0;
	MPI_Reduce( &t0, &t1, 1, MPI_DOUBLE, MPI_MAX,0, MPI_COMM_WORLD );
	printf("El calculo tomo %lf segundos con %d nodos\n", t1, size);*/
	MPI_Finalize();
return 0;
}

void aleatorio(double v[N]){
	//numeros aleatorios enteros hasta 100
	long i;
	for(i=0;i<N;i++){
		v[i]=rand()%100+1;
					}
		}

void imprime(double v[N]){
	long i;
	for(i=0;i<N;i++)
		printf("%.2f ",v[i]);
			}
void pedirT(int *t){
	int n;
	printf("ingrese nro de iteraciones\n");
	scanf("%d",&n);
	*t=n;
				}
