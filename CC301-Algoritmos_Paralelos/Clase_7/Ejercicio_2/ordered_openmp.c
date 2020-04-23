#include <omp.h>
#include <stdio.h>
#define chunksize 5
#define SIZE 100

int
main(void)
{
  int a[SIZE];
  int i,n,th_id;
  n=SIZE;
  printf("\nAntes de el for paralelo\nEl vector a es:\n");
  for(i=0;i<n;i++)
    printf("a[%d]:%d\n",i,a[i]);
  printf("\n\n");
  #pragma omp parallel for ordered schedule(static,chunksize)
    for(i=0;i<n;i++){
      a[i]=i;
      printf("%d del hilo %d\n",i,omp_get_thread_num());
    }
  printf("\nDespues de el for paralelo\nEl vector a es:\n");
  for(i=0;i<n;i++)
    printf("a[%d]:%d\n",i,a[i]);
  return 0;
}
