#!/usr/bin/python
from math import fabs
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE JACOBI
# Usar de ejemplo:
# A = [[4.,1.,1.,0.,1.],[-1.,-3.,1.,1.,0.],[2.,1.,5.,-1.,-1.],[-1.,-1.,-1.,4.,0.],[0.,2.,-1.,1.,4.]]
# b = [6,6,6,6,6]
def jacobi(A, b, prec=1e-7):
  n = len(A)
  Xk = [0.0]*n
  sumation = 0.0
  for i in range(n):
    if A[i][i] == 0:
      exit('Los elementos A[i][i] deben ser diferentes de 0')
  Xk1 = [b[i]/float(A[i][i]) for i in range(n)]
  minus = lambda x, y: [x[i]-y[i] for i in range(n)]
  for j in range(n):
    dominancia = 0.0
    for i in range(j+1, n):
      if j != i:
        dominancia += fabs(A[i][j])
    if A[i][i] < dominancia:
      exit('La matriz no converge')
  itr=1
  print Xk ,
  print " Condiciones iniciales"
  while (normaInfVector(minus(Xk1,Xk)) / float(normaInfVector(Xk1))) > prec:
    Xk[:] = Xk1[:]
    for i in range(n):
      sumation = sum(A[i][j]*Xk1[j] if i!=j else 0 for j in range(n))
      Xk1[i] = (1.0/A[i][i])*(b[i] - sumation)
    print Xk ,
    print " Iteracion: " + str(itr)
    itr+=1
  return Xk1

# ------------------------------------------------------------
# matriz de Jacobi
# A = D + (L + U) = D + R
# (D + R)x = b
# Dx = b - Rx
# x1 = C + T.x0
# T = -D-1.R, matriz de jacobi
# C = D-1.b
# R = L + U
def jacobiMatrix(M):
  n = len(M)
  A = [row[:] for row in M]
  L = [[0. for j in range(n)] for i in range(n)]
  U = [[0. for j in range(n)] for i in range(n)]
  Dinv = [[0. for j in range(n)] for i in range(n)]
  R = [[0. for j in range(n)] for i in range(n)]
  T = [[0. for j in range(n)] for i in range(n)]
  for i in range(n):
    for j in range(n):
      if i==j:
        Dinv[i][j] = 1./A[i][j]
      elif i<j:
        U[i][j] = A[i][j]
      elif j<i:
        L[i][j] = A[i][j]
      R[i][j] = -1.*(L[i][j] + U[i][j])
  T = matrixMulti(Dinv,R)
  return T

# ------------------------------------------------------------
