#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#define MAX_PARTICLES 300
#define G 1//6.668

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
  MPI_Aint dis[1] = {          // internal displacements 
          (address2 - address1)
  };

  MPI_Type_create_struct(count, blocks, dis, types, mpi_struct);
  MPI_Type_commit(mpi_struct);

  return(EXIT_SUCCESS);
}*/

int malloc2ddouble(double ***array, int n, int m) {
  int i;
  /* allocate the n*m contiguous items */
  double *p = (double *)malloc(n*m*sizeof(double));
  if (!p) return -1;

  /* allocate the row pointers into the memory */
  (*array) = (double **)malloc(n*sizeof(double*));
  if (!(*array)) {
     free(p);
     return -1;
  }

  /* set up the pointers into the contiguous memory */
  for (i=0; i<n; i++) 
     (*array)[i] = &(p[i*m]);

  return 0;
}

int free2ddouble(double ***array) {
    /* free the memory - the first element of the array is at the start */
    free(&((*array)[0][0]));

    /* free the pointers into the memory */
    free(*array);

    return 0;
}

double
norm_3d(double a[7][MAX_PARTICLES],double b[7][MAX_PARTICLES],int i,int j){
  double norm;
  norm = pow((a[i][1]-b[j][1]),2) + pow((a[i][2]-b[j][2]),2) + pow((a[i][3]-b[j][3]),2);
  norm = pow(norm,1.5);
  return norm;
}

void
particleDescription(double particles[7][MAX_PARTICLES]){
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
    particles[4][i]=0.0;
    particles[5][i]=0.0;
    particles[6][i]=0.0;
  }
  return;
}

void
particleInteraction(double a[7][MAX_PARTICLES],int rangeA,int rangeB,double dt,int source){
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
        K = G*a[j][0];
        ax += K*(a[i][1]-a[j][1])/norm;
        ay += K*(a[i][2]-a[j][2])/norm;
        az += K*(a[i][3]-a[j][3])/norm;
      }
    }
    a[i][4]+=ax*dt;
    a[i][5]+=ay*dt;
    a[i][6]+=az*dt;
    a[i][1]+=a[i][4]*dt;
    a[i][2]+=a[i][5]*dt;
    a[i][3]+=a[i][6]*dt;
    MPI_Bcast(a[1],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
    MPI_Bcast(a[2],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
    MPI_Bcast(a[3],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
    MPI_Bcast(a[4],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
    MPI_Bcast(a[5],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
    MPI_Bcast(a[6],MAX_PARTICLES,MPI_DOUBLE,source,MPI_COMM_WORLD);
  }
//  MPI_Bcast(&(a[rangeA][0]), (rangeB-rangeA)*7, MPI_DOUBLE, source, MPI_COMM_WORLD);
  return ;
}

int
main(int argc,char *argv[]){
  double particles[7][MAX_PARTICLES];
  /*
    N particulas con 7 componentes
    0: masa
    1: x
    2: y
    3: z
    4: vx
    5: vy
    6: vz
  */
  
  int rank,size,npart,i; // particulas locales
  int iter = 1000;

  double time0,dt; // integracion de paso de tiempo
  FILE *f;  
    
  srand(time(NULL));
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  MPI_Barrier(MPI_COMM_WORLD);
  if(rank==0){
    f=fopen("Puntos.txt","w");
    time0=MPI_Wtime();
  }
//  if(rank==0)
//    particleDescription(particles);
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
    particles[4][i]=0.0;
    particles[5][i]=0.0;
    particles[6][i]=0.0;
  }
//  MPI_Bcast(particles[0], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[1], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[2], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[3], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[4], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[5], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//  MPI_Bcast(particles[6], MAX_PARTICLES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  npart=MAX_PARTICLES/size;
    
  double a = npart*rank,b = npart*(rank+1);
/*  if(rank==0)
    for(i=0;i<MAX_PARTICLES;i++)
      printf("posicion: %i\t%lf\t%lf\t%lf\n",i+1,particles[1][i],particles[2][i],particles[3][i]);*/
  dt = 0.01;
//  if(rank==0){
  printf("hola\n");
    for(i=0;i<iter;i++){
      particleInteraction(particles,a,b,dt,rank);
//      fprintf(f,"%lf\t%lf\t%lf\n",particles[4][98],particles[5][150],particles[6][299]);
    }
    time0 = MPI_Wtime() - time0;
    printf("\nEl tiempo fue: %lf para %i cuerpos\n\n",time0,MAX_PARTICLES);
//    fclose(f);
//  }
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
