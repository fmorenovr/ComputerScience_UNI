#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

const double a = 0.05;
const double b = 0.02;
const double c = 0.04;
const double d = 0.6;
const double step = .25;
const int numberOfLoops = 4000;

double dxdt(double x, double y){
  return x*(a - b*y);
}

double dydt(double x, double y){
  return y*(c*x - d);
}

int main(int argc, char** argv){
  //x -> prey
  //y -> predator
  double y0Step = 1;
			
  //		for(int i1 = 0; i1 < 10; i1++){
  double x0 = 10;
  //		double y0 = 10+i1*y0Step;							
  double y0 = 10;							
  double x = x0;
  double y = y0;
  string filename;
  if(a==0.05 && b == 0.002 && d == 0.06 && c == 0.004){
    filename = "ficheros/poblacion.txt";
  } else {
    filename = "ficheros/poblacion_inestable.txt";
  }
										
  ofstream cf(filename.c_str(),ofstream::out);

  for(double i1 = 0; i1 < numberOfLoops * step ; i1 += step){
    cf<<i1<<",\t"<<x<<",\t"<<y<<endl;
    x0=x;
    y0=y;
    x += step * dxdt(x0,y0);
    y += step * dydt(x0,y0);
  }
  cf.close();
  //		}
  return 0;
}
