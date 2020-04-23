> my_media<-function(vector){
suma<-0
for(i in 1:length(vector)){
suma<-vector[i] + suma
}
prom<-suma/length(vector)
par(mfrow=c(2,1))
plot(vector)
hist(vector)
return(prom)
}

> moda=function(mod){
#funcion que encuentra la moda de un vector x
m1=sort(table(mod),decreasing=T)
moda=names(m1[m1==m1[1]])
moda=as.numeric(moda)
return(moda)
}

> tablaq=function(dato){

freq.abs=table(dato)
freq.rel.perc=freq.abs*100/NROW(dato)
freq.abs.acum=cumsum(freq.abs)
freq.rel.perc.acum=cumsum(freq.rel.perc)
cat("\n","Tabla de frecuencias para datos discretos","\n")
tabla=cbind(freq.abs,freq.rel.perc,freq.abs.acum,freq.rel.perc.acum)
cat("\n","variable")
colnames(tabla)=c("frec.absoluta","frec.relativa","frec.abs.acum","frec.rel.acum")
print(tabla)
}

Cálculo de Ancho de clase:
AC=function(dato)
{n=NROW(dato)
rango=max(dato)-min(dato)
k=1+3.3*log10(n) # k: numero de intervalo
k=round(k) #n: numero de datos
Ancho=rango/k
list("Ancho de clase"=Ancho,"clases"=k)}

Limites de clase
#tic : ancho de clase

limites=function(dato,tic,clases)
{mini=min(dato) #ancho de clase
LInf=seq(mini,length=clases,by=tic)
LSup=seq(LInf[2],length=clases,by=tic)
marca=(LInf+LSup)/2
Intervalo=cbind(LInf,LSup,marca)
return(Intervalo)}

Transforma los datos en clases
clase=function(dato)
{ n=NROW(dato)
y=rep(0,n)
for(i in 1:n)
{ if(dato[i]<48.4)y[i]=1 else {;
if(dato[i]<66.8)y[i]=2 else {;
if(dato[i]<85.2)y[i]=3 else {;
if(dato[i]<103.6)y[i]=4 else {;
if(dato[i]<122.0)y[i]=5 else y[i]=6}}}}}
return(y)
}

Tabla de frecuencias de datos agrupados
tablaf=function(y)
{ n=NROW(y)
fabs=table(y)
frel=round((fabs/n)*100,2)
facum=cumsum(fabs)
Facum=round((facum/n)*100,2)
tabla=cbind(fabs,frel,facum,Facum)
print(tabla)
}

Para construir una tabla:
mydat<-matrix(c(0,0,1,3,2, 0,1,2,4,4, 1,5,1,3,3, 3,2,1,0,0),nrow=4,ncol=5,byrow=TRUE,dimnames=list(c("[7,9>","[9,11>","[11,14>","[14,18>"),c("[5,6>","[6,7>","[7,8>","[8,9>","[9,12>")))
