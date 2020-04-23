#include<stdio.h> 
#include<stdlib.h>
int main(){
    int i,j,n=0,x=0;
    int pasc[x];
    printf("Ingrese el numero de filas para el triangulo de Pascal: ");
    scanf("%d",&x);
    for(i=0;i<x;i++){
	for(j=n;j>=0;j--){
	    if((j==n)||(j==0))
		pasc[j] = 1;
	    else
 		pasc[j] = pasc[j] + pasc[j-1];
	}
	n++;
	printf("\n");
	for(j=1;j<=x-i;j++)
	    printf("   ");
	for(j=0;j<n;j++)
	    printf("%3d   ",pasc[j]);
    }
    return 0;	    
}
