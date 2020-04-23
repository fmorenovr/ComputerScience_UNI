Poisson <- function(lambda){

# lambda es la probabilidad por el numero de ensayos(n*p)

v<-list()

T <- -log((1.0 - runif(1,0,1)),base=exp(1)) / lambda; 

i <- 0;

while (T < 1){
  i <- i + 1;
  v[i] <- T;
  T <- T -log((1.0 - runif(1,0,1)),base=exp(1))/ lambda;
}

return (v)

}