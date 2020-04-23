#ifndef __NBODY_H
#define __NBODY_H

#define NBODIES        4
#define G              1
#define estrella       0
#define dt             0.01
#define maxMasa(a,b)   ((a)>(b)?(a):(b))

typedef struct p{
  double x,y,z;
  double masa;
  double vx,vy,vz;
  double ax,ay,az;
} Particle;

Particle particles[NBODIES];

extern double distance(Particle,Particle);
extern double modulus(double,double,double);
extern double* vectorialProd(double,double,double,double,double,double);
extern double escalarProd(double,double,double,double,double,double);
extern double kineticEnergySystem(Particle*);
extern double potentialEnergySystem(Particle*);
extern void particleEnergySystem(Particle*,double,FILE*);
extern double* rungeLenz(Particle,Particle);
extern void particleRungeLenz(Particle*,double,FILE*,FILE*,FILE*);
extern void particleInteraction(Particle*,int,FILE*);
extern void setParticles(Particle*,FILE*);
extern void help();
extern int* evalInput(int,char**);

#endif
