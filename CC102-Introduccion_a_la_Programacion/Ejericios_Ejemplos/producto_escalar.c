//obtener el producto escalar de dos vectores
#include <stdio.h>
int main(){
	//declaracion e inicializacion de vectores
	float u[]={2,3,5,8};
	float v[]={4,7,6,8};
	float pescalar=0;
	int i;
	for(i=0;i<4;i++)
	pescalar+=u[i]*v[i];
printf("El producto escalar de u.v=%.2f\n",pescalar);

return 0;
}
