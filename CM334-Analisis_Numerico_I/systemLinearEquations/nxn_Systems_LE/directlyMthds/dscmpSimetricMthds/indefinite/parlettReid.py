#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE PARLETT-REID
# Usar de ejemplo: A=[[0,1,2,3],[1,2,2,2],[2,2,3,3],[3,2,3,4]]
# PAPt = LTLt
def parlettReid(A):
  An = [row[:] for row in A]
  if not isSymmetricMatrix(A):
    exit('La matriz no es simetrica')
  n = len(A)
  # crea matrices identidad
  P = [[float(i == j) for j in range(n)] for i in range(n)]
  I = [[float(i == j) for j in range(n)] for i in range(n)]
  Mn = [[float(i == j) for j in range(n)] for i in range(n)]
  MPn = [[float(i == j) for j in range(n)] for i in range(n)]
  for i in range(n-2):
    v = [0.]*n
    e = [row for row in P[i+1]]
    row_maxColum = maxColumDiag(An, i)
    if row_maxColum!=i:
      Pn = exchangeRows(I, row_maxColum, i+1)
      An = matrixMulti(Pn,An)
      maxVal = An[i+1][i]
      for j in range(i+2,n):
        v[j] = An[j][i]/maxVal
      Mn = [ [float(k==m) - e[k] * v[m] for k in xrange(n)] for m in xrange(n) ]
    else: # significa que todos son 0
      Pn = [row[:] for row in I]
      Mn = Pn
    # actualizamos el valor de la matriz An = MnPnAPnMn
    PMn = matrixMulti(Mn,Pn)
    PMn = transMatrix(PMn)
    An = matrixMulti(Mn,An)
    An = matrixMulti(An,PMn)
    # actualizamos el valor de la matriz MP
    MPn = matrixMulti(Pn,MPn)
    MPn = matrixMulti(Mn,MPn)
    # actualizamos el valor de la matriz P
    P = matrixMulti(Pn,P)
  # matriz Tridiagonal
  T = An
  # matriz de permutacion
  Pt = transMatrix(P)
  # matriz triangular inferior
  L = matrixMulti(MPn,Pt)
  L = invMatrix(L)
  return P, L, T

# ------------------------------------------------------------
