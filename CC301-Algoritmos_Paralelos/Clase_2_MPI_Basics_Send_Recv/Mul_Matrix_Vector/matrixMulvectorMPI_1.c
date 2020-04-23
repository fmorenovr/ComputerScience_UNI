#include <stdio.h>
#include <mpi.h>
#include <time.h>
int main(int argc, char* argv[]){
	int n=500,i,j;
	int a[n][n],b[n],c[n],d[n];
	int rank,size;
	double time0,temp,time1;
	MPI_Status status;
	
	srand(time(0));
	MPI_Init (&argc, &argv);      /* starts MPI */
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
	
	//fase de lectura de elementos
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=rand()%6;
		}
	}
	
	for(i=0;i<n;i++){
		c[i]=0;
		d[i]=0;
		b[i]=rand()%6;
	}
	
	/*if(rank==0){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%3d ",a[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	
		for(i=0;i<n;i++){
			printf("%3d\n",b[i]);
		}
		printf("\n");
	}
	*/
	time0=MPI_Wtime();

	time0=MPI_Wtime();
	for(i=rank;i<n;i+=size){
		for(j=0;j<n;j++){
			c[i]+=a[i][j]*b[j];
		}
	}
	if(rank!=0)
		MPI_Send(c, n, MPI_INT, 0, 1234+rank, MPI_COMM_WORLD);
	if(rank==0){
		for(i=1;i<size;i++){
			MPI_Recv(d, n, MPI_INT, i, 1234+i, MPI_COMM_WORLD, &status);
			for(j=0;j<n;j++){
				c[j]+=d[j];
			}
		}
	}
	time1=MPI_Wtime();
	MPI_Reduce(&time1, &temp, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	if(rank==0){
		printf("El tiempo es: %.8lfs\n",(temp-time0));
	}
/*	if(rank==0){
		for(i=0;i<n;i++){
			printf("%3d\n",c[i]);
		}
	}*/
	MPI_Finalize();
	return 0;
}
