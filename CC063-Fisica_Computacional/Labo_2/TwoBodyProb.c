#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nbody.h"

int main(int argc,char *argv[]){
  int iter,i,metodo;
  int* parametros=evalInput(argc,argv);
  iter=parametros[0];
  metodo=parametros[1];
  FILE* finit=fopen("./ficheros/xyzInit.txt","w");
  FILE* fE=fopen("./ficheros/energia.txt","w");  
  // hacer por cada particula
  FILE* fxyz=fopen("./ficheros/movimiento.txt","w");
  FILE* fexec = fopen("./ficheros/excentricidad.txt","w");
  FILE* frmin = fopen("./ficheros/rmin.txt","w");
  FILE* frmax = fopen("./ficheros/rmax.txt","w");

  srand(time(NULL));
  setParticles(particles,finit);
  
  // inicia el ciclo
  for(i=0;i<iter;i++){
    // analiza el movimiento por interaccion
    particleInteraction(particles, metodo, fxyz);
    // calcula la excentricidad y radios max, min
    particleRungeLenz(particles, i*dt, fexec, frmin, frmax);
    // calcula la energia del sistema
    particleEnergySystem(particles,i*dt,fE);
  }
  fclose(finit);
  fclose(frmax);
  fclose(frmin);
  fclose(fexec);
  fclose(fxyz);
  fclose(fE);
  return 0;
}
