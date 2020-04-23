#!/usr/bin/python
from math import fabs
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.3 METODO SOR
  """ Metodo SOR, calcula la solucion de un sistema de ecuaciones
    usando el parametro de relajacion w, que necesariamente varia
    de <0, 2> solo en el caso que la matriz converja.
  """
# Usar de ejemplo:
# A = [[4,3,0],[3,4,-1],[0,-1,4]]
# b = [24,30,-24]
def sor(A, b, w=1.5, prec=1e-7):
  n = len(A)
  Xk = [0.0]*n
  sumation = 0.0
	#Garantizar que los elementos de la diagonal principal sean distintos de cero
  for i in range(n):
    if A[i][i] == 0:
      exit('Los elementos A[i][i] deben ser diferentes de 0')
  Xk1 = [b[i]/float(A[i][i]) for i in range(n)]
  minus = lambda x, y: [x[i]-y[i] for i in range(n)]
  for j in range(n):
    dominancia = 0.0
    for i in range(n):
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
      Xk1[i] = (float(w)/A[i][i])*(b[i] - sumation1 - sumation2) + (1-w)*Xk[i]
    print Xk ,
    print " Iteracion: " + str(itr)
    itr+=1
  return Xk1

# ------------------------------------------------------------
# matriz de sor
# A = D + L + U
# w.Ax = w.b
# w.A = (D + w.L) + ( w.U + (w-1).D )
# (D + w.L)x = w.b - ( w.U + (w-1).D )x
# x1 = C + T.x0
# T = -w.R-1.U + (1 - w).R-1.D
# C = w.R-1.b
# R = (D + w.L)
def sorMatrix(M,w=1):
  n = len(M)
  w1 = -1.*w
  A = [row[:] for row in M]
  L = [[0. for j in range(n)] for i in range(n)]
  U = [[0. for j in range(n)] for i in range(n)]
  D = [[0. for j in range(n)] for i in range(n)]
  R = [[0. for j in range(n)] for i in range(n)]
  T = [[0. for j in range(n)] for i in range(n)]
  T1 = [[0. for j in range(n)] for i in range(n)]
  for i in range(n):
    for j in range(n):
      if i==j:
        D[i][j] = A[i][j]
      elif i<j:
        U[i][j] = A[i][j]
      elif j<i:
        L[i][j] = A[i][j]
      R[i][j] = (D[i][j] + w*L[i][j])
      T1[i][j] = w1*U[i][j] + (1 + w1)*D[i][j]
  Rinv = invMatrix(R)
  T = matrixMulti(Rinv,T1)
  return T

# ------------------------------------------------------------
