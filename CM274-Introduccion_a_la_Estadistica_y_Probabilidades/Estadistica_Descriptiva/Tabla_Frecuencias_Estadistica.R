# TABLA DE FRECUENCIAS:

# Para datos Tipo I:

# No es necesario

# Para Datos Tipo II : Muchos datos y pocos valores

Tabla.Frecuencias<-function(x){

    insertar<-function(x,obj){
        len<-length(x)
        x[len+1]<-obj
        return (x)
    }

    x<-sort(x)
    len <- length(x)
    primer<-x[1]
    Xi<-NULL
    Xi<-insertar(Xi,primer)
    ni<-NULL
    cont<-0

# Para calcular los diferentes datos
# y a la vez cuenta el numero de repeticiones de cada uno

    for(i in 1:len){
      if(primer != x[i]){
         ni<-insertar(ni,cont)
         primer<-x[i]
         Xi<-insertar(Xi,primer)
         cont<-1
         if(i == len){
            ni<-insertar(ni,cont)
         }
      }
      else{
         cont<-cont+1
         if(i == len){
            ni<-insertar(ni,cont)
         }
      }
    }

    Ni<-1:length(ni) # frecuencias absolutas
    Ni<-cumsum(ni) # frecuencias absolutas acumuladas

    tabla<-data.frame(Xi,ni,Ni)

    return (tabla)
}


# -----------------------------------------------------------------

# Para Datos Tipo III: Muchos Datos y Muchos Valores

# A) Los intervalos se determinan con el metodo de Struges


Tabla.Intervalos<-function(x){ 
# primero se ordena de menor a mayor
   y<-sort(x)
# segundo el rango de clase
   c<-max(y)-min(y) # Rango
# tercero determinamos el numero de intervalos
# primer metodo para el numero de clases
   len<-length(y)
#nc<-trunc(sqrt(len)) +1 # numero de intervalos (clases) se redondea al mayor entero
# segundo metodo para el numero de clases Metodo de Struges
   nc<-trunc(1 + 3.33*log10(len)) +1 
# cuarto determinamos la amplitud de clase
   Amp<-c/nc #  Amplitud de clase
# quinto determinamos los limites superiores eh inferiores
# sexto determinamos los limites reales
# septimo determinamos las marcas de clase
# octavo frecuencias de clase
# noveno frecuencias relativas
   ni<- 1:nc  # Frecuencia --- Tamaño de cada intervalo(numero de datos reales que tiene)
   mi<-1:nc   # marca de clase
   L.inf<-1:nc  # limites inferiores de clase
   L.sup<-1:nc  # limites superiores de las clases
   L.inf.real<-1:nc   # limites inferiores reales
   L.sup.real<-1:nc   # limites superiores reales

   for(i in 1:(nc-1)) {
      L.inf[i]<- (min(y)+Amp*(i-1))
      L.sup[i]<- (min(y)+Amp*i)
      ni[i] <- length(y[y>=L.inf[i] & y<L.sup[i]])
      mi[i]<-(L.inf[i]+L.sup[i])/2
      L.inf.real[i]<-L.inf[i]-0.5
      L.sup.real[i]<-L.sup[i]-0.5
   }
   L.inf[nc]<- (min(y)+Amp*(nc-1))
   L.sup[nc]<- (min(y)+Amp*nc)
   ni[nc] <- length(y[y>=L.inf[nc] & y<=L.sup[nc]])
   mi[nc]<-(L.inf[nc]+L.sup[nc])/2
   fi<- ni/sum(ni) # frecuencia relativa
   Ni <- cumsum(ni) # frecuencia absoluta acumulada
   Fi <- Ni/sum(ni) # frecuencia relativa acumulada

   tabla<- data.frame(L.inf, L.sup,mi,ni,Ni,fi,Fi)
   #cat("<Intervalos> | Marca | Frec. rel. | Frec. rel. Ac. | Frec. abs. | Frec. abs. Ac.\n")
   #for(i in 1:(nc)) {
   #  cat("<",L.inf[i],"-",L.sup[i],"> |\t",mi[i]," |\t",ni[i]," |\t",Ni[i]," |\t",fi[i]," |\t",Fi[i],"\n")
   
   #}
   
  return (round(tabla,2))
}

# -----------------------------------------------------------------


# B) Tu escocges el numero de intervalos


Tabla.Intervalos2<- function(x,k){ 

# x: vector de datos 
# k: numero de intervalos


   c<-(max(x)-min(x))/k   #c: longitud de intervalo de clase
   ni<- 1:k  # frecuencia -- Tamaño de cada intervalo(numero de datos reales que tiene)
   mi<-1:k   # marca de clase
   L.inf<-1:k  # limites inferiores de clase
   L.sup<-1:k  # limites superiores de las clases
   L.inf.real<-1:k   # limites inferiores reales
   L.sup.real<-1:k   # limites superiores reales

   for(i in 1:(k-1)) {
      L.inf[i]<- (min(x)+c*(i-1))
      L.sup[i]<- (min(x)+c*i)
      ni[i] <- length(x[x>=L.inf[i] & x<L.sup[i]])
      mi[i]<-(L.inf[i]+L.sup[i])/2
      L.inf.real[i]<-L.inf[i]-0.5
      L.sup.real[i]<-L.sup[i]-0.5
   }
   L.inf[k]<- (min(x)+c*(k-1))
   L.sup[k]<- (min(x)+c*k)
   mi[k]<-(L.inf[k]+L.sup[k])/2
   ni[k] <- length(x[x>=L.inf[k]& x<=L.sup[k]])
   fi<- ni/sum(ni) # frecuencia relativa
   Ni <- cumsum(ni) # frecuencia absoluta acumulada
   Fi <- Ni/sum(ni) # frecuencia relativa acumulada
   tabla<- data.frame(L.inf, L.sup,mi,ni,Ni,fi,Fi)
   
return(round(tabla,2))

}
