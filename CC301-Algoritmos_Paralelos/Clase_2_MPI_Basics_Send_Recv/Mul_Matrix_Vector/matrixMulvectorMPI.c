#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

/* Process mapping function */
int proc_map(int i, int size,int a)
{
  size = size - 1;
  int r = (int) ceil( (double)a / (double)size);
  int proc = i / r;
  return proc + 1;
}

int main(int argc, char** argv)
{
  int size, rank;
  int i,j;
  int AROW,ACOL;
  MPI_Status Stat;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (size < 2 ) {
    printf("Need at least two MPI tasks. Quitting...\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
    exit(1);
  }
  sscanf(argv[1],"%i",&AROW);
  sscanf(argv[2],"%i",&ACOL);

  if(rank == 0)
  {
    int a[AROW][ACOL];
    int b[ACOL];
    int c[AROW];

    /* Generando variables aleatorias para  A y B */
    srand(time(NULL));
    for(i=0;i<AROW;i++)
    {
      for(j=0;j<ACOL;j++)
      {
        if(i==0) b[j] = rand() % 500;
          a[i][j] = rand() % 500;
      }
    }

    /* Printing the Matrix*/

    printf("Matrix A :\n");
    for(i=0;i<AROW;i++)
    {
      for(j=0;j<ACOL;j++)
      {
        printf("%3d ", a[i][j]);
      }
      printf("\n");
    }
    printf("\nMatrix B :\n");
    for(i=0;i<ACOL;i++)
    {
      printf("%3d ", b[i]);
    }
    printf("\n\n");
    /* (1) Envio valores de B a otros procesadores */
    for(j=1;j<size;j++)
    {
      MPI_Send(b, ACOL, MPI_INTEGER, j, 99, MPI_COMM_WORLD);
    }

    /* (2) Envio filas especificas a cada procesador */
    for(i=0;i<AROW;i++)
    {
      int processor = proc_map(i, size,AROW);
      MPI_Send(a[i], ACOL, MPI_INTEGER, processor, (100*(i+1)), MPI_COMM_WORLD);
    }

    /* (3) Traigo los resultados a mi procesador*/
    for(i=0;i<AROW;i++)
    {
      int source_process = proc_map(i, size,AROW);
      MPI_Recv(&c[i], 1, MPI_INTEGER, source_process, i, MPI_COMM_WORLD, &Stat);
      printf("P%d : c[%d]\t= %d\n", rank, i, c[i]);
    }
  }
  else
  {
    int b[ACOL];

    /* (1) Each process get B Values from Master */
    MPI_Recv(b, ACOL, MPI_INTEGER, 0, 99, MPI_COMM_WORLD, &Stat);

    /* (2) Get Required A Values from Master then Compute the result */
    for(i=0;i<AROW;i++)
    {
      int processor = proc_map(i, size,AROW);
      if(rank == processor)
      {
        int buffer[ACOL];
        MPI_Recv(buffer, ACOL, MPI_INTEGER, 0, (100*(i+1)), MPI_COMM_WORLD, &Stat);
        int sum = 0;
        for(j=0;j<ACOL;j++)
        {
          sum = sum + (buffer[j] * b[j] );
        }
        MPI_Send(&sum, 1, MPI_INTEGER, 0, i, MPI_COMM_WORLD);
      }
    }
  }

  MPI_Finalize();
  return 0;
}
