#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define MAXPOINTS 1000
#define MAXSTEPS 1000
#define MINPOINTS 20
#define PI 3.14159265

void init_param(void);
void init_line(void);
void update(void);
void printfinal(void);
void do_math(int);

int nsteps, // numero de tiempo de pasos 
    tpoints, // total de puntos en el string
    rcode; // generic return code
double values[MAXPOINTS+2],	// valores al tiempo t
       oldval[MAXPOINTS+2], // valores al tiempo (t -dt)
       newval[MAXPOINTS+2]; // valores al tiempo (t + dt)

FILE *f;

// inicializa los puntos en linea de acuerdo a la funcion sin()
void
init_line(){
  int i,j;
  double x,fac,k,tmp;
  fac=2.0*PI;
  k=0.0;
  tmp=tpoints-1;
  // calcula los valores iniciales de la curva de seno
  for(j=1;j<=tpoints;j++){
    x=k/tmp;
    values[j] = sin(fac*x);
    k=k+1.0;
  }
  // inicializa los antguos valores del array
  for(i=1;i<=tpoints;i++){
    oldval[i] = values[i];
  }
}

void
init_param(){
  char tchar[8];
  // set number of points, numero de iteraciones
  tpoints=0;
  nsteps=0;
  while((tpoints<MINPOINTS)||(tpoints>MAXPOINTS)){
    printf("Ingresa numero de puntos en la cuerda vibrante [%d-%d]: ",MINPOINTS,MAXPOINTS);
    scanf("%s",tchar);
    tpoints = atoi(tchar);
  }
  while((nsteps<1)||(nsteps>MAXSTEPS)){
    printf("Ingresa el numero de lapsos de tiempo [1-%d]: ",MAXSTEPS);
    scanf("%s",tchar);
    nsteps = atoi(tchar);
  }
  printf("Using points = %d, steps = %d\n",tpoints,nsteps);
}
  
void
do_math(int i){
  double dtime,c,dx,tau,sqtau;
  dtime=0.3;
  c=1.0;
  dx=1.0;
  tau=(c* dtime/dx);
  sqtau = tau * tau;
  newval[i]  =	(2.0*values[i]) - oldval[i] + (sqtau * (values[i-1] - (2.0 * values[i]) + values[i+1]));
}

void
update(){
  int i,j;
  // actualiza valores por cada iteracion
  for(i=1;i<=nsteps;i++){
    // actualiza los puntos lineas para este tiempo
    for(j=1;j<=tpoints;j++){
      // endpoints globales
      if((j==1) || (j==tpoints))  newval[j]=0.0;
      else  do_math(j);
    }
    // actualiza viejos valores con nuevos valores
    for(j=1;j<=tpoints;j++){
      oldval[i]=values[j];
      values[j] = newval[j];
    }
  }
}

void
printfinal(){
  int i;
  FILE *f;
  f=fopen("ondaPoints.txt","w");
  for(i=0;i<=tpoints;i++){
    printf("%d %6.4f\n",i,values[i]);
    fprintf(f,"%lf\n",values[i]);
  }
  fclose(f);
}

int
main(int argc,char* argv[]){
  printf("Inicializa La Ecuacion de Onda...\n");
  init_param();
  printf("Inicializa puntos en la linea ...\n");
  init_line();
  printf("Actualizando todos los puntos para todo el lapso de tiempo ... \n");
  update();
  printf("Imprimiendo los resultados finales ... \n");
  printfinal();
  printf("\nTerminado.\n\n");
  return 0;
}
