#!usr/bin/env python
from auxFuncSLE import *
from croutL1U import *
from croutLU1 import *
from doolittle import *
from LDMt import *

pivoteo = 2

A = [[1,1,0,3],[2,2,-1,1],[3,-1,-4,2],[-1,2,3,-1]]

print "\nMatriz a descomponer medio LU"
printMatrix(A)

# crout L1U
print "\nMetodo Crout L1U"
P, L, U = croutL1U(A,pivoteo)
print "\nMatrix L1"
printMatrix(L)
print "\nMatrix U"
printMatrix(U)
# crout L1U
print "\nMetodo Crout LU1"
P, L, U = croutLU1(A,pivoteo)
print "\nMatrix L"
printMatrix(L)
print "\nMatrix U"
printMatrix(U)
# doolittle
print "\nMetodo Doolittle"
P, L, U = doolittle(A,pivoteo)
print "\nMatrix L"
printMatrix(L)
print "\nMatrix U"
printMatrix(U)
# crout L1U
print "\nMetodo LDMt"
P, L, D, M = LDMt(A,pivoteo)
print "\nMatrix L"
printMatrix(L)
print "\nMatrix D"
printMatrix(D)
print "\nMatrix Mt"
printMatrix(transMatrix(M))
print
