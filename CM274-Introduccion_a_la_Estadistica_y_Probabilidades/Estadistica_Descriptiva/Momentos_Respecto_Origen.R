# MOMENTOS:

# DATOS TIPOS I :

Momento_Origen.No_agrupados<-function(x,k){

	MO<- sum(x^k)
	N <- length(x)
	MO <- MO/N
	return (round(MO,2));
}


# -----------------------------------------------

# DATOS TIPO II:

Momento_Origen.Frecuencias<-function(x,k){

	Tabla<-Tabla.Frecuencias(x)
	MO<- sum(Tabla[[2]]*Tabla[[1]]^k)
	N <- sum(Tabla[[2]])
	MO <- MO/N
	return (round(MO,2));
}

# -----------------------------------------------

# DATOS TIPO III:

Momento_Origen.Intervalos<-function(x,k){

	Tabla<-Tabla.Intervalos(x)
	MO<- sum(Tabla[[4]]*Tabla[[3]]^k)
	N <- sum(Tabla[[4]])
	MO <- MO/N
	return (round(MO,2));
}

Momento_Origen.Intervalos2<-function(x,m,k){

	Tabla<-Tabla.Intervalos2(x,m)
	MO<- sum(Tabla[[4]]*Tabla[[3]]^k)
	N <- sum(Tabla[[4]])
	MO <- MO/N
	return (round(MO,2));
}

# LOS MOMENTOS RESPECTO DEL ORIGEN

# -----------------------------------