
# FUNCION DE CLIENTE SERVIDOR CON BERNOOULLI-------------

# Funcion para limpiar una lista(y/o cualquier otro tipo de objeto)

clear <- function(lst){
   i<-0
   while(0<length(lst)){
    lst[1]<-NULL
   }
    return(lst)
}

# Funcion para la distribucion uniforme sobre los resultados de 7,8,9,10,11

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

# Funcion para insertar listas a una lista(y/o cualquier otro tipo de objeto)

Insert <- function(lst, obj) {
    lst[[length(lst)+1]] <- obj
    return(lst)
}

# Funcion para quitar listas a una lista(y/o cualquier otro tipo de objeto)

Obtain<-function(lst){
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


###----------------------------------------------------------------------

BernoulliClientServer<-function(N){ # numero de milisegundos a simular

 totQTime<-0                            #tiempo total acumulativo
 totSysTime<-0                          # tiempo en el cual el sistema trabaja
 totIdleTime<-0                             # tiempo en el cual el sistema no trabaja
 n<-0                                       # numero de solicitudes al sistema
 m<-0                                       # numero de veces que type = 1
 serverBusy<-0                              #denota que el servidor esta libre (denotado por 0)
 lastService<-0                             # empieza un idle(ocioso) lapso de spacios
 evenList<-list()
 waitQueue<-list()
 evenList<-Clear(evenList)                  # crea una lista vacia
 waitQueue<-Clear(waitQueue)                # crea una cola vacia
 j <- floor(log((1.0-Rand()),base=exp(1))/log((0.9),base=exp(1))) +1 # genera la primera llegada de tiempo
 type<-0; 
 arrive<-j; 
 exitQ<-0;
 exitSys<-0;

 if(j<=N){
  evenList<-Insert(evenList,c(type,arrive,exitQ,exitSys))
 }
 a<-length(evenList) 

 while(a>0){

   evenList1<-Obtain(evenList)
   evenList<-Delete(evenList)

   type<-evenList1[[1]][1]
   arrive<-evenList1[[1]][2]
   exitQ<-evenList1[[1]][3]
   exitSys<-evenList1[[1]][4]

   if(type == 0){
     n <- n + 1
     j <- arrive + floor(log((1-Rand()),base=exp(1))/log((0.9),base=exp(1))) +1
     if(j<=N){ 
      evenList <- Insert(evenList,c(0,j,0,0))
     }
     if(serverBusy){
       waitQueue<-Insert(waitQueue,c(type,arrive,exitQ,exitSys))
     }
     else{
      m<-m+1 
      totIdleTime<- totIdleTime + arrive - lastService - 1
      serverBusy <- 1
      type1 <- 1
      exitQ1 <- arrive
      exitSys1 <- exitQ + floor(5*Rand()) + 7
      evenList<- Insert(evenList,c(type1,arrive,exitQ1,exitSys1))
      }
   }

   else{
    QTime<- exitQ - arrive
    totQTime <- totQTime + QTime
    SysTime <- exitSys - arrive
    totSysTime <- totSysTime + SysTime
    now <- exitSys
    b<-length(waitQueue) 
    if(b > 0){
      waitQueue1<-Obtain(waitQueue)                         
      arrive1<-as.numeric(waitQueue1[[1]][2])
      waitQueue<-Delete(waitQueue)                          
      type1 <- 1
      exitQ1 <- now
      exitSys1 <- now + floor(5*Rand()) + 7
      evenList <- Insert(evenList,c(type1,arrive1,exitQ1,exitSys1))
     }
     else{
       serverBusy <- 0
       lastService <-now - 1
     }
   }
   a<-length(evenList)
  }

  avgQTime <- round(totQTime/n,2);
  avgSysTime <- round(totSysTime/n,2);

  SS<-c(avgQTime,avgSysTime,totIdleTime,n,m)

  return (SS)

}


BernoulliClientServer(50000)
