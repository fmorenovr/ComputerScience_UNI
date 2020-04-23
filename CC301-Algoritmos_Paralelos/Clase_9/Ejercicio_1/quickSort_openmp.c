/* ordenamiento quickSort */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void quickSort(double*, int);

void quickSort(double *vector, int n) {
    int i, j;
    double t,p;
    if (n < 2)
        return;
    p = vector[n / 2];
    for (i=0,j=n-1;; i++, j--) {
        while (vector[i] < p)
            i++;
        while (p < vector[j])
            j--;
        if (i >= j)
            break;
        t = vector[i];
        vector[i] = vector[j];
        vector[j] = t;
    }
    #pragma omp task
      quickSort(vector, i);
    #pragma omp task
      quickSort(vector + i, n - i);
    #pragma omp taskwait
}

int main(){
  int n=10;
  double vector[n];
  int i;
  omp_set_num_threads(4);
  printf("\nInicializando el vector:\n");
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
        vector[i]=rand()%n + (double)rand()/RAND_MAX;
  printf("\n");
  printf("Vector antes de quickSort:\n");
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
      #pragma omp ordered
        printf("%.4lf ",vector[i]);   
  printf("\n");
  #pragma omp parallel
    #pragma omp single
      quickSort(vector,n);
  printf("\n");
  printf("Vector despues de quickSort:\n");
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
      #pragma omp ordered
        printf("%.4lf ",vector[i]);   
  printf("\n\n");
  return 0;
}
