#include <stdio.h>
long int comb(int m, int n);
main(){
int a,b;
	printf("Ingresar los numeros a y b \n");
	printf("a=");scanf("%i",&a);
	printf("b=");scanf("%i",&b);
	if(a<=b)
		printf("El combinatorio de %d en %d es %Lf\n",b,a,comb(b,a));
	else
		printf("El combinatorio de %d en %d es %Lf\n",a,b,comb(a,b));
}

long int comb(int m, int n){
	if((n==1)||(n==0)) return m;
	if(n==m) return 1;
else return ((m-n+1)/n)*comb(m,n-1);
}

