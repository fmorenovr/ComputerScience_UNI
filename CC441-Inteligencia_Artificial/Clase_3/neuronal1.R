#!/usr/bin/Rscript

# Ejemplo de interfaz grafica de redes neuronales 
library(neural); 
# Entreno una red de base radial 
neurons <- 16;
data <- rbftrain(x, neurons, y, sigma=NaN);
rbf(x, data$weigth, data$dist, data$neurons, data$sigma);
# Genero un conjunto de datos artificial 
x <- matrix(c(1,1,0,0,1,0,1,0), 4, 2);
y <- matrix(c(0,1,1,0), 4, 1);
# Entreno un perceptron multicapa 
neurons <- 4;
data <- mlptrain(x, neurons, y, it=1000); 
mlp(x, data$weigth, data$dist, data$neurons, data$actfns);
