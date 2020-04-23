/*
##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################
*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>

double quadrature( double x) { return 4.0/(1+x*x); }

int fact(int n)
{
  return ((n <= 0)? 1:n*fact(n-1));
}

double Sin(double x)
{
  int i;
  double sum=0.0;
  for(i=0;i<4;i++)
  {
    sum = sum + pow(-1,i)*pow(x,2*i+1)/fact(2*i+1);
  }
  return sum;
}
double simpsonRule(double (*f)(double),int a,int b,int n)
{
	int i;
	double sum=0.0,h=(double)(b-a)/(double)n;
	for(i=0;i<n-1;i+=2)
	{
		sum = sum + ( (*f)(a+h*i) + 4*(*f)(a+h*(i+1)) + (*f)(a+h*(i+2)) );
	}
	return sum*h/3;
}

int main(int argc, char *argv[])
{
  int done=0;
  int numprocs, myid,i,n; // info de procesadores
  double a=0,my_a,b=1,my_b,interval,range; // intervalos 
  double result,my_result; // resultados
  double startwtime = 0.0, endwtime=0.0;
  
  FILE *f;
  int source,tag,dest; // indicadores de MPI de los comunicadores
  MPI_Status status;
  tag = 123;
  dest = 0;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  n=0;
  while(!done) // hasta que todos los procesadores terminen
  {
    if(myid==0)
    {
//   	  f=fopen("datos_SIN.txt","a");
      if(n==0)
      {
        n=10000000;
      }else n=0;
      startwtime = MPI_Wtime();
    }
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    if(n==0)  done=1; // si es cero, termina todo
    else
    {
      interval = n/numprocs; // numero de particiones para cada procesador
      range = (b-a)/numprocs; // longuitud de intervalo para cada procesador
      my_a = a + myid*range;  // limites inferiores de los intervalos de cada procesador
      my_b = a + (myid+1)*range;  // limites superiores de los intervalos de cada procesador
      
      my_result = simpsonRule(quadrature,my_a,my_b,interval);
      printf("Proceso %d tiene la integral parcial de resultado: %.16f\n", myid,my_result);
      
      MPI_Barrier(MPI_COMM_WORLD);
/*      MPI_Reduce(&my_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
      if(myid==0)
      {
        printf("Integral aproximada es: %.16f\n",result);
        endwtime = MPI_Wtime();
        printf("Tiempo del ordenador = %f\n",endwtime-startwtime);
      }*/

      if(myid == 0)
      {
        result = my_result;
        for (i=1;i<numprocs;i++)
        {
          source = i;  // MPI process number range is [0,p-1]
          MPI_Recv(&my_result, 1, MPI_DOUBLE, source, tag,MPI_COMM_WORLD, &status);
          result += my_result;
        }
        printf("The result =%.16f\n",result);
        endwtime = MPI_Wtime();
        printf("Tiempo del ordenador = %f\n",endwtime-startwtime);
//        fprintf(f,"%.18f\t%i\n",endwtime-startwtime,numprocs);
//  	fclose(f);
      }
      else
        MPI_Send(&my_result, 1, MPI_DOUBLE, dest, tag,MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();

  return 0;
}



/*

mpicc integralMPI.c -o inte
mpiexec -n 4 ./inte

*/
