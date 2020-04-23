#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;

class sphere{
	public:
		double x, y, z;
		double r;
		
		sphere(double r, double x, double y, double z){
			this->r=r;
			this->x=x;
			this->y=y;
			this->z=z;
		}
		sphere(){
		}
		~sphere();
		
		bool isInside(double x, double y, double z){
			double r_=sqrt(pow(x-this->x,2)+pow(y-this->y,2)+pow(z-this->z,2));
			//cout<<"r="<<r_<<endl;
			if(r_<= r)
				return true;
			else
				return false;
		}
};

int main(){
	bool inside;
	int n=1,counter=0,nPoints=10000000;
	double x,y,z;
	double a_M=0,b_M=0,c_M=0;
	double a_m=0,b_m=0,c_m=0;
	
	sphere *s = new sphere[n];
	
	srand(time(NULL));
	
	for(int i=0;i<n;i++){
		s[i].x = ((double)rand()/(RAND_MAX));
		s[i].y = ((double)rand()/(RAND_MAX));
		s[i].z = ((double)rand()/(RAND_MAX));
		s[i].r = 1;
		
		if(s[i].x + s[i].r > a_M)
			a_M=s[i].x + s[i].r;
		if(s[i].y + s[i].r > b_M)
			b_M=s[i].y + s[i].r;
		if(s[i].z + s[i].r > c_M)
			c_M=s[i].z + s[i].r;
		
		if(s[i].x - s[i].r < a_m)
			a_m=s[i].x - s[i].r;
		if(s[i].y - s[i].r < b_m)
			b_m=s[i].y - s[i].r;
		if(s[i].z - s[i].r < c_m)
			c_m=s[i].z - s[i].r;
			
		printf("\t%.3lf  %.3lf  %.3lf\n",s[i].x,s[i].y,s[i].z);
		printf("\t\t%.3lf  %.3lf  %.3lf\n",a_M,b_M,c_M);
		printf("\t\t%.3lf  %.3lf  %.3lf\n",a_m,b_m,c_m);
	}
	
	for(int i=0;i<nPoints;i++){
		x = ((double)rand()/(RAND_MAX))*(a_M - a_m)+a_m;
		y = ((double)rand()/(RAND_MAX))*(b_M - b_m)+b_m;
		z = ((double)rand()/(RAND_MAX))*(c_M - c_m)+c_m;
		inside=true;
		//printf("%.3lf  %.3lf  %.3lf\n",x,y,z);
		for(int j=0;j<n && inside;j++){
			if(!s[j].isInside(x,y,z)){
				inside=false;
			}
		}
		
		if(inside)
			counter++;
	}
	
	printf("Volumen= %lf\n",1.0*counter/nPoints*(a_M - a_m)*(b_M - b_m)*(c_M - c_m));
}
