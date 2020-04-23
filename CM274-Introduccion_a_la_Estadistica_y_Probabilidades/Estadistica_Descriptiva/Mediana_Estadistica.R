# MEDIANA:

# DATOS TIPO I: Pocos datos y pocos valores

Mediana.No_agrupados <- function(x){

   y<-sort(x)

   len<-length(y)

   Me <- 0

   if(len%%2 == 0){
     Me <-( y[len/2] + y[len/2 + 1] ) /2
   }
   else {
      Me <- y[(len+1)/2]
    }

    return (round(Me,2))
}


# --------------------------------------------------------------------

# DATOS TIPO II: Muchos datos y pocos Valores (datos del 1 al 100, pero valores de 1 vez 1 3 veces 4 , etc ... )

Mediana.Frecuencias<-function(x){

     Tabla <- Tabla.Frecuencias(x)

     Me <- 0
   
     N<-sum(Tabla[[2]])  # el numero de datos
     len <- length(Tabla[[3]])

     for(i in 1:len){
       if(N%%2 == 0){
          Pos.N<-N/2 # se calcula la posicion de la mediana
           if(Tabla[[3]][i]==Pos.N){
              Me <- (Tabla[[1]][i] + Tabla[[1]][i+1])/2
              break
           }
           else{
              if(Tabla[[3]][i]>Pos.N){
                 Me<-Tabla[[1]][i]
                 break
              }
           }
        }
        else{
           Pos.N<- (N+1)/2 # se calcula la posicion de la mediana
           if(Tabla[[3]][i]>=Pos.N){
              Me <- Tabla[[1]][i]
              break
           }
        }
      }
      return (round(Me,2))
}

# --------------------------------------------------------


# DATOS TIPO III: Muchos Datos y Muchos Valores (por dato)


Mediana.Intervalos<-function(x){

   Tabla<-Tabla.Intervalos(x)

   Me <- 0

   N <- sum(Tabla[[4]]) # frecuencia absoluta acumulada

   N<- N/2 # la mitad del numero de datos

   len<- length(Tabla[[5]])

   for(i in 1:len){

      if(Tabla[[5]][i]>=N){

           if(i == 1) { Tabla[[5]][i-1] <- 0}

           Me <- Tabla[[1]][i] + (N - Tabla[[5]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i])/Tabla[[4]][i]

           s <- c (i,Tabla[[1]][i],N,Tabla[[5]][i-1],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i],Me)

           break # al encontrar el primero mayor o igual rompe el loop
       }
   }
   return (round(Me,2))
}


Mediana.Intervalos2<-function(x,y){

   Tabla<-Tabla.Intervalos2(x,y)

   N <- sum(Tabla[[4]]) # frecuencia absoluta acumulada

   Me <- 0

   N<- N/2 # la mitad del numero de datos

   len<- length(Tabla[[5]])

   for(i in 1:len){

      if(Tabla[[5]][i]>=N){

           if(i == 1) { Tabla[[5]][i-1] <- 0}

           Me <- Tabla[[1]][i] + (N - Tabla[[5]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i])/Tabla[[4]][i]

           s <- c (i,Tabla[[1]][i],N,Tabla[[5]][i-1],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i],Me)

           break # al encontrar el primero mayor o igual rompe el loop
       }
   }
   return (round(Me,2))
}

# esta segunda media es para que segun su tabla de "y" intervalos se vea mejor en los datos


# CONCLUSIONES

# haciendo comparaciones, ... sacando la media de datos Tipo I , Tipo II , Tipo III, no salen el mismo valor
# aun cuando sean el mismo listado, eso es  porque, la gran variedad de datos hace una mayor incertidumbre
# al momento de encontrar ese numero que cumpla " El primer numero que sea mayor o igual a N/2 (50% del total de datos)
#