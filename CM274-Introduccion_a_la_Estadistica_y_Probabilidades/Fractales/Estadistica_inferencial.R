ESTADISTICA INFERENCIAL 

###

existen dos tipos de hipotesis ...

nula donde P1 = p1 = p3

alternativa p1 != p2 != p3

FUNCION CHISQ.TEST()

# contraste de hipotesis de proporciones

chisq.test(c(25,30,45))

# estadistica de contraste 

# grados de libertad

# probabildad de rechazar la hipotesis cuando es corecta

FRECUENCIA ABSOLUTA

Data(Cars93,package = "MASS")
# trae la data a nuestro espacio

attach(Cars93)
# hace visiible cada uno de sus componentes

table(Type) 
# variable type ... nombre de variable

# lo que hace es crear una tabla de los tipos de carro


FRECUENCIA RELATIVA
# proporcion entre uno y el total

prop.table()
# proporciones de la tabla

cambio <- table(Man.trans.avail)
# man ... ya existe en la base de datos

prop.table(cambio)
# nos regresa la proporcion de datos en esa tabla(que es parte del total)


CONTINGENCIA DOBLE ENTRADA

# usando dos variables de Cars

table(Man.trans.avail, AirBags)

# tambien se puede usar xtabs

xtabs(~Man.trans.avail + DrivveTrain)
# donde las filas seran los valores de Man ...
# y lasa columnas los valores de drivers

MARGIN TABLE

tc <- table(Man.trans.avail, DriveTrain)
# donde las filas seran los valores de Man ...
# y lasa columnas los valores de drivers
# Man y DriVers = marginales
# crea la tabla de Man y Drives

# nos da la suma de margenes (ej: drivers)

margin.table(tc,1)
# por cada fila nos da la suma de cada columna respecto a esa fila

margin.table(tc,2)
# lo inverso

margin.table(tc)
# nos da el numero total de casos (la suma)

addmargins()
# añade marginales

addmargins(tc,1)
# regresa tc y le añade el marginal suma con la suma de filas

addmargins(tc,2)
# similar pero inverso

addmargins(tc)
# nos da en ambos sitios

addmargins(prop.table(tc))
# nos da la proporcion de las variables y el total
# para el porcentaje es solo multiplicar por 100

round(x,2)
# reduce un numero x a tan solo 2 decimales


CUANTIL
# ordenada de menor a mayor, deja una proporcion

centiles o percentiles (lo divide en 100 grupos con proporciones iguales)

deciles(10 partes)

octiles(8 partes)

cuartiles(4 partes)

rivers # datos de rios

quantile(rivers) 
# min cuartil 1  cuartil 2 cuartil 3 max
perceptil     25    50           75
quantile(rivers,probs=c(0.22,0.46,0.67,0.83,0.92))
# nos da los percentiles de porcentaje de probs(probabilidades)

quantile(rivers, probs= seq(0.1,0.9,0.1))
10 - 20 - ... - 90 %


OPCION TYPE
# maneras de calcular los percentiles

quantile(rivers,probs=c(.23,.52.75),type=7)
# el tipo 7 es por defecto con porcentajes
# 23 52 y 75

# para el tipo 9 y para cada type distinto nos da valores ligeramente distintas

SUMMARY

vector:
summary(rivers)
# nos da cuarties min max mediana media 

base de datos:

ChickWeight
summary(ChickWeight)
# nos da informacion de todas sus variables

median(x) == quantile(vector,0.5)

mean(x)

tapply(X,INDEX,FUN)
#INDEX se refiere a los factores de agrupacon
#FUN indica que funcion queremos aplicar
#X variable a resumir


mean(rivers,trim=0,025)
# saca la meadia de rivers
#trim elimina el 2.5% mas bajo del vector y 2.5% mas altos
# nos devuelve la media recortada al 95%

trim va de 0 a 0.5

# para remover los NA

v<-c(4,5,NA,7,9,6,2) #vector concatenacion

mean(v) == NA

# se resuleve

mean(v,na.rm=TRUE)


DISPERSION

# se refiere homogeneo-heterogeneo

VAR
#vector

var(rivers)

#matriz
# matriz de varianza covarianza

data(iris)
iris$Species <- NULL # eliminamos
var(iris)
# lo que aparece en la diagonal es la varianza y lo demas son las covarianzzas

SD
#standar desviation
#vector

sd(rivers)

#matriz

x<-c(2,3,4,5,6,NA)
sd(x,na.rm=TRUE)

#cargar paquete e1071

Library(e1071)
skewness(rivers) # estima el sesgo de distrbucion
# simetrica , simetrica positiva, simetrica negativa
# cercano a cero, positivo, negativo
# . . . , de arriba abajo- izquierda derecha, inversa

KURTOSIS

kurtosis()

# si es positivo leptokurtica
# negativa mesokurtica

# 3 tipos

# el tipo 2 .... defecto SPSS y SAS
# el tipo 3 MINITAB




