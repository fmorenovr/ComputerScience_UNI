#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#define MAX_PARTICLES 300
#define G 1//6.668

typedef struct p{
  double x,y,z;
  double mass;
  double vx,vy,vz;
} Particle;


/* Creating MPI Datatype of struct 
int
mpi_struct_init(MPI_Datatype *mpi_struct,int count)
{
  int i = 0;                   // temporary loop indexer 
  Particle _info;
  //count = 7;               // number of blocks in the struct 
  int blocks[1] = {count};   // set up 7 blocks 
  MPI_Datatype types[1] = {    // pixel internal types 
          MPI_DOUBLE};
  MPI_Aint address1,address2;
  MPI_Get_address(&_info,&address1);
  MPI_Get_address(&_info.x,&address2);
  MPI_Aint dis[1] = {          /* internal displacements 
          (address2 - address1)
  };

  MPI_Type_create_struct(count, blocks, dis, types, mpi_struct);
  MPI_Type_commit(mpi_struct);

  return(EXIT_SUCCESS);
}*/

double
norm_3d(Particle a,Particle b){
  double norm;
  norm = pow((a.x-b.x),2) + pow((a.y-b.y),2) + pow((a.z-b.z),2);
  norm = pow(norm,1.5);
  return norm;
}

void
particleInteraction(Particle *a,int rangeA,int rangeB,double dt,int rank){
  // fuerza ejercida por b  que actua sobre a
  double ax,ay,az;
  double norm;
  int i,j;
  for(i=rangeA;i<rangeB;i++){
    ax=0.0;
    ay=0.0;
    az=0.0;
    for(j=0;j<MAX_PARTICLES;j++){
      if(i!=j){
        norm = norm_3d(a[i],a[j]);
        ax += G*a[j].mass*(a[i].x-a[j].x)/norm;
        ay += G*a[j].mass*(a[i].y-a[j].y)/norm;
        az += G*a[j].mass*(a[i].z-a[j].z)/norm;
      }
    }
    a[i].vx+=ax*dt;
    a[i].vy+=ay*dt;
    a[i].vz+=az*dt;
    a[i].x+=a[i].vx*dt;
    a[i].y+=a[i].vy*dt;
    a[i].z+=a[i].vz*dt;
    MPI_Bcast(&a[i].x,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].y,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].z,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].mass,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].vx,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].vy,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
    MPI_Bcast(&a[i].vz,1,MPI_DOUBLE,rank,MPI_COMM_WORLD);
  }
  return ;
}

int
main(int argc,char *argv[]){
  Particle particles[MAX_PARTICLES];
  
  int rank,size,npart,i,j; // particulas locales
  int iter = 1000;

  double time0,dt; // integracion de paso de tiempo
  FILE *f;  
    
  srand(time(NULL));
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  if(rank==0){
    f=fopen("Puntos.txt","w");
    time0=MPI_Wtime();
  }
  npart=MAX_PARTICLES/size;
    
  double a = npart*rank,b = npart*(rank+1);
/*
  particles[0].x    = 50.0;
  particles[0].y    = 50.0;
  particles[0].z    = 50.0;
  particles[0].mass = 1000 * 0.2582;
  particles[0].vx=0.0;
  particles[0].vy=0.0;
  particles[0].vz=0.0;*/

  for (i=0; i<MAX_PARTICLES; i++) {
    particles[i].x    = (double)rand()/RAND_MAX;
    particles[i].y    = (double)rand()/RAND_MAX;
    particles[i].z    = (double)rand()/RAND_MAX;
    particles[i].mass = (double)rand()/RAND_MAX;//(double)(rand()%2) + ((double)(rand()%999))/1000;
    /* velocidad inicial */
    particles[i].vx=0.0;
    particles[i].vy=0.0;
    particles[i].vz=0.0;
  }
  MPI_Barrier(MPI_COMM_WORLD);
/*  if(rank==0)
    for(i=0;i<MAX_PARTICLES;i++)
      printf("posicion: %i\t%lf\t%lf\t%lf\n",i+1,particles[i].x,particles[i].y,particles[i].z);*/
  dt = 0.0001/iter;
  if(rank==0){
    for(i=0;i<iter;i++){
      particleInteraction(particles,a,b,dt,rank);
      printf("%lf\t%lf\t%lf\n",particles[150].vx,particles[150].vy,particles[150].vz);
    }
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
