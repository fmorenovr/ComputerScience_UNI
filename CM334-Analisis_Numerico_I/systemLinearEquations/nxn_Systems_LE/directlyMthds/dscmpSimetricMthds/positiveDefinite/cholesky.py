#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE CHOLESKY
# Usar de ejemplo: A=[[5,1,-2,0],[1,2,0,0],[-2,0,4,1],[0,0,1,3]]
# A = GGt
def cholesky(M):
  A = [row[:] for row in M]
  if not isSymmetricMatrix(A):
    exit('La matriz no es simetrica')
  n = len(A)
  for i in range(n):
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
  G = transMatrix(A)
  return G

# ------------------------------------------------------------
