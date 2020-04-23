#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//convertir a polares
void convertir(float radio, float ang);//prototipo
int main(){
float r,thetasexag,theta;
	printf("Radio= ");scanf("%f",&r);
	printf("Angulo(sexag)= ");scanf("%f",&thetasexag);
	theta=thetasexag*M_PI/180;
	convertir(r,theta);
return 0;

}
void convertir(float radio, float ang){
float x,y;
x=radio*cos(ang);
y=radio*sin(ang);
printf("x=%.2f\n",x);
printf("y=%.2f\n",y);
}






