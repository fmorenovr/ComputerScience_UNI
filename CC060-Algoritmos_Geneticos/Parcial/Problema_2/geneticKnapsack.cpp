#include<math.h>
#include<time.h>
#include<algorithm>
#include<vector>
#include<fstream>
#include<limits.h>

#define PESOLIMITE 50     // knapsack peso limite
#define MAXGEN 1000       // numero maximo de generaciones
#define VOPT 675          // valor optimo de carga
#define PXOVER 0.35       // probabilidad de cruce
#define POPSIZE 250       // poblacion
#define NVAR 1000
#define PELITE 0.2        // probabilidad de elitismo

#if defined(__linux) || defined(__linux__)
	unsigned int seed = time(NULL);
	#define RND ((double)rand_r(&seed)/RAND_MAX) // reentrant uniform rnd
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define RND ((double)rand()/RAND_MAX) // distribucion uniforme
#endif

using namespace std;

struct carga {
	carga(int dimc) { elegidos = new bool[dimc]; }
	~carga() {	elegidos = NULL; }
	void mutate(const int dimc, const int count) {
		int mi;
		for(int i=0;i<count;i++) {
			mi = (int)(round(RND*(dimc-1)));
			elegidos[mi] = !elegidos[mi];
		}
	}
	bool* elegidos;
	int fitness;
};

int fitnessFunction(bool*& x, const int dimc, const vector<int>& v, const vector<int>& w,int limit) {
	int fit = 0, wsum = 0;
	for(int i=0;i<dimc;i++) {
		wsum += x[i]*w[i]; // suma de cargas
		fit += x[i]*v[i];
	}
	if(wsum>limit) fit -= 7*(wsum-limit); // penalidad por sobrepeso
	return fit;
}

void crossover1p(const carga& c1, const carga& c2, const carga& c3, const int dimc, const int cp) {
	for(int i=0;i<dimc;i++) {
		if(i<cp) { c3.elegidos[i] = c1.elegidos[i]; }
		else { c3.elegidos[i] = c2.elegidos[i]; }
	}
}

void crossover1p_b(const carga &c1, const carga &c2, const carga &c3, int dimc, int cp) {
	for(int i=0;i<dimc;i++) {
		if(i>=cp) { c3.elegidos[i] = c1.elegidos[i]; }
		else { c3.elegidos[i] = c2.elegidos[i]; }
	}
}
/*
void crossoverrand(const carga &c1, const carga &c2, const carga &c3, const int dimc) {
	for(int i=0;i<dimc;i++) {
		if(round(RND)) { c3.elegidos[i] = c1.elegidos[i]; }
		else { c3.elegidos[i] = c2.elegidos[i]; }
	}
}

void crossoverarit(const carga &c1, const carga &c2, const carga &c3, int dimc) {
	for(int i=0;i<dimc;i++) {
		c3.elegidos[i] = (c1.elegidos[i]^c2.elegidos[i]);
	}
}
*/

// compara el fitness acumulado
bool cfit(const carga &c1,const carga &c2) {
  return c1.fitness > c2.fitness;
}

// compara los fitness relativos
bool cmpfun(const std::pair<int,double> &r1, const std::pair<int,double> &r2) {
  return r1.second > r2.second;
}

int coin(double pxover) { // a cointoss
	if(RND<pxover) return 1; // crossover
	else return 0; // mutation
}

// inicializa las cargas con los resultados de un algoritmo voraz
void initpopg(bool**& c, const std::vector<int> &w, const std::vector<int> &v, const int dimw, int limit,int pop) {
	std::vector<std::pair<int,double> > rvals(dimw);
	std::vector<int> index(dimw,0);
	for(int i=0;i<dimw;i++) {
		rvals.push_back(std::pair<int,double>(std::make_pair(i,(double)v[i]/(double)w[i])));
	}
	std::sort(rvals.begin(),rvals.end(),cmpfun);
	int currentw = 0, k;
	for(int i=0;i<dimw;i++) {
		k = rvals[i].first;
		if(currentw + w[k] <= limit) { // greedy fill
			currentw += w[k];
			index[k] = 1;
		}
	}
	for(int i=0;i<pop;i++) {
		for(int j=0;j<dimw;j++) {
			c[i][j] = index[j];
		}
	}
}

int main() {
	printf("\n");
	srand(time(NULL));
	vector<int> w, v; // pesos y valores de los elegidos
	int info=0;
	FILE *f = fopen("pesos.txt","r");
	FILE *f2 = fopen("valores.txt","r");
	
	// leyendo los ficargaseros
	while(!feof(f) || !feof(f2) ) {
		fscanf(f," %d ",&info);
		w.push_back(info);
		info=0;
		fscanf(f2," %d ",&info);
		v.push_back(info);
	}

	const int descartados = (int)(ceil(POPSIZE*PELITE)); // cargas se descargan via elitismo
	const int dimw = w.size();
	int best = 0, ind = 0, ind2 = 0;
	int parc = 0; // indice de loa padres a cruzar
	double avg = 0; // promedio de peso
	
	// vector de poblaciones
	vector<carga> cargas(POPSIZE,carga(dimw));
	bool **c = new bool*[POPSIZE];
	
	for(int i=0;i<POPSIZE;i++) c[i] = new bool[dimw];
	clock_t start = clock();
	
	printf("Iniciando el programa para resolver Knapsack problem... ");
	initpopg(c,w,v,dimw,PESOLIMITE,POPSIZE);
	for(int i=0;i<POPSIZE;i++) {
		cargas[i].elegidos = c[i];
		cargas[i].fitness = fitnessFunction(cargas[i].elegidos, dimw ,v, w, PESOLIMITE);
	}
	printf("\n\n");

	for(int p=0;p<MAXGEN;p++) {
		std::sort(cargas.begin(), cargas.end(), cfit);
		for(int i=0;i<POPSIZE;i++) {
			if(i>descartados) { // elitism - solos las cargas descartadas
				if(coin(PXOVER)==1) { // seccion crossover
					ind = parc+round(10*RND); // escoge los padres para el crossover
					ind2 = parc+1+round(10*RND);
					
					// estrategia de cruce
					crossover1p(cargas[ind%POPSIZE],cargas[ind2%POPSIZE],cargas[i],dimw,round(RND*(dimw-1)));
//					crossoverrand(cargas[ind],cargas[ind2],cargas[i],dimw);
//					crossoverarit(cargas[0],cargas[1],cargas[i],dimw);
					cargas[i].fitness = fitnessFunction(cargas[i].elegidos, dimw ,v, w, PESOLIMITE);
					parc += 1;
				}
				else { // seccion mutacion
					cargas[i].mutate(dimw,1);
					cargas[i].fitness = fitnessFunction(cargas[i].elegidos, dimw ,v, w, PESOLIMITE);
				}
			}
			avg += cargas[i].fitness;
			if(cargas[i].fitness>best) best=cargas[i].fitness;
		}
		parc = 0;
		if(p%5==0) {
			printf("\ngeneracion: %d   \t",p);
			printf("Mejor fitness: %d  \t",best);
			printf("fitness prmedio: %f",avg/POPSIZE);
			if(best == VOPT){
			  printf("\n\n");
        clock_t end = clock();
        double t = (double)(end-start)/CLOCKS_PER_SEC;
        printf("\nLa generacion donde se alcanzo el mejor fitness fue: %d.\n",p);
        printf("\nTiempo de calculo: %fs.\n\n",t);
        printf("Terminado Meow!!!!!!\n\n");
        return 0;
			}
		}
		best = avg = 0;
	}
	return 0;
}
