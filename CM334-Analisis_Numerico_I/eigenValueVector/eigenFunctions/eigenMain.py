#!/usr/bin/env python
from math import *
from auxFuncEigen import *
from jacobi import *
from symmetricPower import *
from inversePower import *
from rayleigh import *
from gerschgorinSturm import *
from qr import *
from power import *

A = [[4,-1,0],
     [-1,3,-1],
     [0,-1,2]]

x0 = [1,1,1]
n = len(A)
lamb = 1
# metodo jacobi
print "\nMetodo de Jacobi"
vectors,Matrix = jacobiEigen(A)
print vectors
printMatrix(Matrix)
# power
print "\nMetodo de Potencia"
vector, value = power(A,x0,printText = 0)
print vector
print value
# symmetric power
print "\nMetodo de Potencia Simetrica"
vector1, value1 = symmetricPower(A,x0,printText = 0)
print vector1
print value1
# inverse power
print "\nMetodo de Potencia Inversa"
vector2, value2 = inversePower(A,x0,printText = 0)
print vector2
print value2
print "\nMetodo potencia inversa, para el maximo autovalor"
maxeigen = maxEigenInvPower(A,x0)
print maxeigen
# rayleigh
print "\nMetodo de Rayleigh"
value3, vector3 = rayleigh(A,lamb)
print vector3
print value3
# gerschgorin sturm
print "\nMetodo de Gerschgorin Sturm"
values = gerschgorinSturmEigen(A,n, printText = 0)
print values
# QR algorithm
print "\nMetodo QR"
values1 = qrEigen(A)
print values1
print
