# MEDIA:

# DATOS TIPO I:

Media.No_agrupados<-function(x){

    len <- length(x)

    Me <- sum(x)/len

    return (round(Me,2))


}

# ------------------------------------------------------------------

# Datos tipo II: 

Media.Frecuencias<-function(x){

    Tabla<- Tabla.Frecuencias(x)

    len<- length(Tabla[[1]])

    Me <- 0

    Sum <- 0

    Div <- 0

    for(i in 1:len){

       Sum <- Sum + Tabla[[1]][i]*Tabla[[2]][i]
       Div <- Div + Tabla[[2]][i]

    }

    Me <- Sum/Div

    return (round(Me,2))

}


# ----------------------------------------------------------------------


# Datos Tipos III:

Media.Intervalos<-function(x){

      Tabla<-Tabla.Intervalos(x)

      len<-length(Tabla[[3]])

      Me <- 0

      Sum <- 0

      Div <- 0
 
      for(i in 1:len){

       Sum <- Sum + Tabla[[3]][i]*Tabla[[4]][i]
       Div <- Div + Tabla[[4]][i]

      }

      Me <- Sum / Div

      return (round(Me,2))
}



Media.Intervalos2<-function(x,k){

      Tabla<-Tabla.Intervalos2(x,k)

      len<-length(Tabla[[3]])

      Me <- 0

      Sum <- 0

      Div <- 0
 
      for(i in 1:len){

       Sum <- Sum + Tabla[[3]][i]*Tabla[[4]][i]
       Div <- Div + Tabla[[4]][i]

      }

      Me <- Sum / Div

      return (round(Me,2))
}