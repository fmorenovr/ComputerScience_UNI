#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>

#define SIZE 10

double t0,t1;

static int intcompare(const void *i, const void *j)
{
  if ((*(int *)i) > (*(int *)j))
    return (1);
  if ((*(int *)i) < (*(int *)j))
    return (-1);
  return (0);
}

int main (int argc, char *argv[])
{
  srand(time(NULL));
  int  size,rank, master = 0;
  int  i,j,k, totElem, totElem_Bloc, elemToSort;
  int  count;
  int  *Input , *InputData  ; 
  int  *Splitter, *AllSplitter;
  int  *Buckets, *BucketBuffer, *LocalBucket;
  int  *OutputBuffer, *Output;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  Input=NULL;
  Output=NULL;
  OutputBuffer=NULL;

  if(argc != 2) {
    if(rank ==0)
      printf("\nUsage : recibe como parametro el numero de datos\n\n");
	 MPI_Finalize();
	 exit(0);
	}

  // entrada de datos
  
  if (rank == master){
    totElem = atoi(argv[1]);
    Input = (int *) malloc (totElem*sizeof(int));
    if(Input == NULL) {
      printf("Error : No se puede reservar memoria \n");
    }
    printf("\nArray antes del bucketSort\n\n");
    for(i=0; i< totElem; i++) {
      Input[i] = rand()%totElem;
      printf("%d ",Input[i]);
    }
    printf("\n\n");
  }
  t0=MPI_Wtime();

  // Envia datos
  MPI_Bcast (&totElem, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if(( totElem % size) != 0){
    if(rank == master)
      printf("Numero de Elementos no es divisible por size \n\n");
    MPI_Finalize();
    exit(0);
  }

  totElem_Bloc = totElem / size;
  InputData = (int *) malloc (totElem_Bloc * sizeof (int));

  // enviando desde el master los numeros
  MPI_Scatter(Input, totElem_Bloc, MPI_INT, InputData,totElem_Bloc, MPI_INT, master, MPI_COMM_WORLD);

  // ordenando cada bucket
  qsort((char *) InputData, totElem_Bloc, sizeof(int), intcompare);

  // escogiendo los splitters
  Splitter = (int *) malloc (sizeof (int) * (size-1));
  for (i=0; i< (size-1); i++){
        Splitter[i] = InputData[totElem/(size*size) * (i+1)];
  } 

  // enviando hacia el master los splitters
  AllSplitter = (int *) malloc (sizeof (int) * size * (size-1));
  MPI_Gather(Splitter, size-1, MPI_INT, AllSplitter, size-1,MPI_INT, master, MPI_COMM_WORLD);

  // Escoje los splitters globales
  if (rank == master){
    qsort ((char *) AllSplitter, size*(size-1), sizeof(int), intcompare);

    for (i=0; i<size-1; i++)
      Splitter[i] = AllSplitter[(size-1)*(i+1)];
  }
  
  // compartiendo los spliters globales
  MPI_Bcast (Splitter, size-1, MPI_INT, 0, MPI_COMM_WORLD);

  // Crea los buckets locales
  Buckets = (int *) malloc (sizeof (int) * (totElem + size));
  j = 0;
  k = 1;
  for (i=0; i<totElem_Bloc; i++){
    if(j < (size-1)){
      if (InputData[i] < Splitter[j]) 
			  Buckets[((totElem_Bloc + 1) * j) + k++] = InputData[i]; 
      else{
	      Buckets[(totElem_Bloc + 1) * j] = k-1;
		    k=1;
			  j++;
		    i--;
      }
    }
    else 
      Buckets[((totElem_Bloc + 1) * j) + k++] = InputData[i];
  }
  Buckets[(totElem_Bloc + 1) * j] = k - 1;

  // envia los buckets a cada procesador
  BucketBuffer = (int *) malloc (sizeof (int) * (totElem + size));
  MPI_Alltoall(Buckets, totElem_Bloc + 1, MPI_INT, BucketBuffer,totElem_Bloc + 1, MPI_INT, MPI_COMM_WORLD);

  // reordenando los buckets
  LocalBucket = (int *) malloc (sizeof (int) * 2 * totElem / size);
  count = 1;
  for (j=0; j<size; j++) {
    k = 1;
    for (i=0; i<BucketBuffer[(totElem/size + 1) * j]; i++) 
      LocalBucket[count++] = BucketBuffer[(totElem/size + 1) * j + k++];
  }
  LocalBucket[0] = count-1;

  // ordenando los buckets locales usando bubble sort
  /*qsort ((char *) InputData, totElem_Bloc, sizeof(int), intcompare); */
  elemToSort = LocalBucket[0];
  qsort ((char *) &LocalBucket[1], elemToSort, sizeof(int), intcompare); 

  // Enviando al master los buckets ordenados localmente
  if(rank == master) {
    OutputBuffer = (int *) malloc (sizeof(int) * 2 * totElem);
    Output = (int *) malloc (sizeof (int) * totElem);
  }
  MPI_Gather(LocalBucket, 2*totElem_Bloc, MPI_INT, OutputBuffer ,2*totElem_Bloc, MPI_INT, master, MPI_COMM_WORLD);

  // reordenando las salidas
  if (rank == master){
    count = 0;
    for(j=0; j<size; j++){
      k = 1;
      for(i=0; i<OutputBuffer[(2 * totElem/size) * j]; i++) 
        Output[count++] = OutputBuffer[(2*totElem/size) * j + k++];
    }
    t1=MPI_Wtime();

    // Imprime la salida
    printf("Array despues del bucketSort\n\n");
    for (i=0; i<totElem; i++){
      printf("%d ", Output[i]);
    }
    printf("\n\n");
    printf("Tiempo de ordenamiento: %.12fs en %d procesos.\n\n",t1-t0,size);
  }
  MPI_Finalize();
  return 0;
}
