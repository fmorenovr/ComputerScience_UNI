#include<stdio.h>
struct complejo{
	long r;
	long i;
};
void  inicializar(struct complejo z);
void leer(struct complejo *z);
void mostrar(struct complejo z);

int main(void){
	struct complejo z;
		inicializar(z);
		leer(&z);
		mostrar(z);
	return 0;
}
void  inicializar(struct complejo z)
{
    z.r=0;
    z.i=0;
	printf("complejo inicializado:(%d;%d)\n",z.r,z.i);	
}
void leer(struct complejo *z){
	printf("ingrese complejo:\n");
	printf("parte real:\n");
	scanf("%d",&z->r);
	printf("parte imaginaria: \n");
	scanf("%d",&z->i);
}
void mostrar(struct complejo z){
	printf("EL COMPLEJO:(%d,%d)\n",z.r,z.i);
}
