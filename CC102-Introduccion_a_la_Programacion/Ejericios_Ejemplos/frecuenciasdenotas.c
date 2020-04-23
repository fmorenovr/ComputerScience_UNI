// diseñe un programa que pida ingresar las notas entre 0 y 5 e indique cual fue la nota sacada por la mayoria
#include <stdio.h>
#define NUM 5
int main(){
	//declaracion e inicializacion de vectores
	int nota[NUM],max,idx,i,dato,frec[6];
	for(i=0;i<NUM;i++){
	//validacion nota (0-5)
	do{
		printf("Ingrese nota %d (0-5): ",(i+1));
		scanf("%d",&dato);}
	while((dato<0)||(dato>5));
	nota[i]=dato;}
	printf("Notas ingresadas\n");
	for(i=0;i<NUM;i++){
		printf("%d ",nota[i]);
	}
	//incicializacion el acumulador de frecuencias
	for(i=0;i<6;i++)
		frec[i]=0;
	//averiguamos la frecuencia de cada nota
	for(i=0;i<NUM;i++){
		if(nota[i]==0)
			frec[0]+=1;
		else if(nota[i]==1)
			frec[1]+=1;
		else if(nota[i]==2)
			frec[2]+=1;
		else if(nota[i]==3)
			frec[3]+=1;
		else if(nota[i]==4)
			frec[4]+=1;
		else if(nota[i]==5)
			frec[5]+=1;}
//mostraremos las notas y su frecuencia
printf("\nnota\t\tfrecuencia\n");
max=frec[0];idx=0;
for(i=0;i<6;i++){
	printf("%d\t\t%d\n",i,frec[i]);
	if(frec[i]>max){
	max=frec[i];
	idx=i;}
}
printf("La nota %d tiene la frecuencia mas alta: %d \n",idx,max);
return 0;
}
