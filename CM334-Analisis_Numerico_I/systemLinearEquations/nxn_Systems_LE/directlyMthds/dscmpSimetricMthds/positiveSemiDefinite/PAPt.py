#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 PAPt
# Usar de ejemplo: A=[[4,2,1],[2,5,3],[1,3,3]]
# PAPt = GGt
def PAPt(M):
  A = [row[:] for row in M]
  n = len(A)
  I = [[float(i == j) for j in range(n)] for i in range(n)]
  P = [[float(i == j) for j in range(n)] for i in range(n)]
  Pn = [[float(i == j) for j in range(n)] for i in range(n)]
  if not isSymmetricMatrix(A):
    exit('La matriz no es simetrica')
  if not isPosSemiDef(A):
    exit('La matriz no es semi definida positiva')
  maxpp = 0.0
  p=0
  for i in range(n):
    maxpp,p = maxDiagon(A,i)
    if maxpp>0:
      # interxambia las filas y columnas i e p
      Pn=exchangeRows(I,i,p)
      Pn=exchangeCols(I,i,p)
      P = matrixMulti(Pn,P)
      A=exchangeRows(A,i,p)
      A=exchangeCols(A,i,p)
      suma = A[i][i]
      for k in range(i):
        suma -= A[k][i]**2
      if suma < 0:
        exit('No es definida positiva')
      A[i][i] = sqrt(suma)
      for j in range(i+1, n):
        suma = A[i][j]
        for k in range(i):
          suma -= A[k][i]*A[k][j]
        A[i][j] = suma / A[i][i]
      
  for j in range(n):
    for i in range(n):
      if(i > j):
        A[i][j] = 0.0
  G=transMatrix(A)
  return P,G

# ------------------------------------------------------------
