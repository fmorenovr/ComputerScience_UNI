/*
##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################
*/


# ifndef _MATRIXOP_H
# define _MATRIXOP_H

# ifndef __MATRIXOP_INLINE
#  ifndef __extern_inline
#   define __MATRIXOP_INLINE inline
#  else
#   define __MATRIXOP_INLINE __extern_inline
#  endif
# endif

/* Asignacion de variables a un vector */
__MATRIXOP_INLINE double*allocVector(int);

__MATRIXOP_INLINE double *
allocVector(int dim)
{
  int i;
  double *vector;
  //allocate space for values at once, so as to be contiguous in memory
  vector = (double *)malloc(dim*sizeof(double ));

  return vector;
}

/* Asignacion de variables a una matrix nxn */
__MATRIXOP_INLINE double**allocMatrix(int);

__MATRIXOP_INLINE double **
allocMatrix(int dim)
{
  int i;
  double **matrix;
  //allocate space for values at once, so as to be contiguous in memory
  matrix = (double **)malloc(dim*sizeof(double *));
  matrix[0] = (double *)malloc(dim*sizeof(double));
  for(i=1; i < dim; i++) {
      matrix[i]=&matrix[0][dim*i];
      //matrix[i] = (double *)malloc(dim*sizeof(double));
  }
  return matrix;
}

/* Asignacion de variables a una matriz nxm */

__MATRIXOP_INLINE double**allocMatrixDiffer(int,int);

__MATRIXOP_INLINE double **
allocMatrixDiffer(int n,int m)
{
  int i;
  double **matrix;
  //allocate space for values at once, so as to be contiguous in memory
  matrix = (double **)malloc(n*sizeof(double *));
  matrix[0] = (double *)malloc(m*sizeof(double));
  for(i=1; i < n; i++) {
      matrix[i]=&matrix[0][m*i];
      //matrix[i] = (double *)malloc(m*sizeof(double));
  }
  return matrix;
}

/* Imprimir matrix nxn */

__MATRIXOP_INLINE void printMatrix(double **, int);

__MATRIXOP_INLINE void
printMatrix(double **values, int size)
{
  int i, j;
  for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++) {
          printf("%10lf ", values[i][j]);
      }
      printf("\n");
  }
}

/* Imprimir matrix nxm */

__MATRIXOP_INLINE void printMatrixDiffer(double **,int,int);

__MATRIXOP_INLINE void
printMatrixDiffer(double **values, int n,int m)
{
  int i, j;
  for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
          printf("%10lf ", values[i][j]);
      }
      printf("\n");
  }
}

/* Liberar memoria de matriz */

__MATRIXOP_INLINE void freeMatrix(double **);

__MATRIXOP_INLINE void
freeMatrix(double **values) {
    free(values[0]);
    free(values);
}

/* Multiplicar matriz por matriz de nxn*/

__MATRIXOP_INLINE double**matrixMulMatrix(double**,double**,int);

__MATRIXOP_INLINE double**
matrixMulMatrix(double**A,double**B,int dim)
{
  int i, j, k;
  double **AB=allocMatrix(dim);
  for(i=0;i<dim;i++)
    for(j=0;j<dim;j++)
      for(k=0,AB[i][j]=0; k<dim; k++)
	      AB[i][j] += A[i][k] * B[k][j];
	return AB;
}

/* multiplicar matriz nxm con otra de mxk */

__MATRIXOP_INLINE double**matrixMulMatrixDiffer(double**,double**,int,int,int);

__MATRIXOP_INLINE double**
matrixMulMatrixDiffer(double**A,double**B,int nrowA,int ncolB,int dim)
{
  // nrowB = ncolA = dim
  int i, j, k;
  double **AB=allocMatrixDiffer(nrowA,ncolB);
  for(i=0;i<nrowA;i++)
    for(j=0;j<ncolB;j++)
      for(k=0,AB[i][j]=0; k<dim; k++)
	      AB[i][j] += A[i][k] * B[k][j];
	return AB;
}

/* Multiplicar una matriz por un vector */

__MATRIXOP_INLINE double*matrixMulVector(double**,double*,int,int);

__MATRIXOP_INLINE double*
matrixMulVector(double**A,double*B,int nrowA,int lenB)
{
  // lenB = ncolA
  int i, j, k;
  double *AB = (double *)malloc(sizeof(double)*lenB);
  for(k=0;k<lenB;k++)
  {
    AB[i]=0;
  }
  for(i=0;i<nrowA;i++)
    for(j=0;j<lenB;j++)
      AB[i] = AB[i] + A[i][j]*B[j];
	return AB;
}

/* Multiplicar vector por una matriz */

__MATRIXOP_INLINE double*vectorMulMatrix(double*,double**,int,int);

__MATRIXOP_INLINE double*
vectorMulMatrix(double*A,double**B,int lenA,int ncolB)
{
  // nrowB = lenA
  int i, j, k;
  double *AB = (double *)malloc(sizeof(double)*lenA);
  for(k=0;k<lenA;k++)
  {
    AB[i]=0;
  }
  for(i=0;i<lenA;i++)
    for(j=0;j<ncolB;j++)
      AB[i] = AB[i] + A[i]*B[i][j];
	return AB;
}

/* Multiplicar vector por una matriz */

__MATRIXOP_INLINE double vectorMulVector(double*,double*,int);

__MATRIXOP_INLINE double
vectorMulVector(double*A,double*B,int lenA)
{
  // nrowB = lenA
  int i, j, k;
  double AB=0.0;
  for(i=0;i<lenA;i++)
    AB = AB + A[i]*B[i];
	return AB;
}

/* Convierte la fila de una matriz a un vector */

__MATRIXOP_INLINE double*matrixToVector(double**,int,int);

__MATRIXOP_INLINE double*
matrixToVector(double**A,int index,int lenA)
{
  //  lenA = ncolA
  // index = index of nrowA
  int i, j, k;
  double *AB = (double *)malloc(sizeof(double)*lenA);
  for(k=0;k<lenA;k++)
  {
    AB[i]=A[index][k];
  }
	return AB;
}

#endif
