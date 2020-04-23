#!/usr/bin/python
from math import fabs
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO GAUSS-SEIDEL
# Usar de ejemplo:
# A = [[4.,1.,1.,0.,1.],[-1.,-3.,1.,1.,0.],[2.,1.,5.,-1.,-1.],[-1.,-1.,-1.,4.,0.],[0.,2.,-1.,1.,4.]]
# b = [6,6,6,6,6]
def gaussSeidel(A, b, prec=1e-7):
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
      sumation1 = sum(A[i][j]*Xk1[j] for j in range(i))
      sumation2 = sum(A[i][j]*Xk1[j] for j in range(i+1, n))
      Xk1[i] = (1.0/A[i][i])*(b[i] - sumation1 - sumation2)
    print Xk ,
    print " Iteracion: " + str(itr)
    itr+=1
  return Xk1

# ------------------------------------------------------------
# matriz de Gauss Seidel
# A = (D + L) + U = F + U
# (F + U)x = b
# Fx = b - Ux
# x1 = C + T.x0
# T = -F-1.U, matriz de jacobi
# C = F-1.b
# F = D + L
def gaussSeidelMatrix(M):
  n = len(M)
  A = [row[:] for row in M]
  F = [[0. for j in range(n)] for i in range(n)]
  U = [[0. for j in range(n)] for i in range(n)]
  T = [[0. for j in range(n)] for i in range(n)]
  for i in range(n):
    for j in range(n):
      if i<j:
        U[i][j] = -1.*A[i][j]
      elif j<=i:
        F[i][j] = A[i][j]
  Finv = invMatrix(F)
  T = matrixMulti(Finv,U)
  return T

# ------------------------------------------------------------
