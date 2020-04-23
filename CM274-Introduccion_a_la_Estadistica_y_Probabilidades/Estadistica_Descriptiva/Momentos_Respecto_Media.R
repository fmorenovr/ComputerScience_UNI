# MOMENTOS RESPECTO DE LA MEDIA:

# DATOS TIPOS I :

Momento_Media.No_agrupados<-function(x,k){

	Me <- Media.No_agrupados(x)
	MO<- sum((x-Me)^k)
	N <- length(x)
	MO <- MO/N
	return (round(MO,2));
}


# -----------------------------------------------

# DATOS TIPO II:

Momento_Media.Frecuencias<-function(x,k){

	Tabla<-Tabla.Frecuencias(x)
	Me <- Media.Frecuencias(x)
	MO<- sum(Tabla[[2]]*(Tabla[[1]]-Me)^k)
	N <- sum(Tabla[[2]])
	MO <- MO/N
	return (round(MO,2));
}

# -----------------------------------------------

# DATOS TIPO III:

Momento_Media.Intervalos<-function(x,k){

	Tabla<-Tabla.Intervalos(x)
	Me<- Media.Intervalos(x)
	MO<- sum(Tabla[[4]]*(Tabla[[3]]-Me)^k)
	N <- sum(Tabla[[4]])
	MO <- MO/N
	return (round(MO,2));
}

Momento_Media.Intervalos2<-function(x,m,k){

	Tabla<-Tabla.Intervalos2(x,m)
	Me<-Media.Intervalos2(x,m)
	MO<- sum(Tabla[[4]]*(Tabla[[3]]-Me)^k)
	N <- sum(Tabla[[4]])
	MO <- MO/N
	return (round(MO,2));
}

# -----------------------------------