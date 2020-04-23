#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

#define ITER 10000

void poissonSolver(int numProcs, int myRank,int num_grid_x, int num_grid_y, int num_random);

double f(double, double);

void grid( int*, int*, int, int );

const double pi = 3.1415926535897932;
int n1, n2, n3, n4;   // posiciones frontera (para identificar que vector esta)
int point = 1;        // para calcular un punto, 1 significa que empieza desde abajo ( izquierda )
//    int ix, iy;           // index of the position

int
main(int argc, char* argv[]){
  int myRank, numProcs ;
  double startTime, endTime;
  unsigned int semilla;	

  MPI_Init(&argc,&argv);
  MPI_Comm_rank( MPI_COMM_WORLD, &myRank );
  MPI_Comm_size( MPI_COMM_WORLD, &numProcs );

  // determina el numero de ecuaciones de la matriz gauss-Seidel
  int num_random = 100; // numero de elementos
  int num_grid_x = 100; // numero de ecuaciones
  int num_grid_y = 100; // numero de incognitas

  // genera numeros random distintos cada ejecucion
  semilla=(unsigned int)time((time_t *)NULL);

  MPI_Bcast(&semilla, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  // guardamos la semilla ( seed ) creada para volver a utilizar dichos puntos cuando toquen el mismo semilla random
  // y no tener que calcular todo de nuevo
  srand((unsigned int)(semilla+131*myRank));

  // empezamos el tiempo de ejecucion
  startTime = MPI_Wtime();
    poissonSolver( numProcs, myRank, num_grid_x, num_grid_y, num_random);
  endTime = MPI_Wtime();

  printf( "Tiempo de Ejecucion (segundos) es %13.8f en el processor %d\n",endTime - startTime, myRank );

  MPI_Finalize();
  return 0;
}


// Resuelve la ecuacion de Poisson con condicion de Frontera mediante gaussSeidel
void poissonSolver( int numProcs, int myRank, int num_grid_x, int num_grid_y, int N ) {
  const int nx = num_grid_x;
  const int ny = num_grid_y;
  const double h = 1. / nx;   // el h que avanza x o y ( x1 = x + dx o y1 = y + dy )
  double ran; // genera random para elegir los nuevos numeros
  int iteraciones; // controla las iteraciones

  // inicizializa las fronteras
  n1 = 1;
  n2 = nx - 1;
  n3 = ny - 1;
  n4 = 1;

  const int nxx = 100; 
  const int nyy = 100;

  // creacion del vector
  double u[nxx+1][nyy+1], x[nxx+1], y[nyy+1];

  // onBoundary es el vector u en un estado anterior
  int onBoundary[nxx+1][nyy+1]; 

  int ix, iy;
  int tmpX, tmpY;

  // condiciones de frontera
  for ( ix=0; ix<=nxx; ix++ ) {
    for ( iy=0; iy<=nyy; iy++ )
      u[ix][iy] = 0.0;
  }

  for ( ix=0; ix<=nx; ix++ ) {
    for ( iy=0; iy<=ny; iy++ )
      onBoundary[ix][iy] = 0;
  }

  // dominio de x(0,1) y(0,1)
  for ( ix=0; ix<=nx; ix++ )
    x[ix] = (1. * ix) / nx;
  for ( iy=0; iy<=ny; iy++ )
    y[iy] = (1. * iy) / ny;

  // condiciones de frontera
  for ( ix=0; ix<=nx; ix++ ) {
    u[ix][0] = 0;    // lower
    onBoundary[ix][0] = 1;
    u[ix][ny] = 0;   // upper
    onBoundary[ix][ny] = 1;
  }

  for ( iy=0; iy<=ny; iy++ ) {
    u[0][iy] = 0;    // left 
    onBoundary[0][iy] = 1;
    u[nx][iy] = 0;   // right
    onBoundary[nx][iy] = 1;
  } 

  // condicion frontera interior
  int inx1 = nx / 4;
  int inx2 = 3 * nx / 4;
  int iny1 = ny / 4;
  int iny2 = 3 * ny / 4;

  for ( ix=inx1; ix<=inx2; ix++ ) {
    u[ix][iny1] = 0;    // lower
    onBoundary[ix][iny1] = 1;
    u[ix][iny2] = 0;   // upper
    onBoundary[ix][iny2] = 1;
  }

  for ( iy=iny1; iy<=iny2; iy++ ) {
    u[inx1][iy] = 0;    // left
    onBoundary[inx1][iy] = 1;
    u[inx2][iy] = 0;   // right
    onBoundary[inx2][iy] = 1;
  }

  // inicializa ix, iy 
  ix = myRank + 1; // donde inicializa
  iy = 1;

  int iix, iiy; 
  int flag = 0;   // (= 1) significa que se termino el calculo
  double myU;
  while( iteraciones < ITER ) {
    // calcula u[ix][iy] para el punto (ix,iy) 
    double uxy = 0, sqU = 0; 

    if (onBoundary[ix][iy] == 1) {   // u[x][y] anterior
    myU = -1000.5;
    flag = 1;
    }
    else {
      int i;
      for ( i=1; i<=N; i++ ) {   // N random walks
        iix = ix;
        iiy = iy;
        double fxy = f( x[iix], y[iiy] );
        while ( 1 ) {
          ran=(rand())/(double) RAND_MAX;
          if ( ran >= 0.75 ) {
            iix++;
          }
          else if ( ran >= 0.50) {
            iiy++; 
          }
          else if ( ran >= 0.25) {
            iix--;   
          }
          else {
            iiy--;  
          }
          if ( onBoundary[iix][iiy] == 1 ) break;
          fxy += f( x[iix], y[iiy] );
        }
        // actualizacion del vector por gauss Seidel
        double tempU = u[iix][iiy] + fxy * h * h / 2;
        uxy += tempU;
        sqU += tempU * tempU;
      }
      myU = uxy / N;
      sqU /= N;
      u[ix][iy] = myU;
      onBoundary[ix][iy] = 1;

      // output
      //if ( ix == iy )
      printf("ix=%d iy=%d u=%f sigma=%f on proc. %d\n",ix , iy, u[ix][iy], sqrt( (sqU - myU * myU)/N ), myRank);
    }  



    /////// PARALELIZACION VA AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // enviamos u[ix][iy] a los otros procesadores
    int i;
    for ( i = 0; i < numProcs; i++) {
      if (i != myRank) 
        MPI_Send(&myU, 1, MPI_DOUBLE, i, 99, MPI_COMM_WORLD);
    }

    // recibe u[iix][iiy] desde otros procesadores
    MPI_Status status;
    double u0;
    for ( i = 0; i < numProcs; i++) {
      if (i != myRank) { 
        MPI_Recv(&u0, 1, MPI_DOUBLE, i, 99, MPI_COMM_WORLD,&status);
        if (u0 <= -1000) {
          flag = 1;
        }
        else {   
          tmpX = ix;
          tmpY = iy;  
          grid( &tmpX, &tmpY, i - myRank, 0 );
          iix = tmpX;
          iiy = tmpY;
          u[iix][iiy] = u0;
          onBoundary[iix][iiy] = 1;
        }
      }
    }

    MPI_Barrier( MPI_COMM_WORLD );

    // verifica si termino
    if (flag == 1) break;

    // ix, iy del siguiente nodo para el procesador
    tmpX = ix;
    tmpY = iy;
    grid( &tmpX, &tmpY, numProcs, 1 );
    ix = tmpX;
    iy = tmpY;

    // verifica si ix es menor al siguiente e iy es menor al siguiente
    assert( ((ix < nx+1) && (iy < ny+1))  );
    iteraciones+=1;
  }

  /* a un archivo de texto */
  int i,j;
  FILE *pFile;
  if (myRank==0)
  {
    pFile = fopen ("resultado.txt","w");
    fprintf (pFile, " x  ");
    for (i=0; i<=num_grid_x; i++) fprintf (pFile, " %13d",i);;
      fprintf (pFile, "\n");
    for (j=0; j<=num_grid_y; j++)
    {
      fprintf (pFile, "%4d",j);
      for (i=0; i<=num_grid_x; i++)			
        fprintf (pFile, " %13.8f",u[i][j]);
      fprintf (pFile, "\n");
    }
    fclose(pFile);
  };

  printf("========  FIN ========= %d\n",myRank);
}


// evalua f(x,y)
// (1-exp(2*x)) = como 2 * pi^2 * sin(pi*x)*sin(pi*y) 
double f(double x, double y) {
  return ( exp(-1.*x*y) );
} 


// Imprime el grid segun el numero point de arriba
void grid(int *ix,int *iy,int numProcs,int flag){
  switch ( point ) {
    case 1 :
      (*ix) += numProcs;
      if ( (n2-n4) <= (numProcs+1) ) {
        if ( (*ix) > n2 ) {
          (*ix) = (n4 - 1) + ((*ix) - n2);
          (*iy)++;
        }
      }
      else {
        if ( (*ix) > n2 ) {
          (*iy) = n1 + ((*ix) - n2);
          (*ix) = n2;
          if (flag == 1) {
            n1++;
            point = 2;
          }
        }
      }
      break;
    case 2 :
      (*iy) += numProcs;
      if ( (*iy) > n3 ) {
        (*ix) = n2 - ((*iy) -n3);
        (*iy) = n3;
        if (flag == 1) {
          n2--;
          point = 3;
        }
      }
      break;
    case 3 :
      (*ix) -= numProcs;
      if ( (*ix) < n4 ) {
        (*iy) = n3 + ((*ix) - n4);
        (*ix) = n4;
        if (flag == 1) {
          n3--;
          point = 4;
        }
      }
      break;
    case 4 :
      *iy -= numProcs;
      if ( *iy < n1 ) {
        *ix = n4 - (*iy - n1);
        *iy = n1;
        if (flag == 1) {
          n4++;
          point = 1;
        }
      }
  }
}
