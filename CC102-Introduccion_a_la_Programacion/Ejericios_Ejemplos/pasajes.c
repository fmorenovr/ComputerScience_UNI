#include <stdio.h>
int main(void){
	int edad;
	char familia_numerosa,estudiante;
	float precio_pasaje,descuento;
	printf("su familia es numerosa?:");
	scanf("%c",&familia_numerosa);
	printf("Precio del boleto: ");
	scanf("%f",&precio_pasaje);
	if(familia_numerosa=='S'){
				printf("Son una familia numerosa\n");
				precio_pasaje = 7*precio_pasaje/10;
				descuento=3*precio_pasaje/10;
				printf("El descuento fue %.2f\n",descuento);
				printf("El pasaje fue %.2f\n",precio_pasaje);
				printf("Se rebajo el 70 porciento\n");}
	if(familia_numerosa=='N'){
			printf("Es estudiante?:");
			scanf("%c",&estudiante);
			if(estudiante=='S'){
				printf("Es estudiante\n");
				precio_pasaje = precio_pasaje/2;
				descuento=precio_pasaje/2;
				printf("El descuento fue %.2f\n",descuento);
				printf("El pasaje fue %.2f\n",precio_pasaje);
				printf("Se rebajo el 50 porciento\n");}
			if(estudiante=='N'){
				printf("Edad del pasajero: ");
				scanf("%i",&edad);
				if (edad>0){
					if(edad<4){
						precio_pasaje = 0;
						printf("Es menor de 4 años, No paga pasaje");}
					if((edad>=4)&&(edad<=7)){
						precio_pasaje = precio_pasaje/2;
						printf("Es mayor de 4 años y menor de 7, Pagará solo la mitad del pasaje el cual es %.2f\n",precio_pasaje);}
					if((edad>7)&&(edad<=65)){
						precio_pasaje = precio_pasaje;
						printf("Paga pasaje normal,El cual es %.2f\n",precio_pasaje);}
					if(edad>65){
						precio_pasaje=2*precio_pasaje/5;
						descuento=3*precio_pasaje/5;
						printf("Paga el 40 porciento del pasaje");
						printf("El descuento fue %.2f\n",descuento);}
				}
			}

}
return 0;
}
