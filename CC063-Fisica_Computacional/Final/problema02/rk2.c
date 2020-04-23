#define NRANSI
#include "nrutil.h"

void rk2(float y[], float dydx[], int n, float x, float h, float yout[],
	void (*derivs)(float, float [], float []))
{
	int i;
	float xh,hh,h6,*dym,*dyt,*yt;

	dym=vector(1,n);
	dyt=vector(1,n);
	yt=vector(1,n);
	hh=h*0.5;
	h6=h/6.0;
	xh=x+hh;
	for (i=1;i<=n;i++) yt[i]=y[i]+h*dydx[i];
	(*derivs)(xh,yt,dyt);
	for (i=1;i<=n;i++)
		yout[i]=y[i]+h*dyt[i];
	free_vector(yt,1,n);
	free_vector(dyt,1,n);
	free_vector(dym,1,n);
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software */
