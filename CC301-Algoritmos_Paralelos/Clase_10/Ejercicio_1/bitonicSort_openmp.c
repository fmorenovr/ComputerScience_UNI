#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void bitonicSort(int, int *, int);
void bitonicMerge(int, int *, int);
void bitonicCompare(int, int *, int);
void swap(int *, int *);
void printArray(int*,int);

int main(int argc, char ** argv)
{
  int i;
  int * arr;
  int N;
  double end,start;
  FILE *fp = fopen(argv[1],"r");

  if (fp == NULL) {
    fprintf(stderr,"file not found\n");
    exit(1);
  }
  omp_set_num_threads(4);
  // first line gives number of numbers to be sorted 
  fscanf(fp,"%d",&N);
  // allocate space and read all the numbers
  arr = (int *)malloc(N*sizeof(int));
  for (i=0; i < N; i++) {
    fscanf(fp,"%d",(arr+i));
  }
  printf("\nAntes de bitonicSort OpenMP\n");
  printArray(arr,N);
  start  = omp_get_wtime();
  bitonicSort(1, arr, N);
  end  = omp_get_wtime();
  printf("\nDespues de bitonicSort OpenMP\n");
  printArray(arr,N);
  printf("\n");
  printf("El proceso paralelizado en openMP demoro %.8fs de tiempo.\n\n",end-start);
  return 0;
}

void bitonicSort(int up, int * sequence, int size)
{
  if(size == 1)
    return;
  else
  {
    bitonicSort(1, sequence,size/2);
    bitonicSort(0, sequence+size/2, size/2);
    bitonicMerge(up, sequence, size);
  }
}

void bitonicMerge(int up, int * sequence, int size)
{
  if(size == 1)
    return;
  else
  {
    bitonicCompare(up, sequence, size);
    bitonicMerge(up, sequence, size/2);
    bitonicMerge(up, sequence+size/2, size/2);
  }
}

void bitonicCompare(int up, int * sequence, int size)
{
  int distance = size/2;
  int * start, * end = sequence+distance;
  #pragma omp parallel for private(start) shared(sequence, end, up, distance)
  for(start = sequence; start < end; start++)
    if( (*start > *(start+distance)) == up)
      swap(start, start+distance);
}

void swap(int * x, int * y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void printArray(int *arr, int n) {
  int i;
  printf("[%d",arr[0]);
  for (i=1; i < n;i++) {
    printf(",%d",arr[i]);
  }
  printf("]\n");
}
