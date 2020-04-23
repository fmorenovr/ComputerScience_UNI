#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int
main(int argc, char* argv[])
{
  int n=3,i,j,k;
	int a[n][n],b[n][n],c[n],d,f,e[n][n];
	int rank,size,source;
	double time0,temp,time1;
	MPI_Status status;
	
	srand(time(0));
	MPI_Init (&argc, &argv);      /* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
	
	//fase de lectura de elementos
	for(i=0;i<n;i++){
	  c[i]=0;
		for(j=0;j<n;j++){
			a[i][j]=(int)rand()%3;
			b[i][j]=(int)rand()%3;
			e[i][j]=0;
		}
	}
	
	if(rank==0){
	  time0=MPI_Wtime();
		printf("\nMatrix A:\n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
		printf("\nMatrix B:\n");
	
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%d ",b[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for(i=rank;i<n;i+=size){
		for(j=0;j<n;j++){
		  c[j]=0;
		  for(k=0;k<n;k++)
    	  c[j]+=a[i][k]*b[k][j];
    }
    for(j=0;j<n;j++)
      e[i][j]=c[j];
  }
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank==0){
	  for(k=1;k<size;k++)
		  for(i=k;i<n;i+=size){
			  for(j=0;j<n;j++){
			    source=k;
    			MPI_Recv(&f, 1, MPI_INTEGER, source, 123, MPI_COMM_WORLD, &status);
				  e[i][j]=f;
			  }
		  }
		printf("\nMatrix C = A*B:\n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%d ",e[i][j]);
			}
			printf("\n");
		}
    time1=MPI_Wtime();
		printf("\nEl tiempo de proceso es: %.8lfs\n",(time1-time0));
	}
  else{
    for(i=rank;i<n;i+=size)
      for(j=0;i<n;j++){
        f=e[i][j];
        MPI_Send(&f,1,MPI_INTEGER, 0, 123, MPI_COMM_WORLD);
      }
//    MPI_Barrier(MPI_COMM_WORLD);
  }
  printf("Hola rank: %i\n",rank);
	MPI_Finalize();
	return 0;
}
