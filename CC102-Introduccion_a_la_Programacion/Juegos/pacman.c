#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MAXFIL 20 // 19 bloques eje y
#define MAXCOL 31 // 30 bloques eje x

int dir=4; // movimiento de pacman
int px=14,py=17; // posicion inicial de pacman
int fdir=0; // movimiento de fantasma
int _x=14,_y=4; // posiciones del enemigo inicial
int anteriorpx,anteriorpy;

char mapa[MAXFIL][MAXCOL] = {
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X  o |o o o XXXXXXo o o |o o X",
		"XoXXX XXXXXoXXXXXX XXXXXoXXXoX",
		"X XXX XXXXX XXXXXXoXXXXXoXXX X",
		"Xo o o  |  o o o o o o o| o oX",
		"X XXX XX XXXXXXXXXXXX XXoXXXoX",
		"Xo o oXXo o oXXXXo o oXX    |X",
		"X XXX XXXXXX XXXX XXXXXXoXXXoX",
		"XoXXXoXX o  o  o o o |XXoXXX X",
		"  o o|XX XXXXXXXXXXXX XX| o o ",
		"X XXXoXX XXXXXXXXXXXXoXXoXXX X",
		"XoXXX XX| o o o o o o XXoXXXoX",
		"X XXX XXXXXX XXXX XXXXXXoXXX X",
		"Xo   XXo o  oXXXXo o XX o o oX",
		"X XXX XX oXXXXXXXXXXX XX XXXoX",
		"XoXXX|o o |o o o o o|o | XXXoX",
		"X XXXoXXXX XXXXXXXXX XXX XXX X",
		"XoXXX XXXX|o  o o o |XXX XXXoX",
		"X o o o o oXXXXXXXXX o o o o X",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

void dibujar_mapa(){
	int a,b;

	for(a=0;a<MAXFIL;a++){
		for(b=0;b<MAXCOL;b++){
			if(mapa[a][b]=='X')
				printf("X");
			else
				printf(" ");
			if(mapa[a][b]=='o'){
				printf("o");
				if((py == a)&&(px == b))
					mapa[a][b]=' ';	
			}
		}
		printf("\n");
	}
}


void dibujar_pacman(){
		mapa[py][px]='Q';
}

int game_over(){ // evaluamos para cuando ya no hayan bolitas el juego termina
	int a,b;

	for(a=0;a<MAXFIL;a++){
		for(b=0;b<MAXCOL;b++){
			if(mapa[a][b]=='o'){
				return 1;} // verdadero
		}	
	}
	return 0;		// falso
}

void dibujar_fantasma(){
	mapa[_y][_x]='W'; // este es el fantasma
}

void choque_pacman(){
int j;
	if(((py == _y) && (px == _x)) || ((_y == anteriorpy) && (_x == anteriorpx))){
		for(j = 0; j<=5;j++){
			dibujar_mapa();
			mapa[py][px]='+';
			sleep(1);
		}	
	px=14; py=17;
	dir = 4;
	}
}

void mover_fantasma(){ // el movimiento alleatorio del fantasmita
	dibujar_fantasma();
	choque_pacman();
	if(mapa[_y][_x]=='|'){
		fdir= rand()%4;
	}
	if(fdir==0){
		if(mapa[_y][_x-1]!='X') _x-=1;
		else fdir = rand()%4; // valores entre 0 a 3
	}
	if(fdir==1){
		if(mapa[_y][_x+1]!='X') _x+=1;
		else fdir = rand()%4;
	}
	if(fdir==2){
		if(mapa[_y-1][_x]!='X') _y-=1;
		else fdir = rand()%4;
	}
	if(fdir==3){
		if(mapa[_y+1][_x]!='X') _y+=1;
		else fdir = rand()%4;
	}
	// para que atraviesen atajos
		if(_x<=-1) _x = 19;
		else if(_x>=19) _x =-1;
}


void main(){ // falta los datos de las flechas ****

  FILE *fp;

    fp=fopen("tetris.txt","w");
  if (fp==NULL)
    {
      printf("Error al crear el archivo de salida\n");
      return;
    }
	char key;
	scanf("%c",&key);
	while((key!='x')&& (game_over())){ // evalua si se acaba el juego y si se presiona ESC
		anteriorpx = px;
		anteriorpy = py;
		// mover al pacman
		if(key=='d') dir = 1; // derecha
		else if(key=='a') dir = 0; // izquierda
		else if(key=='w') dir = 2; //arriba
		else if(key=='s') dir = 3; // abajo 
	switch(dir){
		case 0:
			if(mapa[py][(px-1)]!= 'X')	
				px -=1;
			else dir = 4; // no hay caso para dir = 4 por lo que pacmana se detendra
			break;
		case 1:		
			if(mapa[py][px+1]!= 'X')
				px +=1;
			else dir = 4;
			break;
		case 2:
			if(mapa[py-1][(px)]!= 'X')
				px -=1;
			else dir = 4;
			break;
		case 3:	
			if(mapa[py+1][px]!= 'X')
				px +=1;
			else dir = 4;
			break;
	}
		if(px<=-1) px = 19;
		else if(px>=19) px =-1;
		dibujar_mapa();
		dibujar_pacman();
		mover_fantasma();
		sleep(1);// a qui va el controlador del programa
	}
  fprintf(fp,"Juego finalizado\n");
  fclose(fp);
}
