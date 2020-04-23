## CLIENTE SERVIDOR CON DISTRIBUCION DE POISSON


# Funcion para limpiar una lista(y/o cualquier otro tipo de objeto)

clear <- function(lst){
   while(0<length(lst)){
    lst[1]<-NULL
   }
    return(lst)
}

# Funcion para insertar listas a una lista(y/o cualquier otro tipo de objeto)

Insert <- function(lst, obj) {
    lst[[length(lst)+1]] <- obj
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

###------------------------------------------------------------

PoissonClientServer<-function(T,lambda){

# T es el tiempo total a simular
# lambda es la probabilidad por el numero de ensayos(n*p)
  totQTime<-0
  totSysTime<-0
  totIdleTime<-0
  n<-0
  serverBusy<-0
  lastService<-0
  evenList<-list()
  waitQueue<-list()
  evenList<-Clear(evenList)
  waitQueue<-Clear(waitQueue)
  t <- -log((1.0-Rand()),base=exp(1))/lambda; 
  type <- 0
  arrive <- t
  exitQ <- 0
  exitSys <- 0

  if(t<=T){
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

   if(type==0){
     n <- n+1
     t <- arrive - log((1.0-Rand()),base=exp(1))/lambda;
     if(t<=T){
       evenList<-Insert(evenList,c(0,t,0,0))
     }
     if(serverBusy){
       waitQueue<-Insert(waitQueue,c(type,arrive,exitQ,exitSys))
     }
     else{
       totIdleTime <- totIdleTime + arrive - lastService
       serverBusy <- 1
       type <- 1
       exitQ <- arrive
       exitSys <- exitQ + runif(1,7,11)
       evenList <- Insert(evenList,c(type,arrive,exitQ,exitSys))
     }
   }

   else {
     totQTime<- totQTime + exitQ - arrive
     totSysTime <- totSysTime + exitSys - arrive
     now <- exitSys
     b<-length(waitQueue) 
     if(b > 0){
      waitQueue1<-delete(waitQueue)  
      arrive<-as.numeric(waitQueue1[[1]][2])
      waitQueue<-Delete(waitQueue) 
      type<- 1
      exitQ<-now
      exitSys<-now + runif(1,7,11)
      evenList <- Insert(evenList,c(type,arrive,exitQ,exitSys))
     }
     else{
       serverBusy <- 0
       lastService <- now
     }
   }
   a<-length(evenList)
  }
  avgQTime <- round(totQTime/n,2);
  avgSysTime <- round(totSysTime/n,2)
  
  SS <- c(avgQTime,avgSysTime,totIdleTime)

  return (SS)
}


PoissonClientServer(5000,0.1)