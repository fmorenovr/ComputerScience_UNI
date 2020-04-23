#include <stdio.h>
#include <math.h>
#include <time.h>

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
  double pi,  h, sumpi,x, y;
  clock_t start, end;

  if( argc == 2 ) {
    sscanf( argv[1], "%d", &n );
  } 
  else {      
    printf("\nIngrese numero de intervalos: \n");
    fflush(stdout);
    scanf("%d",&n);
  }
  if (n == 0)
      printf("\nNo puede haber division entre 0.\n\n");
  else{
    start = clock();
    printf("\nCalculando PI usando %d intervalos.\n",n);
    h = 1.0 / (double)n;
    pi = 0.0;
    sumpi=0.0;
    for( i=0; i<n; i++) {
      x = h * ((double)i - 0.5);
      sumpi += f(x);
    }
    pi = sumpi*h;
    end = clock();
    printf("\npi aprox es: %.16f\nError es: %.16f\n",pi, fabs(pi - pi_25));
    printf("El calculo fue en %.8fs\n\n",(double)(end - start)/CLOCKS_PER_SEC);
  }
  return 0;
}

