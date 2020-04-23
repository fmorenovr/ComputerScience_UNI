#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

#define N 4
const double /*dt = 0.1,*/ te = 30;
double dt, initE;
double maxDt = 1e-2;
double minDt = 1e-4;
double U=-1;
static double EA,jA,eA,rmaxA,rminA;
ofstream forb_dtMax; //FILE * forb_dtMax
ofstream forb_dtMin;
ofstream ferr_dtMax;
ofstream ferr_dtMin;

#define rx y[0]
#define ry y[1]
#define vx y[2]
#define vy y[3]
#define drx dy[0]
#define dry dy[1]
#define dvx dy[2]
#define dvy dy[3]

// aceleracion
double nBodyA(double* y, double* dy) { 
  double r = sqrt(rx*rx+ry*ry);
  dvx = -rx/(r*r*r);
  dvy = -ry/(r*r*r);
  return -1/r;
}

// convert double to string
string doubleToString(double a){
  ostringstream temp;
  temp<<a;
  return temp.str();
}

// velocidad
double nBodyV(double* y, double* dy) { 
  drx = vx;
  dry = vy;
  return initE-.5*(vx*vx+vy*vy);
}

// metodo de euler
void euler(double* y) {
  double dy[N],ny[N];
  nBodyA(y,dy);
  nBodyV(y,dy);
  for (int i = 0; i<N; i++) {
    ny[i] = y[i]+dy[i]*dt;
  }
  memcpy(y,ny,sizeof(double)*N);
}

// metodo de leapfrog
// siendo las posiciones guardadas en 0-N/2 y las velocidades en N/2-N
// ademas, no existe dependencia entre posiciones y velocidades
void leapfrog(double* y) {   
  double dy[N];
  nBodyA(y,dy);
  for (int i = N/2; i<N; i++) {
    y[i] = y[i]+dy[i]*dt;
  }
  nBodyV(y,dy);
  for (int i = 0; i<N/2; i++) {
    y[i] = y[i]+dy[i]*dt;
  }
}

void printY(double t, double *y,double ddt) {
  int i;
  for (i =0; i<N; i++){
    if(ddt==minDt){
      forb_dtMin << y[i] << ",\t";
    } else if(ddt==maxDt){
      forb_dtMax << y[i] << ",\t";
    }
  }
  if(ddt==minDt){
    forb_dtMin<<endl;
  } else if(ddt== maxDt){
    forb_dtMax<<endl;
  }
}

// calcula la energia cinetica, radios, excentricidad y j
void printRelError(double t, double *y,double ddt) {
  double r = sqrt(rx*rx+ry*ry);
  //double v = sqrt(vx*vx+vy*vy);
  double E = .5*(vx*vx+vy*vy)-1/r;
  double j = rx*vy-ry*vx;
  double ex =  vy*j - rx/r;
  double ey = -vx*j - ry/r;
  double e = sqrt(ex*ex+ey*ey);
  double rmax = j*j/(1+e);
  double rmin = j*j/(1-e);
  if (t==0) {
    EA = E; jA = j; eA = e; rmaxA = rmax; rminA = rmin;
  } else {
    if(ddt=minDt){
      ferr_dtMin<<t<<",\t"<<fabs((E-EA)/EA)<<",\t"<<fabs((j-jA)/jA)<<",\t"<<fabs((e-eA))<< ",\t"<<fabs((rmax-rmaxA)/rmaxA)<<",\t"<<fabs((rmin-rminA)/rminA)<<endl;
    }
    if(ddt=maxDt){
      ferr_dtMax<<t<<",\t"<<fabs((E-EA)/EA)<<",\t"<<fabs((j-jA)/jA)<<",\t"<<fabs((e-eA))<< ",\t"<<fabs((rmax-rmaxA)/rmaxA)<<",\t"<<fabs((rmin-rminA)/rminA)<<endl;
    }
  }
}

void printOrb(double t, double *y,double ddt) {
  static int p = 0;
  int pi = 100;
  if (p==pi) {
    if(ddt==minDt){
      forb_dtMin << t << ",\t";
      for (int i =0; i<N; i++){
        forb_dtMin << y[i] << ",\t";
      }
      forb_dtMin<<endl;
    } else if(ddt== maxDt){
      forb_dtMax << t << ",\t";
      for (int i =0; i<N; i++){
        forb_dtMax << y[i] << ",\t";
      }
      forb_dtMax<<endl;
    }
    p = 0;
  }
  p++;
}

void help(){
  cout<<"Ingrese e o l como parametro de entrada"<<endl;
  cout<<"./doscuerpos [e] [metodo]"<<endl;
}

#define AnalisisError 1
#define AnalisisOrbitas 1
int main(int argc, char** argv) {
  string fnorbdtMin = "ficheros/orbitadtMin_e_";
  string fnerrdtMin = "ficheros/erroresdtMin_e_";
  string fnorbdtMax = "ficheros/orbitadtMax_e_";
  string fnerrdtMax = "ficheros/erroresdtMax_e_";
  string fnend = ".txt";
  double e = 0;
  char m = 'e';
  double t;
  if (argc==1){ help(); return 0;}
  if (argc>1) e = atof(argv[1]);
  if (argc>2) m = argv[2][0];
  
  fnorbdtMin = fnorbdtMin + doubleToString(e) + "_m_"+m +"_" + fnend;
  fnerrdtMin = fnerrdtMin + doubleToString(e) + "_m_"+m +"_" + fnend;
  fnorbdtMax = fnorbdtMax + doubleToString(e) + "_m_"+m +"_" + fnend;
  fnerrdtMax = fnerrdtMax + doubleToString(e) + "_m_"+m +"_" + fnend;
  cout << fnorbdtMin<<endl;
  cout << fnorbdtMax<<endl;
  cout << fnerrdtMin<<endl;
  cout << fnerrdtMax<<endl;
  forb_dtMin.open(fnorbdtMin.c_str( ));
  forb_dtMax.open(fnorbdtMax.c_str( ));
  ferr_dtMin.open(fnerrdtMin.c_str( ));
  ferr_dtMax.open(fnerrdtMax.c_str( ));
  //if (AnalisisError) {
  //} else {
  //  maxDt = 1e-4; minDt = maxDt*.9;
  //}
  dt = maxDt;
  double y[N] = { 1, 0, 0, sqrt(1+e)};  
  initE = .5*(vx*vx+vy*vy) - 1/sqrt(rx*rx+ry*ry);
  printRelError(0,y,dt); //init
  for(t = 0; t < te; t+=dt/(-U)) {
    switch(m) {
      case 'e':
        euler(y);
        break;
      case 'l':
        leapfrog(y);
        break;
    }
    if (AnalisisOrbitas){ //perfect
      printOrb(t,y,dt);
    }
    if (AnalisisError){
      printRelError(t,y,dt);
    }
  }
  dt = minDt;
  y[0] = 1; y[1]=0; y[2]=0; y[3] = sqrt(1+e);
  initE = .5*(vx*vx+vy*vy) - 1/sqrt(rx*rx+ry*ry);
  printRelError(0,y,dt); //init
  for(t = 0; t < te; t+=dt/(-U)) {
    switch(m) {
      case 'e':
        euler(y);
        break;
      case 'l':
        leapfrog(y);
        break;
    }
    if (AnalisisOrbitas){ //perfect
      printOrb(t,y,dt);
    }
    if (AnalisisError){
      printRelError(t,y,dt);
    }
  }
  /*
  for (dt = maxDt; dt>=minDt; dt=dt/10) {
    double y[N] = { 1, 0, 0, sqrt(1+e)};
    initE = .5*(vx*vx+vy*vy) - 1/sqrt(rx*rx+ry*ry);
    if(dt==maxDt || dt==minDt){
      printRelError(0,y,dt); //init
      for(t = 0; t < te; t+=dt/(-U)) {
        switch(m) {
          case 'e':
            euler(y);
            break;
          case 'l':
            leapfrog(y);
            break;
        }
        if (AnalisisOrbitas){ //perfect
          if(dt==minDt){
            printOrb(t,y,dt);
          }
          if(dt==maxDt){
            printOrb(t,y,dt);
          }
        }
        if (AnalisisError){
          if(dt==minDt){
            printRelError(t,y,dt);
          }
          if(dt==maxDt){
            printRelError(t,y,dt);
          }
        }
      }
    }
  }*/
  ferr_dtMax.close();
  ferr_dtMin.close();
  forb_dtMax.close();
  forb_dtMin.close();
}
