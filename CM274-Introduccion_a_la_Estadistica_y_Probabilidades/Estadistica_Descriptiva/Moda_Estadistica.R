# Calculo de la MODA:


# Para datos Tipo I : Pocos datos y pocos valores

Moda.No_agrupados<-function(x){

    insertar<-function(x,obj){
        len<-length(x)
        x[len+1]<-obj
        return (x)
    }

    x<-sort(x)

    len <- length(x)
    y<-rep(0,len) # array auxliar
    num <- 0
    pos <- 1
    max <- 0
    Mo<-0

    for(cont in 1:len){

        num<-x[cont]
        pos<- cont
        for(cont1 in cont:len){
            if(x[cont1] == num ){
               y[pos]<-y[pos]+1
            }
        }
    }

# hasta aqui nos da el numero de repeticiones de cada numero (3,2,1,5,4,3, ...)

    max <- max(y)
    vect.modal<-NULL

    for(cont in 1:len){

        if(y[cont] == max){
           vect.modal<-insertar(vect.modal,cont)
        }

    }

# aqui compara dato a dato hasta el encontrar el mayor

    Mo <- x[vect.modal]

    return (round(Mo,2))

}

# --------------------------------------------------------------------

# Para datos Tipo II: Muchos datos y pocos valores

Moda.Frecuencias<-function(x){

    insertar<-function(x,obj){
        len<-length(x)
        x[len+1]<-obj
        return (x)
    }

     y <- sort(x) # sirve para ordenar de menor a mayor

     Tabla<-Tabla.Frecuencias(x)
 
     len <- length(Tabla[[1]])

     max <- max(Tabla[[2]]) # el maximo de las frecuencias absolutas
     vect.modal<-NULL

     for(cont in 1:len){
        if(Tabla[[2]][cont] == max){
           vect.modal<-insertar(vect.modal,cont)
        }
    }

     Mo <- Tabla[[1]][vect.modal]

     return (round(Mo,2))

}


# ---------------------------------------------------------------------

# para datos tipo III: Muchos Datos Muchos Valores

Moda.Intervalos<-function(x){

   insertar<-function(x,obj){
        len<-length(x)
        x[len+1]<-obj
        return (x)
   }

   Tabla<-Tabla.Intervalos(x)

   y<- max(Tabla[[4]]) # la mayor frecuencia absoluta
 
   len <- length(Tabla[[4]])

   intervalos<-NULL

   Mo<-NULL

   Moda<-0

   for(i in 1:len){
     if(Tabla[[4]][i] == y){
         intervalos<-insertar(intervalos,i)
     }
   }

   lon <- length(intervalos)

   for(j in 1:lon){

     i <- intervalos[j]

     if(Tabla[[4]][i] == y){

       if (i == 1) { 
         Moda <- Tabla[[1]][i] + ((Tabla[[4]][i])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i+1])
         Mo<-insertar(Mo,Moda)
         s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)
       }
       else{
            if (i == len) { 
               Moda <- Tabla[[1]][i] + ((Tabla[[4]][i] - Tabla[[4]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i-1])
               Mo<-insertar(Mo,Moda)
               s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)    
            }

             else{

                Moda <- Tabla[[1]][i] + ((Tabla[[4]][i] - Tabla[[4]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i-1] - Tabla[[4]][i+1])
                Mo<-insertar(Mo,Moda)
                s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)

             }
        }
      }
      else {
         Mo <- "No existe la moda, o no se puede calcular."
       }
   }

   return (round(Mo,2))
}

# --------------------------------------------


Moda.Intervalos2<-function(x,k){

   insertar<-function(x,obj){
        len<-length(x)
        x[len+1]<-obj
        return (x)
   }

   Tabla<-Tabla.Intervalos2(x,k)

   y<- max(Tabla[[4]]) # la mayor frecuencia absoluta
 
   len <- length(Tabla[[4]])

   intervalos<-NULL

   Mo<-NULL

   Moda<-0

   for(i in 1:len){
     if(Tabla[[4]][i] == y){
         intervalos<-insertar(intervalos,i)
     }
   }

   lon <- length(intervalos)

   for(j in 1:lon){

     i <- intervalos[j]

     if(Tabla[[4]][i] == y){

       if (i == 1) { 
         Moda <- Tabla[[1]][i] + ((Tabla[[4]][i])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i+1])
         Mo<-insertar(Mo,Moda)
         s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)
       }
       else{
            if (i == len) { 
               Moda <- Tabla[[1]][i] + ((Tabla[[4]][i] - Tabla[[4]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i-1])
               Mo<-insertar(Mo,Moda)
               s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)    
            }

             else{

                Moda <- Tabla[[1]][i] + ((Tabla[[4]][i] - Tabla[[4]][i-1])*(Tabla[[2]][i]-Tabla[[1]][i]))/(2*Tabla[[4]][i] - Tabla[[4]][i-1] - Tabla[[4]][i+1])
                Mo<-insertar(Mo,Moda)
                s <- c (i,Tabla[[1]][i],Tabla[[4]][i],Tabla[[2]][i],Tabla[[1]][i],Tabla[[4]][i+1],Tabla[[4]][i-1],Mo)

             }
        }
      }
      else {
         Mo <- "No existe la moda, o no se puede calcular."
       }
   }

   return (round(Mo,2))
}

# CONCLUSIONES:

# De manera similar que con la mediana, si tenemos datos libres es mejor usar Tipo II o I, el tipo II tiene
# el calculo de la moda muy distinto, por ello la diferencia de valores de la Moda para un mismo grup de datos


