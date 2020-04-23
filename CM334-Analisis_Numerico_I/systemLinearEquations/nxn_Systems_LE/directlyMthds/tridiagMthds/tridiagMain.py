#!usr/bin/env python
from auxFuncSLE import  *
from croutTridiag import *
from householderTridiag import *
from thomas import *

# resolvamos el sistema Ax = b

A = [[4.75,2.25,-0.25],[2.25,4.75,1.25],[-0.25,1.25,4.75]]
b = [1.5, 2.5 , 1.0]
print "\nMatriz del sistema"
printMatrix(A)
print "\nVector del sistema"
print b

# tridiagonalizamos
# householder
print "\nMetodo de householder"
Q,T = householderTridiag(A)
print "\nMatrix tridiagonal"
printMatrix(T)
Qb = multiMatrixVector(Q,b)
print "\nNuevo vector despues de tridiagonalizar"
print Qb

print "\n\tMetodos de solucion"
print "\nMetodo de Thomas"
X = thomas(T,b)
print "\nSolucion con Metodo de Thomas"
print X
# crout tridiagonal
print "\nMetodo de Crout para tridiagonales"
L,U = croutTridiag(T)
print "\nMatrix L"
printMatrix(L)
print "\nMatrix U"
printMatrix(U)
print "\nSolucion con Metodo de Crout para tridiagonalies"
X = solCroutTridiag(L,U,b)
print X
print
