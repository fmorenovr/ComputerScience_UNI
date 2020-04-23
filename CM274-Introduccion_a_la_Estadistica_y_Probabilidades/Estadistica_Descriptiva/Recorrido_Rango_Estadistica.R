# COEFICIENTE DE VARIACION:

# DATOS TIPO I:

CoeficienteVariacion.No_agrupados<-function(x){
	Me<-Media.No_agrupados(x)
	sd<-DesviacionStandar.No_agrupados(x)
	CV<-sd/abs(Me)
	CV<-round(CV,2)
	return (CV);
}


# ------------------------------------------

# DATOS TIPO II:

CoeficienteVariacion.Frecuencias<-function(x){
	Me<-Media.Frecuencias(x)
	sd<-DesviacionStandar.Frecuencias(x)
	CV<-sd/abs(Me)
	CV<-round(CV,2)
	return (CV);
}



# ------------------------------------------

# DATOS TIPO III:

CoeficienteVariacion.Intervalos<-function(x){
	Me<-Media.Intervalos(x)
	sd<-DesviacionStandar.Intervalos(x)
	CV<-sd/abs(Me)
	CV<-round(CV,2)
	return (CV);
}


CoeficienteVariacion.Intervalos2<-function(x,k){
	Me<-Media.Intervalos2(x,k)
	sd<-DesviacionStandar.Intervalos2(x,k)
	CV<-sd/abs(Me)
	CV<-round(CV,2)
	return (CV);
}

# --------------------------------


# RECORRIDO Y RANGO :

#DATOS TIPO I:

Recorrido_Rango.No_agrupados<-function(x){
	Re<-max(x) - min(x)
	Ran<-c(min(x),max(x))
	RR<-matrix(c(Re,Ran[1],Ran[2]),byrow=T,nrow=1)
	colnames(RR)<-c("Recorrido","[Rango Inferior","Rango Superior]")
	rownames(RR)<-c("Valores")
	return (RR)
}

# ------------------------------------------

# DATOS TIPO II:

Recorrido_Rango.Frecuencias<-function(x){
	Tabla<-Tabla.Frecuencias(x)
	Re<-max(Tabla[[1]]) - min(Tabla[[1]])
	Ran<-c(min(Tabla[[1]]),max(Tabla[[1]]))
	RR<-matrix(c(Re,Ran[1],Ran[2]),byrow=T,nrow=1)
	colnames(RR)<-c("Recorrido","[Rango Inferior","Rango Superior]")
	rownames(RR)<-c("Valores")
	return (RR);
}


# ------------------------------------------

# DATOS TIPO III:

Recorrido_Rango.Intervalos<-function(x){
	Tabla<-Tabla.Intervalos(x)
	Re<-max(Tabla[[2]]) - min(Tabla[[1]])
	Ran<-c(min(Tabla[[1]]),max(Tabla[[2]]))
	RR<-matrix(c(Re,Ran[1],Ran[2]),byrow=T,nrow=1)
	colnames(RR)<-c("Recorrido","[Rango Inferior","Rango Superior]")
	rownames(RR)<-c("Valores")
	return (RR);
}


Recorrido_Rango.Intervalos2<-function(x,k){
	Tabla<-Tabla.Intervalos2(x,k)
	Re<-max(Tabla[[2]]) - min(Tabla[[1]])
	Ran<-c(min(Tabla[[1]]),max(Tabla[[2]]))
	RR<-matrix(c(Re,Ran[1],Ran[2]),byrow=T,nrow=1)
	colnames(RR)<-c("Recorrido","[Rango Inferior","Rango Superior]")
	rownames(RR)<-c("Valores")
	return (RR);
}