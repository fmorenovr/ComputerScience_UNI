#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
//#define GA_POPSIZE              32            // ga population size
#define GA_POPSIZE              2048            // ga population size
//#define GA_MAXITER              128           // maximum iterations
#define GA_MAXITER              16384           // maximum iterations
#define GA_ELITRATE             0.10f           // elitism rate
#define GA_MUTATIONRATE 0.25f           // mutation rate
//#define GA_MUTATIONRATE 0.01f           // mutation rate
#define GA_MUTATION             RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET               std::string("Hello world!")

struct ga_struct
{
  string str;
  unsigned int fitness; 
};

typedef vector<ga_struct> ga_vector;

void init_population(ga_vector &population, ga_vector &buffer)
{
        int tsize = GA_TARGET.size();
//	cout<<"tsize: "<<tsize<<endl;

        for (int i=0; i<GA_POPSIZE; i++) {
             ga_struct citizen;

             citizen.fitness = 0;
         //    citizen.str.erase();
  //     cout<<"citizen.str: "<<citizen.str<<endl;

       for (int j=0; j<tsize; j++)
             citizen.str += (rand() % 90) + 32;
         //    citizen.str +=88;
	
//       cout<<"citizen.str: "<<citizen.str<<endl;

       population.push_back(citizen);
       }
        buffer.resize(GA_POPSIZE);
}

void calc_fitness(ga_vector &population)
{
       string target = GA_TARGET;
       int tsize = target.size();
       unsigned int fitness;

       for (int i=0; i<GA_POPSIZE; i++) {
              fitness = 0;
              for (int j=0; j<tsize; j++) {
                   fitness += abs(int(population[i].str[j] - target[j]));
//		   cout<<"j: "<<j<<", fitness: "<<fitness<<endl;
               }
        population[i].fitness = fitness;
//	cout<<"i: "<<i<<", fitness: "<<population[i].fitness<<endl;
        }
}

void elitism(ga_vector &population,ga_vector &buffer, int esize )
{
     for (int i=0; i<esize; i++) {
        buffer[i].str = population[i].str;
        buffer[i].fitness = population[i].fitness;
//	cout<<"i: "<<i<<", pop.str: "<<population[i].str<<endl;
//	cout<<"i: "<<i<<", pop.fit: "<<population[i].fitness<<endl;
       }
}

void mutate(ga_struct &member)
{
       int tsize = GA_TARGET.size();
       int ipos = rand() % tsize;
       int delta = (rand() % 90) + 32;

       member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void mate(ga_vector &population, ga_vector &buffer)
{
       int esize = GA_POPSIZE * GA_ELITRATE;
       int tsize = GA_TARGET.size(), spos, i1, i2;

//	cout<<"elitism, esize: "<<esize<<endl;
       elitism(population, buffer, esize);


// Mate the rest
      for (int i=esize; i<GA_POPSIZE; i++) {
         i1 = rand() % (GA_POPSIZE / 2);
         i2 = rand() % (GA_POPSIZE / 2);
        spos = rand() % tsize;
//	cout<<"spos: "<<spos<<", i1: "<<i1<<", i2: "<<i2<<endl;
        buffer[i].str = population[i1].str.substr(0, spos) +
        population[i2].str.substr(spos, esize - spos);
//	cout<<"i: "<<i<<", buf.str: "<<buffer[i].str<<endl;

        if (rand() < GA_MUTATION) mutate(buffer[i]);
      }
}

inline void print_best(ga_vector &gav)
{ cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl; }

inline void swap(ga_vector *&population,ga_vector *&buffer)
{ 	ga_vector *temp = population; 
	population = buffer; 
	buffer = temp; }

bool fitness_sort(ga_struct x, ga_struct y)
{ return (x.fitness < y.fitness); }

inline void sort_by_fitness(ga_vector &population)
{ sort(population.begin(), population.end(), fitness_sort); }

int main(){
	srand(unsigned(time(NULL)));

        ga_vector pop_alpha, pop_beta;
        ga_vector *population, *buffer;

	init_population(pop_alpha, pop_beta);
	population = &pop_alpha;
        buffer = &pop_beta;
//for (int j=0; j<GA_POPSIZE; j++)	cout<<"j: "<<j<<", pop.str: "<<pop_alpha[j].str<<endl;

for (int i=0; i<GA_MAXITER; i++) {
	cout<<"Generation i: "<<i<<endl;
            calc_fitness(*population);              // calculate fitness
	    sort_by_fitness(*population);   // sort them

//for (int j=0; j<GA_POPSIZE; j++)	cout<<"j: "<<j<<", pop.str: "<<pop_alpha[j].str<<endl;
//for (int j=0; j<GA_POPSIZE; j++)	cout<<"j: "<<j<<", pop.fitness: "<<pop_alpha[j].fitness<<endl;
	    

            print_best(*population);                // print the best one

            if ((*population)[0].fitness == 0) break;

              mate(*population, *buffer);             // mate the population together
              swap(population, buffer);               // swap buffers
      	      }

	        return 0;
}
