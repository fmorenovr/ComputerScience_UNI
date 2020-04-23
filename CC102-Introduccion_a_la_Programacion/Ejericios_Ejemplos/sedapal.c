#include <stdio.h>
int main(void){
	int consumo;
	float tarifa,importe_consumo,importe_impuesto,importe_total;

	printf("el consumo fue de ");
	scanf("%i",&consumo);
	if(consumo>0){
		if(consumo<=20)
				tarifa = 0.80;
				importe_consumo = consumo*tarifa;
				printf("el consumo a pagar es %i * %f\n",consumo,tarifa);
		if((consumo>20)&&(consumo<=30)){
				consumo = consumo-20;
				tarifa = 1.10;
				importe_consumo = consumo*tarifa+20*0.80;}
		if((consumo>30)&&(consumo<=50)){
				consumo = consumo-30;
				tarifa = 1.55;
				importe_consumo = consumo*tarifa+20*0.80+10*1.10;}
		if((consumo>50)&&(consumo<=80)){
				consumo = consumo-50;
				tarifa = 2.13;
				importe_consumo = consumo*tarifa+20*0.80+10*1.10+20*1.55;}
		if(consumo>80){
				consumo = consumo-80;
				tarifa = 3.00;
				importe_consumo = consumo*tarifa+20*0.80+10*1.10+20*1.55+30*2.13;}
		importe_impuesto = 1.19*importe_consumo;
		importe_total = 3.40 + importe_impuesto;
		
		printf("El importe total es %f\n",importe_total);
		}
		else
			printf("El consumo es no nulo y no puede ser negativo\n");

return 0;
}
