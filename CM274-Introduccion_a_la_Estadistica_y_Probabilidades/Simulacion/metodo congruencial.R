

a<-7; c<-3; m<-10
z<-matrix(0,10,10)
z[,1]<-seq(0,9)

for (j in 1:9) {
     for (i in 1:10) {
       z[i,j+1] <- (a*z[i,j] +c) %% m
     }
}  
z


##-------------------------------------
a<-137; c<-0; m<-256;  
x[1]<-87;  
for (j in 1:256){
    x[j+1] <- (a*x[j] +c) %% m
}  
u<- x/256  
plot(u,type="l")
plot(u[2:256],u[1:255],type="l") 

##-------------------------------------
a<-314159269; c<- 453806245; m<- 2^31-1  
x[1]<-87;  
for (j in 1:256){
    x[j+1] <- (a*x[j] +c) %% m
}
u<-x/m;  
plot(u,type="l")
plot(u[2:256],u[1:255],type="l")  


############################################
integral<- function(k){
## k:  Numero de iteraciones

s<- c(rep(0,each=k))

x<-1:k
for (i in 2:k) {
       s[i]<-s[i-1]+exp(runif(1,0,1));
}
int<-s/x
plot(x,int,type="l")
integral<-int[k]
integral
}



