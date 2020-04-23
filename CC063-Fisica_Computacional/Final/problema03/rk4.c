#include "nrutil.cpp"

void rk4(double y[], double dydx[], int n, double x, double h, void (*derivs)(double, double [], double []))
{
	int i;
	double xh,hh,h6,*dym,*dyt,*yt;

	dym = dvector(1,n);
	dyt = dvector(1,n);
	yt  = dvector(1,n);

	hh = 0.5 * h;
	h6 = h / 6.0;
	xh = x + hh;

	for (i=1; i<=n; i++) yt[i] = y[i] + hh * dydx[i];		// First step

	derivs(xh,yt,dyt);										// Second step

	for (i=1; i<=n; i++) yt[i] = y[i] + hh * dyt[i];

	derivs(xh,yt,dym);										// Third step

	for (i=1; i<=n; i++)
	{
		yt[i] = y[i] + h * dym[i];
		dym[i] += dyt[i];
	}

	derivs(x+h,yt,dyt);										// Fourth step

	for (i=1; i<=n; i++) y[i] += h6 * (dydx[i] + dyt[i] + 2.0 * dym[i]);

	free_dvector(yt,1,n);
	free_dvector(dyt,1,n);
	free_dvector(dym,1,n);
}
#undef NRANSI