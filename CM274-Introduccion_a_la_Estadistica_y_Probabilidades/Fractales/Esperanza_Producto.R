### PREGUNTA 2

Producto<-function(k){
  ##--k numero de interacciones
 
  u<-c(rep(1,each=k)) # inicimos con 1 para que no afecte el producto
  t<-c(rep(0,each=k)) # iniciamos en cero
  for(i in 2:k){ # prouctoria
    u[i]<-u[i-1]*runif(1,0,1) # ranom entre 0 y 1
    if(u[i]<exp(-3)){
     t[i]<-i;break
    }
  }
  maxn<-max(t)# maxaimo valor en t
  print(maxn) # imprime el maximo t
  E<-u[1:maxn]*1:maxn # calculo de la esperanza
  print(sum(E)) # imprime la esperanza
}

------------------------------------
##-- hallamos la esperanza de manera
##-- discreta para los valores hasta N
##-- que es maximo en el intervalo de 
##-- interacciones || E=sum(xi*Pi) ||

# si le damos la simulacion para 1000000
# no aparece el la quinta posicion y con valor de 4.879704 de esperanza



