#include <stdio.h>
int main(){
int n;
do {
printf("ingrese el orden de su cuadrado magico ");
scanf("%i",&n);
}while((n<3)&&(n>10));

int i,j,a[n][n],k;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        a[i][j]=0;
    }
}
//inicializando con 1
i=0; j=(n-1)/2; k=1;
a[0][j]=k;
//llenando
while(k<n*n){
    i-=1; j+=1; k+=1;
    if(j==n) j=0; 
    if(i<0) i += n;
    if(a[i][j]!=0){
        i+=2;
        j-=1;
    }
    i = i%n;
    if(j<0) j += n;
    a[i][j]=k;
}

printf("Elementos de la matriz\n");
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		printf(" %d ",a[i][j]);
    }
	printf("\n");
}


return 0;
}


