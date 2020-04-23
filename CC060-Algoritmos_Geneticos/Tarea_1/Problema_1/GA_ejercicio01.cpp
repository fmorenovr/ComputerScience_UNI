#include<iostream>
#include <fstream>
#include <stdlib.h> 
using namespace std;

#define POPSIZE 4      // tamano de population
#define MAXGENS 10     // generaciones
#define NVARS 5          // genes por individuo
#define PXOVER 1       // probabilidad de cruce
#define PMUTATION 0.001   // probabilidad de mutacion

struct genotype
{
  int gene[NVARS];         // string de genes
  int fitness;             // funcion fitness
  double upper[NVARS];        // 
  double lower[NVARS];        // 
  double rfitness;            // fitness relativo = fitness / sum(fitnessPoblacion)
  double cfitness;            // fitness acumulado de la poblacion
  int number;
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

// Evalua que indice (random) tomara para hacer el Crossover
int iRand(int iMin, int iMax){
  return	rand() % iMax + iMin;
}

void initialize(string filename, int &seed){
  ifstream input;
  input.open(filename.c_str( ));
  int i;
  int j;
  double lbound;
  double ubound;

  srand(time(NULL));

  for ( i = 0; i < NVARS; i++ ){
    input >> lbound >> ubound; // coge los genes del filename
    for ( j = 0; j < POPSIZE; j++ ){
      population[j].fitness = 0;
      population[j].rfitness = 0;
      population[j].cfitness = 0;
      population[j].lower[i] = lbound;
      population[j].upper[i]= ubound;
	    population[j].gene[i] = iRand(lbound,ubound);
    }
  }
  input.close();
}

void evaluate(){
  int member;
  int i;
  int sum=0;

  for ( member = 0; member < POPSIZE; member++ ){
    for ( i = 0; i < NVARS; i++ ){
      sum = sum + population[member].gene[i];
      sum = sum*2;
    }
    // *************************************
    sum = sum/2;
    population[member].number = sum;
    population[member].fitness = sum*sum;
    sum = 0;
  }
  return;
}

void keep_the_best(){
  int cur_best,cur_poor;
  int mem;
  int i;

  cur_best = 0;
  cur_poor = 0;

  for ( mem = 0; mem < POPSIZE; mem++ ){
    if ( population[cur_best].fitness < population[mem].fitness ){
      cur_best = mem;
//      population[POPSIZE].fitness = population[mem].fitness;
	  }
	  if ( population[cur_poor].fitness > population[mem].fitness ){
	    cur_poor = mem;
	  }
  }
  // se copian los genes del mejor miembro de la poblacion (el ultimo miembro es una copia del mejor)
  for ( i = 0; i < NVARS; i++ ){
    population[cur_poor].gene[i] = population[cur_best].gene[i];
  }
  return; 
}

void print_generation_vals(){
  cout<<"ind"<<" | str gen"<<" | real point "<<"| fitness "<<endl;
  for ( int i = 0; i < POPSIZE; i++ ){
    cout<<i<<" | ";
    for(int j=0;j<NVARS;j++)
      cout<<population[i].gene[j];
    cout<<"| "<<population[i].number<<" | "<<population[i].fitness<<" | "<<population[i].rfitness<<" | "<<population[i].cfitness<<endl;
  }
  return;
}

void selector(){
  int i;
  int j;
  int mem;
  double p;
  double sum;

//  Find the total fitness of the population.
  // suma total de las funciones fitness de cada miembro (individuo)
  sum = 0.0;
  for ( mem = 0; mem < POPSIZE; mem++ ){
    sum = sum + population[mem].fitness;
  }

//  Calculate the relative fitness of each member.
  for ( mem = 0; mem < POPSIZE; mem++ ){
    population[mem].rfitness = population[mem].fitness / sum;
  }

//  Calculate the cumulative fitness.
  population[0].cfitness = population[0].rfitness;
  for ( mem = 1; mem < POPSIZE; mem++ ){
    population[mem].cfitness = population[mem-1].cfitness + population[mem].rfitness;
  }
  
  print_generation_vals();

// Selecciona a los sobrevivientes usando el fitness acumulado ***********************
  for ( i = 0; i < POPSIZE; i++ ){
	  p = fRand(a, b);
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
  return;
}

// Hace el intercambio de genes ( o indices del string )
void Xover(int point, int one, int two){
  int i;
  double t;
/*
  cout<<"point: "<<point<<endl;
  cout<<"one: "<<one<<", fitness: "<<population[one].fitness<<endl;
  for ( i = 0; i < NVARS; i++ ){
	  cout<<"i: "<<i<<", gene: "<<population[one].gene[i]<<endl;
  }
  cout<<"two: "<<two<<", fitness: "<<population[one].fitness<<endl;
  for ( i = 0; i < NVARS; i++ ){
	  cout<<"i: "<<i<<", gene: "<<population[two].gene[i]<<endl;
  }
*/

  //  Swap genes in positions 0 through POINT-1.
  for ( i = 0; i < point; i++ ){
    t = population[one].gene[i];
    population[one].gene[i] = population[two].gene[i];
    population[two].gene[i] = t;
  }
/*
  cout<<"swap genes"<<endl;
  for ( i = 0; i < NVARS; i++ ){
	cout<<"one, i: "<<i<<", gene: "<<population[one].gene[i]<<endl;
	cout<<"two, i: "<<i<<", gene: "<<population[two].gene[i]<<endl;
  }
*/
  return;
}

void crossover(){
  int mem;
  int one;
  int first = 0;
  int point;
  double x;

  for ( mem = 0; mem < POPSIZE; ++mem ){
    x = fRand(a,b);
    if ( x < PXOVER ){
      ++first;
      if ( first % 2 == 0 ){
//  Select the crossover point.
        point = iRand ( 1, NVARS-1);
        Xover (point, one, mem);
      }
      else{
        one = mem;
      }
    }
  }
  return;
}

void mutate(){
  int i;
  int j;
  double lbound;
  double ubound;
  double x;

  for ( i = 0; i < POPSIZE; i++ ){
    for ( j = 0; j < NVARS; j++ ){
      x = fRand(a,b);
      if ( x < PMUTATION ){
        lbound = population[i].lower[j];
        ubound = population[i].upper[j];
        population[i].gene[j] = iRand ( lbound, ubound);
      }
    }
  }
  return;
}

void print_generation(int generation,string output_filename){
  ofstream output;
  output.open(output_filename.c_str( ));
  output<<generation<<endl;
  for ( int i = 0; i < POPSIZE; i++ ){
    output<<i<<" "<<population[i].gene[0]<<" "<<population[i].gene[1]<<" "<<population[i].gene[2]<<" "<<population[i].fitness<<" "<<population[i].rfitness<<" "<<population[i].cfitness<<endl;
  }
  return;
}

void print_vals(int generation,FILE* output_filename){
  fprintf(output_filename,"%i\n\n",generation);
  for ( int i = 0; i < POPSIZE; i++ ){
    fprintf(output_filename,"%i\n",population[i].fitness);
  }
  fprintf(output_filename,"\n");
  return;
}

int main(){

  string filename="inicio.txt";
  FILE *points=fopen("points.txt","w");
  string output_gen_ini="Pob_Inicial.txt";
  string output_gen_end="Pob_Final.txt";
  int seed;
  int generation;

  initialize(filename, seed);

  evaluate();
  print_generation(0,output_gen_ini);

  for ( generation = 0; generation < MAXGENS; generation++ ){
    srand(time(NULL));
    cout<<"generation: "<<generation<<endl;
    print_vals(generation,points);
    keep_the_best ( );
    evaluate ( );
	  selector ( );
    crossover ();
    mutate ( );
    evaluate ( );
    if(generation==MAXGENS-1)	 print_generation(generation,output_gen_end);
  }
}
