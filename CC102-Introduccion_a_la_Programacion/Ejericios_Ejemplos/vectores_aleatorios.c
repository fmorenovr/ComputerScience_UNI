#include<stdio.h>
void leer(int v[],int n);
void escribir(int v[],int n);
int main(){
	int n;
	//validamos tal que n>0
	do{
		printf("dimencion del vector = ");
		scanf("%d",&n);
	}while(n<=0);
int v[n],i;
leer(v,n);
printf("\nElementos del vector: \n");
escribir(v,n);
return 0;
}
void leer(int v[],int n){
int i;
	srand(time(NULL));
	for(i=0;i<n;i++){
	v[i]=rand()%10; //generacion aleatoria entre 0 y 9
}
}
void escribir(int v[],int n){
int i;
	for(i=0;i<n;i++){
	printf("%d ",v[i]);}

}
