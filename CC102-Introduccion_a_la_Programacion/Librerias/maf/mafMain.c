/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###                       MAF                        ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maf.h"


int main(int argc,char**argv)
{
  srand(time(NULL));
  int i,ct;
  float random;
  double ran;
  maf_tPtr list = Create_maf_t_initial_size(16);
  for (i = 0;i<16; ++i) {
    maf_t_push_back(list, i);
  }
  maf_t_print(list);
  sleep(1);
  ct = 0;
  float prom = maf_t_prom(list);
  printf("prom de list: %f\n",prom);

  while(1)
  {
    ran = (double)rand()/(double)RAND_MAX;
    random = (float)ran;
    maf_t_set_value_by_index(list,ct,random);
    maf_t_print(list);
    prom = maf_t_prom(list);
    printf("prom de list: %f\n",prom);
    sleep(1);
    ct+=1;
    if( ct >15){
      ct = 0;
    }
  }

  return 0;
}
