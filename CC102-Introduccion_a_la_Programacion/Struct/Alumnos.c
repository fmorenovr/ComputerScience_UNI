/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define alum 1

typedef struct Alumno{
	char nombre[40];
	float nota;
} Alumno;

int main(){
	int i;
	Alumno alumnos[alum];
	for(i=0;i<alum;i++){
		printf("ingrese nombre de alumno:\n");
		gets(alumnos[i].nombre);
		printf("ingrese nota:\n");
		scanf(" %f",&alumnos[i].nota);
	}
	float promedio=0;
	for(i=0;i<alum;i++){
		promedio = promedio + alumnos[i].nota;
	}
	promedio=promedio/(float)alum;
	printf("\nla nota promedio es:\t %.2f\n\n",promedio);
	for(i=0;i<alum;i++){
		if(promedio<alumnos[i].nota)
			puts(alumnos[i].nombre);
	}
	return 0;
}
