/*
##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################


	Newton-Cotes Method's:
		Cerradas:
			Simpson Rule
			Boole Rule

		Abiertas:
			Rectangule Rule
			Trapezoidal Rule

	Gauss Quadrature:
		n: numero de puntos a utilizar
		
		Gauss-Hermite:
			w(x) = exp(-(pow(x,2))
			
  		si f(x).w(x) = wi Sum f(xi)
  		donde: xi = raices del polnomio de Hermite
  						wi = ( pow(2,n-1)*fact(n)*sqrt(pi) )/( pow(n,2)*pow(hermitePoly(n-1,xi),2) )
  				donde: hermitePoly(n-1,xi) = Hn(x) 
  						fatc(n)*Sum[0-n/2] de pow(-1,m)*pow(2*xi,n-2*m) /( fatc(m)*fact(n-2*m) )
  						hermitePolyE(n-1,xi) = Hen(x)
  							fatc(n)*Sum[0-n/2] de pow(-1,m) * pow(xi,n-2*m)/( pow(2,m)*fatc(m)*fact(n-2*m) )
  		
		Chevyshev-Gauss:
			w(x) = 1/sqrt(1-pow(x,2))
			
			si f(x).w(x) = wi Sum f(xi)
				donde: xi = cos((2*i-1)*pi/(2*n))
							 wi = pi/n
			o f(x)/w(x) = wi.Sum f(xi)
				donde:	xi = cos(i*pi/(n+1))
								wi = (pi/(n+1))*pow(sin(i*pi/(n+1)),2)
			
*/

# ifndef _NUMINTEGRATION_H
# define _NUMINTEGRATION_H

# ifndef __NUMINTEGRATION_INLINE
#  ifndef __extern_inline
#   define __NUMINTEGRATION_INLINE inline
#  else
#   define __NUMINTEGRATION_INLINE __extern_inline
#  endif
# endif

__NUMINTEGRATION_INLINE double trapezoidalRule(double(*)(double),int,int,int);

__NUMINTEGRATION_INLINE double
trapezoidalRule(double(*f)(double),int a,int b,int n)
{
	int i;
	double sum=0.0,h=(double)(b-a)/(double)n;
	for(i=0;i<n;i++)
	{
		sum = sum + ( (*f)(a+h*i) + (*f)(a+h*(i+1)) )*h/2;
	}
	return sum;
}

__NUMINTEGRATION_INLINE double simpsonRule(double(*)(double),int,int,int);

__NUMINTEGRATION_INLINE double
simpsonRule(double (*f)(double),int a,int b,int n)
{
	int i;
	double sum=0.0,h=(double)(b-a)/(double)n;
	for(i=0;i<n-1;i+=2)
	{
		sum = sum + ( (*f)(a+h*i) + 4*(*f)(a+h*(i+1)) + (*f)(a+h*(i+2)) );
	}
	return sum*h/3;
}

__NUMINTEGRATION_INLINE double rectanguleRule(double(*)(double),int,int,int);

__NUMINTEGRATION_INLINE double
rectanguleRule(double (*f)(double),int a,int b,int n)
{
	int i;
	double suminf=0.0,sumsup=0.0,h=(double)(b-a)/(double)n;
	for(i=0;i<n-1;i++)
	{
		suminf = suminf + (*f)(a+h*i)*h; // Suma inferior
		sumsup = sumsup + (*f)(a+h*(i+1))*h; // Suma superior
	}
	return (suminf+sumsup)/2.0;
}

__NUMINTEGRATION_INLINE double booleRule(double(*)(double),int,int,int);

__NUMINTEGRATION_INLINE double
booleRule(double (*f)(double),int a,int b,int n)
{
	int i;
	double sum=0.0,h=(double)(b-a)/(double)n;
	for(i=0;i<n-4;i+=4)
	{
		sum = sum + 7*(*f)(a+h*i) + 32*(*f)(a+h*(i+1)) + 12*(*f)(a+h*(i+2)) + 32*(*f)(a+h*(i+1)) + 7*(*f)(a+h*(i+1));
	}
	return sum*2*h/45;
}

__NUMINTEGRATION_INLINE double quadratureIntegral(double(*f)(double),double,double,float)

__NUMINTEGRATION_INLINE double
quadratureIntegral(double(*f)(double),double p,double q,float s)
{
  double z;
	if((q-p)<=s)
	{
		z=(*f)(q)+(*f)(p)*(q-p)/2;
		return z;
  }
	else
		return quadratureIntegral(p,(q+p)/2,s)+quadratureIntegral((p+q)/2,q,s);	

}

#endif /* Numerical */
