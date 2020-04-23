##### PROBLEMA 3 !!!!!

# PARA CLIENTE SERVIDOR BERNOULLI
# FUNCION DE CLIENTE SERVIDOR CON BERNOOULLI-------------

# Funcion para limpiar una lista(y/o cualquier otro tipo de objeto)

clear <- function(lst){
   i<-0
   while(0<length(lst)){
    lst[1]<-NULL
   }
    return(lst)
}

# Funcion para insertar listas a una lista(y/o cualquier otro tipo de objeto)

insert <- function(lst, obj) {
    lst[[length(lst)+1]] <- obj
    return(lst)
}

# Funcion para quitar listas a una lista(y/o cualquier otro tipo de objeto)

delete<-function(lst){
   lst1<-lst[1]
   return (lst1)  # si solo quiero el que he quitado
}

Delete<-function(lst){
   lst[1]<-NULL
   return(lst) #si quiero el original sin el que he quitado
}


# Funcion para liberar absolutamente todo

Clear<-function(lst){
   lst<-NULL
   return(lst)
}


Rand<-function(){
 i<-1
 u<-runif(1,0,1)
 if(u<=0.2){
  i<-0.47
  return (i)# ------ devuelve 7
 }
 if((0.2<u) && (u<=0.4)){
   i<-0.53
   return (i) # -------- devuelve 8
 }
 if((0.4<u) && (u<=0.6)){
   i<-0.61
   return (i) # -------- devuelve 9
 }
 if((0.6<u) && (u<=0.8)){
  i<-0.65
  return(i) # ------ devuelve 10
 }
 else{
  i<-0.67
  return(i)
 } # ------- devuelve 11
}



###----------------------------------------------------------------------

BernoulliClientServer<-function(N){ # numero de milisegundos a simular

 totQTime<-0                            #tiempo total acumulativo
 totSysTime<-0                          # tiempo en el cual el sistema trabaja
 totIdleTime<-0                             # tiempo en el cual el sistema no trabaja
 n<-0                                       # numero de solicitudes al sistema
 serverBusy<-0                              #denota que el servidor esta libre (denotado por 0)
 lastService<-0                             # empieza un idle(ocioso) lapso de spacios
 evenList<-list()
 waitQueue<-list()
 evenList<-Clear(evenList)                  # crea una lista vacia
 waitQueue<-Clear(waitQueue)                # crea una cola vacia
 j <- trunc(log((1.0-runif(1,0,1)),base=exp(1))/log((0.9),base=exp(1))) +1 # genera la primera llegada de tiempo
 type<- 0; 
 arrive<- j; 
 exitQ<- 0;
 exitSys<- 0;

  arrive1<-NULL
  exitQ1<-NULL
  exitSys1<-NULL
  tI<-NULL
  run<-NULL

 if(j<=N){
  evenList<-insert(evenList,c(type,arrive,exitQ,exitSys))
 }
 a<-length(evenList) 

 while(a>0){

   evenList1<-delete(evenList)
   evenList<-Delete(evenList)

   type<-evenList1[[1]][1]
   arrive<-evenList1[[1]][2]
   exitQ<-evenList1[[1]][3]
   exitSys<-evenList1[[1]][4]

  if(type!=0){
  arrive1<-insert(arrive1,arrive)
  exitQ1<-insert(exitQ1,exitQ)
  exitSys1<-insert(exitSys1,exitSys)
}



   if(type == 0){
     n <- n + 1
     j <- arrive + trunc(log((1-Rand()),base=exp(1))/log((0.9),base=exp(1))) + 1
     if(j<=N){ 
      evenList <- insert(evenList,c(0,j,0,0))
     }
     if(serverBusy){
       waitQueue<-insert(waitQueue,c(type,arrive,exitQ,exitSys))
     }
     else{
      totIdleTime<- totIdleTime + arrive - lastService - 1

  tI<-insert(tI,totIdleTime)

      serverBusy <- 1
      type <- 1
      exitQ <- arrive
      exitSys <- exitQ + trunc(5*runif(1,0,1)) + 7
      evenList<- insert(evenList,c(type,arrive,exitQ,exitSys))
      }
   }
   else{
    totQTime <- totQTime + exitQ - arrive
    totSysTime <- totSysTime + exitSys - arrive
    now <- exitSys 
    if(b > 0){
      waitQueue1<-delete(waitQueue)                         
      arrive<-as.numeric(waitQueue1[[1]][2])
      waitQueue<-Delete(waitQueue)                          
      type <- 1
      exitQ <- now
      exitSys <- now + trunc(5*runif(1,0,1)) + 7
      evenList <- insert(evenList,c(type,arrive,exitQ,exitSys))
     }
     else{
       serverBusy <- 0
       lastService <-now - 1
       run<-insert(run,lastService)

     }
   }
   b<-length(waitQueue)
   if(b==0){
   waitQueue<-Clear(waitQueue)}
   a<-length(evenList)
  }


  SS8<-NULL

  SS2<-as.vector(arrive1)
  SS3<-as.vector(exitQ1)
  SS4<-as.vector(exitSys1) 
  SS7<-as.vector(tI)
  SS9<-as.vector(run)  # los valores de lastservice


  SS10 <- abs(SS2-SS3)
  SS11<-abs(SS4-SS2)
  SS12<-SS2 -1

  SS8<-insert(SS8,SS10)   # totQTime
  SS8<-insert(SS8,SS11)    # totSysTime
  SS8<-insert(SS8,SS12)     #totIdleTime
  SS8<-insert(SS8,SS9)

  toIdleTime <- sum(SS12) - run
  toSysTime<-sum(SS11)*5
  toQTime<-sum(SS10)*5

  avgQTime = toQTime/n
  avgSysTime = toSysTime/n

 Resultado<-c(avgQTime,avgSysTime,toIdleTime/n)

  return (Resultado)

}



######## ---------------PROBANDO LOS PROGRAMAS ---------------



#FUNCION DE BERNOULLI Uselo para comprobar los tiempos por programa de una sola simulacion


#BernoulliClientServer(200)  

# ----------------------------------------------------------------------

# FUNCION QUE EJECUTA LOS "n" veces el bernoulli

Ejecutar.n.veces.Client.Servidor.Bernoulli<-function(n){  # este programa ejecuta "n" veces el programa Bernoulli cliente servidor

i<-0

T<-list()

T1<-vector()  # almacenara los tiempos de encola

T2<-vector()  # almacena los tiempos de salida

T3<-vector()  #almacena los tiempos totales

while(i<n){

S<-BernoulliClientServer(200) # este programa nos retorna los tiempos del sistema

T1<-insert(T1,S[1])
T2<-insert(T2,S[2])
T3<-insert(T3,S[3])

i<-i+1

}

T1<-T1[1:n]
T2<-T2[1:n]
T3<-T3[1:n]

T<-insert(T,T1)
T<-insert(T,T2)
T<-insert(T,T3)

return (T) # retorna los 100 tiempos de cada uno

}

# Para probarla Hacemos:

# Por conveniencia : almacenamos las 100 simulaciones en una variable

 Datos.tiempo <- Ejecutar.n.veces.Client.Servidor.Bernoulli(100)

# corra para que vea los datos de simulacion

# -------------------------------------------------------------------

# FUNCION que calcula los resultados estadisticos (coeficiente de variacion, media ponderada, y graficos)

# calculo de la media ponderada y el coeficiente de variacion para cada tiempo despues de las 100 simulaciones
# para eso los guardamos en la variable "S" y la usamos para la funcion que calcula las medidas de dispersion



Medidas.Dispersion.por.cada.tiempo<-function(S){

S1<-S[[1]]
S2<-S[[2]]
S3<-S[[3]]

ST<-S1+S2+S3
ST<-ST/3 # estos valores son las medias de cada tiempo
# ahora sacaremos una media Global

# Calculamos la media de cada tiempo

M1<-mean(S1)
M2<-mean(S2)
M3<-mean(S3)

#Calculamos las desviaciones estandar de cada tiempo

SD1<-sd(S1)
SD2<-sd(S2)
SD3<-sd(S3)

#Calculamos los coeficientes de variacion de cada tiempo 

CoV1<-SD1/M1
CoV2<-SD2/M2
CoV3<-SD3/M3

#y sus respectivas Varianzas:

# el coeficiente de variacion debe ser menor que 0.5 para que podamos
# aplicar la media siendo esta una medida de dispersion y a menor valor
# denota mayor homogeneidad en los datos 

CV<-c(CoV1,CoV2,CoV3)
# vector de las coeficientes de variacion

return (CV)

}

# para probar el programa USE:

# Medidas.Dispersion.por.cada.tiempo(Datos.tiempo)

# que fue la variable que definimos hace un momento que almacena los 100 tiempo de simulacion

#--------- FUNCION PARA DIBUJAR LOS HISTOGRAMAS DE CADA TIEMPO

Dibujar<-function(n){

par(mfrow=c(1,3)) # crea los espacios para 3 graficos
hist(n[[1]],col.main="Red",col="blue",border="brown",ylab="Frecuencia de tiempos",xlab="Valores de Tiempo",density=50,angle=75,main="Histograma de Tiempo Encola")
hist(n[[2]],col.main="Red",col="red",border="yellow",ylab="Frecuencia de tiempos",xlab="Valores de Tiempo",density=30,angle=80,main="Histograma de Tiempo Salida")
hist(n[[3]],col.main="Red",col="purple",border="green",ylab="Frecuencia de tiempos",xlab="Valores de Tiempo",density=40,angle=60,main="Histograma de Tiempo Total")

}

# Para probarla use:
#  Dibujar(Datos.tiempo)

#### ____________________________________________________________________


# Funcion para el tiempo total analizado simulado por las "n" simulaciones

Medidas.Dispersion.tiempo.total<-function(S){

S1<-S[[1]]
S2<-S[[2]]
S3<-S[[3]]

ST<-S1+S2+S3
ST<-ST/3 # estos valores son las medias de cada tiempo
# ahora sacaremos una media Global
#weighted.mean(x,wt) ... media ponderada funcion de R

# como los programas que uso son los valores de Bernouilli y Poisson
# los pesos los defino como el numero de valores que retornan,
# entonces mis pesos siempre seran 3
# por lo tanto mi media ponderada sera MediaPon = 3*(valor1+ ...+ valorn)/(3*n)
# porq se multiplica el peso de cada uno a su valor y divide la suma de todos los pesos...
# lo que nos lleva a MediaPon= (Valor1+....+valorn)/n
# donde n es el numero de valores ... por entonces la MediaPonderada es la Media de los valores
# entonces hacemos:


Mean.ST<-sum(ST)/(length(ST)) # Media Total del tiempo

SD.ST<-sd(ST)

CoV<-SD.ST/Mean.ST

return (CoV)

}

# Pruebe la funcion usando:

# Medidas.Dispersion.tiempo.total(Datos.tiempo)

#--------------------------------------------------

#Y la grafica del tiempo total es :

Dibujar.tiempo<-function(n){

N1<-n[[1]]
N2<-n[[2]]
N3<-n[[3]]

NT<-N1+N2+N3

par(mfrow=c(1,1)) # crea los espacios para 3 graficos

hist(NT,col.main="Red",col="blue",border="brown",ylab="Frecuencia de tiempos",xlab="Valores de Tiempo",density=50,angle=75,main="Histograma de Tiempo Encola")

}

# Pruebe la Funcion Usando:

#Dibujar.tiempo(Datos.tiempo)

####################### NOTAS FINALES


# se hace notar que el coeficiente de variacion de cada tiempo es cercano a 0.6 o 0.5
# pero como los tiempos del Servidor se hacen de manera que se transforma en una Distribucion Exponencial
# se observa en los graficos presentados que los histogramas tienen el comportamiento de una curva que 
# crece y decrece en un determinado valor, con una concentracion casi al centro y gracias al Coeficiente de Variacion,
# podemos inducir que ES UN RESULTADO HOMOGENEO en cada tiempo,
# Y ahora comparando con el resultado total del tiempo Total Analizado del sistema
# es decir ya con los tiempos sumados y adheridos tenemos que Tambien tiene una tendencia Central de aglomeracion
# de datos, y ademas el valor del coeficiente de variacion del analisis del tiempo global
# resulto mucho menor que el analisis para cada uno, y cercano a 0.2 comparando con los demas que era 0.5 ~~ 0.6
# nuestro resultado nos dice que este metodo de sintetizar datos es mas optimo
# por lo que tambien se puede decir que es un RESULTADO CON VALORES DE VARIABLE HOMOGENEAS!!!! 

