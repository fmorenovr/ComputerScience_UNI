#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <mpi.h>
using namespace std;
	
void fuerza(int n, double pos[3][500], double vel[3][500], double mas[500], double dt, int rank, int size){
	int i,j;
	double d[3],a[3],dl;
	for(i=rank;i<n;i+=size){
		a[0]=0;
		a[1]=0;
		a[2]=0;
		for(j=0;j<n;j++){
			if(i!=j){
				d[0]=pos[0][i]-pos[0][j];
				d[1]=pos[1][i]-pos[1][j];
				d[2]=pos[2][i]-pos[2][j];
				dl=pow(pow(d[0],2)+pow(d[1],2)+pow(d[2],2),1.5);
				a[0]+=1*mas[j]*d[0]/pow(dl,2);
				a[1]+=1*mas[j]*d[1]/pow(dl,2);
				a[2]+=1*mas[j]*d[2]/pow(dl,2);
			}
		}
		vel[0][i]+=a[0]*dt;
		vel[1][i]+=a[1]*dt;
		vel[2][i]+=a[2]*dt;
		//actualiza posiciones
		pos[0][i]+=vel[0][i]*dt;
		pos[1][i]+=vel[1][i]*dt;
		pos[2][i]+=vel[2][i]*dt;
	}
	MPI_Bcast(pos[0], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
	MPI_Bcast(pos[1], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
	MPI_Bcast(pos[2], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
	MPI_Bcast(vel[0], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
	MPI_Bcast(vel[1], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
	MPI_Bcast(vel[2], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
}

void rellenar(int n, double pos[3][500],double vel[3][500],double mas[500]){
	int i;
	for(i=0; i<n;i++){
		pos[0][i]=((double)rand()/RAND_MAX);
		pos[1][i]=((double)rand()/RAND_MAX);
		pos[2][i]=((double)rand()/RAND_MAX);
		vel[0][i]=(0.0);
		vel[1][i]=(0.0);
		vel[2][i]=(0.0);
		mas[i]=((double)rand()/RAND_MAX);
	}
}

int main(int argc, char* argv[]){
	int n=500,m=1000,rank,size;
	double t=0.01/m, pos[3][500], vel[3][500], mas[500];
	srand(time(NULL));
	MPI_Init (&argc, &argv);      /* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
	ofstream f;
	if(rank==0){
		
		f.open("datos.txt");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	rellenar(n,pos,vel,mas);
	
	for(int i=0;i<m;i++){
		if(rank==0){
			f<<pos[0][320];
			f<<" "<<pos[1][320];
			f<<" "<<pos[2][320];
			f<<endl;
		}
		fuerza(n,pos,vel,mas,t,rank,size);
	}
	f.close();
}
