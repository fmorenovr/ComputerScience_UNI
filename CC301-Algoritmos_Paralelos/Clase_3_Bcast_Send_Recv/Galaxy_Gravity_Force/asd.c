#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#define MAX_PARTICLES 300
#define G 1//6.668

double
norm_3d(double a[7][MAX_PARTICLES],double b[7][MAX_PARTICLES],int i,int j){
  double norm;
  norm = pow((a[1][i]-b[1][j]),2) + pow((a[2][i]-b[2][j]),2) + pow((a[3][i]-b[3][j]),2);
  norm = pow(norm,1.5);
  return norm;
}

void
particleAlloc(double particles[7][MAX_PARTICLES]){
  int i;
  particles[0][0] = 1000 * 0.2582;
  particles[1][0] = 0.5;
  particles[2][0] = 0.5;
  particles[3][0] = 0.5;
  particles[4][0] = 0.0;
  particles[5][0] = 0.0;
  particles[6][0] = 0.0;

  for (i=1; i<MAX_PARTICLES; i++) {
    particles[1][i] = (double)rand()/RAND_MAX;
    particles[2][i] = (double)rand()/RAND_MAX;
    particles[3][i] = (double)rand()/RAND_MAX;
    particles[0][i] = (double)rand()/RAND_MAX;
    /* velocidad inicial */
    particles[4][i] = 0.0;
    particles[5][i] = 0.0;
    particles[6][i] = 0.0;
  }
  return;
}

void
particleInteraction(double a[7][MAX_PARTICLES],int rangeA,int rangeB,double dt,int rank){
  // fuerza ejercida por b  que actua sobre a
  double ax,ay,az;
  double norm;
  double K;
  int i,j;
  for(i=rangeA;i<rangeB;i++){
    ax=0.0;
    ay=0.0;
    az=0.0;
    for(j=0;j<MAX_PARTICLES;j++){
      if(i!=j){
        norm = norm_3d(a,a,i,j);
        K = G*a[0][j];
        ax += K*(a[1][i]-a[1][j])/norm;
        ay += K*(a[2][i]-a[2][j])/norm;
        az += K*(a[3][i]-a[3][j])/norm;
      }
    }
    a[4][i]+=ax*dt;
    a[5][i]+=ay*dt;
    a[6][i]+=az*dt;
    a[1][i]+=a[4][i]*dt;
    a[2][i]+=a[5][i]*dt;
    a[3][i]+=a[6][i]*dt;
    if(rank==0)
    printf("%lf\n",a[6][299]);
    MPI_Bcast(a[1],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(a[2],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(a[3],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(a[4],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(a[5],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(a[6],MAX_PARTICLES,MPI_DOUBLE,rank,MPI_COMM_WORLD);
  }
  return ;
}

int
main(int argc,char *argv[]){
  double particles[7][MAX_PARTICLES]; /*  N particulas con 7 componentes
                                          0: masa
                                          1: x
                                          2: y
                                          3: z
                                          4: vx
                                          5: vy
                                          6: vz
                                       */
  
  int rank,size,npart,i,j;
  int iter = 1000;

  double time0,dt;
  FILE *f;  
    
  srand(time(NULL));
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if(rank==0){
    f=fopen("Puntos.txt","w");
    time0=MPI_Wtime();
  }
  particleAlloc(particles);
  npart=MAX_PARTICLES/size;
    
  double a = npart*rank,b = npart*(rank+1);
  
  
  MPI_Barrier(MPI_COMM_WORLD);
/*  if(rank==0)
    for(i=0;i<MAX_PARTICLES;i++)
      printf("posicion: %i\t%lf\t%lf\t%lf\n",i+1,particles[1][i],particles[2][i],particles[3][i]);*/
  // ---------------------------------------------------------------------------------------------------------- bien
  
  
  dt = 0.01;
  for(i=0;i<iter;i++){
    particleInteraction(particles,a,b,dt,rank);
    if(rank==0)
      fprintf(f,"%lf\t%lf\t%lf\n",particles[4][90],particles[5][150],particles[6][299]);
  }
  if(rank==0){
    time0 = MPI_Wtime() - time0;
    printf("\nEl tiempo fue: %lf para %i cuerpos\n\n",time0,MAX_PARTICLES);
    fclose(f);
  }
  MPI_Finalize();
  return 0;
}

/*

library(plot3D);

Data<-read.table("Puntos.txt");
x<-Data[[1]];
y<-Data[[2]];
z<-Data[[3]];

scatter3D(x,y,z,theta=45,phi=5);
*/
