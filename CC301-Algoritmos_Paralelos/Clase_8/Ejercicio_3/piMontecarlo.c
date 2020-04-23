#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

int
main(int argc, char *argv[]){

  double x[SIZE],y[SIZE];
  double piSum=0.;
  int i;
  
  srand(time(NULL));
  clock_t start=clock();
  for(i=0;i<SIZE;i++){
    x[i] = (double)rand()/RAND_MAX;
    y[i] = (double)rand()/RAND_MAX;
  }
  
  for(i=0;i<SIZE;i++){
    if((x[i]*x[i]+y[i]*y[i])<=1){
      piSum+=1.;
    }
  }
  
  double piAprox = piSum/SIZE*4;
  
  clock_t end=clock();
  double dif = (double)(end - start)/CLOCKS_PER_SEC;
  
  printf("\n\nEl proceso demoro %.8fs de tiempo.\n",dif);
  printf("El montecarlo para PI es: %.6f\n\n\n",piAprox);
  return 0;
}
/*
n<-10000
x<-runif(n)
y<-runif(n)
a<-1:n
for(i in 1:n){
  if((x[i]*x[i]+y[i]*y[i])<=1){
    a[i]<-1
  }
  else{
    a[i]<-0
  }
}
sum(a)/length(a)*4
*/
