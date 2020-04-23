ENSAYOS DE BERNOULLE EN R:

# dos parametros

# n = numero de ensayos

# p = probabilidad de que ocurran un evento

Bernoulli<-function(n,p){

v<-c(rep(0,each=n));

# creo mi "vector o cola" para guardar los datos

for(i in 1:n){
 v[i]<-0
}

# i acaba con el valor de "n"

i <- 1 + floor(log((1.0-runif(1,0,1)),base=exp(1))/log((1.0-p),base=exp(1)))

# log((1.0-runif(1,0,1)),base=exp(1))   ---------- logaritmo de x en base exp(1) (neperiano)
# floor --- funcion maximo entero 

while(i<=n){
  v[i] <- 1
 i <- i + 1 + floor(log((1.0-runif(1,0,1)),base=exp(1))/log((1.0-p),base=exp(1)))
}

return (v);

}

