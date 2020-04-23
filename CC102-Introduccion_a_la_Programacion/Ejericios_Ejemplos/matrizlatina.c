#include <stdio.h>
int main(){
    int n;
    printf("Ingrese n : ");
    scanf("%i",&n);
    int i,j,cont1=n,cont2=2,a[n][n];
    for(i=0;i<n;i++){
	    for(j=0;j<n;j++){
            a[i][j] = (1 - i + j)%5;
            if (a[i][j] <= 0)
                a[i][j] += 5;
	    }
    }
    printf("Elementos de la matriz Latina \n");
    for(i=0;i<n;i++){
	    for(j=0;j<n;j++)
	    	printf("  %d  ",a[i][j]);
	    printf("\n");
    }
    return 0;
}
