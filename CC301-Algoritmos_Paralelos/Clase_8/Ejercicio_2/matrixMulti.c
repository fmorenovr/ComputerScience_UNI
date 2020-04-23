#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NRA 160               /* number of rows in matrix A */
#define NCA 160               /* number of columns in matrix A */
#define NCB 90               /* number of columns in matrix B */

int
main(int argc, char *argv[])
{
  int i,j,k;
  double	a[NRA][NCA],           /* matrix A */
          b[NCA][NCB],           /* matrix B */
          c[NRA][NCB];           /* matrix C */
  srand(time(0));
  
  printf("\n\n");
  printf("Inicializando arrays...\n");
  clock_t start = clock();
  for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= rand()%3+1;

  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= rand()%3+1;

  for (i=0; i<NRA; i++)
        for (j=0; j<NCB; j++)
          c[i][j]= 0;
  
  for (i = 0; i < NRA; ++i)
    for (j = 0; j < NCB; ++j)
      for (k = 0; k < NCA; ++k)
        c[i][j] += a[i][k] * b[k][j];
  clock_t end = clock();
  double dif = (double)(end - start)/CLOCKS_PER_SEC;
  
  printf("El proceso demoro %.8fs de tiempo.\n",dif);
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

  return 0;
}
