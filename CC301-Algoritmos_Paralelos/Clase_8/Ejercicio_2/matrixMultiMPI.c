#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 160               /* # de filas de matrix A */
#define NCA 160               /* # de columnas de matrix A */
#define NCB 90               /* # de conlumnas in matrix B */
#define MASTER 0            /* rank del primer proceso(task) */
#define FROM_MASTER 1       /* tipo de mensaje */
#define FROM_WORKER 2       /* tipo de mensaje */

int
main (int argc, char *argv[])
{
  int	size,                  /* # de procesos */
	    rank,                  /* procesoID */
	    numworkers,            /* number de procesadores de instrucciones tasks */
	    source,                /* task id del mensaje origen */
	    dest,                  /* task id del mensaje destino */
	    mtype,                 /* message type */
	    rows,                  /* # fila de matrix A enviado a otro proceso */
	    averow, extra, offset, /* determina el numero de filas a enviar a otro proceso */
	    i, j, k, rc;           /* misc */
  double	a[NRA][NCA],           /* matrix A */
	        b[NCA][NCB],           /* matrix B */
	        c[NRA][NCB];           /* matrix C = AB */
  MPI_Status status;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  if(size<2)
  {
    printf("se necesita almenos  2 tareas(procesos) MPI. Saliendo...\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(1);
  }
  numworkers = size-1;

  srand(time(0));
  double start = MPI_Wtime();
/**************************** master task ************************************/
  if (rank == MASTER)
  {
    printf("MPI se inicializa con %d procesos copia.\n",size);
    printf("Inicializando arrays...\n");
    for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= rand()%3+1;

    for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
        b[i][j]= rand()%3+1;

    /* envia datos de matrix a los otros procesos */
    averow = NRA/numworkers; // # de filas por cada proceso
    extra = NRA%numworkers;  // las que sobran
    offset = 0;
    mtype = FROM_MASTER; // desde el master
    for (dest=1; dest<=numworkers; dest++)
    {
      rows = (dest <= extra) ? averow+1 : averow;   	
      printf("Enviando %d filas a la tarea %d, compensado=%d\n",rows,dest,offset);
      MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
      MPI_Send(&a[offset][0], rows*NCA, MPI_DOUBLE, dest, mtype,MPI_COMM_WORLD);
      MPI_Send(&b, NCA*NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
      offset = offset + rows;
    }

    /* Recibe resultados de los procesos */
    mtype = FROM_WORKER;
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&c[offset][0], rows*NCB, MPI_DOUBLE, source, mtype, MPI_COMM_WORLD, &status);
      printf("Recibido desde el proceso: %d\n",source);
    }

    /* Print results */
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
  }


/**************************** proceso task ************************************/
  if (rank > MASTER)
  {
    mtype = FROM_MASTER;
    MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
    MPI_Recv(&a, rows*NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
    MPI_Recv(&b, NCA*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

    for (k=0; k<NCB; k++)
      for (i=0; i<rows; i++)
      {
        c[i][k] = 0.0;
        for (j=0; j<NCA; j++)
          c[i][k] += + a[i][j] * b[j][k];
      }
    mtype = FROM_WORKER;
    MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
    MPI_Send(&c, rows*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
  }
  double end = MPI_Wtime();
  double dif = end - start;
  double time_tot;
  MPI_Allreduce(&dif,&time_tot,1,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD);
  if(rank == MASTER)
  {
    printf("El proceso paralelizado en MPI demoro %.8fs de tiempo.\n",time_tot);
  }  
  MPI_Finalize();
  return 0;
}
