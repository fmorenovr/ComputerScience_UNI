METODO ACEPTACION RECHAZO !!! 

u=runif(1)*M
y=randg(1) # esto viene de la funcion G(x)
while (u>f(y)/g(y))
{
 u=runif(1)*M
 y=randg(1)
}


-------------------------------------------------------------------


#generacion para la distribucion BETA

gen.Beta <- function(alpha=2.7,beta=6.3,n=100){
  X <- NULL
  M <- (beta-1)/(alpha-1)
  M <- 1/(1+M)
  M <- (1/beta(alpha,beta))*M^(alpha-1)*(1-M)^(beta-1) # esta es la semilla :D
  while (length(X)<=n){
    Y <- runif(1)
    fY <- (1/beta(alpha,beta))*Y^(alpha-1)*(1-Y)^(beta-1)   ## aqui escribes la funcion para realizar la sumatoria :D :D :D :D :D :D :D :D :D :D :D :D :D :D
    U <- m*runif(1) # Es es el valor generado
    if (U<fY){
      X <- c(X,Y)
    }
  }
  return(X) 
}


-------------------------------------------------------------------

otro metodo de integrar

> integrand1 <- function(x){
+ 1/((x+1)*sqrt(x))
+ }
> integrate(integrand, lower= 0, upper = Inf)

-------------------------------------------------------------------

# Para la distribucion exponencial

> Nsim=10^4 #number of random variables
> U=runif(Nsim)
> X=-log(U) #transforms of uniforms
> Y=rexp(Nsim) #exponentials from R
> par(mfrow=c(1,2)) #plots
> hist(X,freq=F,main="Exp from Uniform")
> hist(Y,freq=F,main="Exp from R")