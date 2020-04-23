/* Driver for routine rkdumb */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"
#include "nrutil.c"
#include "rkdumb.c"
#include "rk4.c"

#define NVAR 1

int NSTEP;
float x1, x2;

void derivs(float x,float y[],float dydx[]){
  dydx[1]= y[1];
	dydx[2]= y[2];
	dydx[3]= y[3];
}

extern float **y,*xx;   /* referencing declaration */
// xx es la variacion de x(t) y y(t) es el resultado aproximado
int main(int argc, char **argv){
  if(argc == 4){
    NSTEP = atoi(argv[1]);
    x1 = atof(argv[2]);
    x2 = atof(argv[3]);
  } else if(argc ==1 ){
    NSTEP = 10;
    x1 = 0.0;
    x2 = 1.0;
  } else if(argc == 2){
    NSTEP = atoi(argv[1]);
    x1 = 0.0;
    x2 = 1.0;
  }
	int j;
	float *vstart;
	vstart=vector(1,NVAR);
	/* Note: The arrays xx and y must have indices up to NSTEP+1 */
	xx=vector(1,NSTEP+1);
	y=matrix(1,NVAR,1,NSTEP+1);
	vstart[1]=exp(x1);
	rkdumb(vstart,NVAR,x1,x2,NSTEP,derivs);
	//printf("%8s %17s %10s\n","x","integrated","exponential");

  for(j=1;j<=NSTEP+1;j++){
    //printf("x[%i]=%f\ty[%i]=%f\n",j,xx[j],j,y[1][j]);
    printf("%f\t%f\t%f\t%f\n",xx[j],exp(xx[j]),y[1][j],(exp(xx[j])-y[1][j])/exp(xx[j]));
  }

	free_matrix(y,1,NVAR,1,NSTEP+1);
	free_vector(xx,1,NSTEP+1);
	free_vector(vstart,1,NVAR);
	return 0;
}
#undef NRANSI
