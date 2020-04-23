/* Driver for routine tqli */
//#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"
#include "nrutil.c"
#include "tred2.c"
#include "tqli.c"

#define iter 1000
#define NP 99 //para 99 particulas
#define TINY 1.0e-6

int main(int argc, char **argv){
  int n0; //la fila que cambiara la masa en este caso sera en la primera fila n_0
  char outvalue[50];
  char outvector[50];
  char outxi[50];
  char number[10];
  float t;
  
  if(argc == 2){
    n0 = atoi(argv[1]);
    strcpy(number,argv[1]);
  } else if (argc ==1 ) {
    n0 = 30;
    strcpy(number,"30");
  }
  printf("\nvalor de n0 = %i\n",n0);

  strcpy(outxi,"results/");
  strcat(outxi,"Salida_xi_");
  strcat(outxi,number);
  strcat(outxi,".txt");
  
  strcpy(outvalue,"results/");
  strcat(outvalue,"autovalores_");
  strcat(outvalue,number);
  strcat(outvalue,".txt");
    
  strcpy(outvector,"results/");
  strcat(outvector,"autovectores_");
  strcat(outvector,number);
  strcat(outvector,".txt");
  
  FILE *outputvalue = fopen(outvalue, "wt+");
  FILE *outputvector = fopen(outvector, "wt+");
  FILE *salida = fopen(outxi,"wt+");
  
  int i,j,k;
  float *d,*e,*f,**a,**x;
  static float c[NP][NP];
  // C es la matriz tridiagonal de los valores
  //se dan los valores a la matriz
  for(i=1 ; i<=NP ; i++){
    for(j=1 ; j<=NP ;j++){
      if(i+1==j || i-1==j){
        if(i==n0)
          c[i][j]=-1.0/100;
        else
          c[i][j]=-1.0;
      }
      else if(i==j){
        if(i==n0)
          c[i][j]=2.0/100;
        else
          c[i][j]=2.0;	
      }
      else 
        c[i][j]=0.0;
    }
  }
  
  // vector de posiciones
  x=matrix(1,NP,1,iter);
  for(i=1;i<=NP;i++)
    for(j=1;j<=iter;j++)
      x[i][j] = 0.0;
      
  d=vector(1,NP); // vector de eigenvalues
  e=vector(1,NP);
  f=vector(1,NP);
  a=matrix(1,NP,1,NP); // matriz de eigenvectors
  for (i=1;i<=NP;i++)
	  for (j=1;j<=NP;j++)
	    a[i][j]=c[i-1][j-1];

  tred2(a,NP,d,e);
  tqli(d,e,NP,a);	
  // calcular valores y vectores propios de una matriz simetrica
  // utilizando tred2() y tqli() de Numerical Recipees

  printf("\nCalculo de los eigenvalue y eigenvector de una matriz simetrica real\n\n");
  for (i=1;i<=NP;i++) {
	  for (j=1;j<=NP;j++) {
      f[j]=0.0;
      for (k=1;k<=NP;k++)
        f[j] += (c[j-1][k-1]*a[k][i]);
	  }
	  fprintf(outputvalue,"%10.6f\n",d[i]);
	  //printf("%s %3d %s %10.6f\n","eigenvalue",i," =",d[i]);
	  /*printf("%11s %14s %9s\n","vector","mtrx*vect.","ratio");
	  for (j=1;j<=NP;j++) {
      if (fabs(a[j][i]) < TINY)
        printf("%12.6f %12.6f %12s\n",a[j][i],f[j],"div. by 0");
      else
        printf("%12.6f %12.6f %12.6f\n",a[j][i],f[j],f[j]/a[j][i]);
	  }*/
  }
  
  for (i=1;i<=NP;i++){
    for (j=1;j<=NP;j++){
      fprintf(outputvector,"%12.6f ",a[i][j]);
    }
    fprintf(outputvector,"\n");
  }
  
  float xi=0.0;
  float *aux=vector(1,NP);
  for(i=1;i<=NP;i++)
    aux[i]=0.0;
  // Analizando los xi
  k=0;
  for (t=0.0;t<=2;t=t+1.0/iter){
    for(i=1;i<=NP;i++)
      for(j=1;j<=NP;j++)
        aux[i] = aux[i] + exp(d[i]*t)*a[i][j];
    for(i=1;i<=NP;i++){
      x[i][k] = aux[i];
      aux[i]=0.0;
      if(i==n0)
        fprintf(salida,"%10.6f\n",x[i][k]);
    }
    k++;
  }
  
  free_matrix(a,1,NP,1,NP);
  free_vector(f,1,NP);
  free_vector(e,1,NP);
  free_vector(d,1,NP);
  fclose(outputvector);
  fclose(outputvalue);
  fclose(salida);
  return 0;
}
 
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software */
#include <math.h>
#include "nrutil.h"
//Computes (a2 + b2)1/2 without destructive under ow or over ow.//
float pythag(float a, float b){
  float absa,absb;
  absa=fabs(a);
  absb=fabs(b);
  if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));
  else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}
