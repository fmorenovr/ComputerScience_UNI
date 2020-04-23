#include <stdio.h>
#include <stdlib.h>
#include "quantum.h"
#include <omp.h>

void main(int argc, char* argv){
  printf("Hello world libQuantum\n");
  printf("Ingresa el numero de threads: \n");
  int n;
  scanf("%i",&n);
  omp_set_num_threads(n);
  quantum_matrix A,B;
  A = quantum_new_matrix(10,4);
  B = quantum_new_matrix(4,10);
  printf("Matriz A:\n");
  quantum_print_matrix(A);
  printf("Matriz B:\n");
  quantum_print_matrix(B);
  quantum_matrix C = quantum_mmult(A,B);
  printf("Matriz C:\n");
  quantum_print_matrix(C);
  return;
}

// gcc libquantum.a -fopenmp
