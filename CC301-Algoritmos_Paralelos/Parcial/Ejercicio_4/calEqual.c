# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include "mpi.h"

double frontera ( double x, double tiempo ){
  double limite;
  if ( x < 0.5 ) limite = 100.0 + 10.0 * sin ( tiempo );
  else limite = 75.0;
  return limite;
}

double inicial ( double x, double tiempo ) {
  double limite;
  limite = 95.0;
  return limite;
}

int main ( int argc, char *argv[] )
{
  int rank;
  int p;

  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  MPI_Status status;

  int i,j,j_min = 0,j_max = 400,tag,n = 10;
  double k = 0.002;
  double tiempo,dt,tmax = 10.0,tmin = 0.0,tnew;
  double temp[n],tempnew[n],x[n],dx;
  double x_max = 1.0,x_min = 0.0;
  /*
   * descomponer el dominio por proceso
  */
  dt = ( tmax - tmin ) / ( double ) ( j_max - j_min );
  dx = ( x_max - x_min ) / ( double ) ( p * n - 1 );
  for(i=0;i<=n+1;i++){
    x[i] = ((double)(rank * n + i - 1 ) * x_max)/(double)( p * n - 1 );
  }
  /*
    Inicializacion.
  */
  tiempo = tmin;
  temp[0] = 0.0;
  for(i=1;i<=n;i++) temp[i] = inicial(x[i],tiempo);
  temp[n+1] = 0.0;
  
  /*
  * Valores de temperatura al siguiente intervalo de tiempo
  */
  for(j=1;j<=j_max;j++){
    tnew+=dt;
    if (0<rank){
      tag = 1;
      MPI_Send ( &temp[1], 1, MPI_DOUBLE, rank-1, tag, MPI_COMM_WORLD );
    } //Enviar temp[1] a rank-1.
    if(rank<p-1){
      tag = 1;
      MPI_Recv ( &temp[n+1], 1,  MPI_DOUBLE, rank+1, tag, MPI_COMM_WORLD, &status );
    } // Recibe temp[n+1] de rank+1.
    if(rank<p-1){
      tag = 2;
      MPI_Send ( &temp[n], 1, MPI_DOUBLE, rank+1, tag, MPI_COMM_WORLD );
    } // Envia temp[n] a rank+1
    if(0<rank){
      tag = 2;
      MPI_Recv ( &temp[0], 1, MPI_DOUBLE, rank-1, tag, MPI_COMM_WORLD, &status );
    } // Recibe temp[0] de tank-1.
    /*
    * actualizar temperatura
    */
    for(i=1;i<=n;i++){
      tempnew[i] = temp[i] + ( dt * k / dx / dx ) * ( temp[i-1] - 2.0 * temp[i] + temp[i+1] ); 
    }
    /*
    * aplicar condiciones de frontera
    */
    if (0==rank)   tempnew[1] = frontera( x[1], tnew );
    if (rank==p-1)  tempnew[n] = frontera( x[n], tnew );
    /*
     * Actualizar tiempo y temperatura
    */
    tiempo = tnew;
    for (i=1;i<=n;i++){
      temp[i] = tempnew[i];
      if(j==j_max)  printf("%i %f %f %f\n",rank,tiempo,x[i],temp[i]);
//if(j==200)printf("%i %f %f %f\n",rank,tiempo,x[i],temp[i]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

/*
double temptot[n*p];
double xtot[n*p];
//printf("rank: %i tiempo: %f i: %i temp[i] %f\n",rank,tiempo,i,temp[i]);
MPI_Gather(&temp,n,MPI_DOUBLE,&temptot,n*p,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&x,n,MPI_DOUBLE,&xtot,n*p,MPI_DOUBLE,0,MPI_COMM_WORLD);
if(rank==0)  for ( i = 1; i <= n*p; i++ ) printf("%f %f\n",xtot[i],temptot[i]);
*/

  MPI_Finalize ( );
  return 0;
}
