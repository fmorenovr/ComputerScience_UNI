#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <algorithm>
using namespace std;

#define POPSIZE 50       // tamano de population
#define NGENS 24          // genes por individuo
#define PXOVER 1       // probabilidad de cruce
#define PMUTATION 0.01   // probabilidad de mutacion
#define ELITRIATE 1

struct genotype
{
  bool geneX[NGENS];         // string de genes
  bool geneY[NGENS];         // string de genes
  double fitness;             // funcion fitness
  double upper[NGENS];        // 
  double lower[NGENS];        // 
  double rfitness;            // fitness relativo = fitness / sum(fitnessPoblacion)
  double cfitness;            // fitness acumulado de la poblacion
  double numberX;              // valor del gen
  double numberY;              // valor del gen
};


struct genotype population[POPSIZE+1];
struct genotype newpopulation[POPSIZE+1];

const double a = 0.0;
const double b = 1.0;

// random flotante entre a y b
double fRand(double fMin, double fMax){
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

bool compareGen(struct genotype lh,struct genotype rh){ return lh.fitness > rh.fitness; }

// Evalua que indice (random) tomara para hacer el Crossover
int iRand(int iMin, int iMax){
  return	rand() % iMax + iMin;
}

// yap
void initialize(string filename, int &seed){
  ifstream input;
  input.open(filename.c_str( ));
  int i;
  int j;
//  double* valores;
  double lbound;
  double ubound;

  srand(time(NULL));
  input >> lbound >> ubound; // coge los genes del filename

//  *valores = lbound;
//  *(valores+1) = ubound;
  for ( i = 0; i < NGENS; i++ ){
    for ( j = 0; j <= POPSIZE; j++ ){
      population[j].fitness = 0;
      population[j].rfitness = 0;
      population[j].cfitness = 0;
      population[j].numberX = 0;
      population[j].numberY = 0;
      population[j].lower[i] = lbound;
      population[j].upper[i]= ubound;
	    population[j].geneX[i] = iRand(lbound,ubound);
	    population[j].geneY[i] = iRand(lbound,ubound);
    }
  }
  input.close();
}

/* 
set xrange [-10:10]
set yrange [-10:10]
set zrange [-0.2:1.2]
set isosamples 100
splot "0098.txt",(1 - sin(sqrt(x*x+y*y))*sin(sqrt(x*x+y*y)))/(1 + 0.001*(x*x+y*y))  w l lt 26; set title "3D AG plot"
*/

// yap
void evaluate(){
  int member;
  int i;
  double sumX=0,sumY=0;
  double div = pow(2,NGENS);
  
  sort(population,population+POPSIZE,compareGen);
  for ( member = 0; member < POPSIZE; member++ ){
    for ( i = 0; i < NGENS; i++ ){
      sumX = sumX + population[member].geneX[i];
      sumY = sumY + population[member].geneY[i];
      sumX = sumX*2;
      sumY = sumY*2;
    }
    // *************************************
    sumX = sumX/2;
    sumY = sumY/2;
    sumX = ( sumX - (div-1)/2 )/((div-1)/20);
    sumY = ( sumY - (div-1)/2 )/((div-1)/20);
    population[member].numberX = sumX;
    population[member].numberY = sumY;
    population[member].fitness = (1 - sin(sqrt(sumX*sumX+sumY*sumY))*sin(sqrt(sumX*sumX+sumY*sumY)))/(1 + 0.001*(sumX*sumX+sumY*sumY));
    sumX = 0;
    sumY = 0;
  }
  return;
}

void evalProbFitness(){
  int mem;
  double sum;
  sum = 0.0;
  for ( mem = 0; mem < POPSIZE; mem++ ){
    sum = sum + population[mem].fitness;
  }

//  Calculate the relative fitness of each member.
  for ( mem = 0; mem < POPSIZE; mem++ ){
    population[mem].rfitness = population[mem].fitness/sum;
  }

//  Calculate the cumulative fitness.
  population[0].cfitness = population[0].rfitness;
  for ( mem = 1; mem < POPSIZE; mem++ ){
    population[mem].cfitness = population[mem-1].cfitness + population[mem].rfitness;
  }
  return;
}

// yap
void keep_the_best(){
  int cur_best;
  int mem;
  int i;

  cur_best = 0;

  for ( mem = 0; mem < POPSIZE; mem++ )
    {
     if ( population[POPSIZE].fitness < population[mem].fitness )
	    {
        cur_best = mem;
        population[POPSIZE].fitness = population[mem].fitness;
	    }
  }
  for ( i = 0; i < NGENS; i++ )
  {
    population[0].geneX[i] = population[cur_best].geneX[i];
    population[0].geneY[i] = population[cur_best].geneY[i];
    population[POPSIZE].geneX[i] = population[cur_best].geneX[i];
    population[POPSIZE].geneY[i] = population[cur_best].geneY[i];
  }
  return; 
}

void print_generation(){
  cout<<"ind"<<" | str gen"<<" | real point "<<"| fitness "<<endl;
  for ( int i = 0; i < POPSIZE; i++ ){
    cout<<"X"<<i<<" | ";
    for(int j = 0;j<NGENS;j++){
      cout<<population[i].geneX[j];
    }
    cout<<"| "<<population[i].numberX<<" | "<<population[i].fitness<<" | "<<population[i].rfitness<<" | "<<population[i].cfitness<<endl;
    cout<<"Y"<<i<<" | ";
    for(int j = 0;j<NGENS;j++){
      cout<<population[i].geneY[j];
    }
    cout<<"| "<<population[i].numberY<<endl;
  }
  return;
}

void printFiles(int generation,string output_filename){
  ofstream output;
  output.open(output_filename.c_str());
  for ( int i = 0; i < POPSIZE; i++ )
  {
    output<<" "<<population[i].numberX<<" "<<population[i].numberY<<" "<<population[i].fitness<<endl;
  }
}

void selector(){
  int i;
  int j;
  double p;
  sort(population,population+POPSIZE,compareGen);
  evalProbFitness();
// Selecciona a los sobrevivientes usando el fitness acumulado ***********************
  for ( i = 0; i < POPSIZE*ELITRIATE; i++ ){
	  p = fRand(0., 1.);
    if ( p < population[0].cfitness ){
      newpopulation[i] = population[0];
    }
    else{
      for ( j = 0; j < POPSIZE; j++ ){
        if ( population[j].cfitness <= p && p < population[j+1].cfitness ){
          newpopulation[i] = population[j+1];
        }
      }
    }
  }

//  Reemplaza la nueva poblacion
  for ( i = 0; i < POPSIZE; i++ ){
    population[i] = newpopulation[i];
  }
  sort(population,population+POPSIZE,compareGen);
  return;
}

// yap
void Xover(int point, int one, int two){
  int i;
  double t,w;
  int point1;
  point1 = iRand ( 1, NGENS-1);
  for ( i = 0; i < point; i++ ){
    t = population[one].geneX[i];
    population[one].geneX[i] = population[two].geneX[i];
    population[two].geneX[i] = t;
  }
  for ( i = 0; i < point1; i++ ){
    w = population[one].geneY[i];
    population[one].geneY[i] = population[two].geneY[i];
    population[two].geneY[i] = w;
  }
  return;
}

// yap
void generateGens(double* valores,int j){
  int i;
  double lbound=*(valores);
  double ubound=*(valores+1);
  srand(time(NULL));

  for ( i = 0; i < NGENS; i++ ){
	    population[j].geneX[i] = iRand(lbound,ubound);
	    population[j].geneY[i] = iRand(lbound,ubound);
  }
}

// yap
void crossover(){
  int mem;
  int one;
  int first = 0;
  int point;
  double x;

  for ( mem = 0; mem < POPSIZE*ELITRATE; ++mem ){
    x = fRand(0.,1.);
    if ( x < PXOVER ){
      ++first;
      if ( first % 2 == 0 ){
//  Select the crossover point.
        point = iRand ( 1, NGENS-1);
        if(population[mem].fitness!=population[one].fitness)
          Xover (point, one, mem);
      }
      else{
        one = mem;
      }
    }
  }
  return;
}

// yap
void mutate(){
  int i;
  int j;
  double lbound;
  double ubound;
  double x;

  for ( i = 0; i < POPSIZE; i++ ){
    for ( j = 0; j < NGENS; j++ ){
      x = fRand(0.,1.);
      if ( x < PMUTATION ){
        lbound = population[i].lower[j];
        ubound = population[i].upper[j];
        population[i].geneX[j] = iRand ( lbound, ubound);
        population[i].geneY[j] = iRand ( lbound, ubound);
      }
    }
  }
  return;
}

string IntToString (int a)
{
  ostringstream temp;
  temp<<a;
  return temp.str();
}

int main(){

  string filename="inicio.txt";
  int seed;
  int generation;
  double error=1;
  int maxGeneration=100;
  string filenumber = ".txt";

  initialize(filename, seed);
  evaluate();
  keep_the_best ( );
  for ( generation = 0;generation<maxGeneration && error>0.01; generation++ ){
//    delete(filenumber);
    srand(time(NULL));
    //cout<<"generation: "<<generation<<endl;
	  selector();
    keep_the_best();
    filenumber = ""+IntToString(generation)+".txt";
    crossover();
    mutate();
    if(generation==maxGeneration-1)  print_generation();
    evaluate();
    printFiles(generation,filenumber);
    error = 1 - population[0].fitness;
    if(generation==maxGeneration-1)  print_generation();
  }
  cout<<"generation: "<<generation<<endl;
  print_generation();
  cout<<"\n\nLa generacion donde alcanzo el valor mas proximo fue: "<<generation<<"\nCon error de aproximacion: "<<error<<endl<<"Con valor maximo tomado: "<<population[0].fitness<<endl<<endl;
}
