#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char **argv){
  srand(time(NULL));
  FILE *fp = fopen("numeros.txt","w");
  long int numero, n = (long int)atoi(argv[1]); // 2^19 = 524288
  int i;                                        // 2^14 = 16384 maximo
  omp_set_num_threads(4);
  fprintf(fp,"%li\n",n);
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++){
      numero = rand()%n;
      #pragma omp ordered
        fprintf(fp,"%li",numero);
      if(i<n-1)
        #pragma omp ordered
          fprintf(fp," ");
    }
  fclose(fp);
  return 0;
}
