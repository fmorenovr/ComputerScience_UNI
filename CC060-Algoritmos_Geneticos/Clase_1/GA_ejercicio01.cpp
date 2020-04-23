#include<iostream>
#include <fstream>
#include <stdlib.h> 
using namespace std;

# define POPSIZE 50
# define MAXGENS 1000
//# define MAXGENS 2
# define NVARS 3
# define PXOVER 0.8
# define PMUTATION 0.15

struct genotype
{
  double gene[NVARS];
  double fitness;
  double upper[NVARS];
  double lower[NVARS];
  double rfitness;
  double cfitness;
};
struct genotype population[POPSIZE+1];
struct genotype newpopulation[POPSIZE+1];

double fRand(double fMin, double fMax)
{
	    double f = (double)rand() / RAND_MAX;
	        return fMin + f * (fMax - fMin);
}
int iRand(int iMin, int iMax)
{
	 //   int i = (int)rand() / RAND_MAX;
	   //     return iMin + i * (iMax - iMin);
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

 for ( i = 0; i < NVARS; i++ )
    {
        input >> lbound >> ubound;

    for ( j = 0; j < POPSIZE; j++ )
        {
      population[j].fitness = 0;
      population[j].rfitness = 0;
      population[j].cfitness = 0;
      population[j].lower[i] = lbound;
      population[j].upper[i]= ubound;
      //population[j].gene[i] = r8_uniform_ab ( lbound, ubound, seed );
//      population[j].gene[i] = (double) rand() % ubound + lbound;
	population[j].gene[i] = fRand(lbound, ubound);
//	cout<<population[j].gene[i]<<endl;

	}
    }
 input.close();
}

void evaluate(){
  int member;
  int i;
  double x[NVARS+1];

  for ( member = 0; member < POPSIZE; member++ )
    {
     for ( i = 0; i < NVARS; i++ )
         {
           x[i+1] = population[member].gene[i];
//	cout<<"member: "<<member<<", i: "<<i<<", population[member].gene[i] "<<population[member].gene[i]<<endl;
    	 }
         population[member].fitness = ( x[1] * x[1] ) - ( x[1] * x[2] ) + x[3];
	//cout<<"member: "<<member<<", fitness: "<<population[member].fitness<<endl;
    }
  return;
}

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
 // cout<<"best member: "<<cur_best<<", fitness: "<<population[POPSIZE].fitness<<endl;
  //
  // se copian los genes del mejor miembro de la poblacion (el ultimo miembro es una copia del mejor)
  //
  for ( i = 0; i < NVARS; i++ )
  {
     population[POPSIZE].gene[i] = population[cur_best].gene[i];
  }

  return; 
}

void selector(){
  const double a = 0.0;
  const double b = 1.0;
  int i;
  int j;
  int mem;
  double p;
  double sum;

//  Find the total fitness of the population.

  sum = 0.0;
  for ( mem = 0; mem < POPSIZE; mem++ )
     {
        sum = sum + population[mem].fitness;
     }
//cout<<"sum: "<<sum<<endl;

//  Calculate the relative fitness of each member.

  for ( mem = 0; mem < POPSIZE; mem++ )
  {
     population[mem].rfitness = population[mem].fitness / sum;
//cout<<"mem: "<<mem<<", rfit: "<<population[mem].rfitness<<endl;
  }

//  Calculate the cumulative fitness.

  population[0].cfitness = population[0].rfitness;
  for ( mem = 1; mem < POPSIZE; mem++ )
  {
    population[mem].cfitness = population[mem-1].cfitness +
    population[mem].rfitness;
  }
    
  for ( int i = 0; i < POPSIZE; i++ )
  {
//cout<<i<<" "<<population[i].gene[0]<<" "<<population[i].gene[1]<<" "<<population[i].gene[2]<<" "<<population[i].fitness<<" "<<population[i].rfitness<<" "<<population[i].cfitness<<endl;
  }

//  Select survivors using cumulative fitness. 
  for ( i = 0; i < POPSIZE; i++ )
  {
	p = fRand(a, b);
      // p = r8_uniform_ab ( a, b, seed );
    if ( p < population[0].cfitness )
       {
      newpopulation[i] = population[0];
       }
    else
    {
         for ( j = 0; j < POPSIZE; j++ )
        {
       if ( population[j].cfitness <= p && p < population[j+1].cfitness )
        {
          newpopulation[i] = population[j+1];
        }
     }
  }
 }

//  Overwrite the old population with the new one.

  for ( i = 0; i < POPSIZE; i++ )
   {
       population[i] = newpopulation[i];
   //    cout<<"new gen: "<<population[i].fitness<<endl;
 }

    return;

}

void Xover(int one, int two){
  int i;
  int point;
  double t;
  //  Select the crossover point.
  //point = i4_uniform_ab ( 0, NVARS - 1, seed );
  point = iRand ( 0, NVARS - 1);
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
  for ( i = 0; i < point; i++ )
    {
     t                       = population[one].gene[i];
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
  const double a = 0.0;
  const double b = 1.0;
  int mem;
  int one;
  int first = 0;
  double x;

  for ( mem = 0; mem < POPSIZE; ++mem )
     {
	     x=fRand(a,b);
//    x = r8_uniform_ab ( a, b, seed );
//cout<<"mem: "<<mem<<", x: "<<x<<endl;

      if ( x < PXOVER )
   {
         ++first;

       if ( first % 2 == 0 )
     {
          //Xover ( one, mem, seed );
          Xover ( one, mem);
      }
     else
       {
         one = mem;
       }

    }
 }
     return;
}

void mutate(){
  const double a = 0.0;
  const double b = 1.0;
 int i;
 int j;
double lbound;
double ubound;
double x;

  for ( i = 0; i < POPSIZE; i++ )
  {
   for ( j = 0; j < NVARS; j++ )
     {
  //     x = r8_uniform_ab ( a, b, seed );
 	x = fRand(a,b);

if ( x < PMUTATION )
       {
         lbound = population[i].lower[j];
         ubound = population[i].upper[j];
         //population[i].gene[j] = r8_uniform_ab ( lbound, ubound, seed );
//	 cout<<"member: "<<i<<endl;
//	cout<<"mutation of gene j: "<<j<<", value: "<<population[i].gene[j]<<endl;
         population[i].gene[j] = fRand ( lbound, ubound);
//	cout<<"new gene value: "<<population[i].gene[j]<<endl;
          }
       }
     }
  return;
}

void print_generation(int generation,string output_filename){
  ofstream output;
  output.open(output_filename.c_str( ));
  output<<generation<<endl;
  for ( int i = 0; i < POPSIZE; i++ )
  {
output<<i<<" "<<population[i].gene[0]<<" "<<population[i].gene[1]<<" "<<population[i].gene[2]<<" "<<population[i].fitness<<" "<<population[i].rfitness<<" "<<population[i].cfitness<<endl;
  }
}


int main(){

string filename="inicio.txt";
string output_ini="ini.txt";
string output_gen0="0000.txt";
string output_gen_end="0999.txt";
int seed;
int generation;

initialize(filename, seed);

evaluate();
print_generation(0,output_ini);

keep_the_best ( );
  
for ( generation = 0; generation < MAXGENS; generation++ )
    {
  srand(time(NULL));
  cout<<"generation: "<<generation<<endl;

	  selector ( );

if(generation==0)	  print_generation(generation,output_gen0);

	    crossover ();
	    mutate ( );
//	    report ( generation );
	    evaluate ( );

if(generation==999)	  print_generation(generation,output_gen_end);

//	    elitist ( );
      }

}
