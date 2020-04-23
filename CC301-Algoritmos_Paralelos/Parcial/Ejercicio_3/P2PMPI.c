#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>

#define USERS 1000

int rank,size;
int sum=0.0;

int
main(int argc, char *argv[]){
  FILE *f;
  int i;
  int useraux;
  int aux,tag;
    
  /*inicializacion de MPI	*/
	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  MPI_Status status;

  int user = USERS + 100*rank;
  useraux = user;
//  printf("Usuarios del proceso %i es: %i\n",rank,user);
  
  MPI_Barrier(MPI_COMM_WORLD);
  if(size>1){
    for(i=0;i<size;i++){
			//el rank 0 solo envia al rank 1
			if(i==0&&rank==0){
				MPI_Send(&user,1,MPI_INT,rank+1,tag+rank,MPI_COMM_WORLD);
			}
			//el ultimo rank recibe del penultimo rank
			if(i==size-1&&rank==size-1){
				MPI_Recv(&aux,1,MPI_INT,rank-1,tag+rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				useraux=user+aux;
			}
			//los rank's internos primero reciben del rank anterior a ellos para que luego vuelvan a enviar
			if((i!=0&&i!=size-1)&&(rank==i)){
				MPI_Recv(&aux,1,MPI_INT,rank-1,tag+rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				useraux=user+ aux;
				MPI_Send(&useraux,1,MPI_INT,rank+1,tag+rank,MPI_COMM_WORLD);
			}
		}
  /*if (rank!=size-1){
    MPI_Send(&user,1,MPI_INT,rank+1,12+rank,MPI_COMM_WORLD);
    if (rank!=0){
      MPI_Recv(&useraux,1,MPI_INT,rank-1,rank+11,MPI_COMM_WORLD,&status);
      user = user + useraux;
    }
  }*/  
  }
  
  if (rank==0)
    printf("Rank\t\tUser/Proceso\t\tSum:\n");
  MPI_Barrier(MPI_COMM_WORLD);
  printf("%i\t\t%i\t\t%i\n",rank,user,useraux);
  
  if(rank!=0){
    //cada rank envia su numero de usuarios y su suma acumulada al rank 0
		MPI_Send(&user,1,MPI_INT,0,tag+rank*100,MPI_COMM_WORLD);
		MPI_Send(&useraux,1,MPI_INT,0,tag+rank*1000,MPI_COMM_WORLD);
  }
  else{
   int us,usaux;
    f=fopen("Tabla.txt","w");
    // el rank 0 recibe los valores de los demas rank y luego los imprime
    fprintf(f,"Rank\t\tUser/Proceso\t\tSum:\n");
    fprintf(f,"%i\t\t%i\t\t%i\n",rank,user,useraux);
    for(i=1;i<size;i++){
      MPI_Recv(&us,1,MPI_INT,i,tag+i*100,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&usaux,1,MPI_INT,i,tag+i*1000,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			fprintf(f,"%i\t\t%i\t\t%i\n",i,us,usaux);
    }
    fclose(f);
  }
  MPI_Finalize();
  return 0;
}
