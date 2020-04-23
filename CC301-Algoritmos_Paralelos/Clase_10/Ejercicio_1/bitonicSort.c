#include <stdio.h>
#include <stdlib.h>

void merge_up(int*,int);
void merge_down(int*,int);
void printArray(int*,int);
void swap(int*,int*);

int main(int argc, char **argv) {
  int n, *arr, i,s;
  FILE *fp = fopen(argv[1],"r");

  if (fp == NULL) {
    fprintf(stderr,"file not found\n");
    exit(1);
  }
  // first line gives number of numbers to be sorted 
  fscanf(fp,"%d",&n);
  // allocate space and read all the numbers
  arr = (int *)malloc(n*sizeof(int));
  for (i=0; i < n; i++) {
    fscanf(fp,"%d",(arr+i));
  }
  // print array before 
  printf("\nAntes de bitonicSort\n");
  printArray(arr,n);
  // do merges
  for (s=2; s <= n; s*=2) {
    for (i=0; i < n;) {
      merge_up((arr+i),s);
      merge_down((arr+i+s),s);
      i += s*2;
    }
  }
  printf("\nDespues de bitonicSort\n");
  printArray(arr,n);
  printf("\n");
  return 0;
}

void swap(int * x, int * y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void merge_up(int *arr, int n) {
  int step=n/2,i,j,k,temp;
  while (step > 0) {
    for (i=0; i < n; i+=step*2)
      for (j=i,k=0;k < step;j++,k++) {
        if (arr[j] > arr[j+step]) {
          swap(arr+j,arr+j+step);
        }
      }
    step /= 2;
  }
}

void merge_down(int *arr, int n) {
  int step=n/2,i,j,k,temp;
  while (step > 0) {
    for (i=0; i < n; i+=step*2)
      for (j=i,k=0;k < step;j++,k++) {
        if (arr[j] < arr[j+step]) {
          swap(arr+j,arr+j+step);
        }
      }
    step /= 2;
  }
}

void printArray(int *arr, int n) {
  int i;
  printf("[%d",arr[0]);
  for (i=1; i < n;i++) {
    printf(",%d",arr[i]);
  }
  printf("]\n");
}
