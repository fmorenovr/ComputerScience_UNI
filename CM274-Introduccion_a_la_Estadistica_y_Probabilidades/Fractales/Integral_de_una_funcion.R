##-- PREGUNTA 1 

Integral<-function(k){
  ##--k numero de interacciones 

  s<-c(rep(0,each=k)) # le doy la iniciaion para la suma
  t<-1:k

  for(i in 2:k){
    x<-runif(1,0,1)

    s[i]<-s[i-1]+sqrt((1-x^2)^3);
  }

  int<-s/t
  plot(t,int,type="s")

  Integral<-int[k]
  Integral
}

##-- int seria la aproximacion de la 
##-- integral y mientras mas alto sea k,
##-- mejor sera la aproximación, se puede apreciar la grafica 
##-- donde nos muestra el grafico con barrs(para observar el area)

