#include <stdio.h>
#include <math.h>
#include <omp.h>

double f( double );
double f( double a )
{
  return (4.0 / (1.0 + a*a));
}

int main(int argc, char *argv[])
{
  int num_th, th_id;
  int i,n;
  double pi_25 = 3.141592653589793238462643;
  double pi,  h, sumpi,x;
  double startwtime, endwtime;

  if( argc == 3 ) {
    sscanf( argv[1], "%d", &num_th );
    sscanf( argv[2], "%d", &n );
  }
  else if(argc == 2){
    sscanf( argv[1], "%d", &n );
    num_th = omp_get_max_threads();
  }
  else {      
    printf("\nIngrese numero de intervalos: \n");
    fflush(stdout);
    scanf("%d",&n);
    num_th = omp_get_max_threads();
  }
  omp_set_num_threads(num_th);
  if (n == 0)
      printf("\nNo puede haber division entre 0.\n\n");
  else{
    #pragma omp parallel private(th_id,sumpi,h,x,i,startwtime, endwtime) shared(num_th,n,pi)
    {
      th_id=omp_get_thread_num();
      if (th_id == 0){
        printf("\nCalculando PI en OpenMP usando %d intervalos.\n",n);
      }
      h = 1.0 / (double)n;
      pi = 0.0;
      sumpi=0.0;
      #pragma omp barrier
        startwtime = omp_get_wtime();
      #pragma omp for reduction(+:pi)
        for( i=0; i<n; i++) {
          x = h * ((double)i - 0.5);
          sumpi = f(x);
          pi = pi + sumpi*h;
        }
      endwtime = omp_get_wtime();
      if (th_id == 0){
        printf("\npi aprox es: %.16f\nError es: %.16f\n",pi, fabs(pi - pi_25));
        printf("El calculo fue en %.8fs en %d hilos\n\n",endwtime-startwtime,num_th);
      }
    }
  }
  return 0;
}

