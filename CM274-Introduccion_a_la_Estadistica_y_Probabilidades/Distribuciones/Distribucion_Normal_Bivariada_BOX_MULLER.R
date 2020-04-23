# Generar Variables de la Normal Bivariada

# de 2 variables independientes

# X ~ N(0,I), I es la matriz identidad que es la matriz de covarianza

# I = S = c(varx*varx, p*varx*vary, p*varx*vary, vary*vary) , var = varianza

# 0 = al vector 2x1  u<-c(0,0) = (ux,uy) # las medias de cada valor(x,y)

# si p = 0, entonces son independientes. = covar(X,Y)/sd()*sd() ... coeficiente de Pearson ... para variables discretas

# lo que significa que 2 variables u1 y u2 ~ N(0,1)

# En general sea X ~ N(u,S) , u : vector de medias, S matriz de covarianza

# entonces se definen dos variables aleatorias, u1 con media ux y raiz varx y lo mismo para y

# ---------------------------------------------------------------

# Metodo... Box Muller:

BoxMuller<-function(){

# generamos 2 variables aleatorias entre 0 y 1

u1<-runif(1,0,1) # nos da el valor random de la normal con ux y raiz(varx)
u2<-runif(1,0,1) # nos da el valor random de la normal con uy y raiz(vary)
u<-matrix(c(u1,u2),nrow=2)

x1<- sqrt(-2*log(u[1,1],base=exp(1)))*cos(2*pi*u[2,1])
x2<- sqrt(-2*log(u[1,1],base=exp(1)))*sin(2*pi*u[2,1])

X<-matrix(c(x1,x2),nrow=2)

return(X)

}

