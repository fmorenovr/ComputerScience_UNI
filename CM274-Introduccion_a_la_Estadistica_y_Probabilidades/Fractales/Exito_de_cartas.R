### PREGUNTA 3

cartas<-1:100 # enumeramos las 100 cartas en las barajas

cartas1<-sample(cartas) # "barajamos" las cartas para obtener ubn orden aleatorio

exito<-c(rep(0,each=100))

if( cartas1[1] == 1 ){ exito[1] <-1; }

for(i in 2:100) {

	if( cartas1[i] == i ){ exito[i] <- exito[i-1] + 1; }  # sumamos los exitos de los casos

	else{ exito[i]<-exito[i-1];}   # en caso de que no ocurra ... lo dejamos tal cual es el caso anterior

}

# se hace la suma de exitos porque queremos saber el numero total de aciertos

E<-sum(exito/cartas) # calculamos la esperanza como la suma de la probabilidad y los casos

E

# vemos que la esperanza de las variables 
# a calcular (de las respectivas barajas) va incrementando conforme haya mayor probabilidad de exito





