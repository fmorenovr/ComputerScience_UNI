/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Dinamic Array List Functions              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "AL.h"

/*
int main(int argc, char *argv[])
{
  ALmain();
  return 0;
}
*/

int main(int argc,char**argv)
{
  srand(time(NULL));
  int i,ct;
  float random;
  double ran;
  ArrayListPtr list = Create_arrayList_initial_size(2);
  for (i = 0;i<100; ++i) {
    arrayList_push_back(list, i);
  }
  arrayList_print(list);
  sleep(1);
  ct = 0;
  size_t len = arrayList_length(list);
  printf("len de list: %ld\n",len);
  
  while(1)
  {
    ran = (double)rand()/(double)RAND_MAX;
    random = (float)ran;
    arrayList_set_value_by_index(list,ct,random);
    arrayList_print(list);
    float prom = arrayList_prom(list);
    printf("prom de list: %f\n",prom);
    sleep(1);
    ct+=1;
    if( ct >71){
      ct = 0;
    }
  }
  return 0;
}
