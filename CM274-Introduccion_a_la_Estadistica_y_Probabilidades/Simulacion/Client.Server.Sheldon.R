insert <- function(lst, obj) {
    lst[[length(lst)+1]] <- obj
    return(lst)
}


#Funcion para ejecutar "n" veces (en este caso n=100)
Ejecucion<-function(n){
i<-0

T<-list()

while(i<n){

S<-servidor.cliente(20) #llamamos a la funcion servidor.cliente con T=20
T<-insert(T,S)
i<-i+1
}
return(T) #mostramos los tiempos (de los que llegaron)

}

##funcion proporcionada por el profesor

servidor.cliente <-function(T) {
##  T      : Número de Requerimientos
##  D.A    : Vector de permanencias en el sistema  
##  lambda : parAmetro de proceso Poisson (=0.1)
      
lambda<-0.1;
t<- 0; N.A<- 0;N.D<- 0;ES<- 0;      ## Inicializacion
T0<- (-1/lambda)*(log(runif(1,0,1)))   
tA<-T0; tD<-Inf; A<-as.vector(NULL); D<-as.vector(NULL)           
while  (t<=T) {
        if ((tA <= tD)&&(tA<=T)) {  #if3
           t<-tA            
           N.A<-N.A+1
           ES<-ES+1
           Tt<- t + (-1/lambda)*(log(runif(1,0,1))); tA<-Tt;   
           if (ES==1){
              Y<-7+((11-7)*runif(1,0,1))
              tD<-t+Y
           }
           A[N.A]<-t 
           }                         #if3
       else {              
           if ((tD<tA)&&(tD<=T)){ 
               t<-tD             
               ES<- ES-1
               N.D<- N.D+1
               if (ES==0)
               tD<- Inf
               if(ES>0){
                 Y<- (7+(11-7)*runif(1,0,1))
                 tD<- t+Y
               }
               D[N.D]<-t
           }
           else { 
              if ((min(tA,tD)>T)&&(ES>0)) {
                 t<-tD      
                 ES<-ES-1
                 N.D<-N.D+1         
                 D[N.D]<-t      
                 while (ES>0){
                    Y<-7+((11-7)*runif(1,0,1))
                    tD<-t+Y
                    t<-tD
                    ES<-ES-1
                    N.D<-N.D+1
                    D[N.D]<-t   
                 }
               }
               else {
                 if ((min(tA,tD)>T)&&(ES==0)) {       
                    D<-0
                    A<-0
                    t<-min(tA,tD);  ## asignar este valor para 't' para salir del bucle WHILE
                  }
               } 
             } 
            }

}# While


return(D-A)
}  

MediaPonderada<-function(n){

Pesos<-vector() # pesos
A<-vector() # suma de cada objeto dentro de la lista

for(i in 1:length(n)){
   l<-length(n[[i]])
   M<-mean(n[[i]])
   A<-insert(A,M) # inserto la media interna de los datos dentro de n
   Pesos<-insert(Pesos,l) # inserto los respectivos pesos de casa simulacion
}

MediaPonderada<-sum(A*Pesos)/sum(Pesos)

return (MediaPonderada)

}

DesviacionStandar<-function(n){

A<-vector() # suma de cada objeto dentro de la lista

for(i in 1:length(n)){
   M<-mean(n[[i]])
   A<-insert(A,M) # inserto la media interna de los datos dentro de n
}

 SD<-sd(A)
 return (SD)

}

Coeficiente.Variacion<-function(n){

   Media<-MediaPonderada(n)
   SD<-DesviacionStandar(n)
 
   Coef.Var<-SD/Media

   return (Coef.Var)

}

Graficar<-function(n){

  A<-vector() # suma de cada objeto dentro de la lista

  for(i in 1:length(n)){
    M<-mean(n[[i]])
    A<-insert(A,M) # inserto la media interna de los datos dentro de n
  }

  hist(A)
}
