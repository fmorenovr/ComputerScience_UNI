
### Ejemplo 4.a

# de mayor a menor  --- la forma optima

x<-c(1,2,3,4)
p<-c(0.20,0.15,0.25,0.40)

met.transf.inv<-function(x,p){
p<-sort(p,decreasing=TRUE, index.return=TRUE)
u<-runif(1,0,1);i<-1
while (u>sum(p$x[1:i])) {
       i<-i+1
}
print(p$ix[i])
}

# de menor a mayor 

met.transf.inv<-function(x,p){
p<-sort(p,decreasing=FALSE, index.return=TRUE)
u<-runif(1,0,1);i<-1
while (u>sum(p$x[1:i])) {
       i<-i+1
}
print(p$ix[i])
}
