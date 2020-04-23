Generacion de complejos :D

library(caTools)

jet.colors<- colorRampPalette (c ("#00007F", "blue", "#007FFF", "cyan", "#7FFF7F","yellow", "#FF7F00", "red", "#7F0000"))

n<- numero # numero de numeros a evaluar

Mandelbrot<-function(m,Y){

C <- complex(real = rep(seq(1.8,0.6,length.out = m), each = m),imaginary = rep(seq(1.2,1.2,length.out=m),m))

C<-matrix(C,m,m) 

Z<- 0 #inicializamos en complejo

X <- array(0,c(m,m,20)) 

for (k in 1: 20) {
 Z<-Z^2 + C
 X[,,k]<- exp(-abs(Z))
 }
 Y <- X
 return (Y)
}
image (X [,, k], col = jet.colors (256))

write.gif(X,"Mandelbrot.gif", col= jet.colors , delay = 100)

# la funcion write crea "escribe" el archivo en nuestro sistema de archivos, es decir que lo crea :D

# C(matrix C,m,m) agrupa esos reales y enteros en una matriz de m*m

#X <- array(0,c(m,m,20)) --- 0 son los valores, c(m,m,20) son las dimensiones en este caso un array de m*m*20

#seq(1.8,0.6,length.out=m) # lo que hace length.out es crear "m" numeros que estan igual mente distanciados entre si entre 1.8 y 0.6 incluidos

#real = rep(seq(1.8,0.6,length.out = m), each = m) , seq crea la secuencia, y ahora rep significa repetir, "each" significa cualquiera, es decir repetira todos "m" veces

# Z <- Z^2 + C , donde cuando sumas un entero a una matriz, se le suma a toodos sus miembros

# abs(Z) siendo el valor absoluto de todos los miembro a miembro de la matriz

# X[,,k] <- exp(-abs(Z)) pasa los valores por defecto en i = 1:1200, j= 1:200 y para k le reemplaza a la exp de cada miembro de la matriz Z

