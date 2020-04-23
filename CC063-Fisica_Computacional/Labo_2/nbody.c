#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "nbody.h"

double distance(Particle a,Particle b){
  double r,r1;
  r = modulus((a.x-b.x),(a.y-b.y),(a.z-b.z));
  r1 = r*r;
  return (r*r1);
}

double modulus(double x,double y, double z){
  return (sqrt(x*x + y*y + z*z));
}

double* vectorialProd(double ux,double uy, double uz, double vx, double vy, double vz){
  double* vector=malloc(3*sizeof(double));
  *(vector)   = uy*vz - uz*vy;
  *(vector+1) = uz*vx - ux*vz;
  *(vector+2) = ux*vy - uy*vx;
  return vector;
}

double escalarProd(double ux,double uy, double uz, double vx, double vy, double vz){
  return (ux*vx+uy*vy+uz*vz);
}

double kineticEnergySystem(Particle *a){
  int i;
  double E=0.0;
  for(i=0;i<NBODIES;i++){
    E += a[i].masa*(a[i].vx*a[i].vx+a[i].vy*a[i].vy+a[i].vz*a[i].vz);
  }
  E = E/2.0;
  return E;
}

double potentialEnergySystem(Particle *a){
  int i,j;
  double x,y,z,r;
  double E=0.0;
  for(i=0;i<NBODIES;i++){
    for(j=0;j<NBODIES;j++)
      if(i!=j){
        x = a[j].x-a[i].x,
        y = a[j].y-a[i].y,
        z = a[j].z-a[i].z;
        r = modulus(x,y,z);
        E-=G*a[j].masa*a[i].masa/r;
      }
  }
  return E;
}

void particleEnergySystem(Particle *a, double dt1, FILE* f){
  double energia = kineticEnergySystem(a) + potentialEnergySystem(a);
  fprintf(f,"%lf\t%lf\n",energia,dt1);
  return ;
}

double* rungeLenz(Particle a,Particle b){
  // vector diferencia de posiciones
  double x = a.x-b.x,
         y = a.y-b.y,
         z = a.z-b.z;
  // vector diferencia de velocidades
  double vx = a.vx-b.vx,
         vy = a.vy-b.vy,
         vz = a.vz-b.vz;
  double r = modulus(x,y,z);
  double M = a.masa+b.masa;//maxMasa(a.masa,b.masa);
  double mu = G*M;
  // vector momento angular j=rxv
  double* j = vectorialProd(x,y,z,vx,vy,vz);
  double jmod = modulus(j[0],j[1],j[2]);
  // vx(rxv)
  double* vj = vectorialProd(vx,vy,vz,j[0],j[1],j[2]);
  // vector Runge-Lenz
  //double Ax = vj[0] + mu*x/r,
  // excentricidad
  double ex = vj[0]/mu - x/r,
         ey = vj[1]/mu - y/r,
         ez = vj[2]/mu - z/r;
  // excentricidad de la orbita
  double e = modulus(ex,ey,ez);
  // calculo del angulo de separacion
  double cos0 = escalarProd(ex,ey,ez,x,y,z)/e/r;
  // radio maximo y minimo
  double rmax = jmod*jmod/(mu*(1+e*cos0)),
         rmin = jmod*jmod/(mu*(1-e*cos0));
  double* output=malloc(3*sizeof(double));
  *(output)   = e;
  *(output+1) = rmin;
  *(output+2) = rmax;
  return output;
}

void particleRungeLenz(Particle *a,double dt1,FILE* f,FILE* g,FILE* h){
  double* outputs;
  int j;
  for(j=1;j<NBODIES;j++){
    if(j!=estrella && j==1){
      outputs=rungeLenz(a[estrella],a[j]);
      // excentricidad
      fprintf(f,"%lf\t%lf\n",outputs[0],dt1);
      // rmin
      fprintf(g,"%lf\t%lf\n",outputs[1],dt1);
      // rmax
      fprintf(h,"%lf\t%lf\n",outputs[2],dt1);
    }
  }
  return ;
}

void particleInteraction(Particle *a, int metodo,FILE *f){
  // fuerza ejercida por b  que actua sobre a
  double ax=0,ay=0,az=0,r,vx1_2,vy1_2,vz1_2;
  int i,j;
  for(i=0;i<NBODIES;i++){
    // iniciando variables para euler y leapfrog
    // v1_2(t) = v(t)+a(t)*dt/2
    vx1_2 = a[i].vx + a[i].ax*dt/2.;
    vy1_2 = a[i].vy + a[i].ay*dt/2.;
    vz1_2 = a[i].vz + a[i].az*dt/2.;
    ax=ay=az=0;
    for(j=0;j<NBODIES;j++){
      if(i!=j){
        r = distance(a[j],a[i]);
        ax += G*a[j].masa*(a[j].x-a[i].x)/r;
        ay += G*a[j].masa*(a[j].y-a[i].y)/r;
        az += G*a[j].masa*(a[j].z-a[i].z)/r;
      }
    }
    a[i].ax=ax;
    a[i].ay=ay;
    a[i].az=az;
    if(metodo==1){ // metodo de euler
      // calculo de la velocidad
      // v(t+1) = v(t) + a(t)*dt
      a[i].vx = a[i].vx + ax*dt;
      a[i].vy = a[i].vy + ay*dt;
      a[i].vz = a[i].vz + az*dt;
      // calculo de la posicion
      // r(t+1) = r(t) + v(t)*dt
      a[i].x = a[i].x + a[i].vx*dt;
      a[i].y = a[i].y + a[i].vy*dt;
      a[i].z = a[i].z + a[i].vz*dt;
    } else if(metodo==2){ // metodo de leapfrog
      // calculo de la posicion
      // r(t+1) = r(t) + v1_2(t)*dt
      a[i].x = a[i].x + vx1_2*dt;
      a[i].y = a[i].y + vy1_2*dt;
      a[i].z = a[i].z + vz1_2*dt;
      // calculo de la velocidad
      // v(t+1) = v1_2(t) + a(t+1)*dt/2
      a[i].vx = vx1_2 + ax*dt/2.;
      a[i].vy = vy1_2 + ay*dt/2.;
      a[i].vz = vz1_2 + az*dt/2.;
    }
  }
  fprintf(f,"%lf\t%lf\t%lf\n",a[1].x,a[1].y,a[1].z);
  return ;
}

void setParticles(Particle* a, FILE* f){
  int i;
  a[0].x    = 50.0;
  a[0].y    = 50.0;
  a[0].z    = 50.0;
  a[0].masa = 1.0;
  /* velocidad inicial */
  a[0].vx=0.0;
  a[0].vy=0.0;
  a[0].vz=0.0;
  /* aceleracion inicial */
  a[0].ax=0.0;
  a[0].ay=0.0;
  a[0].az=0.0;
  fprintf(f,"%lf\t%lf\t%lf\n",a[0].x,a[0].y,a[0].z);
  for (i=1; i<NBODIES; i++) {
    a[i].x    = (double)rand()/(double)RAND_MAX*20+40.0;
    a[i].y    = (double)rand()/(double)RAND_MAX*20+40.0;
    a[i].z    = (double)rand()/(double)RAND_MAX*20+40.0;
    a[i].masa = 1.0;//((double)(rand()%999))/1000.;
    /* velocidad inicial */
    a[i].vx=2.0;
    a[i].vy=3.0;
    a[i].vz=0.0;
    /* aceleracion inicial */
    a[i].ax=0.0;
    a[i].ay=0.0;
    a[i].az=0.0;
    fprintf(f,"%lf\t%lf\t%lf\n",a[i].x,a[i].y,a[i].z);
  }
  return ;
}

void help(int iter){
  printf("\n\nProblema de 2 cuerpos:\n");
  printf("El ingreso de datos es de la siguiente manera:\n");
  printf("./TwoBodyProb [command]\n\t\t- - donde [command] puede ser:\n");
  printf("--help          --  muestra este mensaje.\n");
  printf("[]              --  ejecuta la simulacion con el metodo de euler y %i iteraciones.\n",iter);
  printf("[num]           --  ejecuta la simulacion con el metodo de euler y [num] iteraciones.\n");
  printf("[method]        --  ejecuta la simulacion con el metodo [method] y %i iteraciones.\n",iter);
  printf("[num] [method]  --  ejecuta la simulacion con el metodo [method] y [num] iteraciones.\n\n\n");
  return ;
}

int* evalInput(int argc, char *argv[]){
  int iter=1000,metodo=1;
  int *data=malloc(2*sizeof(int));
  if(argc==1){
    printf("Usando el metodo de euler y %i iteraciones por default ...\n",iter);
  } else if(argc==2){
    if(strcmp("--help",argv[1])==0 || strcmp("--h",argv[1])==0){
      help(iter);
      exit(1);
    } else if(strcmp("euler",argv[1])!=0 && strcmp("leapfrog",argv[1])!=0){
      iter = atoi(argv[1]);
      printf("Usando el metodo de euler y %s iteraciones por default ... \n",argv[1]);
    } else{
      if(strcmp("euler",argv[1])==0){
        printf("Usaremos el metodo de %s y %i iteraciones por default para aproximar ... \n",argv[1],iter);
        metodo = 1; // euler
      } else if(strcmp("leapfrog",argv[1])==0){
        printf("Usaremos el metodo de %s y %i iteraciones por default para aproximar ... \n",argv[1],iter);
        metodo = 2; // leap frog
      } else{
        printf("Error de metodo...\n");
        help(iter);
        exit(1);
      }
    }
  } else if(argc==3){
    iter = atoi(argv[1]);
    if(strcmp("euler",argv[2])==0){
      printf("Usaremos el metodo de %s y %s iteraciones para aproximar ... \n",argv[2],argv[1]);
      metodo = 1; // euler
    }else if(strcmp("leapfrog",argv[2])==0){
      printf("Usaremos el metodo de %s y %s iteraciones para aproximar ... \n",argv[2],argv[1]);
      metodo = 2; // leap frog
    } else{
      printf("Error de ingreso...\n");
      help(iter);
      exit(1);
    }
  } else{
    printf("Error de ingreso...\n");
    help(iter);
    exit(1);
  }
  *(data)=iter;
  *(data+1)=metodo;
  return data;
}
