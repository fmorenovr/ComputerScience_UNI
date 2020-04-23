# MOMENTOS STANDAR:

# DATOS TIPO I:

MomentoStandar.No_agrupados<-function(x,k){
	MO <- Momento_Media.No_agrupados(x,k)
	sd <- DesviacionStandar.No_agrupados(x)
	sd<-sd^k
	MOSD <- MO/sd
	return (round(MOSD,4));
}

# --------------------------------------

# DATOS TIPO II:

MomentoStandar.Frecuencias<-function(x,k){
	MO <- Momento_Media.Frecuencias(x,k)
	sd <- DesviacionStandar.Frecuencias(x)
	sd<-sd^k
	MOSD <- MO/sd
	return (round(MOSD,4));
}

# --------------------------------------

# DATOS TIPO III:

MomentoStandar.Intervalos<-function(x,k){
	MO <- Momento_Media.Intervalos(x,k)
	sd <- DesviacionStandar.Intervalos(x)
	sd<-sd^k
	MOSD <- MO/sd
	return (round(MOSD,4));
}

MomentoStandar.Intervalos2<-function(x,m,k){
	MO <- Momento_Media.Intervalos(x,m,k)
	sd <- DesviacionStandar.Intervalos(x,m)
	sd<-sd^k
	MOSD <- MO/sd
	return (round(MOSD,4));
}

# --------------------------------------

# CON RESPECTO A LOS MOMENTOS STANDARES, SE TIENE:

# SON LLAMADOS ASI PORQUE SON MOMENTOS CENTRADOS RESPECTO DE LA MEDIA

# Y ADEMAS SE DEFINE COMO U(k) / SD(k)

# EL K-ESIMO MOMENTO RESPECTO A LA MEDIA U ENTRE

# LA DESVIACION STANDAR A LA "K"

# ----------------------------------------

# ENTONCES TENEMOS :

#SI K = 0:

# NOS DEVUELVE "1", PERO ES UN VALOR QUE NO SE TOMA EN CUENTA

# --------------------------------------------------

#SI K = 1:

# Nos devuelve "0", porque el primer momento es como
# calcular la suma de los elementos mismos
# Porque Sum(X[i])/length(x) - Me = 0

# ---------------------------------------------------

#SI K = 2:

# Nos devuelve "1", Porque el segundo momento es como
#calcular la suma de los elementos al cuadrado
# porque sum(x[i]- Me)^2 / length(x) = VARIANZA = sd^2
# Y SD^2 / SD^2 = 1

# --------------------------------------------------

#SI K = 3:

# NOS DEVUELVE EL COEFICIENTE DE ASIMETRIA,
# EL CUAL NOS PERMITE CONOCER:
# EL GRADO DE SIMETRIA O ASIMETRIA DE LA DISTRIBUCION 
# DE TAL FORMA QUE SI :

# "As" : COEFICIENTE DE ASIMETRIA

# SI As > 0 :ASIMETRICA POSITIVA ( TIENDE INCLINARSE A LA DERECHA ... MEDIA < MEDIANA < MODA)
# SI As = 0 : MEDIA = MODA = MEDIANA (QUIZA SEA SIMETRICA)
# SI As < 0 :ASIMETRICA NEGATIVA ( TIENDE INCLINARSE A LA IZQUIERDA ... MODA < MEDIANA < MEDIA)

# NOTA:
# SI LA DISTRIBUCION ES SIMETRICA ==> As = 0,
# PERO LO CONTRARIO NO SIEMPRE SE CUMPLE.

# ---------------------------------------------------

#SI K = 4:

# NOS DEVUELVE EL COEFICIENTE DE KURTOSIS,
# EL CUAL NOS PERMITE CONOCER:
# EL GRADO DE CONCENTRACION DE DATOS CERCANO A LA MEDIA
# Y LOS DATOS NO TAN CERCANOS A LA MEDIA. 
# DE TAL FORMA QUE SI :

# "Kur" : COEFICIENTE DE ASIMETRIA

# SI Kur > 3 :LEPTOCURTICA
# SI Kur = 3 :PLATICURTICA
# SI Kur < 3 :MESOCURTICA

# CUANDO SE TOMA LA KURTOSIS RESPECTO DE LA DISTRIBUCION NORMAL
# A KUR SE LE RESTA 3 
# ES DECIR QUE Kur - 3 = Kur1
# Y TOMAMOS LOS MISMOS CASOS EXCEPTUANDO POR:

# SI Kur1 > 0 :LEPTOCURTICA
# SI Kur1 = 0 :PLATICURTICA
# SI Kur1 < 0 :MESOCURTICA


# --------------------------------------------------

# NOTA FINAL: PARA MEJOR ENTENDIMIENTO DE LOS COEFICIENTE 
# DE ASIMETRIA Y KURTOSIS VEA LAS GRAFICAS ADJUNTAS...