#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]){
  double r=0.1;// 1.0/atoi(argv[1]);
  double x0=1;//  atoi(argv[3]);
  double N=100;// atoi(argv[4]);
  int i;
  double x=x0;
  ofstream f;
  f.open("ficheros/poblacion.txt");
  cout<<"# Malthus-Model,  r="<<r<<",  x0="<<x0<<endl;
  cout<<"t\tx\tx\'"<<endl;
  for(i=0; i<=N; i++){
    f<<i<<",\t"<<x<<",\t"<<r*x<<endl;      
    x=x+r*x;
  }
  f<<i<<"\t"<<x<<endl;      
  return EXIT_SUCCESS;
}
