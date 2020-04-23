#!/bin/bash

##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################


mpicc matrixMulvectorMPI.c -o mult -lm

echo "Ingrese el numero de procesadores a usar: "

read n

echo "Ingrese las dimesiones de la matriz: "

read i
read j

mpiexec -n $n ./mult $i $j
