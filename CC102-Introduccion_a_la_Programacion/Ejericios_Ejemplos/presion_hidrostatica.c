#include<stdio.h>

int main()

{
	float presion[6],presion_error[6], den_agua=1000,den_mercu=13579.04,gravedad=9.8,altura_agua,altura_mercurio,error_altura=0.05/100;
int i,temperatura[6];

for(i=1;i<=5;i++)//modificar el 5 por la cantidad de datos
{printf("Altura del agua=");scanf("%f",&altura_agua);
printf("Altura del mercurio=");scanf("%f",&altura_mercurio);
printf("temperatura=");scanf("%d",&temperatura[i]);
presion[i]=gravedad*(den_agua*(altura_agua/100)+den_mercu*(altura_mercurio/100));
presion_error[i]=gravedad*(den_agua*error_altura+den_mercu*error_altura);
}
printf("\tpresion(pascal)\t\t\ttemperatura\n");
for(i=1;i<=5;i++){
printf("\t%.2f+-%.2f\t\t\t%d\n",presion[i],presion_error[i],temperatura[i]);
}
printf("\tpresion(atm)\t\t\ttemperatura\n");
for(i=1;i<=5;i++){
printf("\t%.2f+-%.2f\t\t\t%d\n",presion[i]/101.325,presion_error[i]/101.325,temperatura[i]);
}
return 0;}
