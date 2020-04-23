# CUANTILES:

# el numero ingresado es el intervalo de porcentaje
# ejemplo si ingresas 4, el intervalo es 0, 25, 50 ,75 , 100

# DATOS TIPO I:

Cuantiles.No_agrupados<-function(x,y){

    insertar<-function(m,obj){
        len<-length(m)
        m[(len+1)]<-obj
        return (m)
    }

    len <- length(x)

    cuantiles <- NULL

    cuantil<-0

    for(i in 0:y){
      if(i == 0){
           cuantiles<-insertar(cuantiles,x[1])
      }
      else{
        if(N%%2==0){
           cuantil<- (N/y)*i
	   if(cuantil%%1==0){
               cuantiles<-insertar(cuantiles,x[cuantil])
	   }
	   else{
	       cuantiles<-insertar(cuantiles,x[cuantil+1])
	   }
        }
        else{
           cuantil<- (N+1)/y*i
           if(cuantil%%1==0){
               cuantiles<-insertar(cuantiles,x[cuantil])
	   }
	   else{
	       cuantiles<-insertar(cuantiles,x[cuantil+1])
	   }
        }
      }
    }
    return (round(cuantiles,4))
}

# --------------------------------------------------------------

# DATOS TIPO II:

Cuantiles.Frecuencias<-function(x,y){

    insertar<-function(m,obj){
        len<-length(m)
        m[(len+1)]<-obj
        return (m)
    }

    Tabla <- Tabla.Frecuencias(x)

    len<-length(Tabla[[3]])

    N <- Tabla[[3]][len] # numero de datos

    cuantiles <- NULL

    cuantil<-0

    for(i in 0:y){
      if(i == 0){
           cuantiles<-insertar(cuantiles,Tabla[[2]][1])
      }
      else{
           cuantil<- (N/y)*i
           cuantiles<-insertar(cuantiles,cuantil)
      }
    }

    lon <- length(cuantiles)
    quan<-NULL

    for(i in 1:lon){
       k<-cuantiles[i]
       for(j in 1:len){
          if(Tabla[[3]][j] >= k ){
		quan<-insertar(quan,Tabla[[1]][j])
		break;
          }
       }
    }

    return (round(quan,4))
}

# --------------------------------------------------------------

# DATOS DE TIPO III:

Cuantiles.Intervalos<-function(x,y){

    insertar<-function(m,obj){
        len<-length(m)
        m[(len+1)]<-obj
        return (m)
    }

    Tabla <- Tabla.Intervalos(x)

    len<-length(Tabla[[5]])

    N <- Tabla[[5]][len] # numero de datos

    cuantiles <- NULL

    cuantil<-0

    for(i in 0:y){
      if(i == 0){
           cuantiles<-insertar(cuantiles,Tabla[[3]][1])
      }
      else{
           cuantil<- (N/y)*i
           cuantiles<-insertar(cuantiles,cuantil)
      }
    }

    lon <- length(cuantiles)
    quan<-NULL

    for(i in 1:lon){
       k<-cuantiles[i]
       for(j in 1:len){
	  if(j==1&&i==1){
	      quan<-insertar(quan,Tabla[[3]][j])
	      break;
	   }
	  else{
	     if(j!=1){
               if(Tabla[[5]][j] >= k ){
		 quante<-Tabla[[1]][j] + (k-Tabla[[5]][j-1])/Tabla[[4]][j]*(Tabla[[2]][j]-Tabla[[1]][j])
		 quan<-insertar(quan,quante)
		 break;
               }
	     }
          }
       }
    }

    return (round(quan,4))
}

Cuantiles.Intervalos2<-function(x,w,y){

    insertar<-function(m,obj){
        len<-length(m)
        m[(len+1)]<-obj
        return (m)
    }

    Tabla <- Tabla.Intervalos2(x,w)

    len<-length(Tabla[[5]])

    N <- Tabla[[5]][len] # numero de datos

    cuantiles <- NULL

    cuantil<-0

    for(i in 0:y){
      if(i == 0){
           cuantiles<-insertar(cuantiles,Tabla[[3]][1])
      }
      else{
           cuantil<- (N/y)*i
           cuantiles<-insertar(cuantiles,cuantil)
      }
    }

    lon <- length(cuantiles)
    quan<-NULL

    for(i in 1:lon){
       k<-cuantiles[i]
       for(j in 1:len){
	  if(j==1&&i==1){
	      quan<-insertar(quan,Tabla[[3]][j])
	      break;
	   }
	  else{
	     if(j!=1){
               if(Tabla[[5]][j] >= k ){
		 quante<-Tabla[[1]][j] + (k-Tabla[[5]][j-1])/Tabla[[4]][j]*(Tabla[[2]][j]-Tabla[[1]][j])
		 quan<-insertar(quan,quante)
		 break;
               }
	     }
          }
       }
    }

    return (round(quan,4))
}