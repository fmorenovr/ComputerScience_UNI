#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#define PI 3.14159265
#define MAXPOINTS 50000
#define MAXSTEPS 50000
#define MINPOINTS 20

void init_param(void);
void init_line(void);
void update(void);
void printfinal(double[]);
void do_math(int);

int nsteps, // numero de tiempo de pasos 
    tpoints, // total de puntos en el string
    rcode, // generic return code
    rank, // id proces
    size; // number of preocessors
double values[MAXPOINTS+2],	// valores al tiempo t
       oldval[MAXPOINTS+2], // valores al tiempo (t -dt)
       newval[MAXPOINTS+2]; // valores al tiempo (t + dt)


void
init_line(){
  int i,left,right;
  left=rank*tpoints/size;
  right=(rank+1)*tpoints/size;
  double x,k,tmp,fac;
  fac=2.0*PI;
  k=(double)left;
  tmp = tpoints-1;
  for(i=1;i<=right-left;i++){
    x=k/tmp;
    values[i]=sin(fac*x);
    k=k+1.0;
    oldval[i] = values[i];
  }
}

void
init_param(){ 
  /*setnumber of points, number of iterations */
  tpoints = 0;
  nsteps = 0;
  while(tpoints < MINPOINTS || tpoints>size*MAXPOINTS){
    printf("Enter number of points along vibrating string[%d-­‐%d]:",MINPOINTS,size*MAXPOINTS);
    scanf("%d",&tpoints);
  }
  while(nsteps<1 || nsteps>MAXSTEPS){
    printf("Enter number of time steps [1-­‐%d]:",MAXSTEPS);
    scanf("%d",&nsteps); 
  }
  printf("Using points=%d, steps=%d\n",tpoints,nsteps);
}

void
do_math(int i){
  double dt,c,dx,tau,sqtau;
  c=1.0; 
  dt=0.3;
  dx=1.0;
  tau=c*dt/dx;
  sqtau=tau*tau;
  newval[i]=(2.0*values[i])-oldval[i]+(sqtau*(values[i-1]-(2.0*values[i])+values[i+1]));
}

void
update(){
  MPI_Status status;
  int left,right;
  left=rank*tpoints/size;
  right=(rank+1)*tpoints/size;
  int i,j;
  for(i=1;i<=nsteps;i++){
    if(rank!=0){
      MPI_Send(&values[1],1,MPI_DOUBLE,rank-1,1+rank,MPI_COMM_WORLD);
      MPI_Recv(&values[0],1,MPI_DOUBLE,rank-1,30+rank+1,MPI_COMM_WORLD,&status);
    }
    if(rank!=size-1){
      MPI_Recv(&values[right-left+1],1,MPI_DOUBLE,rank+1,1+rank+1,MPI_COMM_WORLD,&status);
      MPI_Send(&values[right-left],1,MPI_DOUBLE,rank+1,30+rank+2,MPI_COMM_WORLD);
    }
    printf("%d recibido from %d\n",i,rank);
    for(j=1;j<=right-left;j++){
      if(j==1 && rank==0 || j==right-left && rank==size-1) newval[j]=0.0;
      else do_math(j);
    }
    for(j=1;j<=right-left;j++){
      oldval[j]=values[j];
      values[j]=newval[j];
    }
  }
}

void
printfinal(double vec[]){
  int i; 
  FILE *f;
  f=fopen("ondaPointsMPI.txt","w");
  for(i=1;i<=tpoints;i++){
    printf("%d %.5lf\n",i,vec[i]);
    fprintf(f,"%lf\n",vec[i]);
  }
  fclose(f);
}

int
main(int argc, char* argv[]){
  double time0,time1;
  int left,right;
  MPI_Init (&argc, &argv); /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */
  if(rank==0){
    printf("\nStarting serial version of wave equation...\n");
    init_param();
  }
  MPI_Barrier(MPI_COMM_WORLD);
  time0=MPI_Wtime();
  // Mandamos el numero de puntos y el numero de pasos a todos los procesadores
  MPI_Bcast(&tpoints,1,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Bcast(&nsteps,1,MPI_INT,0,MPI_COMM_WORLD);
  
  double vec[tpoints+2];
  if(rank==0) printf("Initializing points on the line...\n");
  init_line();

  if(rank==0) printf("Updating all points for all time steps...\n");
  update();

  if(rank==0) printf("Printing final results...\n");
  right=(rank+1)*tpoints/size;
  left=rank*tpoints/size;
  MPI_Gather(values,right-left,MPI_DOUBLE,vec,right-left,MPI_DOUBLE,0,MPI_COMM_WORLD);
  
  if(rank==0) printfinal(vec);
  time1=MPI_Wtime();
  time0=time1-time0;
  MPI_Reduce(&time0,&time1,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

  if(rank==0){
    printf("\nDone.\n\n");
    printf("Time %.8lfseg.\n",time1);
  }
  MPI_Finalize();
  return 0;
}
