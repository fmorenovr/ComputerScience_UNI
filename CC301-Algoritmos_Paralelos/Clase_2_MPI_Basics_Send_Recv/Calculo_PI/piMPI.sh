#!/bin/bash

##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################

#mpic++ piMPI.c -o pi

mpicc piMPI.c -o pi

echo "Ingrese el numero de procesadores a usar: "

read n

echo "Ingrese el numero de intervalos: "

read i

mpiexec -n $n ./pi $i
