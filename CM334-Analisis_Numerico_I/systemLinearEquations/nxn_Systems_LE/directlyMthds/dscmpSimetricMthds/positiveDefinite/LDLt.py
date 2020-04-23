#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO LDLt
# Usar de ejemplo: A=[[4, 12, -16], [12, 37, -43], [-16, -43, 98]]
# A = LDLt
def LDLt(M):
  A = [row[:] for row in M]
  if not isSymmetricMatrix(A):
    exit('La matriz no es simetrica')
  n = len(A)
  D = [[0.0]*n for j in range(n)]
  for i in range(n):
    suma = A[i][i]
    for k in range(i):
      suma -= (A[k][i]**2)*D[k][k]
    if suma == 0:
      exit('No es definida positiva')	
    D[i][i] = suma
    for j in range(i+1, n):
      suma = A[i][j]
      for k in range(i):
        suma -= A[k][i]*A[k][j]*D[k][k]
      A[i][j] = suma / D[i][i]
  for j in range(n):
    for i in range(n):
      if(i==j):
        A[i][j] = 1.0
      elif(i > j):
        A[i][j] = 0.0
  L = transMatrix(A)
  return L,D

# ------------------------------------------------------------
