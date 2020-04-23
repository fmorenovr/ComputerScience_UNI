/* ordenamiento quickSort */
#include <stdio.h>
#include <stdlib.h>

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
    quickSort(vector, i);
    quickSort(vector + i, n - i);
}

int main(){
  int n=10;
  double vector[n];
  int i;
  printf("\nInicializando el vector:\n");
  for(i=0;i<n;i++)
      vector[i]=(double)rand()/RAND_MAX;
  printf("\n");
  printf("Vector antes de quickSort:\n");
  for(i=0;i<n;i++)
    printf("%.4lf ",vector[i]);   
  printf("\n");
  quickSort(vector,n);
  printf("\n");
  printf("Vector despues de quickSort:\n");
  for(i=0;i<n;i++)
    printf("%.4lf ",vector[i]);   
  printf("\n\n");
  return 0;
}
