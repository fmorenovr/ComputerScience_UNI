#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
	int i,j,k,menu,x,y;
	int filas, columnas;
	printf("Ingrese num. de filas y columnas: ");
	scanf("%d %d",&filas, &columnas);
	menu=-1;

			/*Definicion de matrices*/
			int ME[filas][columnas];
			int MS[filas][columnas];
			int matriz_final[filas][columnas];
			for(i=0;i<filas;i++){
				for(j=0;j<columnas;j++){
					ME[i][j]=0;
				}
			}
			for(i=0;i<filas;i++){
				for(j=0;j<columnas;j++){
					MS[i][j]=0;
				}
			}
			for(i=0;i<filas;i++){
				for(j=0;j<columnas;j++){
					matriz_final[i][j]=0;
				}
			}
	 srand(time(NULL));
		while(menu!=0){
			printf("Game of life: \n");
			printf(" 1)Insertar valores\n");
			printf(" 2)Imprimir matriz\n");
			printf(" 3)Aplicar el juego de la vida\n");
			printf(" 4)Usar datos aleatorios\n");
			printf(" 5)Mostrar vecinos\n");
			printf(" 6)Simular Juego de Vida 300 veces\n");
			printf(" 0) Salir\n>>");
			scanf("%d",&menu);		
				if(menu==1){
						printf("Coordenadas:\nx: ");
						scanf("%d",&x);printf("y: ");
						scanf("%d",&y);
						ME[x][y]=(1+ME[x][y])%2;
				}
				if(menu==2){
						printf("Matriz\n");
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								printf("%d ",ME[i][j]);
							}
					    printf("\n");
						}	
				}
				if(menu==3){
						/*esquinas*/
						MS[0][0]=ME[0][1]+ME[1][1]+ME[1][0];
						MS[filas-1][0]=ME[filas-2][0]+ME[filas-2][1]+ME[filas-1][1];
						MS[0][columnas-1]=ME[0][columnas-2]+ME[1][columnas-1]+ME[1][columnas-2];
						MS[filas-1][columnas-1]=ME[filas-2][columnas-2]+ME[filas-2][columnas-1]+ME[filas-1][columnas-2];
						/*primera fila y ultima fila*/
						for(i=1;i<columnas-1;i++){
						MS[0][i]=ME[0][i-1]+ME[0][i+1]+ME[1][i-1]+ME[1][i]+ME[1][i+1];
						MS[filas-1][i]=ME[filas-1][i-1]+ME[filas-1][i+1]+ME[filas-2][i-1]+ME[filas-2][i]+ME[filas-2][i+1];
						}
						/*primera columna y ultima columna*/
						for(j=1;j<filas-1;j++){
						MS[j][0]=ME[j][1]+ME[j-1][0]+ME[j-1][1]+ME[j+1][0]+ME[j+1][1];
						MS[j][columnas-1]=ME[j][columnas-2]+ME[j-1][columnas-1]+ME[j-1][columnas-2]+ME[j+1][columnas-1]+ME[j+1][columnas-2];
						}
						/*inside the core*/
						for(i=1;i<filas-1;i++){
							for(j=1;j<columnas-1;j++){
							MS[i][j]=ME[i-1][j-1]+ME[i-1][j]+ME[i][j-1]+ME[i+1][j+1]+ME[i+1][j]+ME[i][j+1]+ME[i-1][j+1]+ME[i+1][j-1];
							}			
						}
						/*matriz final*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								if(MS[i][j]>=4){/*sobrepoblacion*/
								matriz_final[i][j]=0;
								}					
								if(MS[i][j]<=1){/*bacterias con menos de 2 bacterias cerca aislamiento*/
								matriz_final[i][j]=0;
								}
								if(MS[i][j]==2 && ME[i][j]==1){/*sobrevivencia*/
								matriz_final[i][j]=1;
								}
								else matriz_final[i][j]=0;					
								if(MS[i][j]==3){/*nacimiento*/
								matriz_final[i][j]=1;
								}
							}
						}	
						
						/*Intercambio matrices*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								ME[i][j]=matriz_final[i][j];
							}
						}	
						/*Impresion del resultado*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								if(ME[i][j]==1) printf("X ");
								else printf("- ");
							}
					    printf("\n");
						}	
				}
				if(menu==4){
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								ME[i][j]=rand()%2;
							}
						}	
				}
				if(menu==5){
						/*esquinas*/
						MS[0][0]=ME[0][1]+ME[1][1]+ME[1][0];
						MS[filas-1][0]=ME[filas-2][0]+ME[filas-2][1]+ME[filas-1][1];
						MS[0][columnas-1]=ME[0][columnas-2]+ME[1][columnas-1]+ME[1][columnas-2];
						MS[filas-1][columnas-1]=ME[filas-2][columnas-2]+ME[filas-2][columnas-1]+ME[filas-1][columnas-2];
						/*primera fila y ultima fila*/
						for(i=1;i<columnas-1;i++){
						MS[0][i]=ME[0][i-1]+ME[0][i+1]+ME[1][i-1]+ME[1][i]+ME[1][i+1];
						MS[filas-1][i]=ME[filas-1][i-1]+ME[filas-1][i+1]+ME[filas-2][i-1]+ME[filas-2][i]+ME[filas-2][i+1];
						}
						/*primera columna y ultima columna*/
						for(j=1;j<filas-1;j++){
						MS[j][0]=ME[j][1]+ME[j-1][0]+ME[j-1][1]+ME[j+1][0]+ME[j+1][1];
						MS[j][columnas-1]=ME[j][columnas-2]+ME[j-1][columnas-1]+ME[j-1][columnas-2]+ME[j+1][columnas-1]+ME[j+1][columnas-2];
						}
						/*inside the core*/
						for(i=1;i<filas-1;i++){
							for(j=1;j<columnas-1;j++){
							MS[i][j]=ME[i-1][j-1]+ME[i-1][j]+ME[i][j-1]+ME[i+1][j+1]+ME[i+1][j]+ME[i][j+1]+ME[i-1][j+1]+ME[i+1][j-1];
							}			
						}
							printf("Vecinos\n");
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
							printf("%d ",MS[i][j]);
							}
					    printf("\n");
						}
				}
				if(menu==6){
for(k=0;k<300;k++)
{
							system("clear");
						/*esquinas*/
						MS[0][0]=ME[0][1]+ME[1][1]+ME[1][0];
						MS[filas-1][0]=ME[filas-2][0]+ME[filas-2][1]+ME[filas-1][1];
						MS[0][columnas-1]=ME[0][columnas-2]+ME[1][columnas-1]+ME[1][columnas-2];
						MS[filas-1][columnas-1]=ME[filas-2][columnas-2]+ME[filas-2][columnas-1]+ME[filas-1][columnas-2];
						/*primera fila y ultima fila*/
						for(i=1;i<columnas-1;i++){
						MS[0][i]=ME[0][i-1]+ME[0][i+1]+ME[1][i-1]+ME[1][i]+ME[1][i+1];
						MS[filas-1][i]=ME[filas-1][i-1]+ME[filas-1][i+1]+ME[filas-2][i-1]+ME[filas-2][i]+ME[filas-2][i+1];
						}
						/*primera columna y ultima columna*/
						for(j=1;j<filas-1;j++){
						MS[j][0]=ME[j][1]+ME[j-1][0]+ME[j-1][1]+ME[j+1][0]+ME[j+1][1];
						MS[j][columnas-1]=ME[j][columnas-2]+ME[j-1][columnas-1]+ME[j-1][columnas-2]+ME[j+1][columnas-1]+ME[j+1][columnas-2];
						}
						/*inside the core*/
						for(i=1;i<filas-1;i++){
							for(j=1;j<columnas-1;j++){
							MS[i][j]=ME[i-1][j-1]+ME[i-1][j]+ME[i][j-1]+ME[i+1][j+1]+ME[i+1][j]+ME[i][j+1]+ME[i-1][j+1]+ME[i+1][j-1];
							}			
						}
						/*matriz final*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								if(MS[i][j]>=4){/*sobrepoblacion*/
								matriz_final[i][j]=0;
								}					
								if(MS[i][j]<=1){/*bacterias con menos de 2 bacterias cerca aislamiento*/
								matriz_final[i][j]=0;
								}
								if(MS[i][j]==2 && ME[i][j]==1){/*sobrevivencia*/
								matriz_final[i][j]=1;
								}
								else matriz_final[i][j]=0;					
								if(MS[i][j]==3){/*nacimiento*/
								matriz_final[i][j]=1;
								}
							}
						}	
						
						/*Intercambio matrices*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								ME[i][j]=matriz_final[i][j];
							}
						}	
						/*Impresion del resultado*/
						for(i=0;i<filas;i++){
							for(j=0;j<columnas;j++){
								if(ME[i][j]==1) printf(". ");
								else printf("  ");
							}
					    printf("\n");
						}	
						
						for(i=0;i<1000000;i++)
							i=i*1;

}
				}
		}		
		return 0;
	
}
