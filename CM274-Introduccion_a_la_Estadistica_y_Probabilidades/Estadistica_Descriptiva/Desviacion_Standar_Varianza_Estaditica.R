# Desviacion Standar y Varianza


#DATOS TIPO I:

Varianza.No_agrupados<-function(x){

	Me<-Media.No_agrupados(x)
	N<- length(x)
	var <- sum((x-Me)^2)
	var <- var/N
	var<-round(var,3)
	return (var);
}

DesviacionStandar.No_agrupados<-function(x){
	sd <- Varianza.No_agrupados(x)
	sd <- sqrt(sd)
	sd<-round(sd,3)
	return (sd);
}

# --------------------------------------------


#DATOS TIPO II:

Varianza.Frecuencias<-function(x){

	Me<-Media.Frecuencias(x)
	Tabla<-Tabla.Frecuencias(x)
	N<- sum(Tabla[[2]])
	var <-  sum(Tabla[[2]]*(Tabla[[1]]-Me)^2)
	var <- var/N
	var<-round(var,3)
	return (var);
}

DesviacionStandar.Frecuencias<-function(x){
	sd <- Varianza.Frecuencias(x)
	sd <- sqrt(sd)
	sd<-round(sd,3)
	return (sd);
}

# --------------------------------------


# DATOS TIPO III:

Varianza.Intervalos<-function(x){

	Me<-Media.Intervalos(x)
	Tabla<-Tabla.Intervalos(x)
	N<- sum(Tabla[[4]])
	var <- sum(Tabla[[4]]*(Tabla[[3]]-Me)^2)
	var <- var/N
	var<-round(var,3)
	return (var);
}

DesviacionStandar.Intervalos<-function(x){
	sd <- Varianza.Intervalos(x)
	sd <- sqrt(sd)
	sd<-round(sd,3)
	return (sd);
}

Varianza.Intervalos2<-function(x,k){

	Me<-Media.Intervalos2(x,k)
	Tabla<-Tabla.Intervalos2(x,k)
	N<- sum(Tabla[[4]])
	var <- sum(Tabla[[4]]*(Tabla[[3]]-Me)^2)
	var <- var/N
	var<-round(var,3)
	return (var);
}

DesviacionStandar.Intervalos2<-function(x,k){
	sd <- Varianza.Intervalos2(x,k)
	sd <- sqrt(sd)
	sd<-round(sd,3)
	return (sd);
}

